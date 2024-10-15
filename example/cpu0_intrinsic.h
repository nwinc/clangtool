#ifndef _CPU0_INTRINSIC_H_
#define _CPU0_INTRINSIC_H_


//===-- cpu0_intrinsic.h - cpu0 'scalar' & 'vector' & 'tensor' intrinsic define file----*- C++ -*-===//
// Match isa
//
// Intrinsic Name
//  scalar intrinsic: 'instruction name'
//  vector intrinsic: 'instruction name'
//  tensor intrinsic: t_ + 'instruction name'
//===-----------------------------------------------------------------------------------------------------===//

#define INLINE inline __attribute__((always_inline))

//---------------------------------
//        Builtin data types
//---------------------------------

/****** immediate data type ******/
typedef unsigned int uint1;
typedef unsigned int uint3;
typedef unsigned int uint4;
typedef unsigned int uint5;
typedef unsigned int uint8;
typedef signed   int int12;
typedef signed   int int20;

/****** scalar data type ******/
#ifndef __cplusplus
typedef _Bool  bool;
#endif
typedef signed   char  int8_t;
typedef unsigned char  uint8_t;
typedef signed   short int16_t;
typedef unsigned short uint16_t;
typedef signed   int   int32_t;
typedef unsigned int   uint32_t;
typedef unsigned long long uint64_t;
// typedef Float8_152     float8_152_t;   // TODO
// typedef Float8_143     float8_143_t;   // TODO
// typedef Float8_p152    v_float8_p152_t; // TODO
// typedef Float8_p143    v_float8_p143_t; // TODO
typedef _Float16       float16_t;
// typedef __bf16     bfloat16_t; // TODO
typedef float          float32_t;
// typedef _TFloat32      tfloat32_t; // TODO

/****** vector data type ******/
typedef bool     __attribute__((ext_vector_type(256))) v_bool1_t;
typedef bool     __attribute__((ext_vector_type(256))) v_bool2_t;
typedef bool     __attribute__((ext_vector_type(256))) v_bool4_t;
typedef int8_t      __attribute__((ext_vector_type(256))) v_int8_t;   // Disable
typedef uint8_t     __attribute__((ext_vector_type(256))) v_uint8_t;  // Disable
typedef int16_t     __attribute__((ext_vector_type(128))) v_int16_t;  // Disable
typedef uint16_t    __attribute__((ext_vector_type(128))) v_uint16_t; // Disable
typedef int32_t     __attribute__((ext_vector_type(64)))  v_int32_t;  // Disable
typedef uint32_t    __attribute__((ext_vector_type(64)))  v_uint32_t; // Disable
typedef float16_t   __attribute__((ext_vector_type(128))) v_float16_t;
typedef float32_t   __attribute__((ext_vector_type(64)))  v_float32_t;

#ifdef __cplusplus
namespace cpu0 {
#endif

enum FlagType {
    L1V = 0x0,
    VCORESMEM = 0x1,
    L1M = 0x2,
    TCORESMEM = 0x3,
    CDMASMEM = 0x3,
    OUT = 0x4,
    ACC = 0x5,
};


enum FlagMode {
    EMPTY = 0x0,
    FULL = 0x1,
};


enum ChannelId {
    OUT2L1M = 0x0,
    OUT2TCORESMEM = 0x1,
    OUT2CDMASMEM = 0x1,
    OUT2OUT = 0x2,
    ACC2OUT = 0x4,
    ACC2L1M = 0x5,
    ACC2L1V = 0x6,
    OUT2L1V = 0x8,
    OUT2VCORESMEM = 0x9,
    L1V2OUT = 0xc,
    L1V2L1M = 0xd,
    L1V2VCORESMEM = 0xe,
};


enum NotifyId {
    NO_NOTIFY = 0x0,
    NOTIFY1 = 0x1,
    NOTIFY2 = 0x2,
    NOTIFY3 = 0x3,
    NOTIFY4 = 0x4,
    NOTIFY5 = 0x5,
    NOTIFY6 = 0x6,
    NOTIFY7 = 0x7,
};


enum EngineId {
    TCORE_OUT = 0x0,
    TCORE_ACC = 0x1,
    VCORE_OUT = 0x2,
    VCORE_L1 = 0x3,
};


enum BlkSize {
    BLK_128B = 0x0,
    BLK_256B = 0x1,
};


enum Rnd {
    RNE = 0x0,
    RTZ = 0x1,
    RDN = 0x2,
    RUP = 0x3,
    RMM = 0x4,
    DYN = 0x7,
    SR = 0x5,
};


enum Pos {
    LOWER_HALF = 0x0,
    UPPER_HALF = 0x1,
};

enum SortType {
    INC = 0x0,
    DEC = 0x1,
};


enum CsrOffset {
   SCALAR_TRIGGER = 34,
   SCALAR_PC_HIGH_CFG = 33,
   SCALAR_PC_CFG = 35,
   SCALAR_PARAM_BASE_HIGH_CFG = 37,
   SCALAR_PARAM_BASE_CFG = 36,
   SCALAR_AXI_USER_ID_CFG = 70,
   SCALAR_PC_HIGH_WRK = 71,
   SCALAR_PC_WRK = 72,
   SCALAR_PARAM_BASE_HIGH_WRK = 74,
   SCALAR_PARAM_BASE_WRK = 73,
   SCALAR_AXI_USER_ID_WRK = 107,
   SCALAR_WARN_STATUS = 108,
   SCALAR_WARN_FP_OVERFLOW_PC = 109,
   SCALAR_CORE_ID = 116,
   SCALAR_PC = 117,
   SCALAR_IFU_CTRL = 118,
   SCALAR_ICACHE_IDX = 119,
   SCALAR_HW_STS = 120,
   SCALAR_SCSR = 121,
   SCALAR_L1V_CTRL = 122,
   SCALAR_MBOX_ID = 123,
   SCALAR_MBOX_CONFIG = 124,
   SCALAR_MBOX_STATUS_SEL = 125,
   SCALAR_MBOX_STATUS = 126,
   SCALAR_MBOX_ERR_RPT = 127,
   SCALAR_MBOX_ERR_CODE = 128,
   SCALAR_VMM_RPT = 130,
   SCALAR_VMM_STRIDE = 129,
   SCALAR_LSU_EXTERNAL_ADDR_HIGH_BITS = 32,
   SCALAR_PARAM_ID0 = 0,
   SCALAR_PARAM_ID1 = 1,
   SCALAR_PARAM_ID2 = 2,
   SCALAR_PARAM_ID3 = 3,
   SCALAR_PARAM_ID4 = 4,
   SCALAR_PARAM_ID5 = 5,
   SCALAR_PARAM_ID6 = 6,
   SCALAR_PARAM_ID7 = 7,
   SCALAR_PARAM_ID8 = 8,
   SCALAR_PARAM_ID9 = 9,
   SCALAR_PARAM_ID10 = 10,
   SCALAR_PARAM_ID11 = 11,
   SCALAR_PARAM_ID12 = 12,
   SCALAR_PARAM_ID13 = 13,
   SCALAR_PARAM_ID14 = 14,
   SCALAR_PARAM_ID15 = 15,
   SCALAR_PARAM_ID16 = 16,
   SCALAR_PARAM_ID17 = 17,
   SCALAR_PARAM_ID18 = 18,
   SCALAR_PARAM_ID19 = 19,
   SCALAR_PARAM_ID20 = 20,
   SCALAR_PARAM_ID21 = 21,
   SCALAR_PARAM_ID22 = 22,
   SCALAR_PARAM_ID23 = 23,
   SCALAR_PARAM_ID24 = 24,
   SCALAR_PARAM_ID25 = 25,
   SCALAR_PARAM_ID26 = 26,
   SCALAR_PARAM_ID27 = 27,
   SCALAR_PARAM_ID28 = 28,
   SCALAR_PARAM_ID29 = 29,
   SCALAR_PARAM_ID30 = 30,
   SCALAR_PARAM_ID31 = 31,
   SCALAR_INFO0_CFG = 38,
   SCALAR_INFO1_CFG = 39,
   SCALAR_INFO2_CFG = 40,
   SCALAR_INFO3_CFG = 41,
   SCALAR_INFO4_CFG = 42,
   SCALAR_INFO5_CFG = 43,
   SCALAR_INFO6_CFG = 44,
   SCALAR_INFO7_CFG = 45,
   SCALAR_INFO8_CFG = 46,
   SCALAR_INFO9_CFG = 47,
   SCALAR_INFO10_CFG = 48,
   SCALAR_INFO11_CFG = 49,
   SCALAR_INFO12_CFG = 50,
   SCALAR_INFO13_CFG = 51,
   SCALAR_INFO14_CFG = 52,
   SCALAR_INFO15_CFG = 53,
   SCALAR_INFO16_CFG = 54,
   SCALAR_INFO17_CFG = 55,
   SCALAR_INFO18_CFG = 56,
   SCALAR_INFO19_CFG = 57,
   SCALAR_INFO20_CFG = 58,
   SCALAR_INFO21_CFG = 59,
   SCALAR_INFO22_CFG = 60,
   SCALAR_INFO23_CFG = 61,
   SCALAR_INFO24_CFG = 62,
   SCALAR_INFO25_CFG = 63,
   SCALAR_INFO26_CFG = 64,
   SCALAR_INFO27_CFG = 65,
   SCALAR_INFO28_CFG = 66,
   SCALAR_INFO29_CFG = 67,
   SCALAR_INFO30_CFG = 68,
   SCALAR_INFO31_CFG = 69,
   SCALAR_INFO0_WRK = 75,
   SCALAR_INFO1_WRK = 76,
   SCALAR_INFO2_WRK = 77,
   SCALAR_INFO3_WRK = 78,
   SCALAR_INFO4_WRK = 79,
   SCALAR_INFO5_WRK = 80,
   SCALAR_INFO6_WRK = 81,
   SCALAR_INFO7_WRK = 82,
   SCALAR_INFO8_WRK = 83,
   SCALAR_INFO9_WRK = 84,
   SCALAR_INFO10_WRK = 85,
   SCALAR_INFO11_WRK = 86,
   SCALAR_INFO12_WRK = 87,
   SCALAR_INFO13_WRK = 88,
   SCALAR_INFO14_WRK = 89,
   SCALAR_INFO15_WRK = 90,
   SCALAR_INFO16_WRK = 91,
   SCALAR_INFO17_WRK = 92,
   SCALAR_INFO18_WRK = 93,
   SCALAR_INFO19_WRK = 94,
   SCALAR_INFO20_WRK = 95,
   SCALAR_INFO21_WRK = 96,
   SCALAR_INFO22_WRK = 97,
   SCALAR_INFO23_WRK = 98,
   SCALAR_INFO24_WRK = 99,
   SCALAR_INFO25_WRK = 100,
   SCALAR_INFO26_WRK = 101,
   SCALAR_INFO27_WRK = 102,
   SCALAR_INFO28_WRK = 103,
   SCALAR_INFO29_WRK = 104,
   SCALAR_INFO30_WRK = 105,
   SCALAR_INFO31_WRK = 106,
   SCALAR_WARN_FP_UNDERFLOW_PC = 110,
   SCALAR_WARN_FP_DIV0_PC = 111,
   SCALAR_WARN_FP_INVALID_PC = 112,
   SCALAR_WARN_INT_OVERFLOW_PC = 113,
   SCALAR_WARN_INT_INEXACT_PC = 114,
   SCALAR_WARN_INT_DIV0_PC = 115,
   MALU_MCSR = 768,
   MALU_MALU_STATUS = 769,
   MALU_MALU_EXP_BIAS = 770,
   MALU_WARN_STATUS = 771,
   MALU_WARN_FP_OVERFLOW_PC = 772,
   MALU_WARN_FP_UNDERFLOW_PC = 773,
   MALU_WARN_FP_INVALID_PC = 774,
   MALU_WARN_INT_OVERFLOW_PC = 775,
   VECTOR_VCSR = 512,
   VECTOR_VL = 513,
   VECTOR_WARN_STATUS = 515,
   VECTOR_WARN_FP_OVERFLOW_PC = 516,
   VECTOR_VECTOR_EXP_BIAS = 514,
   VECTOR_WARN_FP_UNDERFLOW_PC = 517,
   VECTOR_WARN_FP_DIV0_PC = 518,
   VECTOR_WARN_FP_INVALID_PC = 519,
   VECTOR_WARN_INT_OVERFLOW_PC = 520,
   VECTOR_WARN_INT_INEXACT_PC = 521,
   VECTOR_WARN_INT_DIV0_PC = 522,
   DTE_WARN_STATUS = 1024,
   DTE_AUTO_PAD_VALUE = 1025,
   DTE_DCSR = 1026,
   DTE_ATOMIC_CFG = 1027,
   DTE_SRC_BASE_ADDR_HIGH = 1042,
   DTE_SRC_BASE_ADDR_LOW = 1043,
   DTE_DST_BASE_ADDR_HIGH = 1044,
   DTE_DST_BASE_ADDR_LOW = 1045,
   DTE_GATHER_START_INDEX_HIGH = 1046,
   DTE_GATHER_START_INDEX_LOW = 1047,
   DTE_GATHER_END_INDEX_HIGH = 1048,
   DTE_GATHER_END_INDEX_LOW = 1049,
   DTE_SCATTER_START_INDEX_HIGH = 1050,
   DTE_SCATTER_START_INDEX_LOW = 1051,
   DTE_SCATTER_END_INDEX_HIGH = 1052,
   DTE_SCATTER_END_INDEX_LOW = 1053,
   DTE_INT_AGENT_ADDR1 = 1028,
   DTE_INT_AGENT_ADDR2 = 1029,
   DTE_INT_AGENT_ADDR3 = 1030,
   DTE_INT_AGENT_ADDR4 = 1031,
   DTE_INT_AGENT_ADDR5 = 1032,
   DTE_INT_AGENT_ADDR6 = 1033,
   DTE_INT_AGENT_ADDR7 = 1034,
   DTE_INT_AGENT_MSG1 = 1035,
   DTE_INT_AGENT_MSG2 = 1036,
   DTE_INT_AGENT_MSG3 = 1037,
   DTE_INT_AGENT_MSG4 = 1038,
   DTE_INT_AGENT_MSG5 = 1039,
   DTE_INT_AGENT_MSG6 = 1040,
   DTE_INT_AGENT_MSG7 = 1041,
};


//
// ------ SET_FLAG.type.mode in:Rs1
//
// @brief Represents SET_FLAG instruction.
//
void __builtin_set_flag(enum FlagType type, enum FlagMode mode, uint32_t rs1);

//
// ------ SET_FLAG.type.mode
//
// @brief Represents SET_FLAG instruction.
//
void __builtin_set_flag_without_rs1(enum FlagType type, enum FlagMode mode);


//
// ------ SET_FLAGI.type.mode #uimm4
//
// @brief Represents SET_FLAGI instruction.
//
void __builtin_set_flagi(enum FlagType type, enum FlagMode mode, uint32_t uimm4);

//
// ------ SET_FLAGI.type.mode
//
// @brief Represents SET_FLAGI instruction.
//
void __builtin_set_flagi_without_uimm4(enum FlagType type, enum FlagMode mode);


//
// ------ WAIT_FLAG.type.mode in:Rs1
//
// @brief Represents WAIT_FLAG instruction.
//
void __builtin_wait_flag(enum FlagType type, enum FlagMode mode, uint32_t rs1);


//
// ------ WAIT_FLAGI.type.mode #uimm4
//
// @brief Represents WAIT_FLAGI instruction.
//
void __builtin_wait_flagi(enum FlagType type, enum FlagMode mode, uint32_t uimm4);


//
// ------ DTE_TRIGGER.channelid.notifyid [in:Rs1], #uimm5
//
// @brief Represents DTE_TRIGGER instruction.
//
void __builtin_dte_trigger(enum ChannelId channelid, enum NotifyId notifyid, uint32_t *rs1, uint32_t uimm5);


//
// ------ DTE_ST.dtype [in:Rs1], in:Rs2, in:Rs3, #simm7
//
// @brief Represents DTE_ST instruction.
//
void __builtin_dte_st(uint32_t *rs1, uint32_t rs2, uint32_t rs3, int32_t simm7);

//
// ------ DTE_ST.dtype [in:Rs1], in:Rs2, #simm7
//
// @brief Represents DTE_ST instruction.
//
void __builtin_dte_st_without_rs3(uint32_t *rs1, uint32_t rs2, int32_t simm7);


//
// ------ DTE_LOOPBEGIN.engineid [in:Rs1]
//
// @brief Represents DTE_LOOPBEGIN instruction.
//
void __builtin_dte_loopbegin(enum EngineId engineid, uint32_t *rs1);


//
// ------ DTE_LOOPEND.engineid
//
// @brief Represents DTE_LOOPEND instruction.
//
void __builtin_dte_loopend(enum EngineId engineid);


//
// ------ MOVR2CSR out:CSR, in:Rs1
//
// @brief Represents MOVR2CSR instruction.
//
void __builtin_movr2csr(enum CsrOffset csr, uint32_t rs1);


//
// ------ MOVCSR2R out:Rd, in:CSR
//
// @brief Represents MOVCSR2R instruction.
//
uint32_t __builtin_movcsr2r(enum CsrOffset csr);


//
// ------ MOVR2A_VLD out:Ad, in:Rs1
//
// @brief Represents MOVR2A_VLD instruction.
//
uint32_t __builtin_movr2a_vld(uint32_t rs1);


//
// ------ MOVR2A_VST out:Ad, in:Rs1
//
// @brief Represents MOVR2A_VST instruction.
//
uint32_t __builtin_movr2a_vst(uint32_t rs1);


//
// ------ MOVR2A_MALU out:Ad, in:Rs1
//
// @brief Represents MOVR2A_MALU instruction.
//
uint32_t __builtin_t_movr2a_malu(uint32_t rs1);


//
// ------ MOVA2A_VLD out:Ad, in:As1
//
// @brief Represents MOVA2A_VLD instruction.
//
uint32_t __builtin_mova2a_vld(uint32_t as1);


//
// ------ MOVA2A_VST out:Ad, in:As1
//
// @brief Represents MOVA2A_VST instruction.
//
uint32_t __builtin_mova2a_vst(uint32_t as1);


//
// ------ MOVA2A_MALU out:Ad, in:As1
//
// @brief Represents MOVA2A_MALU instruction.
//
uint32_t __builtin_t_mova2a_malu(uint32_t as1);


//
// ------ UPDATEA_VLD inout:Ad, in:As1
//
// @brief Represents UPDATEA_VLD instruction.
//
void __builtin_updatea_vld(uint32_t ad, uint32_t as1);


//
// ------ UPDATEA_VST inout:Ad, in:As1
//
// @brief Represents UPDATEA_VST instruction.
//
void __builtin_updatea_vst(uint32_t ad, uint32_t as1);


//
// ------ UPDATEA_MALU inout:Ad, in:As1
//
// @brief Represents UPDATEA_MALU instruction.
//
void __builtin_t_updatea_malu(uint32_t ad, uint32_t as1);


//
// ------ VLD out:Vd, [in:Rs1], #simm12
//
// @brief Represents VLD instruction.
//
v_uint8_t __builtin_vld_u8(uint8_t *rs1, int32_t simm12);
v_int8_t __builtin_vld_s8(int8_t *rs1, int32_t simm12);
v_uint16_t __builtin_vld_u16(uint16_t *rs1, int32_t simm12);
v_int16_t __builtin_vld_s16(int16_t *rs1, int32_t simm12);
v_uint32_t __builtin_vld_u32(uint32_t *rs1, int32_t simm12);
v_int32_t __builtin_vld_s32(int32_t *rs1, int32_t simm12);
v_float16_t __builtin_vld_f16(float16_t *rs1, int32_t simm12);
v_float32_t __builtin_vld_f32(float32_t *rs1, int32_t simm12);


//
// ------ VST in:Vs1, [in:Rs2], #simm12, in:Pn
//
// @brief Represents VST instruction.
//
void __builtin_vst_u8(v_uint8_t vs1, uint8_t *rs2, int32_t simm12);
void __builtin_vst_s8(v_int8_t vs1, int8_t *rs2, int32_t simm12);
void __builtin_vst_u16(v_uint16_t vs1, uint16_t *rs2, int32_t simm12);
void __builtin_vst_s16(v_int16_t vs1, int16_t *rs2, int32_t simm12);
void __builtin_vst_u32(v_uint32_t vs1, uint32_t *rs2, int32_t simm12);
void __builtin_vst_s32(v_int32_t vs1, int32_t *rs2, int32_t simm12);
void __builtin_vst_f16(v_float16_t vs1, float16_t *rs2, int32_t simm12);
void __builtin_vst_f32(v_float32_t vs1, float32_t *rs2, int32_t simm12);
void __builtin_vst_u8_with_pn(v_uint8_t vs1, uint8_t *rs2, int32_t simm12, v_bool1_t pn);
void __builtin_vst_s8_with_pn(v_int8_t vs1, int8_t *rs2, int32_t simm12, v_bool1_t pn);
void __builtin_vst_u16_with_pn(v_uint16_t vs1, uint16_t *rs2, int32_t simm12, v_bool2_t pn);
void __builtin_vst_s16_with_pn(v_int16_t vs1, int16_t *rs2, int32_t simm12, v_bool2_t pn);
void __builtin_vst_u32_with_pn(v_uint32_t vs1, uint32_t *rs2, int32_t simm12, v_bool4_t pn);
void __builtin_vst_s32_with_pn(v_int32_t vs1, int32_t *rs2, int32_t simm12, v_bool4_t pn);
void __builtin_vst_f16_with_pn(v_float16_t vs1, float16_t *rs2, int32_t simm12, v_bool2_t pn);
void __builtin_vst_f32_with_pn(v_float32_t vs1, float32_t *rs2, int32_t simm12, v_bool4_t pn);


//
// ------ VALD.blksize out:Vd, [inout:As1], in:As2, in:Rs3
//
// @brief Represents VALD instruction.
//
v_uint8_t __builtin_vald_u8(enum BlkSize blksize, uint8_t *as1, uint32_t as2, uint32_t rs3);
v_int8_t __builtin_vald_s8(enum BlkSize blksize, int8_t *as1, uint32_t as2, uint32_t rs3);
v_uint16_t __builtin_vald_u16(enum BlkSize blksize, uint16_t *as1, uint32_t as2, uint32_t rs3);
v_int16_t __builtin_vald_s16(enum BlkSize blksize, int16_t *as1, uint32_t as2, uint32_t rs3);
v_uint32_t __builtin_vald_u32(enum BlkSize blksize, uint32_t *as1, uint32_t as2, uint32_t rs3);
v_int32_t __builtin_vald_s32(enum BlkSize blksize, int32_t *as1, uint32_t as2, uint32_t rs3);
v_float16_t __builtin_vald_f16(enum BlkSize blksize, float16_t *as1, uint32_t as2, uint32_t rs3);
v_float32_t __builtin_vald_f32(enum BlkSize blksize, float32_t *as1, uint32_t as2, uint32_t rs3);


//
// ------ VALD.blksize out:Vd, [inout:As1], in:As2
//
// @brief Represents VALD instruction.
//
v_uint8_t __builtin_vald_u8_without_rs3(enum BlkSize blksize, uint8_t *as1, uint32_t as2);
v_int8_t __builtin_vald_s8_without_rs3(enum BlkSize blksize, int8_t *as1, uint32_t as2);
v_uint16_t __builtin_vald_u16_without_rs3(enum BlkSize blksize, uint16_t *as1, uint32_t as2);
v_int16_t __builtin_vald_s16_without_rs3(enum BlkSize blksize, int16_t *as1, uint32_t as2);
v_uint32_t __builtin_vald_u32_without_rs3(enum BlkSize blksize, uint32_t *as1, uint32_t as2);
v_int32_t __builtin_vald_s32_without_rs3(enum BlkSize blksize, int32_t *as1, uint32_t as2);
v_float16_t __builtin_vald_f16_without_rs3(enum BlkSize blksize, float16_t *as1, uint32_t as2);
v_float32_t __builtin_vald_f32_without_rs3(enum BlkSize blksize, float32_t *as1, uint32_t as2);


//
// ------ VAST.blksize in:Vs1, [inout:As2], in:As3, in:Rs4, in:Pn
//
// @brief Represents VAST instruction.
//
void __builtin_vast_u8(enum BlkSize blksize, v_uint8_t vs1, uint8_t *as2, uint32_t as3, uint32_t rs4);
void __builtin_vast_s8(enum BlkSize blksize, v_int8_t vs1, int8_t *as2, uint32_t as3, uint32_t rs4);
void __builtin_vast_u16(enum BlkSize blksize, v_uint16_t vs1, uint16_t *as2, uint32_t as3, uint32_t rs4);
void __builtin_vast_s16(enum BlkSize blksize, v_int16_t vs1, int16_t *as2, uint32_t as3, uint32_t rs4);
void __builtin_vast_u32(enum BlkSize blksize, v_uint32_t vs1, uint32_t *as2, uint32_t as3, uint32_t rs4);
void __builtin_vast_s32(enum BlkSize blksize, v_int32_t vs1, int32_t *as2, uint32_t as3, uint32_t rs4);
void __builtin_vast_f16(enum BlkSize blksize, v_float16_t vs1, float16_t *as2, uint32_t as3, uint32_t rs4);
void __builtin_vast_f32(enum BlkSize blksize, v_float32_t vs1, float32_t *as2, uint32_t as3, uint32_t rs4);
void __builtin_vast_u8_with_pn(enum BlkSize blksize, v_uint8_t vs1, uint8_t *as2, uint32_t as3, uint32_t rs4, v_bool1_t pn);
void __builtin_vast_s8_with_pn(enum BlkSize blksize, v_int8_t vs1, int8_t *as2, uint32_t as3, uint32_t rs4, v_bool1_t pn);
void __builtin_vast_u16_with_pn(enum BlkSize blksize, v_uint16_t vs1, uint16_t *as2, uint32_t as3, uint32_t rs4, v_bool2_t pn);
void __builtin_vast_s16_with_pn(enum BlkSize blksize, v_int16_t vs1, int16_t *as2, uint32_t as3, uint32_t rs4, v_bool2_t pn);
void __builtin_vast_u32_with_pn(enum BlkSize blksize, v_uint32_t vs1, uint32_t *as2, uint32_t as3, uint32_t rs4, v_bool4_t pn);
void __builtin_vast_s32_with_pn(enum BlkSize blksize, v_int32_t vs1, int32_t *as2, uint32_t as3, uint32_t rs4, v_bool4_t pn);
void __builtin_vast_f16_with_pn(enum BlkSize blksize, v_float16_t vs1, float16_t *as2, uint32_t as3, uint32_t rs4, v_bool2_t pn);
void __builtin_vast_f32_with_pn(enum BlkSize blksize, v_float32_t vs1, float32_t *as2, uint32_t as3, uint32_t rs4, v_bool4_t pn);


//
// ------ VAST.blksize in:Vs1, [inout:As2], in:As3, in:Pn
//
// @brief Represents VAST instruction.
//
void __builtin_vast_u8_without_rs4(enum BlkSize blksize, v_uint8_t vs1, uint8_t *as2, uint32_t as3);
void __builtin_vast_s8_without_rs4(enum BlkSize blksize, v_int8_t vs1, int8_t *as2, uint32_t as3);
void __builtin_vast_u16_without_rs4(enum BlkSize blksize, v_uint16_t vs1, uint16_t *as2, uint32_t as3);
void __builtin_vast_s16_without_rs4(enum BlkSize blksize, v_int16_t vs1, int16_t *as2, uint32_t as3);
void __builtin_vast_u32_without_rs4(enum BlkSize blksize, v_uint32_t vs1, uint32_t *as2, uint32_t as3);
void __builtin_vast_s32_without_rs4(enum BlkSize blksize, v_int32_t vs1, int32_t *as2, uint32_t as3);
void __builtin_vast_f16_without_rs4(enum BlkSize blksize, v_float16_t vs1, float16_t *as2, uint32_t as3);
void __builtin_vast_f32_without_rs4(enum BlkSize blksize, v_float32_t vs1, float32_t *as2, uint32_t as3);
void __builtin_vast_u8_without_rs4_with_pn(enum BlkSize blksize, v_uint8_t vs1, uint8_t *as2, uint32_t as3, v_bool1_t pn);
void __builtin_vast_s8_without_rs4_with_pn(enum BlkSize blksize, v_int8_t vs1, int8_t *as2, uint32_t as3, v_bool1_t pn);
void __builtin_vast_u16_without_rs4_with_pn(enum BlkSize blksize, v_uint16_t vs1, uint16_t *as2, uint32_t as3, v_bool2_t pn);
void __builtin_vast_s16_without_rs4_with_pn(enum BlkSize blksize, v_int16_t vs1, int16_t *as2, uint32_t as3, v_bool2_t pn);
void __builtin_vast_u32_without_rs4_with_pn(enum BlkSize blksize, v_uint32_t vs1, uint32_t *as2, uint32_t as3, v_bool4_t pn);
void __builtin_vast_s32_without_rs4_with_pn(enum BlkSize blksize, v_int32_t vs1, int32_t *as2, uint32_t as3, v_bool4_t pn);
void __builtin_vast_f16_without_rs4_with_pn(enum BlkSize blksize, v_float16_t vs1, float16_t *as2, uint32_t as3, v_bool2_t pn);
void __builtin_vast_f32_without_rs4_with_pn(enum BlkSize blksize, v_float32_t vs1, float32_t *as2, uint32_t as3, v_bool4_t pn);


//
// ------ VILD.elesize out:Vd, [in:Rs1], in:Vs2, in:Pn
//
// @brief Represents VILD instruction.
//
v_uint8_t __builtin_vild_u8(uint8_t *rs1, v_int32_t vs2);
v_int8_t __builtin_vild_s8(int8_t *rs1, v_int32_t vs2);
v_uint16_t __builtin_vild_u16(uint16_t *rs1, v_int32_t vs2);
v_int16_t __builtin_vild_s16(int16_t *rs1, v_int32_t vs2);
v_uint32_t __builtin_vild_u32(uint32_t *rs1, v_int32_t vs2);
v_int32_t __builtin_vild_s32(int32_t *rs1, v_int32_t vs2);
v_float16_t __builtin_vild_f16(float16_t *rs1, v_int32_t vs2);
v_float32_t __builtin_vild_f32(float32_t *rs1, v_int32_t vs2);
v_uint8_t __builtin_vild_u8_with_pn(uint8_t *rs1, v_int32_t vs2, v_bool1_t pn);
v_int8_t __builtin_vild_s8_with_pn(int8_t *rs1, v_int32_t vs2, v_bool1_t pn);
v_uint16_t __builtin_vild_u16_with_pn(uint16_t *rs1, v_int32_t vs2, v_bool2_t pn);
v_int16_t __builtin_vild_s16_with_pn(int16_t *rs1, v_int32_t vs2, v_bool2_t pn);
v_uint32_t __builtin_vild_u32_with_pn(uint32_t *rs1, v_int32_t vs2, v_bool4_t pn);
v_int32_t __builtin_vild_s32_with_pn(int32_t *rs1, v_int32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vild_f16_with_pn(float16_t *rs1, v_int32_t vs2, v_bool2_t pn);
v_float32_t __builtin_vild_f32_with_pn(float32_t *rs1, v_int32_t vs2, v_bool4_t pn);


//
// ------ VIST.elesize in:Vs1, [in:Rs2], in:Vs3, in:Pn
//
// @brief Represents VIST instruction.
//
void __builtin_vist_u8(v_uint8_t vs1, uint8_t *rs2, v_int32_t vs3);
void __builtin_vist_s8(v_int8_t vs1, int8_t *rs2, v_int32_t vs3);
void __builtin_vist_u16(v_uint16_t vs1, uint16_t *rs2, v_int32_t vs3);
void __builtin_vist_s16(v_int16_t vs1, int16_t *rs2, v_int32_t vs3);
void __builtin_vist_u32(v_uint32_t vs1, uint32_t *rs2, v_int32_t vs3);
void __builtin_vist_s32(v_int32_t vs1, int32_t *rs2, v_int32_t vs3);
void __builtin_vist_f16(v_float16_t vs1, float16_t *rs2, v_int32_t vs3);
void __builtin_vist_f32(v_float32_t vs1, float32_t *rs2, v_int32_t vs3);
void __builtin_vist_u8_with_pn(v_uint8_t vs1, uint8_t *rs2, v_int32_t vs3, v_bool1_t pn);
void __builtin_vist_s8_with_pn(v_int8_t vs1, int8_t *rs2, v_int32_t vs3, v_bool1_t pn);
void __builtin_vist_u16_with_pn(v_uint16_t vs1, uint16_t *rs2, v_int32_t vs3, v_bool2_t pn);
void __builtin_vist_s16_with_pn(v_int16_t vs1, int16_t *rs2, v_int32_t vs3, v_bool2_t pn);
void __builtin_vist_u32_with_pn(v_uint32_t vs1, uint32_t *rs2, v_int32_t vs3, v_bool4_t pn);
void __builtin_vist_s32_with_pn(v_int32_t vs1, int32_t *rs2, v_int32_t vs3, v_bool4_t pn);
void __builtin_vist_f16_with_pn(v_float16_t vs1, float16_t *rs2, v_int32_t vs3, v_bool2_t pn);
void __builtin_vist_f32_with_pn(v_float32_t vs1, float32_t *rs2, v_int32_t vs3, v_bool4_t pn);


//
// ------ PLD out:Pd, [in:Rs1], #simm14
//
// @brief Represents PLD instruction.
//
v_bool1_t __builtin_pld_u8(uint8_t *rs1, int32_t simm14);
v_bool1_t __builtin_pld_s8(int8_t *rs1, int32_t simm14);
v_bool2_t __builtin_pld_u16(uint16_t *rs1, int32_t simm14);
v_bool2_t __builtin_pld_s16(int16_t *rs1, int32_t simm14);
v_bool4_t __builtin_pld_u32(uint32_t *rs1, int32_t simm14);
v_bool4_t __builtin_pld_s32(int32_t *rs1, int32_t simm14);
v_bool2_t __builtin_pld_f16(float16_t *rs1, int32_t simm14);
v_bool4_t __builtin_pld_f32(float32_t *rs1, int32_t simm14);


//
// ------ PST in:Ps1, [in:Rs2], #simm14
//
// @brief Represents PST instruction.
//
void __builtin_pst_u8(v_bool1_t ps1, uint8_t *rs2, int32_t simm14);
void __builtin_pst_s8(v_bool1_t ps1, int8_t *rs2, int32_t simm14);
void __builtin_pst_u16(v_bool2_t ps1, uint16_t *rs2, int32_t simm14);
void __builtin_pst_s16(v_bool2_t ps1, int16_t *rs2, int32_t simm14);
void __builtin_pst_u32(v_bool4_t ps1, uint32_t *rs2, int32_t simm14);
void __builtin_pst_s32(v_bool4_t ps1, int32_t *rs2, int32_t simm14);
void __builtin_pst_f16(v_bool2_t ps1, float16_t *rs2, int32_t simm14);
void __builtin_pst_f32(v_bool4_t ps1, float32_t *rs2, int32_t simm14);


//
// ------ VADD.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VADD instruction.
//
v_float32_t __builtin_vadd_f32(v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vadd_f16(v_float16_t vs1, v_float16_t vs2);
v_int32_t __builtin_vadd_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vadd_u32(v_uint32_t vs1, v_uint32_t vs2);
v_float32_t __builtin_vadd_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vadd_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_int32_t __builtin_vadd_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vadd_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VADDH.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VADDH instruction.
//
v_int32_t __builtin_vaddh_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vaddh_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vaddh_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vaddh_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VSUB.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VSUB instruction.
//
v_float32_t __builtin_vsub_f32(v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vsub_f16(v_float16_t vs1, v_float16_t vs2);
v_int32_t __builtin_vsub_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vsub_u32(v_uint32_t vs1, v_uint32_t vs2);
v_float32_t __builtin_vsub_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vsub_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_int32_t __builtin_vsub_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vsub_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VSUBH.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VSUBH instruction.
//
v_int32_t __builtin_vsubh_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vsubh_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vsubh_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vsubh_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VMUL.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMUL instruction.
//
v_float32_t __builtin_vmul_f32(v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vmul_f16(v_float16_t vs1, v_float16_t vs2);
v_int32_t __builtin_vmul_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vmul_u32(v_uint32_t vs1, v_uint32_t vs2);
v_float32_t __builtin_vmul_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vmul_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_int32_t __builtin_vmul_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vmul_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VMULH.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMULH instruction.
//
v_int32_t __builtin_vmulh_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vmulh_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vmulh_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vmulh_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VDIV.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VDIV instruction.
//
v_float32_t __builtin_vdiv_f32(v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vdiv_f16(v_float16_t vs1, v_float16_t vs2);
v_int32_t __builtin_vdiv_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vdiv_u32(v_uint32_t vs1, v_uint32_t vs2);
v_float32_t __builtin_vdiv_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vdiv_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_int32_t __builtin_vdiv_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vdiv_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VMACC.dtype inout:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMACC instruction.
//
v_float32_t __builtin_vmacc_f32(v_float32_t vd, v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vmacc_f16(v_float16_t vd, v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vmacc_f32_with_pn(v_float32_t vd, v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vmacc_f16_with_pn(v_float16_t vd, v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VNMACC.dtype inout:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VNMACC instruction.
//
v_float32_t __builtin_vnmacc_f32(v_float32_t vd, v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vnmacc_f16(v_float16_t vd, v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vnmacc_f32_with_pn(v_float32_t vd, v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vnmacc_f16_with_pn(v_float16_t vd, v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VMSAC.dtype inout:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMSAC instruction.
//
v_float32_t __builtin_vmsac_f32(v_float32_t vd, v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vmsac_f16(v_float16_t vd, v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vmsac_f32_with_pn(v_float32_t vd, v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vmsac_f16_with_pn(v_float16_t vd, v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VNMSAC.dtype inout:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VNMSAC instruction.
//
v_float32_t __builtin_vnmsac_f32(v_float32_t vd, v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vnmsac_f16(v_float16_t vd, v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vnmsac_f32_with_pn(v_float32_t vd, v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vnmsac_f16_with_pn(v_float16_t vd, v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VMADD.dtype inout:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMADD instruction.
//
v_float32_t __builtin_vmadd_f32(v_float32_t vd, v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vmadd_f16(v_float16_t vd, v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vmadd_f32_with_pn(v_float32_t vd, v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vmadd_f16_with_pn(v_float16_t vd, v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VNMADD.dtype inout:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VNMADD instruction.
//
v_float32_t __builtin_vnmadd_f32(v_float32_t vd, v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vnmadd_f16(v_float16_t vd, v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vnmadd_f32_with_pn(v_float32_t vd, v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vnmadd_f16_with_pn(v_float16_t vd, v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VMSUB.dtype inout:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMSUB instruction.
//
v_float32_t __builtin_vmsub_f32(v_float32_t vd, v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vmsub_f16(v_float16_t vd, v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vmsub_f32_with_pn(v_float32_t vd, v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vmsub_f16_with_pn(v_float16_t vd, v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VNMSUB.dtype inout:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VNMSUB instruction.
//
v_float32_t __builtin_vnmsub_f32(v_float32_t vd, v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vnmsub_f16(v_float16_t vd, v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vnmsub_f32_with_pn(v_float32_t vd, v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vnmsub_f16_with_pn(v_float16_t vd, v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VREM.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VREM instruction.
//
v_int32_t __builtin_vrem_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vrem_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vrem_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vrem_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VRECIP.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VRECIP instruction.
//
v_float32_t __builtin_vrecip_f32(v_float32_t vs1);
v_float16_t __builtin_vrecip_f16(v_float16_t vs1);
v_float32_t __builtin_vrecip_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vrecip_f16_with_pn(v_float16_t vs1, v_bool2_t pn);


//
// ------ VSQRT.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VSQRT instruction.
//
v_float32_t __builtin_vsqrt_f32(v_float32_t vs1);
v_float16_t __builtin_vsqrt_f16(v_float16_t vs1);
v_float32_t __builtin_vsqrt_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vsqrt_f16_with_pn(v_float16_t vs1, v_bool2_t pn);


//
// ------ VABS.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VABS instruction.
//
v_float32_t __builtin_vabs_f32(v_float32_t vs1);
v_float16_t __builtin_vabs_f16(v_float16_t vs1);
v_int32_t __builtin_vabs_s32(v_int32_t vs1);
v_float32_t __builtin_vabs_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vabs_f16_with_pn(v_float16_t vs1, v_bool2_t pn);
v_int32_t __builtin_vabs_s32_with_pn(v_int32_t vs1, v_bool4_t pn);


//
// ------ VNEG.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VNEG instruction.
//
v_float32_t __builtin_vneg_f32(v_float32_t vs1);
v_float16_t __builtin_vneg_f16(v_float16_t vs1);
v_int32_t __builtin_vneg_s32(v_int32_t vs1);
v_float32_t __builtin_vneg_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vneg_f16_with_pn(v_float16_t vs1, v_bool2_t pn);
v_int32_t __builtin_vneg_s32_with_pn(v_int32_t vs1, v_bool4_t pn);


//
// ------ VADDS.dtype out:Vd, in:Vs1, in:Rs2, in:Pn
//
// @brief Represents VADDS instruction.
//
v_float32_t __builtin_vadds_f32(v_float32_t vs1, float32_t rs2);
v_float16_t __builtin_vadds_f16(v_float16_t vs1, float16_t rs2);
v_int32_t __builtin_vadds_s32(v_int32_t vs1, int32_t rs2);
v_uint32_t __builtin_vadds_u32(v_uint32_t vs1, uint32_t rs2);
v_float32_t __builtin_vadds_f32_with_pn(v_float32_t vs1, float32_t rs2, v_bool4_t pn);
v_float16_t __builtin_vadds_f16_with_pn(v_float16_t vs1, float16_t rs2, v_bool2_t pn);
v_int32_t __builtin_vadds_s32_with_pn(v_int32_t vs1, int32_t rs2, v_bool4_t pn);
v_uint32_t __builtin_vadds_u32_with_pn(v_uint32_t vs1, uint32_t rs2, v_bool4_t pn);


//
// ------ VSUBS.dtype out:Vd, in:Vs1, in:Rs2, in:Pn
//
// @brief Represents VSUBS instruction.
//
v_float32_t __builtin_vsubs_f32(v_float32_t vs1, float32_t rs2);
v_float16_t __builtin_vsubs_f16(v_float16_t vs1, float16_t rs2);
v_int32_t __builtin_vsubs_s32(v_int32_t vs1, int32_t rs2);
v_uint32_t __builtin_vsubs_u32(v_uint32_t vs1, uint32_t rs2);
v_float32_t __builtin_vsubs_f32_with_pn(v_float32_t vs1, float32_t rs2, v_bool4_t pn);
v_float16_t __builtin_vsubs_f16_with_pn(v_float16_t vs1, float16_t rs2, v_bool2_t pn);
v_int32_t __builtin_vsubs_s32_with_pn(v_int32_t vs1, int32_t rs2, v_bool4_t pn);
v_uint32_t __builtin_vsubs_u32_with_pn(v_uint32_t vs1, uint32_t rs2, v_bool4_t pn);


//
// ------ VMULS.dtype out:Vd, in:Vs1, in:Rs2, in:Pn
//
// @brief Represents VMULS instruction.
//
v_float32_t __builtin_vmuls_f32(v_float32_t vs1, float32_t rs2);
v_float16_t __builtin_vmuls_f16(v_float16_t vs1, float16_t rs2);
v_int32_t __builtin_vmuls_s32(v_int32_t vs1, int32_t rs2);
v_uint32_t __builtin_vmuls_u32(v_uint32_t vs1, uint32_t rs2);
v_float32_t __builtin_vmuls_f32_with_pn(v_float32_t vs1, float32_t rs2, v_bool4_t pn);
v_float16_t __builtin_vmuls_f16_with_pn(v_float16_t vs1, float16_t rs2, v_bool2_t pn);
v_int32_t __builtin_vmuls_s32_with_pn(v_int32_t vs1, int32_t rs2, v_bool4_t pn);
v_uint32_t __builtin_vmuls_u32_with_pn(v_uint32_t vs1, uint32_t rs2, v_bool4_t pn);


//
// ------ VMULHS.dtype out:Vd, in:Vs1, in:Rs2, in:Pn
//
// @brief Represents VMULHS instruction.
//
v_int32_t __builtin_vmulhs_s32(v_int32_t vs1, int32_t rs2);
v_uint32_t __builtin_vmulhs_u32(v_uint32_t vs1, uint32_t rs2);
v_int32_t __builtin_vmulhs_s32_with_pn(v_int32_t vs1, int32_t rs2, v_bool4_t pn);
v_uint32_t __builtin_vmulhs_u32_with_pn(v_uint32_t vs1, uint32_t rs2, v_bool4_t pn);


//
// ------ VDIVS.dtype out:Vd, in:Vs1, in:Rs2, in:Pn
//
// @brief Represents VDIVS instruction.
//
v_float32_t __builtin_vdivs_f32(v_float32_t vs1, float32_t rs2);
v_float16_t __builtin_vdivs_f16(v_float16_t vs1, float16_t rs2);
v_int32_t __builtin_vdivs_s32(v_int32_t vs1, int32_t rs2);
v_uint32_t __builtin_vdivs_u32(v_uint32_t vs1, uint32_t rs2);
v_float32_t __builtin_vdivs_f32_with_pn(v_float32_t vs1, float32_t rs2, v_bool4_t pn);
v_float16_t __builtin_vdivs_f16_with_pn(v_float16_t vs1, float16_t rs2, v_bool2_t pn);
v_int32_t __builtin_vdivs_s32_with_pn(v_int32_t vs1, int32_t rs2, v_bool4_t pn);
v_uint32_t __builtin_vdivs_u32_with_pn(v_uint32_t vs1, uint32_t rs2, v_bool4_t pn);


//
// ------ VCVTF2I.conv_type.rnd.pos out:Vd, in:Vs1
//
// @brief Represents VCVTF2I instruction.
//
v_int32_t __builtin_vcvtf2i_f162s32(enum Rnd rnd, enum Pos pos, v_float16_t vs1);
v_int16_t __builtin_vcvtf2i_f322s16(enum Rnd rnd, enum Pos pos, v_float32_t vs1);
v_uint16_t __builtin_vcvtf2i_f322u16(enum Rnd rnd, enum Pos pos, v_float32_t vs1);
v_int8_t __builtin_vcvtf2i_f162s8(enum Rnd rnd, enum Pos pos, v_float16_t vs1);
v_uint8_t __builtin_vcvtf2i_f162u8(enum Rnd rnd, enum Pos pos, v_float16_t vs1);


//
// ------ VCVTF2I.conv_type.rnd out:Vd, in:Vs1
//
// @brief Represents VCVTF2I instruction.
//
v_int16_t __builtin_vcvtf2i_f162s16(enum Rnd rnd, v_float16_t vs1);
v_int32_t __builtin_vcvtf2i_f322s32(enum Rnd rnd, v_float32_t vs1);
v_uint32_t __builtin_vcvtf2i_f322u32(enum Rnd rnd, v_float32_t vs1);
v_uint16_t __builtin_vcvtf2i_f162u16(enum Rnd rnd, v_float16_t vs1);


//
// ------ VCVTI2F.conv_type.rnd.pos out:Vd, in:Vs1
//
// @brief Represents VCVTI2F instruction.
//
v_float16_t __builtin_vcvti2f_u82f16(enum Rnd rnd, enum Pos pos, v_uint8_t vs1);
v_float16_t __builtin_vcvti2f_s82f16(enum Rnd rnd, enum Pos pos, v_int8_t vs1);
v_float32_t __builtin_vcvti2f_u162f32(enum Rnd rnd, enum Pos pos, v_uint16_t vs1);
v_float32_t __builtin_vcvti2f_s162f32(enum Rnd rnd, enum Pos pos, v_int16_t vs1);


//
// ------ VCVTI2F.conv_type.rnd out:Vd, in:Vs1
//
// @brief Represents VCVTI2F instruction.
//
v_float32_t __builtin_vcvti2f_u322f32(enum Rnd rnd, v_uint32_t vs1);
v_float32_t __builtin_vcvti2f_s322f32(enum Rnd rnd, v_int32_t vs1);
v_float16_t __builtin_vcvti2f_u162f16(enum Rnd rnd, v_uint16_t vs1);
v_float16_t __builtin_vcvti2f_s162f16(enum Rnd rnd, v_int16_t vs1);


//
// ------ VCVTF2F.conv_type.rnd.pos out:Vd, in:Vs1
//
// @brief Represents VCVTF2F instruction.
//
v_float32_t __builtin_vcvtf2f_f162f32(enum Rnd rnd, enum Pos pos, v_float16_t vs1);
v_float16_t __builtin_vcvtf2f_f322f16(enum Rnd rnd, v_float32_t vs_hi, v_float32_t vs_lo);


//
// ------ VCVTI2I.conv_type.pos out:Vd, in:Vs1
//
// @brief Represents VCVTI2I instruction.
//
v_uint16_t __builtin_vcvti2i_u322u16(enum Pos pos, v_uint32_t vs1);
v_int16_t __builtin_vcvti2i_s322s16(enum Pos pos, v_int32_t vs1);
v_uint8_t __builtin_vcvti2i_u162u8(enum Pos pos, v_uint16_t vs1);
v_int8_t __builtin_vcvti2i_s162s8(enum Pos pos, v_int16_t vs1);
v_uint32_t __builtin_vcvti2i_u162u32(enum Pos pos, v_uint16_t vs1);
v_int32_t __builtin_vcvti2i_s162s32(enum Pos pos, v_int16_t vs1);
v_uint16_t __builtin_vcvti2i_u82u16(enum Pos pos, v_uint8_t vs1);
v_int16_t __builtin_vcvti2i_s82s16(enum Pos pos, v_int8_t vs1);


//
// ------ VAND out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VAND instruction.
//
v_uint8_t __builtin_vand_u8(v_uint8_t vs1, v_uint8_t vs2);
v_int8_t __builtin_vand_s8(v_int8_t vs1, v_int8_t vs2);
v_uint16_t __builtin_vand_u16(v_uint16_t vs1, v_uint16_t vs2);
v_int16_t __builtin_vand_s16(v_int16_t vs1, v_int16_t vs2);
v_uint32_t __builtin_vand_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vand_s32(v_int32_t vs1, v_int32_t vs2);
v_float16_t __builtin_vand_f16(v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vand_f32(v_float32_t vs1, v_float32_t vs2);
v_uint8_t __builtin_vand_u8_with_pn(v_uint8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_int8_t __builtin_vand_s8_with_pn(v_int8_t vs1, v_int8_t vs2, v_bool1_t pn);
v_uint16_t __builtin_vand_u16_with_pn(v_uint16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_int16_t __builtin_vand_s16_with_pn(v_int16_t vs1, v_int16_t vs2, v_bool2_t pn);
v_uint32_t __builtin_vand_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);
v_int32_t __builtin_vand_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vand_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_float32_t __builtin_vand_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);


//
// ------ VOR out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VOR instruction.
//
v_uint8_t __builtin_vor_u8(v_uint8_t vs1, v_uint8_t vs2);
v_int8_t __builtin_vor_s8(v_int8_t vs1, v_int8_t vs2);
v_uint16_t __builtin_vor_u16(v_uint16_t vs1, v_uint16_t vs2);
v_int16_t __builtin_vor_s16(v_int16_t vs1, v_int16_t vs2);
v_uint32_t __builtin_vor_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vor_s32(v_int32_t vs1, v_int32_t vs2);
v_float16_t __builtin_vor_f16(v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vor_f32(v_float32_t vs1, v_float32_t vs2);
v_uint8_t __builtin_vor_u8_with_pn(v_uint8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_int8_t __builtin_vor_s8_with_pn(v_int8_t vs1, v_int8_t vs2, v_bool1_t pn);
v_uint16_t __builtin_vor_u16_with_pn(v_uint16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_int16_t __builtin_vor_s16_with_pn(v_int16_t vs1, v_int16_t vs2, v_bool2_t pn);
v_uint32_t __builtin_vor_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);
v_int32_t __builtin_vor_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vor_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_float32_t __builtin_vor_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);


//
// ------ VXOR out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VXOR instruction.
//
v_uint8_t __builtin_vxor_u8(v_uint8_t vs1, v_uint8_t vs2);
v_int8_t __builtin_vxor_s8(v_int8_t vs1, v_int8_t vs2);
v_uint16_t __builtin_vxor_u16(v_uint16_t vs1, v_uint16_t vs2);
v_int16_t __builtin_vxor_s16(v_int16_t vs1, v_int16_t vs2);
v_uint32_t __builtin_vxor_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vxor_s32(v_int32_t vs1, v_int32_t vs2);
v_float16_t __builtin_vxor_f16(v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vxor_f32(v_float32_t vs1, v_float32_t vs2);
v_uint8_t __builtin_vxor_u8_with_pn(v_uint8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_int8_t __builtin_vxor_s8_with_pn(v_int8_t vs1, v_int8_t vs2, v_bool1_t pn);
v_uint16_t __builtin_vxor_u16_with_pn(v_uint16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_int16_t __builtin_vxor_s16_with_pn(v_int16_t vs1, v_int16_t vs2, v_bool2_t pn);
v_uint32_t __builtin_vxor_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);
v_int32_t __builtin_vxor_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vxor_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_float32_t __builtin_vxor_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);


//
// ------ VINV out:Vd, in:Vs1, in:Pn
//
// @brief Represents VINV instruction.
//
v_uint8_t __builtin_vinv_u8(v_uint8_t vs1);
v_int8_t __builtin_vinv_s8(v_int8_t vs1);
v_uint16_t __builtin_vinv_u16(v_uint16_t vs1);
v_int16_t __builtin_vinv_s16(v_int16_t vs1);
v_uint32_t __builtin_vinv_u32(v_uint32_t vs1);
v_int32_t __builtin_vinv_s32(v_int32_t vs1);
v_float16_t __builtin_vinv_f16(v_float16_t vs1);
v_float32_t __builtin_vinv_f32(v_float32_t vs1);
v_uint8_t __builtin_vinv_u8_with_pn(v_uint8_t vs1, v_bool1_t pn);
v_int8_t __builtin_vinv_s8_with_pn(v_int8_t vs1, v_bool1_t pn);
v_uint16_t __builtin_vinv_u16_with_pn(v_uint16_t vs1, v_bool2_t pn);
v_int16_t __builtin_vinv_s16_with_pn(v_int16_t vs1, v_bool2_t pn);
v_uint32_t __builtin_vinv_u32_with_pn(v_uint32_t vs1, v_bool4_t pn);
v_int32_t __builtin_vinv_s32_with_pn(v_int32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vinv_f16_with_pn(v_float16_t vs1, v_bool2_t pn);
v_float32_t __builtin_vinv_f32_with_pn(v_float32_t vs1, v_bool4_t pn);


//
// ------ VEQ.dtype out:Pd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VEQ instruction.
//
v_bool4_t __builtin_veq_f32(v_float32_t vs1, v_float32_t vs2);
v_bool2_t __builtin_veq_f16(v_float16_t vs1, v_float16_t vs2);
v_bool4_t __builtin_veq_s32(v_int32_t vs1, v_int32_t vs2);
v_bool4_t __builtin_veq_u32(v_uint32_t vs1, v_uint32_t vs2);
v_bool4_t __builtin_veq_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_bool2_t __builtin_veq_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_bool4_t __builtin_veq_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_bool4_t __builtin_veq_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VNEQ.dtype out:Pd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VNEQ instruction.
//
v_bool4_t __builtin_vneq_f32(v_float32_t vs1, v_float32_t vs2);
v_bool2_t __builtin_vneq_f16(v_float16_t vs1, v_float16_t vs2);
v_bool4_t __builtin_vneq_s32(v_int32_t vs1, v_int32_t vs2);
v_bool4_t __builtin_vneq_u32(v_uint32_t vs1, v_uint32_t vs2);
v_bool4_t __builtin_vneq_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_bool2_t __builtin_vneq_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_bool4_t __builtin_vneq_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_bool4_t __builtin_vneq_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VLT.dtype out:Pd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VLT instruction.
//
v_bool4_t __builtin_vlt_f32(v_float32_t vs1, v_float32_t vs2);
v_bool2_t __builtin_vlt_f16(v_float16_t vs1, v_float16_t vs2);
v_bool4_t __builtin_vlt_s32(v_int32_t vs1, v_int32_t vs2);
v_bool4_t __builtin_vlt_u32(v_uint32_t vs1, v_uint32_t vs2);
v_bool4_t __builtin_vlt_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_bool2_t __builtin_vlt_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_bool4_t __builtin_vlt_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_bool4_t __builtin_vlt_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VLE.dtype out:Pd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VLE instruction.
//
v_bool4_t __builtin_vle_f32(v_float32_t vs1, v_float32_t vs2);
v_bool2_t __builtin_vle_f16(v_float16_t vs1, v_float16_t vs2);
v_bool4_t __builtin_vle_s32(v_int32_t vs1, v_int32_t vs2);
v_bool4_t __builtin_vle_u32(v_uint32_t vs1, v_uint32_t vs2);
v_bool4_t __builtin_vle_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_bool2_t __builtin_vle_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_bool4_t __builtin_vle_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_bool4_t __builtin_vle_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VMAX.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMAX instruction.
//
v_float32_t __builtin_vmax_f32(v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vmax_f16(v_float16_t vs1, v_float16_t vs2);
v_int32_t __builtin_vmax_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vmax_u32(v_uint32_t vs1, v_uint32_t vs2);
v_float32_t __builtin_vmax_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vmax_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_int32_t __builtin_vmax_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vmax_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VMIN.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMIN instruction.
//
v_float32_t __builtin_vmin_f32(v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vmin_f16(v_float16_t vs1, v_float16_t vs2);
v_int32_t __builtin_vmin_s32(v_int32_t vs1, v_int32_t vs2);
v_uint32_t __builtin_vmin_u32(v_uint32_t vs1, v_uint32_t vs2);
v_float32_t __builtin_vmin_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vmin_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_int32_t __builtin_vmin_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_uint32_t __builtin_vmin_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VSEL.elesize out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VSEL instruction.
//
v_uint8_t __builtin_vsel_u8(v_uint8_t vs1, v_uint8_t vs2);
v_int8_t __builtin_vsel_s8(v_int8_t vs1, v_int8_t vs2);
v_uint16_t __builtin_vsel_u16(v_uint16_t vs1, v_uint16_t vs2);
v_int16_t __builtin_vsel_s16(v_int16_t vs1, v_int16_t vs2);
v_uint32_t __builtin_vsel_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vsel_s32(v_int32_t vs1, v_int32_t vs2);
v_float16_t __builtin_vsel_f16(v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vsel_f32(v_float32_t vs1, v_float32_t vs2);
v_uint8_t __builtin_vsel_u8_with_pn(v_uint8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_int8_t __builtin_vsel_s8_with_pn(v_int8_t vs1, v_int8_t vs2, v_bool1_t pn);
v_uint16_t __builtin_vsel_u16_with_pn(v_uint16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_int16_t __builtin_vsel_s16_with_pn(v_int16_t vs1, v_int16_t vs2, v_bool2_t pn);
v_uint32_t __builtin_vsel_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);
v_int32_t __builtin_vsel_s32_with_pn(v_int32_t vs1, v_int32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vsel_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);
v_float32_t __builtin_vsel_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);


//
// ------ VSLL.elesize out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VSLL instruction.
//
v_uint8_t __builtin_vsll_u8(v_uint8_t vs1, v_uint8_t vs2);
v_int8_t __builtin_vsll_s8(v_int8_t vs1, v_uint8_t vs2);
v_uint16_t __builtin_vsll_u16(v_uint16_t vs1, v_uint16_t vs2);
v_int16_t __builtin_vsll_s16(v_int16_t vs1, v_uint16_t vs2);
v_uint32_t __builtin_vsll_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vsll_s32(v_int32_t vs1, v_uint32_t vs2);
v_uint8_t __builtin_vsll_u8_with_pn(v_uint8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_int8_t __builtin_vsll_s8_with_pn(v_int8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_uint16_t __builtin_vsll_u16_with_pn(v_uint16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_int16_t __builtin_vsll_s16_with_pn(v_int16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_uint32_t __builtin_vsll_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);
v_int32_t __builtin_vsll_s32_with_pn(v_int32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VSRL.elesize out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VSRL instruction.
//
v_uint8_t __builtin_vsrl_u8(v_uint8_t vs1, v_uint8_t vs2);
v_int8_t __builtin_vsrl_s8(v_int8_t vs1, v_uint8_t vs2);
v_uint16_t __builtin_vsrl_u16(v_uint16_t vs1, v_uint16_t vs2);
v_int16_t __builtin_vsrl_s16(v_int16_t vs1, v_uint16_t vs2);
v_uint32_t __builtin_vsrl_u32(v_uint32_t vs1, v_uint32_t vs2);
v_int32_t __builtin_vsrl_s32(v_int32_t vs1, v_uint32_t vs2);
v_uint8_t __builtin_vsrl_u8_with_pn(v_uint8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_int8_t __builtin_vsrl_s8_with_pn(v_int8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_uint16_t __builtin_vsrl_u16_with_pn(v_uint16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_int16_t __builtin_vsrl_s16_with_pn(v_int16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_uint32_t __builtin_vsrl_u32_with_pn(v_uint32_t vs1, v_uint32_t vs2, v_bool4_t pn);
v_int32_t __builtin_vsrl_s32_with_pn(v_int32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VSRA.elesize out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VSRA instruction.
//
v_int8_t __builtin_vsra_s8(v_int8_t vs1, v_uint8_t vs2);
v_int16_t __builtin_vsra_s16(v_int16_t vs1, v_uint16_t vs2);
v_int32_t __builtin_vsra_s32(v_int32_t vs1, v_uint32_t vs2);
v_int8_t __builtin_vsra_s8_with_pn(v_int8_t vs1, v_uint8_t vs2, v_bool1_t pn);
v_int16_t __builtin_vsra_s16_with_pn(v_int16_t vs1, v_uint16_t vs2, v_bool2_t pn);
v_int32_t __builtin_vsra_s32_with_pn(v_int32_t vs1, v_uint32_t vs2, v_bool4_t pn);


//
// ------ VSLLS.elesize out:Vd, in:Vs1, in:Rs2, in:Pn
//
// @brief Represents VSLLS instruction.
//
v_uint8_t __builtin_vslls_u8(v_uint8_t vs1, uint8_t rs2);
v_int8_t __builtin_vslls_s8(v_int8_t vs1, uint8_t rs2);
v_uint16_t __builtin_vslls_u16(v_uint16_t vs1, uint16_t rs2);
v_int16_t __builtin_vslls_s16(v_int16_t vs1, uint16_t rs2);
v_uint32_t __builtin_vslls_u32(v_uint32_t vs1, uint32_t rs2);
v_int32_t __builtin_vslls_s32(v_int32_t vs1, uint32_t rs2);
v_uint8_t __builtin_vslls_u8_with_pn(v_uint8_t vs1, uint8_t rs2, v_bool1_t pn);
v_int8_t __builtin_vslls_s8_with_pn(v_int8_t vs1, uint8_t rs2, v_bool1_t pn);
v_uint16_t __builtin_vslls_u16_with_pn(v_uint16_t vs1, uint16_t rs2, v_bool2_t pn);
v_int16_t __builtin_vslls_s16_with_pn(v_int16_t vs1, uint16_t rs2, v_bool2_t pn);
v_uint32_t __builtin_vslls_u32_with_pn(v_uint32_t vs1, uint32_t rs2, v_bool4_t pn);
v_int32_t __builtin_vslls_s32_with_pn(v_int32_t vs1, uint32_t rs2, v_bool4_t pn);


//
// ------ VSRLS.elesize out:Vd, in:Vs1, in:Rs2, in:Pn
//
// @brief Represents VSRLS instruction.
//
v_uint8_t __builtin_vsrls_u8(v_uint8_t vs1, uint8_t rs2);
v_int8_t __builtin_vsrls_s8(v_int8_t vs1, uint8_t rs2);
v_uint16_t __builtin_vsrls_u16(v_uint16_t vs1, uint16_t rs2);
v_int16_t __builtin_vsrls_s16(v_int16_t vs1, uint16_t rs2);
v_uint32_t __builtin_vsrls_u32(v_uint32_t vs1, uint32_t rs2);
v_int32_t __builtin_vsrls_s32(v_int32_t vs1, uint32_t rs2);
v_uint8_t __builtin_vsrls_u8_with_pn(v_uint8_t vs1, uint8_t rs2, v_bool1_t pn);
v_int8_t __builtin_vsrls_s8_with_pn(v_int8_t vs1, uint8_t rs2, v_bool1_t pn);
v_uint16_t __builtin_vsrls_u16_with_pn(v_uint16_t vs1, uint16_t rs2, v_bool2_t pn);
v_int16_t __builtin_vsrls_s16_with_pn(v_int16_t vs1, uint16_t rs2, v_bool2_t pn);
v_uint32_t __builtin_vsrls_u32_with_pn(v_uint32_t vs1, uint32_t rs2, v_bool4_t pn);
v_int32_t __builtin_vsrls_s32_with_pn(v_int32_t vs1, uint32_t rs2, v_bool4_t pn);


//
// ------ VSRAS.elesize out:Vd, in:Vs1, in:Rs2, in:Pn
//
// @brief Represents VSRAS instruction.
//
v_int8_t __builtin_vsras_s8(v_int8_t vs1, uint8_t rs2);
v_int16_t __builtin_vsras_s16(v_int16_t vs1, uint16_t rs2);
v_int32_t __builtin_vsras_s32(v_int32_t vs1, uint32_t rs2);
v_int8_t __builtin_vsras_s8_with_pn(v_int8_t vs1, uint8_t rs2, v_bool1_t pn);
v_int16_t __builtin_vsras_s16_with_pn(v_int16_t vs1, uint16_t rs2, v_bool2_t pn);
v_int32_t __builtin_vsras_s32_with_pn(v_int32_t vs1, uint32_t rs2, v_bool4_t pn);


//
// ------ VSLLI.elesize out:Vd, in:Vs1, #uimm5, in:Pn
//
// @brief Represents VSLLI instruction.
//
v_uint8_t __builtin_vslli_u8(v_uint8_t vs1, uint32_t uimm5);
v_int8_t __builtin_vslli_s8(v_int8_t vs1, uint32_t uimm5);
v_uint16_t __builtin_vslli_u16(v_uint16_t vs1, uint32_t uimm5);
v_int16_t __builtin_vslli_s16(v_int16_t vs1, uint32_t uimm5);
v_uint32_t __builtin_vslli_u32(v_uint32_t vs1, uint32_t uimm5);
v_int32_t __builtin_vslli_s32(v_int32_t vs1, uint32_t uimm5);
v_uint8_t __builtin_vslli_u8_with_pn(v_uint8_t vs1, uint32_t uimm5, v_bool1_t pn);
v_int8_t __builtin_vslli_s8_with_pn(v_int8_t vs1, uint32_t uimm5, v_bool1_t pn);
v_uint16_t __builtin_vslli_u16_with_pn(v_uint16_t vs1, uint32_t uimm5, v_bool2_t pn);
v_int16_t __builtin_vslli_s16_with_pn(v_int16_t vs1, uint32_t uimm5, v_bool2_t pn);
v_uint32_t __builtin_vslli_u32_with_pn(v_uint32_t vs1, uint32_t uimm5, v_bool4_t pn);
v_int32_t __builtin_vslli_s32_with_pn(v_int32_t vs1, uint32_t uimm5, v_bool4_t pn);


//
// ------ VSRLI.elesize out:Vd, in:Vs1, #uimm5, in:Pn
//
// @brief Represents VSRLI instruction.
//
v_uint8_t __builtin_vsrli_u8(v_uint8_t vs1, uint32_t uimm5);
v_int8_t __builtin_vsrli_s8(v_int8_t vs1, uint32_t uimm5);
v_uint16_t __builtin_vsrli_u16(v_uint16_t vs1, uint32_t uimm5);
v_int16_t __builtin_vsrli_s16(v_int16_t vs1, uint32_t uimm5);
v_uint32_t __builtin_vsrli_u32(v_uint32_t vs1, uint32_t uimm5);
v_int32_t __builtin_vsrli_s32(v_int32_t vs1, uint32_t uimm5);
v_uint8_t __builtin_vsrli_u8_with_pn(v_uint8_t vs1, uint32_t uimm5, v_bool1_t pn);
v_int8_t __builtin_vsrli_s8_with_pn(v_int8_t vs1, uint32_t uimm5, v_bool1_t pn);
v_uint16_t __builtin_vsrli_u16_with_pn(v_uint16_t vs1, uint32_t uimm5, v_bool2_t pn);
v_int16_t __builtin_vsrli_s16_with_pn(v_int16_t vs1, uint32_t uimm5, v_bool2_t pn);
v_uint32_t __builtin_vsrli_u32_with_pn(v_uint32_t vs1, uint32_t uimm5, v_bool4_t pn);
v_int32_t __builtin_vsrli_s32_with_pn(v_int32_t vs1, uint32_t uimm5, v_bool4_t pn);


//
// ------ VSRAI.elesize out:Vd, in:Vs1, #uimm5, in:Pn
//
// @brief Represents VSRAI instruction.
//
v_int8_t __builtin_vsrai_s8(v_int8_t vs1, uint32_t uimm5);
v_int16_t __builtin_vsrai_s16(v_int16_t vs1, uint32_t uimm5);
v_int32_t __builtin_vsrai_s32(v_int32_t vs1, uint32_t uimm5);
v_int8_t __builtin_vsrai_s8_with_pn(v_int8_t vs1, uint32_t uimm5, v_bool1_t pn);
v_int16_t __builtin_vsrai_s16_with_pn(v_int16_t vs1, uint32_t uimm5, v_bool2_t pn);
v_int32_t __builtin_vsrai_s32_with_pn(v_int32_t vs1, uint32_t uimm5, v_bool4_t pn);


//
// ------ VRSUM.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VRSUM instruction.
//
v_float32_t __builtin_vrsum_f32(v_float32_t vs1);
v_float16_t __builtin_vrsum_f16(v_float16_t vs1);
v_int32_t __builtin_vrsum_s32(v_int32_t vs1);
v_uint32_t __builtin_vrsum_u32(v_uint32_t vs1);
v_float32_t __builtin_vrsum_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vrsum_f16_with_pn(v_float16_t vs1, v_bool2_t pn);
v_int32_t __builtin_vrsum_s32_with_pn(v_int32_t vs1, v_bool4_t pn);
v_uint32_t __builtin_vrsum_u32_with_pn(v_uint32_t vs1, v_bool4_t pn);


//
// ------ VRMAX.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VRMAX instruction.
//
v_float32_t __builtin_vrmax_f32(v_float32_t vs1);
v_float16_t __builtin_vrmax_f16(v_float16_t vs1);
v_int32_t __builtin_vrmax_s32(v_int32_t vs1);
v_uint32_t __builtin_vrmax_u32(v_uint32_t vs1);
v_float32_t __builtin_vrmax_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vrmax_f16_with_pn(v_float16_t vs1, v_bool2_t pn);
v_int32_t __builtin_vrmax_s32_with_pn(v_int32_t vs1, v_bool4_t pn);
v_uint32_t __builtin_vrmax_u32_with_pn(v_uint32_t vs1, v_bool4_t pn);


//
// ------ VRMIN.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VRMIN instruction.
//
v_float32_t __builtin_vrmin_f32(v_float32_t vs1);
v_float16_t __builtin_vrmin_f16(v_float16_t vs1);
v_int32_t __builtin_vrmin_s32(v_int32_t vs1);
v_uint32_t __builtin_vrmin_u32(v_uint32_t vs1);
v_float32_t __builtin_vrmin_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vrmin_f16_with_pn(v_float16_t vs1, v_bool2_t pn);
v_int32_t __builtin_vrmin_s32_with_pn(v_int32_t vs1, v_bool4_t pn);
v_uint32_t __builtin_vrmin_u32_with_pn(v_uint32_t vs1, v_bool4_t pn);


//
// ------ VRMAXI.dtype out:Vd, out:Pd, in:Vs1, in:Pn
//
// @brief Represents VRMAXI instruction.
//
void __builtin_vrmaxi_f32(v_float32_t vd, v_bool4_t pd, v_float32_t vs1);
void __builtin_vrmaxi_f16(v_float16_t vd, v_bool2_t pd, v_float16_t vs1);
void __builtin_vrmaxi_s32(v_int32_t vd, v_bool4_t pd, v_int32_t vs1);
void __builtin_vrmaxi_u32(v_uint32_t vd, v_bool4_t pd, v_uint32_t vs1);
void __builtin_vrmaxi_f32_with_pn(v_float32_t vd, v_bool4_t pd, v_float32_t vs1, v_bool4_t pn);
void __builtin_vrmaxi_f16_with_pn(v_float16_t vd, v_bool2_t pd, v_float16_t vs1, v_bool2_t pn);
void __builtin_vrmaxi_s32_with_pn(v_int32_t vd, v_bool4_t pd, v_int32_t vs1, v_bool4_t pn);
void __builtin_vrmaxi_u32_with_pn(v_uint32_t vd, v_bool4_t pd, v_uint32_t vs1, v_bool4_t pn);


//
// ------ VRMINI.dtype out:Vd, out:Pd, in:Vs1, in:Pn
//
// @brief Represents VRMINI instruction.
//
void __builtin_vrmini_f32(v_float32_t vd, v_bool4_t pd, v_float32_t vs1);
void __builtin_vrmini_f16(v_float16_t vd, v_bool2_t pd, v_float16_t vs1);
void __builtin_vrmini_s32(v_int32_t vd, v_bool4_t pd, v_int32_t vs1);
void __builtin_vrmini_u32(v_uint32_t vd, v_bool4_t pd, v_uint32_t vs1);
void __builtin_vrmini_f32_with_pn(v_float32_t vd, v_bool4_t pd, v_float32_t vs1, v_bool4_t pn);
void __builtin_vrmini_f16_with_pn(v_float16_t vd, v_bool2_t pd, v_float16_t vs1, v_bool2_t pn);
void __builtin_vrmini_s32_with_pn(v_int32_t vd, v_bool4_t pd, v_int32_t vs1, v_bool4_t pn);
void __builtin_vrmini_u32_with_pn(v_uint32_t vd, v_bool4_t pd, v_uint32_t vs1, v_bool4_t pn);


//
// ------ VRSQRT.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VRSQRT instruction.
//
v_float32_t __builtin_vrsqrt_f32(v_float32_t vs1);
v_float16_t __builtin_vrsqrt_f16(v_float16_t vs1);
v_float32_t __builtin_vrsqrt_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vrsqrt_f16_with_pn(v_float16_t vs1, v_bool2_t pn);


//
// ------ VEXP.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VEXP instruction.
//
v_float32_t __builtin_vexp_f32(v_float32_t vs1);
v_float16_t __builtin_vexp_f16(v_float16_t vs1);
v_float32_t __builtin_vexp_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vexp_f16_with_pn(v_float16_t vs1, v_bool2_t pn);


//
// ------ VLN.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VLN instruction.
//
v_float32_t __builtin_vln_f32(v_float32_t vs1);
v_float16_t __builtin_vln_f16(v_float16_t vs1);
v_float32_t __builtin_vln_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vln_f16_with_pn(v_float16_t vs1, v_bool2_t pn);


//
// ------ VSLIDEUP out:Vd, in:Vs1, in:Rs2
//
// @brief Represents VSLIDEUP instruction.
//
v_uint8_t __builtin_vslideup_u8(v_uint8_t vs1, uint32_t rs2);
v_int8_t __builtin_vslideup_s8(v_int8_t vs1, uint32_t rs2);
v_uint16_t __builtin_vslideup_u16(v_uint16_t vs1, uint32_t rs2);
v_int16_t __builtin_vslideup_s16(v_int16_t vs1, uint32_t rs2);
v_uint32_t __builtin_vslideup_u32(v_uint32_t vs1, uint32_t rs2);
v_int32_t __builtin_vslideup_s32(v_int32_t vs1, uint32_t rs2);
v_float16_t __builtin_vslideup_f16(v_float16_t vs1, uint32_t rs2);
v_float32_t __builtin_vslideup_f32(v_float32_t vs1, uint32_t rs2);


//
// ------ VSLIDEUPI out:Vd, in:Vs1, #uimm8
//
// @brief Represents VSLIDEUPI instruction.
//
v_uint8_t __builtin_vslideupi_u8(v_uint8_t vs1, uint32_t uimm8);
v_int8_t __builtin_vslideupi_s8(v_int8_t vs1, uint32_t uimm8);
v_uint16_t __builtin_vslideupi_u16(v_uint16_t vs1, uint32_t uimm8);
v_int16_t __builtin_vslideupi_s16(v_int16_t vs1, uint32_t uimm8);
v_uint32_t __builtin_vslideupi_u32(v_uint32_t vs1, uint32_t uimm8);
v_int32_t __builtin_vslideupi_s32(v_int32_t vs1, uint32_t uimm8);
v_float16_t __builtin_vslideupi_f16(v_float16_t vs1, uint32_t uimm8);
v_float32_t __builtin_vslideupi_f32(v_float32_t vs1, uint32_t uimm8);


//
// ------ VSLIDEDOWN out:Vd, in:Vs1, in:Rs2
//
// @brief Represents VSLIDEDOWN instruction.
//
v_uint8_t __builtin_vslidedown_u8(v_uint8_t vs1, uint32_t rs2);
v_int8_t __builtin_vslidedown_s8(v_int8_t vs1, uint32_t rs2);
v_uint16_t __builtin_vslidedown_u16(v_uint16_t vs1, uint32_t rs2);
v_int16_t __builtin_vslidedown_s16(v_int16_t vs1, uint32_t rs2);
v_uint32_t __builtin_vslidedown_u32(v_uint32_t vs1, uint32_t rs2);
v_int32_t __builtin_vslidedown_s32(v_int32_t vs1, uint32_t rs2);
v_float16_t __builtin_vslidedown_f16(v_float16_t vs1, uint32_t rs2);
v_float32_t __builtin_vslidedown_f32(v_float32_t vs1, uint32_t rs2);


//
// ------ VSLIDEDOWNI out:Vd, in:Vs1, #uimm8
//
// @brief Represents VSLIDEDOWNI instruction.
//
v_uint8_t __builtin_vslidedowni_u8(v_uint8_t vs1, uint32_t uimm8);
v_int8_t __builtin_vslidedowni_s8(v_int8_t vs1, uint32_t uimm8);
v_uint16_t __builtin_vslidedowni_u16(v_uint16_t vs1, uint32_t uimm8);
v_int16_t __builtin_vslidedowni_s16(v_int16_t vs1, uint32_t uimm8);
v_uint32_t __builtin_vslidedowni_u32(v_uint32_t vs1, uint32_t uimm8);
v_int32_t __builtin_vslidedowni_s32(v_int32_t vs1, uint32_t uimm8);
v_float16_t __builtin_vslidedowni_f16(v_float16_t vs1, uint32_t uimm8);
v_float32_t __builtin_vslidedowni_f32(v_float32_t vs1, uint32_t uimm8);


//
// ------ VSLIDEUPC out:Vd, in:Vs1, in:Vs2, in:Rs3
//
// @brief Represents VSLIDEUPC instruction.
//
v_uint8_t __builtin_vslideupc_u8(v_uint8_t vs1, v_uint8_t vs2, uint32_t rs3);
v_int8_t __builtin_vslideupc_s8(v_int8_t vs1, v_int8_t vs2, uint32_t rs3);
v_uint16_t __builtin_vslideupc_u16(v_uint16_t vs1, v_uint16_t vs2, uint32_t rs3);
v_int16_t __builtin_vslideupc_s16(v_int16_t vs1, v_int16_t vs2, uint32_t rs3);
v_uint32_t __builtin_vslideupc_u32(v_uint32_t vs1, v_uint32_t vs2, uint32_t rs3);
v_int32_t __builtin_vslideupc_s32(v_int32_t vs1, v_int32_t vs2, uint32_t rs3);
v_float16_t __builtin_vslideupc_f16(v_float16_t vs1, v_float16_t vs2, uint32_t rs3);
v_float32_t __builtin_vslideupc_f32(v_float32_t vs1, v_float32_t vs2, uint32_t rs3);


//
// ------ VSQZ.elesize out:Vd, in:Ps1, in:Vs2
//
// @brief Represents VSQZ instruction.
//
v_uint8_t __builtin_vsqz_u8(v_bool1_t ps1, v_uint8_t vs2);
v_int8_t __builtin_vsqz_s8(v_bool1_t ps1, v_int8_t vs2);
v_uint16_t __builtin_vsqz_u16(v_bool2_t ps1, v_uint16_t vs2);
v_int16_t __builtin_vsqz_s16(v_bool2_t ps1, v_int16_t vs2);
v_uint32_t __builtin_vsqz_u32(v_bool4_t ps1, v_uint32_t vs2);
v_int32_t __builtin_vsqz_s32(v_bool4_t ps1, v_int32_t vs2);
v_float16_t __builtin_vsqz_f16(v_bool2_t ps1, v_float16_t vs2);
v_float32_t __builtin_vsqz_f32(v_bool4_t ps1, v_float32_t vs2);


//
// ------ PINV out:Pd, in:Ps1
//
// @brief Represents PINV instruction.
//
v_bool1_t __builtin_pinv_u8(v_bool1_t ps1);
v_bool2_t __builtin_pinv_u16(v_bool2_t ps1);
v_bool4_t __builtin_pinv_u32(v_bool4_t ps1);


//
// ------ PAND out:Pd, in:Ps1, in:Ps2
//
// @brief Represents PAND instruction.
//
v_bool1_t __builtin_pand_u8(v_bool1_t ps1, v_bool1_t ps2);
v_bool2_t __builtin_pand_u16(v_bool2_t ps1, v_bool2_t ps2);
v_bool4_t __builtin_pand_u32(v_bool4_t ps1, v_bool4_t ps2);


//
// ------ POR out:Pd, in:Ps1, in:Ps2
//
// @brief Represents POR instruction.
//
v_bool1_t __builtin_por_u8(v_bool1_t ps1, v_bool1_t ps2);
v_bool2_t __builtin_por_u16(v_bool2_t ps1, v_bool2_t ps2);
v_bool4_t __builtin_por_u32(v_bool4_t ps1, v_bool4_t ps2);


//
// ------ PXOR out:Pd, in:Ps1, in:Ps2
//
// @brief Represents PXOR instruction.
//
v_bool1_t __builtin_pxor_u8(v_bool1_t ps1, v_bool1_t ps2);
v_bool2_t __builtin_pxor_u16(v_bool2_t ps1, v_bool2_t ps2);
v_bool4_t __builtin_pxor_u32(v_bool4_t ps1, v_bool4_t ps2);


//
// ------ PSET.elesize out:Pd, in:Rs1
//
// @brief Represents PSET instruction.
//
v_bool1_t __builtin_pset_u8(uint32_t rs1);
v_bool2_t __builtin_pset_u16(uint32_t rs1);
v_bool4_t __builtin_pset_u32(uint32_t rs1);


//
// ------ PSETFIRST.elesize out:Pd, in:Rs1
//
// @brief Represents PSETFIRST instruction.
//
v_bool1_t __builtin_psetfirst_u8(uint32_t rs1);
v_bool2_t __builtin_psetfirst_u16(uint32_t rs1);
v_bool4_t __builtin_psetfirst_u32(uint32_t rs1);


//
// ------ PCOUNT.elesize out:Rd, in:Ps1
//
// @brief Represents PCOUNT instruction.
//
uint32_t __builtin_pcount_u8(v_bool1_t ps1);
uint32_t __builtin_pcount_u16(v_bool2_t ps1);
uint32_t __builtin_pcount_u32(v_bool4_t ps1);


//
// ------ PFIRST.elesize out:Rd, in:Ps1
//
// @brief Represents PFIRST instruction.
//
uint32_t __builtin_pfirst_u8(v_bool1_t ps1);
uint32_t __builtin_pfirst_u16(v_bool2_t ps1);
uint32_t __builtin_pfirst_u32(v_bool4_t ps1);


//
// ------ VGETE.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VGETE instruction.
//
v_float32_t __builtin_vgete_f32(v_float32_t vs1);
v_float16_t __builtin_vgete_f16(v_float16_t vs1);
v_float32_t __builtin_vgete_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vgete_f16_with_pn(v_float16_t vs1, v_bool2_t pn);


//
// ------ VGETM.dtype out:Vd, in:Vs1, in:Pn
//
// @brief Represents VGETM instruction.
//
v_float32_t __builtin_vgetm_f32(v_float32_t vs1);
v_float16_t __builtin_vgetm_f16(v_float16_t vs1);
v_float32_t __builtin_vgetm_f32_with_pn(v_float32_t vs1, v_bool4_t pn);
v_float16_t __builtin_vgetm_f16_with_pn(v_float16_t vs1, v_bool2_t pn);


//
// ------ VMRG.dtype out:Vd, in:Vs1, in:Vs2, in:Pn
//
// @brief Represents VMRG instruction.
//
v_float32_t __builtin_vmrg_f32(v_float32_t vs1, v_float32_t vs2);
v_float16_t __builtin_vmrg_f16(v_float16_t vs1, v_float16_t vs2);
v_float32_t __builtin_vmrg_f32_with_pn(v_float32_t vs1, v_float32_t vs2, v_bool4_t pn);
v_float16_t __builtin_vmrg_f16_with_pn(v_float16_t vs1, v_float16_t vs2, v_bool2_t pn);


//
// ------ VDUPS.elesize out:Vd, in:Rs1
//
// @brief Represents VDUPS instruction.
//
v_uint8_t __builtin_vdups_u8(uint8_t rs1);
v_int8_t __builtin_vdups_s8(int8_t rs1);
v_uint16_t __builtin_vdups_u16(uint16_t rs1);
v_int16_t __builtin_vdups_s16(int16_t rs1);
v_uint32_t __builtin_vdups_u32(uint32_t rs1);
v_int32_t __builtin_vdups_s32(int32_t rs1);
v_float16_t __builtin_vdups_f16(float16_t rs1);
v_float32_t __builtin_vdups_f32(float32_t rs1);


//
// ------ VMV out:Vd, in:Vs1
//
// @brief Represents VMV instruction.
//
v_uint8_t __builtin_vmv_u8(v_uint8_t vs1);
v_int8_t __builtin_vmv_s8(v_int8_t vs1);
v_uint16_t __builtin_vmv_u16(v_uint16_t vs1);
v_int16_t __builtin_vmv_s16(v_int16_t vs1);
v_uint32_t __builtin_vmv_u32(v_uint32_t vs1);
v_int32_t __builtin_vmv_s32(v_int32_t vs1);
v_float16_t __builtin_vmv_f16(v_float16_t vs1);
v_float32_t __builtin_vmv_f32(v_float32_t vs1);


//
// ------ VMVR2VR.elesize out:Vd, in:Rs2, in:Rs1
//
// @brief Represents VMVR2VR instruction.
//
v_uint8_t __builtin_vmvr2vr_u8(uint8_t rs2, uint32_t rs1);
v_int8_t __builtin_vmvr2vr_s8(int8_t rs2, uint32_t rs1);
v_uint16_t __builtin_vmvr2vr_u16(uint16_t rs2, uint32_t rs1);
v_int16_t __builtin_vmvr2vr_s16(int16_t rs2, uint32_t rs1);
v_uint32_t __builtin_vmvr2vr_u32(uint32_t rs2, uint32_t rs1);
v_int32_t __builtin_vmvr2vr_s32(int32_t rs2, uint32_t rs1);
v_float16_t __builtin_vmvr2vr_f16(float16_t rs2, uint32_t rs1);
v_float32_t __builtin_vmvr2vr_f32(float32_t rs2, uint32_t rs1);


//
// ------ VMVR2VRI.elesize out:Vd, in:Rs1, #uimm8
//
// @brief Represents VMVR2VRI instruction.
//
v_uint8_t __builtin_vmvr2vri_u8(uint8_t rs1, uint32_t uimm8);
v_int8_t __builtin_vmvr2vri_s8(int8_t rs1, uint32_t uimm8);
v_uint16_t __builtin_vmvr2vri_u16(uint16_t rs1, uint32_t uimm8);
v_int16_t __builtin_vmvr2vri_s16(int16_t rs1, uint32_t uimm8);
v_uint32_t __builtin_vmvr2vri_u32(uint32_t rs1, uint32_t uimm8);
v_int32_t __builtin_vmvr2vri_s32(int32_t rs1, uint32_t uimm8);
v_float16_t __builtin_vmvr2vri_f16(float16_t rs1, uint32_t uimm8);
v_float32_t __builtin_vmvr2vri_f32(float32_t rs1, uint32_t uimm8);


//
// ------ PMVR2PR out:Pd, in:Rs1, in:Rs2
//
// @brief Represents PMVR2PR instruction.
//
v_bool1_t __builtin_pmvr2pr_u8(uint32_t rs1, uint32_t rs2);
v_bool2_t __builtin_pmvr2pr_u16(uint32_t rs1, uint32_t rs2);
v_bool4_t __builtin_pmvr2pr_u32(uint32_t rs1, uint32_t rs2);


//
// ------ PMVR2PRI out:Pd, in:Rs1, #uimm3
//
// @brief Represents PMVR2PRI instruction.
//
v_bool1_t __builtin_pmvr2pri_u8(uint32_t rs1, uint32_t uimm3);
v_bool2_t __builtin_pmvr2pri_u16(uint32_t rs1, uint32_t uimm3);
v_bool4_t __builtin_pmvr2pri_u32(uint32_t rs1, uint32_t uimm3);


//
// ------ PMVPR2R out:Rd, in:Ps1, in:Rs2
//
// @brief Represents PMVPR2R instruction.
//
uint32_t __builtin_pmvpr2r_u8(v_bool1_t ps1, uint32_t rs2);
uint32_t __builtin_pmvpr2r_u16(v_bool2_t ps1, uint32_t rs2);
uint32_t __builtin_pmvpr2r_u32(v_bool4_t ps1, uint32_t rs2);


//
// ------ PMVPR2RI out:Rd, in:Ps1, #uimm3
//
// @brief Represents PMVPR2RI instruction.
//
uint32_t __builtin_pmvpr2ri_u8(v_bool1_t ps1, uint32_t uimm3);
uint32_t __builtin_pmvpr2ri_u16(v_bool2_t ps1, uint32_t uimm3);
uint32_t __builtin_pmvpr2ri_u32(v_bool4_t ps1, uint32_t uimm3);


//
// ------ PDUPS.elesize out:Pd, in:Rs1
//
// @brief Represents PDUPS instruction.
//
v_bool1_t __builtin_pdups_u8(uint8_t rs1);
v_bool2_t __builtin_pdups_u16(uint16_t rs1);
v_bool4_t __builtin_pdups_u32(uint32_t rs1);


//
// ------ PEXTRACT.pos out:Pd, in:Ps1
//
// @brief Represents PEXTRACT instruction.
//
v_bool1_t __builtin_pextract_u8(enum Pos pos, v_bool1_t ps1);
v_bool2_t __builtin_pextract_u16(enum Pos pos, v_bool2_t ps1);
v_bool4_t __builtin_pextract_u32(enum Pos pos, v_bool4_t ps1);


//
// ------ PJOIN out:Pd, in:Ps2, in:Ps1
//
// @brief Represents PJOIN instruction.
//
v_bool1_t __builtin_pjoin_u8(v_bool1_t ps2, v_bool1_t ps1);
v_bool2_t __builtin_pjoin_u16(v_bool2_t ps2, v_bool2_t ps1);
v_bool4_t __builtin_pjoin_u32(v_bool4_t ps2, v_bool4_t ps1);


//
// ------ VSORT.dtype.sort_type out:Vd1, out:Vd2, in:Vs1, in:Vs2
//
// @brief Represents VSORT instruction.
//
void __builtin_vsort_f32(enum SortType sort_type, v_float32_t vd1, v_int32_t vd2, v_float32_t vs1, v_int32_t vs2);
void __builtin_vsort_s32(enum SortType sort_type, v_int32_t vd1, v_int32_t vd2, v_int32_t vs1, v_int32_t vs2);
void __builtin_vsort_u32(enum SortType sort_type, v_uint32_t vd1, v_int32_t vd2, v_uint32_t vs1, v_int32_t vs2);


//
// ------ VLDNOP
//
// @brief Represents VLDNOP instruction.
//
void __builtin_vldnop();


//
// ------ VSTNOP
//
// @brief Represents VSTNOP instruction.
//
void __builtin_vstnop();


//
// ------ RVMM [inout:Ad], in:As1, [inout:As2], in:As3, in:Rs1, in:Rs2
//
// @brief Represents RVMM instruction.
//
void __builtin_t_rvmm(uint32_t *ad, uint32_t as1, uint32_t *as2, uint32_t as3, uint32_t rs1, uint32_t rs2);


//
// ------ LDMATRIX [inout:As1], in:As2, in:Rs1, in:Rs2
//
// @brief Represents LDMATRIX instruction.
//
void __builtin_t_ldmatrix(uint32_t *as1, uint32_t as2, uint32_t rs1, uint32_t rs2);


//
// ------ LDVECTOR [inout:As1], in:As2, in:Rs1
//
// @brief Represents LDVECTOR instruction.
//
void __builtin_t_ldvector_u8(uint8_t *as1, uint32_t as2, uint32_t rs1);
void __builtin_t_ldvector_s8(int8_t *as1, uint32_t as2, uint32_t rs1);
void __builtin_t_ldvector_u16(uint16_t *as1, uint32_t as2, uint32_t rs1);
void __builtin_t_ldvector_s16(int16_t *as1, uint32_t as2, uint32_t rs1);
void __builtin_t_ldvector_u32(uint32_t *as1, uint32_t as2, uint32_t rs1);
void __builtin_t_ldvector_s32(int32_t *as1, uint32_t as2, uint32_t rs1);
void __builtin_t_ldvector_f16(float16_t *as1, uint32_t as2, uint32_t rs1);
void __builtin_t_ldvector_f32(float32_t *as1, uint32_t as2, uint32_t rs1);


//
// ------ INITACC [inout:Ad], in:As1, in:Rs1
//
// @brief Represents INITACC instruction.
//
void __builtin_t_initacc(void *ad, uint32_t as1, uint32_t rs1);


#ifdef __cplusplus
} // namespace cpu0
#endif

#endif // _CPU0_INTRINSIC_H_
