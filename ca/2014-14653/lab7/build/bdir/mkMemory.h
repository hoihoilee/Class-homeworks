/*
 * Generated by Bluespec Compiler, version 2014.07.A (build 34078, 2014-07-30)
 * 
 * On Fri Jun 15 22:45:49 KST 2018
 * 
 */

/* Generation options: */
#ifndef __mkMemory_h__
#define __mkMemory_h__

#include "bluesim_types.h"
#include "bs_module.h"
#include "bluesim_primitives.h"
#include "bs_vcd.h"


/* Class declaration for the mkMemory module */
class MOD_mkMemory : public Module {
 
 /* Clock handles */
 private:
  tClock __clk_handle_0;
 
 /* Clock gate handles */
 public:
  tUInt8 *clk_gate[0];
 
 /* Instantiation parameters */
 public:
 
 /* Module state */
 public:
  MOD_Reg<tUInt8> INST_dMemCnt;
  MOD_Reg<tUWide> INST_dMemReqQ_data_0;
  MOD_Reg<tUWide> INST_dMemReqQ_data_1;
  MOD_Reg<tUInt8> INST_dMemReqQ_deqEn_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemReqQ_deqEn_dummy2_1;
  MOD_Reg<tUInt8> INST_dMemReqQ_deqEn_dummy2_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_0_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_1_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_2_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_2_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_dummy_2_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_lat_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_lat_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqEn_lat_2;
  MOD_Reg<tUInt8> INST_dMemReqQ_deqEn_rl;
  MOD_Reg<tUInt8> INST_dMemReqQ_deqP_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemReqQ_deqP_dummy2_1;
  MOD_Reg<tUInt8> INST_dMemReqQ_deqP_dummy2_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_0_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_1_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_2_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_2_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_dummy_2_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_lat_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_lat_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_deqP_lat_2;
  MOD_Reg<tUInt8> INST_dMemReqQ_deqP_rl;
  MOD_Reg<tUInt8> INST_dMemReqQ_enqEn_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemReqQ_enqEn_dummy2_1;
  MOD_Reg<tUInt8> INST_dMemReqQ_enqEn_dummy2_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_0_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_1_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_2_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_2_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_dummy_2_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_lat_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_lat_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqEn_lat_2;
  MOD_Reg<tUInt8> INST_dMemReqQ_enqEn_rl;
  MOD_Reg<tUInt8> INST_dMemReqQ_enqP_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemReqQ_enqP_dummy2_1;
  MOD_Reg<tUInt8> INST_dMemReqQ_enqP_dummy2_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_0_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_1_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_2_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_2_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_dummy_2_2;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_lat_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_lat_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_enqP_lat_2;
  MOD_Reg<tUInt8> INST_dMemReqQ_enqP_rl;
  MOD_Reg<tUInt8> INST_dMemReqQ_tempData_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemReqQ_tempData_dummy2_1;
  MOD_Wire<tUWide> INST_dMemReqQ_tempData_dummy_0_0;
  MOD_Wire<tUWide> INST_dMemReqQ_tempData_dummy_0_1;
  MOD_Wire<tUWide> INST_dMemReqQ_tempData_dummy_1_0;
  MOD_Wire<tUWide> INST_dMemReqQ_tempData_dummy_1_1;
  MOD_Wire<tUWide> INST_dMemReqQ_tempData_lat_0;
  MOD_Wire<tUWide> INST_dMemReqQ_tempData_lat_1;
  MOD_Reg<tUWide> INST_dMemReqQ_tempData_rl;
  MOD_Reg<tUInt8> INST_dMemReqQ_tempEnqP_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemReqQ_tempEnqP_dummy2_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_tempEnqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_tempEnqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_tempEnqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_tempEnqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemReqQ_tempEnqP_lat_0;
  MOD_Wire<tUInt8> INST_dMemReqQ_tempEnqP_lat_1;
  MOD_Reg<tUInt8> INST_dMemReqQ_tempEnqP_rl;
  MOD_Reg<tUInt64> INST_dMemRespQ_data_0;
  MOD_Reg<tUInt64> INST_dMemRespQ_data_1;
  MOD_Reg<tUInt8> INST_dMemRespQ_deqEn_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemRespQ_deqEn_dummy2_1;
  MOD_Reg<tUInt8> INST_dMemRespQ_deqEn_dummy2_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_0_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_1_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_2_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_2_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_dummy_2_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_lat_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_lat_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqEn_lat_2;
  MOD_Reg<tUInt8> INST_dMemRespQ_deqEn_rl;
  MOD_Reg<tUInt8> INST_dMemRespQ_deqP_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemRespQ_deqP_dummy2_1;
  MOD_Reg<tUInt8> INST_dMemRespQ_deqP_dummy2_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_0_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_1_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_2_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_2_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_dummy_2_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_lat_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_lat_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_deqP_lat_2;
  MOD_Reg<tUInt8> INST_dMemRespQ_deqP_rl;
  MOD_Reg<tUInt8> INST_dMemRespQ_enqEn_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemRespQ_enqEn_dummy2_1;
  MOD_Reg<tUInt8> INST_dMemRespQ_enqEn_dummy2_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_0_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_1_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_2_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_2_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_dummy_2_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_lat_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_lat_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqEn_lat_2;
  MOD_Reg<tUInt8> INST_dMemRespQ_enqEn_rl;
  MOD_Reg<tUInt8> INST_dMemRespQ_enqP_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemRespQ_enqP_dummy2_1;
  MOD_Reg<tUInt8> INST_dMemRespQ_enqP_dummy2_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_0_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_1_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_2_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_2_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_dummy_2_2;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_lat_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_lat_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_enqP_lat_2;
  MOD_Reg<tUInt8> INST_dMemRespQ_enqP_rl;
  MOD_Reg<tUInt8> INST_dMemRespQ_tempData_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemRespQ_tempData_dummy2_1;
  MOD_Wire<tUWide> INST_dMemRespQ_tempData_dummy_0_0;
  MOD_Wire<tUWide> INST_dMemRespQ_tempData_dummy_0_1;
  MOD_Wire<tUWide> INST_dMemRespQ_tempData_dummy_1_0;
  MOD_Wire<tUWide> INST_dMemRespQ_tempData_dummy_1_1;
  MOD_Wire<tUInt64> INST_dMemRespQ_tempData_lat_0;
  MOD_Wire<tUInt64> INST_dMemRespQ_tempData_lat_1;
  MOD_Reg<tUInt64> INST_dMemRespQ_tempData_rl;
  MOD_Reg<tUInt8> INST_dMemRespQ_tempEnqP_dummy2_0;
  MOD_Reg<tUInt8> INST_dMemRespQ_tempEnqP_dummy2_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_tempEnqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_tempEnqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_tempEnqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_tempEnqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_dMemRespQ_tempEnqP_lat_0;
  MOD_Wire<tUInt8> INST_dMemRespQ_tempEnqP_lat_1;
  MOD_Reg<tUInt8> INST_dMemRespQ_tempEnqP_rl;
  MOD_Reg<tUInt8> INST_dMemStatus;
  MOD_Reg<tUInt64> INST_dMemTempData;
  MOD_Reg<tUInt8> INST_iMemCnt;
  MOD_Reg<tUWide> INST_iMemReqQ_data_0;
  MOD_Reg<tUWide> INST_iMemReqQ_data_1;
  MOD_Reg<tUInt8> INST_iMemReqQ_deqEn_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemReqQ_deqEn_dummy2_1;
  MOD_Reg<tUInt8> INST_iMemReqQ_deqEn_dummy2_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_0_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_1_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_2_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_2_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_dummy_2_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_lat_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_lat_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqEn_lat_2;
  MOD_Reg<tUInt8> INST_iMemReqQ_deqEn_rl;
  MOD_Reg<tUInt8> INST_iMemReqQ_deqP_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemReqQ_deqP_dummy2_1;
  MOD_Reg<tUInt8> INST_iMemReqQ_deqP_dummy2_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_0_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_1_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_2_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_2_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_dummy_2_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_lat_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_lat_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_deqP_lat_2;
  MOD_Reg<tUInt8> INST_iMemReqQ_deqP_rl;
  MOD_Reg<tUInt8> INST_iMemReqQ_enqEn_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemReqQ_enqEn_dummy2_1;
  MOD_Reg<tUInt8> INST_iMemReqQ_enqEn_dummy2_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_0_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_1_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_2_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_2_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_dummy_2_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_lat_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_lat_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqEn_lat_2;
  MOD_Reg<tUInt8> INST_iMemReqQ_enqEn_rl;
  MOD_Reg<tUInt8> INST_iMemReqQ_enqP_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemReqQ_enqP_dummy2_1;
  MOD_Reg<tUInt8> INST_iMemReqQ_enqP_dummy2_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_0_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_1_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_2_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_2_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_dummy_2_2;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_lat_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_lat_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_enqP_lat_2;
  MOD_Reg<tUInt8> INST_iMemReqQ_enqP_rl;
  MOD_Reg<tUInt8> INST_iMemReqQ_tempData_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemReqQ_tempData_dummy2_1;
  MOD_Wire<tUWide> INST_iMemReqQ_tempData_dummy_0_0;
  MOD_Wire<tUWide> INST_iMemReqQ_tempData_dummy_0_1;
  MOD_Wire<tUWide> INST_iMemReqQ_tempData_dummy_1_0;
  MOD_Wire<tUWide> INST_iMemReqQ_tempData_dummy_1_1;
  MOD_Wire<tUWide> INST_iMemReqQ_tempData_lat_0;
  MOD_Wire<tUWide> INST_iMemReqQ_tempData_lat_1;
  MOD_Reg<tUWide> INST_iMemReqQ_tempData_rl;
  MOD_Reg<tUInt8> INST_iMemReqQ_tempEnqP_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemReqQ_tempEnqP_dummy2_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_tempEnqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_tempEnqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_tempEnqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_tempEnqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemReqQ_tempEnqP_lat_0;
  MOD_Wire<tUInt8> INST_iMemReqQ_tempEnqP_lat_1;
  MOD_Reg<tUInt8> INST_iMemReqQ_tempEnqP_rl;
  MOD_Reg<tUInt64> INST_iMemRespQ_data_0;
  MOD_Reg<tUInt64> INST_iMemRespQ_data_1;
  MOD_Reg<tUInt8> INST_iMemRespQ_deqEn_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemRespQ_deqEn_dummy2_1;
  MOD_Reg<tUInt8> INST_iMemRespQ_deqEn_dummy2_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_0_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_1_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_2_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_2_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_dummy_2_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_lat_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_lat_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqEn_lat_2;
  MOD_Reg<tUInt8> INST_iMemRespQ_deqEn_rl;
  MOD_Reg<tUInt8> INST_iMemRespQ_deqP_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemRespQ_deqP_dummy2_1;
  MOD_Reg<tUInt8> INST_iMemRespQ_deqP_dummy2_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_0_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_1_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_2_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_2_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_dummy_2_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_lat_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_lat_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_deqP_lat_2;
  MOD_Reg<tUInt8> INST_iMemRespQ_deqP_rl;
  MOD_Reg<tUInt8> INST_iMemRespQ_enqEn_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemRespQ_enqEn_dummy2_1;
  MOD_Reg<tUInt8> INST_iMemRespQ_enqEn_dummy2_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_0_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_1_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_2_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_2_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_dummy_2_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_lat_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_lat_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqEn_lat_2;
  MOD_Reg<tUInt8> INST_iMemRespQ_enqEn_rl;
  MOD_Reg<tUInt8> INST_iMemRespQ_enqP_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemRespQ_enqP_dummy2_1;
  MOD_Reg<tUInt8> INST_iMemRespQ_enqP_dummy2_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_0_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_1_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_2_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_2_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_dummy_2_2;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_lat_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_lat_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_enqP_lat_2;
  MOD_Reg<tUInt8> INST_iMemRespQ_enqP_rl;
  MOD_Reg<tUInt8> INST_iMemRespQ_tempData_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemRespQ_tempData_dummy2_1;
  MOD_Wire<tUWide> INST_iMemRespQ_tempData_dummy_0_0;
  MOD_Wire<tUWide> INST_iMemRespQ_tempData_dummy_0_1;
  MOD_Wire<tUWide> INST_iMemRespQ_tempData_dummy_1_0;
  MOD_Wire<tUWide> INST_iMemRespQ_tempData_dummy_1_1;
  MOD_Wire<tUInt64> INST_iMemRespQ_tempData_lat_0;
  MOD_Wire<tUInt64> INST_iMemRespQ_tempData_lat_1;
  MOD_Reg<tUInt64> INST_iMemRespQ_tempData_rl;
  MOD_Reg<tUInt8> INST_iMemRespQ_tempEnqP_dummy2_0;
  MOD_Reg<tUInt8> INST_iMemRespQ_tempEnqP_dummy2_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_tempEnqP_dummy_0_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_tempEnqP_dummy_0_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_tempEnqP_dummy_1_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_tempEnqP_dummy_1_1;
  MOD_Wire<tUInt8> INST_iMemRespQ_tempEnqP_lat_0;
  MOD_Wire<tUInt8> INST_iMemRespQ_tempEnqP_lat_1;
  MOD_Reg<tUInt8> INST_iMemRespQ_tempEnqP_rl;
  MOD_Reg<tUInt8> INST_iMemStatus;
  MOD_Reg<tUInt64> INST_iMemTempData;
  MOD_RegFile<tUInt32,tUInt64> INST_mem;
  MOD_Reg<tUInt64> INST_penaltyCnt;
 
 /* Constructor */
 public:
  MOD_mkMemory(tSimStateHdl simHdl, char const *name, Module *parent);
 
 /* Symbol init methods */
 private:
  void init_symbols_0();
 
 /* Reset signal definitions */
 private:
  tUInt8 PORT_RST_N;
 
 /* Port definitions */
 public:
  tUWide PORT_dReq_r;
  tUWide PORT_iReq_r;
 
 /* Publicly accessible definitions */
 public:
  tUInt8 DEF_dMemRespQ_deqEn_rl__h46287;
  tUInt8 DEF_iMemRespQ_deqEn_rl__h20064;
  tUInt8 DEF_iMemCnt_00_EQ_SEL_ARR_iMemReqQ_data_0_01_BIT_0_ETC___d614;
  tUInt8 DEF_x__h56854;
  tUInt8 DEF_dMemCnt_15_EQ_SEL_ARR_dMemReqQ_data_0_16_BIT_0_ETC___d529;
  tUInt8 DEF_x__h55157;
  tUInt8 DEF_SEL_ARR_dMemReqQ_data_0_16_BIT_129_34_dMemReqQ_ETC___d537;
  tUInt8 DEF_NOT_dMemCnt_15_EQ_SEL_ARR_dMemReqQ_data_0_16_B_ETC___d530;
  tUInt8 DEF_x__h53200;
  tUInt64 DEF__read__h52843;
  tUInt8 DEF_dMemRespQ_deqEn_dummy2_2__h50796;
  tUInt8 DEF_dMemRespQ_enqEn_dummy2_2__h49302;
  tUInt8 DEF_dMemReqQ_deqEn_dummy2_2__h37717;
  tUInt8 DEF_dMemReqQ_enqEn_dummy2_2__h36223;
  tUInt8 DEF_iMemRespQ_deqEn_dummy2_2__h24579;
  tUInt8 DEF_iMemRespQ_enqEn_dummy2_2__h23085;
  tUInt8 DEF_iMemReqQ_deqEn_dummy2_2__h11494;
  tUInt8 DEF_iMemReqQ_enqEn_dummy2_2__h10000;
  tUWide DEF_dMemReqQ_data_1___d518;
  tUWide DEF_dMemReqQ_data_0___d516;
  tUWide DEF_iMemReqQ_data_1___d603;
  tUWide DEF_iMemReqQ_data_0___d601;
  tUInt8 DEF_upd__h53217;
  tUInt8 DEF_upd__h55301;
  tUInt8 DEF_dMemStatus__h53090;
  tUInt8 DEF_iMemStatus__h55176;
  tUInt8 DEF_dMemRespQ_enqEn_rl__h44662;
  tUInt8 DEF_dMemReqQ_deqEn_rl__h33111;
  tUInt8 DEF_dMemReqQ_enqEn_rl__h31486;
  tUInt8 DEF_dMemReqQ_deqP_dummy2_2__h36803;
  tUInt8 DEF_dMemReqQ_deqP_dummy2_1__h53272;
  tUInt8 DEF_dMemReqQ_deqP_dummy2_0__h53260;
  tUInt8 DEF_iMemRespQ_enqEn_rl__h18439;
  tUInt8 DEF_iMemReqQ_deqEn_rl__h6888;
  tUInt8 DEF_iMemReqQ_enqEn_rl__h5263;
  tUInt8 DEF_iMemReqQ_deqP_dummy2_2__h10580;
  tUInt8 DEF_iMemReqQ_deqP_dummy2_1__h55356;
  tUInt8 DEF_iMemReqQ_deqP_dummy2_0__h55344;
  tUInt8 DEF__read_burstLength__h55402;
  tUInt8 DEF__read_burstLength__h55394;
  tUInt8 DEF__read_burstLength__h53310;
  tUInt8 DEF__read_burstLength__h53318;
  tUInt8 DEF_x__h55803;
  tUInt8 DEF_x__h54074;
  tUInt8 DEF_x__h55284;
  tUInt8 DEF_y__h55184;
  tUInt8 DEF_y__h53100;
  tUInt8 DEF_penaltyCnt_31_EQ_100___d532;
  tUInt8 DEF_NOT_iMemCnt_00_EQ_SEL_ARR_iMemReqQ_data_0_01_B_ETC___d615;
 
 /* Local definitions */
 private:
  tUInt8 DEF__0_CONCAT_DONTCARE___d123;
  tUInt8 DEF_IF_dMemRespQ_tempEnqP_lat_0_whas__33_THEN_dMem_ETC___d438;
  tUInt8 DEF_IF_dMemRespQ_tempEnqP_lat_0_whas__33_THEN_NOT__ETC___d443;
  tUInt8 DEF_dMemRespQ_deqEn_lat_1_whas____d415;
  tUInt8 DEF_dMemRespQ_enqEn_lat_1_whas____d405;
  tUInt8 DEF_IF_dMemReqQ_tempEnqP_lat_0_whas__06_THEN_dMemR_ETC___d311;
  tUInt8 DEF_IF_dMemReqQ_tempEnqP_lat_0_whas__06_THEN_NOT_d_ETC___d316;
  tUInt8 DEF_dMemReqQ_deqEn_lat_1_whas____d288;
  tUInt8 DEF_dMemReqQ_enqEn_lat_1_whas____d278;
  tUInt8 DEF_IF_iMemRespQ_tempEnqP_lat_0_whas__79_THEN_iMem_ETC___d184;
  tUInt8 DEF_IF_iMemRespQ_tempEnqP_lat_0_whas__79_THEN_NOT__ETC___d189;
  tUInt8 DEF_iMemRespQ_deqEn_lat_1_whas____d161;
  tUInt8 DEF_iMemRespQ_enqEn_lat_1_whas____d151;
  tUInt8 DEF_IF_iMemReqQ_tempEnqP_lat_0_whas__1_THEN_iMemRe_ETC___d56;
  tUInt8 DEF_IF_iMemReqQ_tempEnqP_lat_0_whas__1_THEN_NOT_iM_ETC___d61;
  tUInt8 DEF_iMemReqQ_deqEn_lat_1_whas____d33;
  tUInt8 DEF_iMemReqQ_enqEn_lat_1_whas____d23;
  tUWide DEF_dMemReqQ_tempData_rl___d300;
  tUWide DEF_dMemReqQ_tempData_lat_1_wget____d297;
  tUWide DEF_dMemReqQ_tempData_lat_0_wget____d299;
  tUWide DEF_iMemReqQ_tempData_rl___d45;
  tUWide DEF_iMemReqQ_tempData_lat_1_wget____d42;
  tUWide DEF_iMemReqQ_tempData_lat_0_wget____d44;
  tUInt8 DEF_dMemRespQ_tempEnqP_rl___d436;
  tUInt8 DEF_dMemRespQ_tempEnqP_lat_0_wget____d434;
  tUInt8 DEF_dMemReqQ_tempEnqP_rl___d309;
  tUInt8 DEF_dMemReqQ_tempEnqP_lat_0_wget____d307;
  tUInt8 DEF_iMemRespQ_tempEnqP_rl___d182;
  tUInt8 DEF_iMemRespQ_tempEnqP_lat_0_wget____d180;
  tUInt8 DEF_iMemReqQ_tempEnqP_rl___d54;
  tUInt8 DEF_iMemReqQ_tempEnqP_lat_0_wget____d52;
  tUInt8 DEF_upd__h59956;
  tUInt8 DEF_upd__h49921;
  tUInt8 DEF_upd__h49954;
  tUInt8 DEF_upd__h54716;
  tUInt8 DEF_upd__h49638;
  tUInt8 DEF_upd__h49671;
  tUInt8 DEF_upd__h36842;
  tUInt8 DEF_upd__h36875;
  tUInt8 DEF_upd__h59187;
  tUInt8 DEF_upd__h36559;
  tUInt8 DEF_upd__h36592;
  tUInt8 DEF_upd__h58207;
  tUInt8 DEF_upd__h23704;
  tUInt8 DEF_upd__h23737;
  tUInt8 DEF_upd__h56430;
  tUInt8 DEF_upd__h23421;
  tUInt8 DEF_upd__h23454;
  tUInt8 DEF_upd__h10619;
  tUInt8 DEF_upd__h10652;
  tUInt8 DEF_upd__h57438;
  tUInt8 DEF_upd__h10336;
  tUInt8 DEF_upd__h10369;
  tUInt8 DEF_dMemRespQ_tempEnqP_lat_0_whas____d433;
  tUInt8 DEF_dMemRespQ_deqEn_lat_1_wget____d416;
  tUInt8 DEF_dMemRespQ_deqEn_lat_0_whas____d417;
  tUInt8 DEF_dMemRespQ_deqEn_lat_0_wget____d418;
  tUInt8 DEF_dMemRespQ_enqEn_lat_1_wget____d406;
  tUInt8 DEF_dMemRespQ_enqEn_lat_0_whas____d407;
  tUInt8 DEF_dMemRespQ_enqEn_lat_0_wget____d408;
  tUInt8 DEF_dMemRespQ_deqP_dummy2_2__h49882;
  tUInt8 DEF_dMemRespQ_enqP_dummy2_2__h49599;
  tUInt8 DEF_dMemReqQ_tempEnqP_lat_0_whas____d306;
  tUInt8 DEF_dMemReqQ_deqEn_lat_1_wget____d289;
  tUInt8 DEF_dMemReqQ_deqEn_lat_0_whas____d290;
  tUInt8 DEF_dMemReqQ_deqEn_lat_0_wget____d291;
  tUInt8 DEF_dMemReqQ_enqEn_lat_1_wget____d279;
  tUInt8 DEF_dMemReqQ_enqEn_lat_0_whas____d280;
  tUInt8 DEF_dMemReqQ_enqEn_lat_0_wget____d281;
  tUInt8 DEF_dMemReqQ_enqP_dummy2_2__h36520;
  tUInt8 DEF_iMemRespQ_tempEnqP_lat_0_whas____d179;
  tUInt8 DEF_iMemRespQ_deqEn_lat_1_wget____d162;
  tUInt8 DEF_iMemRespQ_deqEn_lat_0_whas____d163;
  tUInt8 DEF_iMemRespQ_deqEn_lat_0_wget____d164;
  tUInt8 DEF_iMemRespQ_enqEn_lat_1_wget____d152;
  tUInt8 DEF_iMemRespQ_enqEn_lat_0_whas____d153;
  tUInt8 DEF_iMemRespQ_enqEn_lat_0_wget____d154;
  tUInt8 DEF_iMemRespQ_deqP_dummy2_2__h23665;
  tUInt8 DEF_iMemRespQ_enqP_dummy2_2__h23382;
  tUInt8 DEF_iMemReqQ_tempEnqP_lat_0_whas____d51;
  tUInt8 DEF_iMemReqQ_deqEn_lat_1_wget____d34;
  tUInt8 DEF_iMemReqQ_deqEn_lat_0_whas____d35;
  tUInt8 DEF_iMemReqQ_deqEn_lat_0_wget____d36;
  tUInt8 DEF_iMemReqQ_enqEn_lat_1_wget____d24;
  tUInt8 DEF_iMemReqQ_enqEn_lat_0_whas____d25;
  tUInt8 DEF_iMemReqQ_enqEn_lat_0_wget____d26;
  tUInt8 DEF_iMemReqQ_enqP_dummy2_2__h10297;
  tUInt8 DEF_x__h49034;
  tUInt8 DEF_x__h49033;
  tUInt8 DEF_x__h35955;
  tUInt8 DEF_x__h35954;
  tUInt8 DEF_x__h22817;
  tUInt8 DEF_x__h22816;
  tUInt8 DEF_x__h9732;
  tUInt8 DEF_x__h9731;
  tUInt8 DEF_dMemRespQ_tempEnqP_rl_36_BIT_3___d437;
  tUInt8 DEF_dMemRespQ_tempEnqP_lat_0_wget__34_BIT_3___d435;
  tUInt8 DEF_dMemReqQ_tempEnqP_rl_09_BIT_3___d310;
  tUInt8 DEF_dMemReqQ_tempEnqP_lat_0_wget__07_BIT_3___d308;
  tUInt8 DEF_iMemRespQ_tempEnqP_rl_82_BIT_3___d183;
  tUInt8 DEF_iMemRespQ_tempEnqP_lat_0_wget__80_BIT_3___d181;
  tUInt8 DEF_iMemReqQ_tempEnqP_rl_4_BIT_3___d55;
  tUInt8 DEF_iMemReqQ_tempEnqP_lat_0_wget__2_BIT_3___d53;
  tUWide DEF_IF_dMemReqQ_tempData_dummy2_1_74_THEN_IF_dMemR_ETC___d375;
  tUWide DEF_IF_dMemReqQ_tempData_lat_0_whas__98_THEN_dMemR_ETC___d301;
  tUWide DEF_IF_dMemReqQ_tempData_lat_1_whas__96_THEN_dMemR_ETC___d302;
  tUWide DEF_IF_iMemReqQ_tempData_dummy2_1_19_THEN_IF_iMemR_ETC___d120;
  tUWide DEF_IF_iMemReqQ_tempData_lat_0_whas__3_THEN_iMemRe_ETC___d46;
  tUWide DEF_IF_iMemReqQ_tempData_lat_1_whas__1_THEN_iMemRe_ETC___d47;
  tUInt64 DEF_IF_dMemRespQ_tempData_lat_0_whas__25_THEN_dMem_ETC___d428;
  tUInt64 DEF_IF_iMemRespQ_tempData_lat_0_whas__71_THEN_iMem_ETC___d174;
  tUInt8 DEF_IF_dMemRespQ_tempEnqP_lat_0_whas__33_THEN_dMem_ETC___d448;
  tUInt8 DEF_IF_dMemRespQ_deqP_lat_1_whas__95_THEN_dMemResp_ETC___d401;
  tUInt8 DEF_IF_dMemRespQ_enqP_lat_1_whas__85_THEN_dMemResp_ETC___d391;
  tUInt8 DEF_IF_dMemReqQ_tempEnqP_lat_0_whas__06_THEN_dMemR_ETC___d321;
  tUInt8 DEF_IF_dMemReqQ_deqP_lat_1_whas__68_THEN_dMemReqQ__ETC___d274;
  tUInt8 DEF_IF_dMemReqQ_enqP_lat_1_whas__58_THEN_dMemReqQ__ETC___d264;
  tUInt8 DEF_IF_iMemRespQ_tempEnqP_lat_0_whas__79_THEN_iMem_ETC___d194;
  tUInt8 DEF_IF_iMemRespQ_deqP_lat_1_whas__41_THEN_iMemResp_ETC___d147;
  tUInt8 DEF_IF_iMemRespQ_enqP_lat_1_whas__31_THEN_iMemResp_ETC___d137;
  tUInt8 DEF_IF_iMemReqQ_tempEnqP_lat_0_whas__1_THEN_iMemRe_ETC___d66;
  tUInt8 DEF_IF_iMemReqQ_deqP_lat_1_whas__3_THEN_iMemReqQ_d_ETC___d19;
  tUInt8 DEF_IF_iMemReqQ_enqP_lat_1_whas_THEN_iMemReqQ_enqP_ETC___d9;
 
 /* Rules */
 public:
  void RL_iMemReqQ_enqP_canon();
  void RL_iMemReqQ_deqP_canon();
  void RL_iMemReqQ_enqEn_canon();
  void RL_iMemReqQ_deqEn_canon();
  void RL_iMemReqQ_tempData_canon();
  void RL_iMemReqQ_tempEnqP_canon();
  void RL_iMemReqQ_canonicalize();
  void RL_iMemRespQ_enqP_canon();
  void RL_iMemRespQ_deqP_canon();
  void RL_iMemRespQ_enqEn_canon();
  void RL_iMemRespQ_deqEn_canon();
  void RL_iMemRespQ_tempData_canon();
  void RL_iMemRespQ_tempEnqP_canon();
  void RL_iMemRespQ_canonicalize();
  void RL_dMemReqQ_enqP_canon();
  void RL_dMemReqQ_deqP_canon();
  void RL_dMemReqQ_enqEn_canon();
  void RL_dMemReqQ_deqEn_canon();
  void RL_dMemReqQ_tempData_canon();
  void RL_dMemReqQ_tempEnqP_canon();
  void RL_dMemReqQ_canonicalize();
  void RL_dMemRespQ_enqP_canon();
  void RL_dMemRespQ_deqP_canon();
  void RL_dMemRespQ_enqEn_canon();
  void RL_dMemRespQ_deqEn_canon();
  void RL_dMemRespQ_tempData_canon();
  void RL_dMemRespQ_tempEnqP_canon();
  void RL_dMemRespQ_canonicalize();
  void RL_getDResp();
  void RL_getIResp();
 
 /* Methods */
 public:
  void METH_iReq(tUWide ARG_iReq_r);
  tUInt8 METH_RDY_iReq();
  tUInt64 METH_iResp();
  tUInt8 METH_RDY_iResp();
  void METH_dReq(tUWide ARG_dReq_r);
  tUInt8 METH_RDY_dReq();
  tUInt64 METH_dResp();
  tUInt8 METH_RDY_dResp();
 
 /* Reset routines */
 public:
  void reset_RST_N(tUInt8 ARG_rst_in);
 
 /* Static handles to reset routines */
 public:
 
 /* Pointers to reset fns in parent module for asserting output resets */
 private:
 
 /* Functions for the parent module to register its reset fns */
 public:
 
 /* Functions to set the elaborated clock id */
 public:
  void set_clk_0(char const *s);
 
 /* State dumping routine */
 public:
  void dump_state(unsigned int indent);
 
 /* VCD dumping routines */
 public:
  unsigned int dump_VCD_defs(unsigned int levels);
  void dump_VCD(tVCDDumpType dt, unsigned int levels, MOD_mkMemory &backing);
  void vcd_defs(tVCDDumpType dt, MOD_mkMemory &backing);
  void vcd_prims(tVCDDumpType dt, MOD_mkMemory &backing);
};

#endif /* ifndef __mkMemory_h__ */
