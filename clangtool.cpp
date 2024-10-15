//===----------------------------------------------------------------------===//
//
//  This file implements a clang tool that runs clang based on the info
//  stored in a compilation database.
//
//  This tool uses the Clang Tooling infrastructure, see
//    http://clang.llvm.org/docs/HowToSetupToolingForLLVM.html
//  for details on setting it up with LLVM source tree.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/CodeGen/ObjectFilePCHContainerOperations.h"
#include "clang/Driver/Options.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Rewrite/Frontend/FixItRewriter.h"
#include "clang/Rewrite/Frontend/FrontendActions.h"
#include "clang/StaticAnalyzer/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Syntax/BuildTree.h"
#include "clang/Tooling/Syntax/TokenBufferTokenManager.h"
#include "clang/Tooling/Syntax/Tokens.h"
#include "clang/Tooling/Syntax/Tree.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Option/OptTable.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/Path.h"
#include <sstream>

using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

static cl::OptionCategory ClangToolCategory("clang-tool options");

namespace {

struct dataTypeStrAbbrMapping {
    std::string fullName;
    std::string abbrName;
    std::string llvmName;
};

static dataTypeStrAbbrMapping DataTypeStrAbbrMappingTable[] = {
    {"bool", "b", "llvm_i1_ty"},
    {"char", "c", "llvm_i8_ty"},
    {"short", "s", "llvm_i16_ty"},
    {"int", "i", "llvm_i32_ty"},
    {"float", "f", "llvm_float_ty"},
    {"bf16", "y", "llvm_bfloat_ty"},
    {"half", "h", "llvm_half_ty"},
    {"int8_t", "Sc", "llvm_i8_ty"},
    {"uint8_t", "Uc", "llvm_i8_ty"},
    {"int16_t", "s", "llvm_i16_ty"},
    {"uint16_t", "Us", "llvm_i16_ty"},
    {"int32_t", "i", "llvm_i32_ty"},
    {"uint32_t", "Ui", "llvm_i32_ty"},
    {"float32_t", "f", "llvm_float_ty"},
    {"float16_t", "x", "llvm_half_ty"},
    {"void", "v"},
    {"enum", "Ui", "llvm_i32_ty"},
    {"uint1", "Ui", "llvm_i32_ty"},
    {"uint3", "Ui", "llvm_i32_ty"},
    {"uint4", "Ui", "llvm_i32_ty"},
    {"uint5", "Ui", "llvm_i32_ty"},
    {"uint8", "Ui", "llvm_i32_ty"},
    {"int12", "i", "llvm_i32_ty"},
    {"int20", "i", "llvm_i32_ty"},
    // vector
    {"v_int8_t", "V256Sc", "llvm_v256i8_ty"},
    {"v_uint8_t", "V256Uc", "llvm_v256i8_ty"},
    {"v_int16_t", "V128s", "llvm_v128i16_ty"},
    {"v_uint16_t", "V128Us", "llvm_v128i16_ty"},
    {"v_int32_t", "V64i", "llvm_v64i32_ty"},
    {"v_uint32_t", "V64Ui", "llvm_v64i32_ty"},
    {"v_float16_t", "V128x", "llvm_v128f16_ty"},
    {"v_float32_t", "V64f", "llvm_v64f32_ty"},
    {"v_bool1_t", "V256b", "llvm_v256i1_ty"},
    {"v_bool2_t", "V256b", "llvm_v256i1_ty"},
    {"v_bool4_t", "V256b", "llvm_v256i1_ty"},
};

class IntrinGenerator {
  StringRef filename;
  StringRef prefix;
  std::unique_ptr<raw_ostream> OS;

public:
  IntrinGenerator() = default;
  IntrinGenerator(const std::string &fname, const std::string &pref="") : filename(fname), prefix(pref) {
    std::error_code ec;
    SmallString<256> fullPath;

    if (!prefix.empty()) {
      llvm::sys::fs::create_directory(prefix);
      llvm::sys::path::append(fullPath, prefix);
    }

    llvm::sys::path::append(fullPath, filename);
    OS = std::make_unique<raw_fd_ostream>(fullPath, ec, sys::fs::OF_None);
    if (ec) {
      OS = nullptr;
      llvm::outs() << "IntrinGenerator ctor failed!\n";
    }
  }

  raw_ostream &OStream() { return *OS.get(); }

  virtual void gen_builtin_intrinsic_header() {}
  virtual void gen_builtin_intrinsic_body(const std::string &funcName, const std::string &retType,
                                        SmallVectorImpl<std::string> &inType) {}
  virtual void gen_builtin_intrinsic_footer() {}
};

class IntrinDefGenerator : public IntrinGenerator {
public:
  IntrinDefGenerator(const std::string &fname, const std::string &pref="") : IntrinGenerator(fname, pref) {}

  std::string translateDataTypeToAbbr(const std::string &rawType);

  virtual void gen_builtin_intrinsic_header();
  virtual void gen_builtin_intrinsic_body(const std::string &funcName, const std::string &retType,
                                        SmallVectorImpl<std::string> &inType);
  virtual void gen_builtin_intrinsic_footer();
};

std::string IntrinDefGenerator::translateDataTypeToAbbr(const std::string &rawType) {
  std::string orig(rawType);
  std::string encoding;
  bool isPointer = false;

  // preprocess
  if (StringRef(orig).ends_with("*")) {
    isPointer = true;
  }

  auto end = orig.find_first_of(' ');
  if (end != std::string::npos) {
    orig.erase(end, orig.size());
  }

  for (auto ty : DataTypeStrAbbrMappingTable) {
    if (orig == ty.fullName) {
      encoding = ty.abbrName;
      if (isPointer) {
        encoding += "*";
      }
      break;
    }
  }

#ifdef DEBUG
  llvm::outs() << "  translate data type to abbr: " << rawType << "\n";
#endif

  assert(!encoding.empty() && "Data type not found!");

  return encoding;
}

void IntrinDefGenerator::gen_builtin_intrinsic_header() {
  OStream() << "//==- BuiltinsCpu0.def - Cpu0 Builtin function database -------*- C++ -*-==//" << "\n";
  OStream() << "//" << "\n";
  OStream() << "// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions." << "\n";
  OStream() << "// See https://llvm.org/LICENSE.txt for license information." << "\n";
  OStream() << "// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception" << "\n";
  OStream() << "//" << "\n";
  OStream() << "//===------------------------------------------------------------------------===//" << "\n";
  OStream() << "//" << "\n";
  OStream() << "// This file defines the Cpu0-specific builtin function database.  Users of" << "\n";
  OStream() << "// this file must define the BUILTIN macro to make use of this information." << "\n";
  OStream() << "//" << "\n";
  OStream() << "//===------------------------------------------------------------------------===//" << "\n";
  OStream() << "\n";

  OStream() << "#if defined(BUILTIN) && !defined(TARGET_BUILTIN)" << "\n";
  OStream() << "#   define TARGET_BUILTIN(ID, TYPE, ATTRS, FEATURE) BUILTIN(ID, TYPE, ATTRS)" << "\n";
  OStream() << "#endif" << "\n";
  OStream() << "\n";
}

void IntrinDefGenerator::gen_builtin_intrinsic_body(const std::string &funcName, const std::string &retType,
                                        SmallVectorImpl<std::string> &inType) {
  std::string types, attrs;
  bool memory_access = StringRef(retType).ends_with("*");
  types = translateDataTypeToAbbr(retType);

  for (auto ty : inType) {
    types += translateDataTypeToAbbr(ty);
    if (!memory_access) {
      memory_access = StringRef(ty).ends_with("*");
    }
  }

  attrs = !memory_access ? "nc" : "n";

#ifdef DEBUG
  llvm::outs() << "  encoding: " << types << "\n";
#endif

  OStream() << "TARGET_BUILTIN(";
  OStream() << funcName << ", " << "\"" << types << "\"" <<
              ", " << "\"" << attrs << "\"" <<
              ", " << "\"" << "32bit" << "\"";
  OStream() << ")\n";
}

void IntrinDefGenerator::gen_builtin_intrinsic_footer() {
  OStream() << "\n";
  OStream() << "#undef BUILTIN" << "\n";
  OStream() << "#undef TARGET_BUILTIN" << "\n";
}

class IntrinIncGenerator : public IntrinGenerator {
public:
  IntrinIncGenerator(const std::string &fname, const std::string &pref="") : IntrinGenerator(fname, pref) {}

  virtual void gen_builtin_intrinsic_header();
  virtual void gen_builtin_intrinsic_body(const std::string &funcName, const std::string &retType,
                                            SmallVectorImpl<std::string> &inType);
};

void IntrinIncGenerator::gen_builtin_intrinsic_header() {
  OStream() << "/*===- Intrinsic Generator'erated file --------------------------*- C++ -*-===*\\" << "\n";
  OStream() << "|*                                                                            *|" << "\n";
  OStream() << "|* Cpu0 intrinsic builtin CG fragment                                      *|" << "\n";
  OStream() << "|*                                                                            *|" << "\n";
  OStream() << "|* Automatically generated file, do not edit!                                 *|" << "\n";
  OStream() << "|*                                                                            *|" << "\n";
  OStream() << "\\*===----------------------------------------------------------------------===*/" << "\n";
  OStream() << "\n";
}

void IntrinIncGenerator::gen_builtin_intrinsic_body(const std::string &funcName, const std::string &retType,
                                                      SmallVectorImpl<std::string> &inType) {
  std::string intrinsicName(funcName);
  bool is_builtin_prefix = StringRef(funcName).starts_with("__builtin");
  if (is_builtin_prefix) {
    intrinsicName = intrinsicName.erase(0, StringRef("__builtin").size() + 1);
  }

  OStream() << "case Cpu0::BI";
  OStream() << funcName << ":\n";
  OStream() << "  ID = Intrinsic::cpu0_";
  OStream() << intrinsicName << ";\n";
  OStream() << "  break;\n";
}

class IntrinTdGenerator : public IntrinGenerator {
public:
  IntrinTdGenerator(const std::string &fname, const std::string &pref="") : IntrinGenerator(fname, pref) {}

  std::string translateDataTypeToLLVM(const std::string &rawType);

  virtual void gen_builtin_intrinsic_header();
  virtual void gen_builtin_intrinsic_body(const std::string &funcName, const std::string &retType,
                                            SmallVectorImpl<std::string> &inType);
  virtual void gen_builtin_intrinsic_footer();
};

std::string IntrinTdGenerator::translateDataTypeToLLVM(const std::string &rawType) {
  std::string orig(rawType);
  std::string encoding;
  bool isPointer = false;

  // preprocess
  if (StringRef(orig).ends_with("*")) {
    isPointer = true;
    return "llvm_ptr_ty";
  }

  auto end = orig.find_first_of(' ');
  if (end != std::string::npos) {
    orig.erase(end, orig.size());
  }

  for (auto ty : DataTypeStrAbbrMappingTable) {
    if (orig == ty.fullName) {
      encoding = ty.llvmName;
      break;
    }
  }

#ifdef DEBUG
  llvm::outs() << "  translate data type to LLVM: " << rawType << "\n";
#endif

  if (orig != "void") {
    assert(!encoding.empty() && "Data type not found!");
  }

  return encoding;
}

void IntrinTdGenerator::gen_builtin_intrinsic_header() {
  OStream() << "//===- IntrinsicsCpu0.td - Defines Cpu0 intrinsics ---*- tablegen -*-===//" << "\n";
  OStream() << "//" << "\n";
  OStream() << "//                     The LLVM Compiler Infrastructure" << "\n";
  OStream() << "//" << "\n";
  OStream() << "// This file is distributed under the University of Illinois Open Source" << "\n";
  OStream() << "// License. See LICENSE.TXT for details." << "\n";
  OStream() << "//" << "\n";
  OStream() << "//===----------------------------------------------------------------------===//" << "\n";
  OStream() << "//" << "\n";
  OStream() << "// This file defines all of the Cpu0-specific intrinsics." << "\n";
  OStream() << "//" << "\n";
  OStream() << "//===----------------------------------------------------------------------===//" << "\n";
  OStream() << "//" << "\n";
  OStream() << "//===----------------------------------------------------------------------===//" << "\n";
  OStream() << "// Definitions for all Cpu0 intrinsics." << "\n";
  OStream() << "//" << "\n";
  OStream() << "\n";

  OStream() << "let TargetPrefix = \"cpu0\" in {" << "\n";
  OStream() << "\n";
}

void IntrinTdGenerator::gen_builtin_intrinsic_body(const std::string &funcName, const std::string &retType,
                                            SmallVectorImpl<std::string> &inType) {
  std::string rtype, itype, attr;

  bool memory_access = StringRef(retType).ends_with("*");
  rtype = translateDataTypeToLLVM(retType);

  std::string intrinsicName(funcName);
  bool is_builtin_prefix = StringRef(funcName).starts_with("__builtin");
  if (is_builtin_prefix) {
    intrinsicName = intrinsicName.erase(0, StringRef("__builtin").size() + 1);
  }

  OStream() << "  def int_cpu0_";
  OStream() << intrinsicName << " : " << "ClangBuiltin<" << "\"" << funcName << "\"" << ">," << "\n";
  OStream() << "                    Intrinsic<" << "[" << rtype << "]," << "\n";
  OStream() << "                              " << "[" << "\n";
  for (auto i = 0; i != inType.size(); i++) {
    itype = translateDataTypeToLLVM(inType[i]);
    OStream() << "                                " << itype;
    if (i != inType.size() - 1) {
      OStream() << ",";
    }
    OStream() << "\n";
    if (!memory_access) {
      memory_access = StringRef(inType[i]).ends_with("*");
    }
  }
  OStream() << "                              " << "]," << "\n";

  attr = !memory_access ? "IntrNoMem" : "IntrWriteMem";
  OStream() << "                              " << "[" << attr << "]" << ">;" << "\n";
  OStream() << "\n";
}

void IntrinTdGenerator::gen_builtin_intrinsic_footer() {
  OStream() << "}" << "\n";
}

class DeclVisitor : public clang::RecursiveASTVisitor<DeclVisitor> {
  SmallVector<std::unique_ptr<IntrinGenerator>, 4> IGs;

public:
  DeclVisitor() {
    IGs.emplace_back(std::make_unique<IntrinDefGenerator>("BuiltinsCpu0.def", "output"));
    IGs.emplace_back(std::make_unique<IntrinIncGenerator>("Cpu0GenIntrinsicBuiltinsCG.inc", "output"));
    IGs.emplace_back(std::make_unique<IntrinTdGenerator>("IntrinsicsCpu0.td", "output"));
  }

  bool VisitFunctionDecl(clang::FunctionDecl *Decl);

  void gen_header() {
    for (auto &IG : IGs) {
      IG->gen_builtin_intrinsic_header();
    }
  }

  void gen_body(const std::string &funcName, const std::string &retType,
                  SmallVectorImpl<std::string> &inType) {
    for (auto &IG : IGs) {
      IG->gen_builtin_intrinsic_body(funcName, retType, inType);
    }
  }

  void gen_footer() {
    for (auto &IG : IGs) {
      IG->gen_builtin_intrinsic_footer();
    }
  }
};

bool DeclVisitor::VisitFunctionDecl(clang::FunctionDecl *Decl) {
  clang::ASTContext &AST = Decl->getASTContext();
  SmallVector<std::string, 4> inArgs;
  std::string funcName = Decl->getQualifiedNameAsString();
  std::string retType = Decl->getDeclaredReturnType().getAsString();

  if (StringRef(funcName).contains("::")) {
    funcName = Decl->getNameAsString();
  }

  for (size_t i = 0; i != Decl->getNumParams(); i++) {
        inArgs.emplace_back(Decl->parameters()[i]->getType().getAsString());
  }

  if (Decl->hasAttrs()) {
    for (const auto &attr : Decl->getAttrs()) {
      if (attr->getKind() == clang::attr::BuiltinAlias) {
        bool Invalid = false;
        funcName = clang::Lexer::getSourceText(
                        AST.getSourceManager().getExpansionRange(attr->getLocation()),
                        AST.getSourceManager(), AST.getLangOpts(), &Invalid);
        auto extractFunc = [](std::string &orig) {
          auto start = orig.find_first_of('(');
          if (start != std::string::npos) {
            orig.erase(0, start + 1);
          }
          auto end = orig.find_first_of(')');
          if (end != std::string::npos) {
            orig.erase(end);
          }
          return orig;
        };
        funcName = extractFunc(funcName);
#ifdef DEBUG
        llvm::outs() << "attr: " << attr->getSpelling() << ", " << funcName << "\n";
#endif
      }
    }
  }

  gen_body(funcName, retType, inArgs);
  return true;
}

class DeclFindingAction : public clang::ASTFrontendAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, StringRef InFile) override {
    class Consumer : public clang::ASTConsumer {
    public:
      Consumer() : Visitor() {
        Visitor.gen_header();
      }

      void HandleTranslationUnit(clang::ASTContext &AST) override {
        auto Decls = AST.getTranslationUnitDecl()->decls();
        for (auto &D : Decls) {
          const auto &FileID = AST.getSourceManager().getFileID(D->getLocation());
          if (FileID != AST.getSourceManager().getMainFileID()) {
            continue;
          }
          Visitor.TraverseDecl(D);
        }
        Visitor.gen_footer();
      }

    private:
      DeclVisitor Visitor;
    };
    return std::make_unique<Consumer>();
  }
};

} // namespace

int main(int argc, const char **argv) {
  llvm::sys::PrintStackTraceOnErrorSignal(argv[0]);

  // Initialize targets for clang module support.
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmPrinters();
  llvm::InitializeAllAsmParsers();

  auto ExpectedParser =
      CommonOptionsParser::create(argc, argv, ClangToolCategory);
  if (!ExpectedParser) {
    llvm::errs() << ExpectedParser.takeError();
    return 1;
  }
  CommonOptionsParser &OptionsParser = ExpectedParser.get();
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  std::unique_ptr<FrontendActionFactory> FrontendFactory;
  FrontendFactory = newFrontendActionFactory<DeclFindingAction>();

  return Tool.run(FrontendFactory.get());
}
