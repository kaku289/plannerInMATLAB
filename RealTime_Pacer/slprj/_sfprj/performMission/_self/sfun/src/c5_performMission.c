/* Include files */

#include "performMission_sfun.h"
#include "c5_performMission.h"
#include <string.h>
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "performMission_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c5_debug_family_names[12] = { "pprz_id", "dataL_overhead",
  "message_id", "dataL_payload", "ck_a", "ck_b", "i", "dataSent", "nargin",
  "nargout", "stage", "payload" };

/* Function Declarations */
static void initialize_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance);
static void initialize_params_c5_performMission
  (SFc5_performMissionInstanceStruct *chartInstance);
static void enable_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance);
static void disable_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance);
static void c5_update_debugger_state_c5_performMission
  (SFc5_performMissionInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_performMission
  (SFc5_performMissionInstanceStruct *chartInstance);
static void set_sim_state_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_st);
static void finalize_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance);
static void sf_gateway_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance);
static void mdl_start_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance);
static void c5_chartstep_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance);
static void initSimStructsc5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c5_inData_data[], int32_T c5_inData_sizes[2]);
static void c5_emlrt_marshallIn(SFc5_performMissionInstanceStruct *chartInstance,
  const mxArray *c5_dataSent, const char_T *c5_identifier, uint8_T c5_y_data[],
  int32_T c5_y_sizes[2]);
static void c5_b_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  uint8_T c5_y_data[], int32_T c5_y_sizes[2]);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, uint8_T c5_outData_data[],
  int32_T c5_outData_sizes[2]);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, real_T
  c5_inData_data[], int32_T c5_inData_sizes[2]);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_c_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c5_inData_data[], int32_T c5_inData_sizes[2]);
static void c5_d_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  uint8_T c5_y_data[], int32_T c5_y_sizes[2]);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, uint8_T c5_outData_data[],
  int32_T c5_outData_sizes[2]);
static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint8_T c5_e_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_i, const char_T *c5_identifier);
static uint8_T c5_f_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static real_T c5_mpower(SFc5_performMissionInstanceStruct *chartInstance, real_T
  c5_a);
static void c5_scalarEg(SFc5_performMissionInstanceStruct *chartInstance);
static void c5_dimagree(SFc5_performMissionInstanceStruct *chartInstance);
static void c5_typecast(SFc5_performMissionInstanceStruct *chartInstance,
  int32_T c5_x, uint8_T c5_y[4]);
static uint16_T c5_rem(SFc5_performMissionInstanceStruct *chartInstance,
  uint16_T c5_x);
static void c5_b_dimagree(SFc5_performMissionInstanceStruct *chartInstance);
static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_g_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void init_dsm_address_info(SFc5_performMissionInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc5_performMissionInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc5_performMission(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_is_active_c5_performMission = 0U;
}

static void initialize_params_c5_performMission
  (SFc5_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_performMission
  (SFc5_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c5_performMission
  (SFc5_performMissionInstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  const mxArray *c5_b_y = NULL;
  uint8_T c5_hoistedGlobal;
  uint8_T c5_u;
  const mxArray *c5_c_y = NULL;
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(2, 1), false);
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", *chartInstance->c5_dataSent_data, 3,
    0U, 1U, 0U, 2, (*chartInstance->c5_dataSent_sizes)[0],
    (*chartInstance->c5_dataSent_sizes)[1]), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_hoistedGlobal = chartInstance->c5_is_active_c5_performMission;
  c5_u = c5_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  uint8_T c5_tmp_data[20];
  int32_T c5_tmp_sizes[2];
  int32_T c5_i0;
  int32_T c5_i1;
  int32_T c5_loop_ub;
  int32_T c5_i2;
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("dataSent", c5_u,
    0)), "dataSent", c5_tmp_data, c5_tmp_sizes);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 0, 1);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 1, c5_tmp_sizes
    [1]);
  c5_i0 = (*chartInstance->c5_dataSent_sizes)[0];
  c5_i1 = (*chartInstance->c5_dataSent_sizes)[1];
  c5_loop_ub = c5_tmp_sizes[0] * c5_tmp_sizes[1] - 1;
  for (c5_i2 = 0; c5_i2 <= c5_loop_ub; c5_i2++) {
    (*chartInstance->c5_dataSent_data)[c5_i2] = c5_tmp_data[c5_i2];
  }

  chartInstance->c5_is_active_c5_performMission = c5_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c5_performMission",
       c5_u, 1)), "is_active_c5_performMission");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_performMission(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  int32_T c5_loop_ub;
  int32_T c5_i3;
  int32_T c5_b_loop_ub;
  int32_T c5_i4;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
  c5_loop_ub = (*chartInstance->c5_payload_sizes)[0] *
    (*chartInstance->c5_payload_sizes)[1] - 1;
  for (c5_i3 = 0; c5_i3 <= c5_loop_ub; c5_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c5_payload_data)[c5_i3], 1U, 1U, 0U,
                          chartInstance->c5_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_stage, 0U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  chartInstance->c5_sfEvent = CALL_EVENT;
  c5_chartstep_c5_performMission(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_performMissionMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  c5_b_loop_ub = (*chartInstance->c5_dataSent_sizes)[0] *
    (*chartInstance->c5_dataSent_sizes)[1] - 1;
  for (c5_i4 = 0; c5_i4 <= c5_b_loop_ub; c5_i4++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c5_dataSent_data)[c5_i4], 2U,
                          1U, 0U, chartInstance->c5_sfEvent, false);
  }
}

static void mdl_start_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c5_chartstep_c5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  real_T c5_hoistedGlobal;
  real_T c5_b_stage;
  int32_T c5_b_payload_sizes[2];
  int32_T c5_payload;
  int32_T c5_b_payload;
  int32_T c5_loop_ub;
  int32_T c5_i5;
  uint32_T c5_debug_family_var_map[12];
  real_T c5_b_payload_data[5];
  real_T c5_pprz_id;
  real_T c5_dataL_overhead;
  real_T c5_message_id;
  real_T c5_dataL_payload;
  uint8_T c5_ck_a;
  uint8_T c5_ck_b;
  uint8_T c5_i;
  uint8_T c5_b_dataSent_data[18];
  int32_T c5_b_dataSent_sizes[2];
  real_T c5_nargin = 2.0;
  real_T c5_nargout = 1.0;
  uint8_T c5_c_dataSent_data[20];
  int32_T c5_c_dataSent_sizes[2];
  int32_T c5_dataSent;
  int32_T c5_b_dataSent;
  boolean_T c5_b0;
  int32_T c5_c_dataSent;
  int32_T c5_d_dataSent;
  int32_T c5_i6;
  int32_T c5_i7;
  int32_T c5_c_payload[1];
  int32_T c5_b_loop_ub;
  int32_T c5_d_payload;
  int32_T c5_e_payload[1];
  int32_T c5_i8;
  uint8_T c5_uv0[6];
  real_T c5_d0;
  uint32_T c5_q0;
  uint32_T c5_qY;
  int32_T c5_i9;
  int32_T c5_i10;
  uint32_T c5_u0;
  uint8_T c5_uv1[4];
  real_T c5_d1;
  int32_T c5_f_payload[1];
  uint8_T c5_u1;
  real_T c5_d2;
  int32_T c5_e_dataSent;
  uint8_T c5_b_i;
  int32_T c5_f_dataSent;
  uint8_T c5_u2;
  int32_T c5_i11;
  int32_T c5_i12;
  uint8_T c5_uv2[4];
  int32_T c5_x_sizes[2];
  int32_T c5_g_payload[1];
  uint16_T c5_u3;
  real_T c5_d3;
  int32_T c5_c_loop_ub;
  int32_T c5_i13;
  int32_T c5_i14;
  uint8_T c5_x_data[20];
  uint16_T c5_u4;
  uint8_T c5_uv3[4];
  real_T c5_b;
  int32_T c5_h_payload[1];
  int32_T c5_nbytes;
  int32_T c5_i_payload;
  int32_T c5_a;
  uint8_T c5_uv4[18];
  int32_T c5_outlen;
  int32_T c5_b_a;
  int32_T c5_c;
  int32_T c5_i15;
  const mxArray *c5_y = NULL;
  static char_T c5_u[45] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 't', 'y', 'p', 'e', 'c', 'a', 's', 't', 'c', '_', 'n', 'o',
    't', 'E', 'n', 'o', 'u', 'g', 'h', 'I', 'n', 'p', 'u', 't', 'E', 'l', 'e',
    'm', 'e', 'n', 't', 's' };

  int32_T c5_outsize[2];
  int32_T c5_i16;
  real_T c5_d4;
  int32_T c5_tmp_sizes[2];
  int32_T c5_i17;
  int32_T c5_i18;
  uint8_T c5_u5;
  int32_T c5_i19;
  int32_T c5_d_loop_ub;
  int32_T c5_i20;
  int32_T c5_i21;
  int32_T c5_i22;
  uint8_T c5_tmp_data[20];
  int32_T c5_g_dataSent;
  uint8_T c5_b_tmp_data[20];
  int32_T c5_b_tmp_sizes[2];
  int32_T c5_h_dataSent;
  int32_T c5_i23;
  int32_T c5_i_dataSent;
  int32_T c5_j_dataSent;
  int32_T c5_e_loop_ub;
  int32_T c5_i24;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
  c5_hoistedGlobal = *chartInstance->c5_stage;
  c5_b_stage = c5_hoistedGlobal;
  c5_b_payload_sizes[0] = 1;
  c5_b_payload_sizes[1] = (*chartInstance->c5_payload_sizes)[1];
  c5_payload = c5_b_payload_sizes[0];
  c5_b_payload = c5_b_payload_sizes[1];
  c5_loop_ub = (*chartInstance->c5_payload_sizes)[0] *
    (*chartInstance->c5_payload_sizes)[1] - 1;
  for (c5_i5 = 0; c5_i5 <= c5_loop_ub; c5_i5++) {
    c5_b_payload_data[c5_i5] = (*chartInstance->c5_payload_data)[c5_i5];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 13U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_pprz_id, 0U, c5_c_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_dataL_overhead, 1U,
    c5_c_sf_marshallOut, c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_message_id, 2U, c5_c_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_dataL_payload, 3U,
    c5_c_sf_marshallOut, c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_ck_a, 4U, c5_e_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_ck_b, 5U, c5_e_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_i, 6U, c5_e_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c5_b_dataSent_data, (const int32_T *)
    &c5_b_dataSent_sizes, NULL, 0, -1, (void *)c5_d_sf_marshallOut, (void *)
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 8U, c5_c_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 9U, c5_c_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_stage, 10U, c5_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN(c5_b_payload_data, (const int32_T *)
    &c5_b_payload_sizes, NULL, 1, 11, (void *)c5_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c5_c_dataSent_data, (const int32_T *)
    &c5_c_dataSent_sizes, NULL, 0, -1, (void *)c5_sf_marshallOut, (void *)
    c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 10);
  c5_b_dataSent_sizes[0] = 1;
  c5_b_dataSent_sizes[1] = 0;
  c5_dataSent = c5_b_dataSent_sizes[0];
  c5_b_dataSent = c5_b_dataSent_sizes[1];
  _SFD_SYMBOL_SWITCH(7U, 7U);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 11);
  c5_b0 = (c5_b_payload_sizes[1] == 0);
  if (CV_EML_IF(0, 1, 0, CV_EML_MCDC(0, 1, 0, !CV_EML_COND(0, 1, 0, c5_b0)))) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 12);
    c5_pprz_id = 153.0;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 13);
    c5_dataL_overhead = 6.0;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 14);
    if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 0, c5_b_stage, 1.0, -1, 0U,
          c5_b_stage == 1.0))) {
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 16);
      c5_message_id = 2.0;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 17);
      c5_dataL_payload = 14.0;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 18);
      (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 884, 10, MAX_uint32_T, 3, 1, c5_b_payload_sizes[1]);
      (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 925, 10, MAX_uint32_T, 4, 1, c5_b_payload_sizes[1]);
      (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 966, 10, MAX_uint32_T, 5, 1, c5_b_payload_sizes[1]);
      c5_e_payload[0] = c5_b_payload_sizes[1];
      c5_d0 = muDoubleScalarRound(c5_b_payload_data[2] * 1.0E+7);
      if (c5_d0 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(4, 0, 5, 1, c5_d0 >= -2.147483648E+9)) {
          c5_i9 = (int32_T)c5_d0;
        } else {
          c5_i9 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(4, 0, 5, 0, c5_d0 >= 2.147483648E+9)) {
        c5_i9 = MAX_int32_T;
      } else {
        c5_i9 = 0;
      }

      c5_typecast(chartInstance, c5_i9, c5_uv1);
      c5_f_payload[0] = c5_b_payload_sizes[1];
      c5_d2 = muDoubleScalarRound(c5_b_payload_data[3] * 1.0E+7);
      if (c5_d2 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(4, 0, 6, 1, c5_d2 >= -2.147483648E+9)) {
          c5_i12 = (int32_T)c5_d2;
        } else {
          c5_i12 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(4, 0, 6, 0, c5_d2 >= 2.147483648E+9)) {
        c5_i12 = MAX_int32_T;
      } else {
        c5_i12 = 0;
      }

      c5_typecast(chartInstance, c5_i12, c5_uv2);
      c5_g_payload[0] = c5_b_payload_sizes[1];
      c5_d3 = muDoubleScalarRound(c5_b_payload_data[4] * 1000.0);
      if (c5_d3 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(4, 0, 7, 1, c5_d3 >= -2.147483648E+9)) {
          c5_i14 = (int32_T)c5_d3;
        } else {
          c5_i14 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(4, 0, 7, 0, c5_d3 >= 2.147483648E+9)) {
        c5_i14 = MAX_int32_T;
      } else {
        c5_i14 = 0;
      }

      c5_typecast(chartInstance, c5_i14, c5_uv3);
      c5_h_payload[0] = c5_b_payload_sizes[1];
      c5_i_payload = c5_b_payload_sizes[1];
      c5_uv4[0] = 153U;
      c5_uv4[1] = 20U;
      c5_uv4[2] = 0U;
      c5_uv4[3] = 2U;
      for (c5_i15 = 0; c5_i15 < 2; c5_i15++) {
        c5_d4 = muDoubleScalarRound(c5_b_payload_data[sf_eml_array_bounds_check
          (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 855, 12,
           MAX_uint32_T, c5_i15 + 1, 1, c5_i_payload) - 1]);
        if (c5_d4 < 256.0) {
          if (CV_SATURATION_EVAL(4, 0, 4, 1, c5_d4 >= 0.0)) {
            c5_u5 = (uint8_T)c5_d4;
          } else {
            c5_u5 = 0U;
          }
        } else if (CV_SATURATION_EVAL(4, 0, 4, 0, c5_d4 >= 256.0)) {
          c5_u5 = MAX_uint8_T;
        } else {
          c5_u5 = 0U;
        }

        c5_uv4[c5_i15 + 4] = c5_u5;
      }

      for (c5_i16 = 0; c5_i16 < 4; c5_i16++) {
        c5_uv4[c5_i16 + 6] = c5_uv1[c5_i16];
      }

      for (c5_i18 = 0; c5_i18 < 4; c5_i18++) {
        c5_uv4[c5_i18 + 10] = c5_uv2[c5_i18];
      }

      for (c5_i21 = 0; c5_i21 < 4; c5_i21++) {
        c5_uv4[c5_i21 + 14] = c5_uv3[c5_i21];
      }

      c5_b_dataSent_sizes[0] = 1;
      c5_b_dataSent_sizes[1] = 18;
      c5_g_dataSent = c5_b_dataSent_sizes[0];
      c5_h_dataSent = c5_b_dataSent_sizes[1];
      for (c5_i23 = 0; c5_i23 < 18; c5_i23++) {
        c5_b_dataSent_data[c5_i23] = c5_uv4[c5_i23];
      }

      _SFD_SYMBOL_SWITCH(7U, 7U);
    } else {
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 20);
      if (CV_EML_IF(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 1, c5_b_stage, 2.0, -1,
            0U, c5_b_stage == 2.0))) {
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 22);
        c5_message_id = 5.0;
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 23);
        c5_dataL_payload = 2.0;
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 24);
        c5_c_payload[0] = c5_b_payload_sizes[1];
        c5_d_payload = c5_b_payload_sizes[1];
        c5_uv0[0] = 153U;
        c5_uv0[1] = 8U;
        c5_uv0[2] = 0U;
        c5_uv0[3] = 5U;
        for (c5_i10 = 0; c5_i10 < 2; c5_i10++) {
          c5_d1 = muDoubleScalarRound
            (c5_b_payload_data[sf_eml_array_bounds_check
             (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 1220, 12,
              MAX_uint32_T, c5_i10 + 1, 1, c5_d_payload) - 1]);
          if (c5_d1 < 256.0) {
            if (CV_SATURATION_EVAL(4, 0, 0, 1, c5_d1 >= 0.0)) {
              c5_u2 = (uint8_T)c5_d1;
            } else {
              c5_u2 = 0U;
            }
          } else if (CV_SATURATION_EVAL(4, 0, 0, 0, c5_d1 >= 256.0)) {
            c5_u2 = MAX_uint8_T;
          } else {
            c5_u2 = 0U;
          }

          c5_uv0[c5_i10 + 4] = c5_u2;
        }

        c5_b_dataSent_sizes[0] = 1;
        c5_b_dataSent_sizes[1] = 6;
        c5_e_dataSent = c5_b_dataSent_sizes[0];
        c5_f_dataSent = c5_b_dataSent_sizes[1];
        for (c5_i11 = 0; c5_i11 < 6; c5_i11++) {
          c5_b_dataSent_data[c5_i11] = c5_uv0[c5_i11];
        }

        _SFD_SYMBOL_SWITCH(7U, 7U);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 29);
    c5_ck_a = 0U;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 30);
    c5_ck_b = 0U;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 31);
    (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 1351, 11, MAX_uint32_T, 2, 1, c5_b_dataSent_sizes[1]);
    c5_q0 = c5_b_dataSent_data[1];
    c5_qY = c5_q0 - 2U;
    if (CV_SATURATION_EVAL(4, 0, 1, 0, c5_qY > c5_q0)) {
      c5_qY = 0U;
    }

    c5_u0 = c5_qY;
    if (CV_SATURATION_EVAL(4, 0, 1, 0, c5_u0 > 255U)) {
      c5_u0 = 255U;
    }

    c5_u1 = (uint8_T)c5_u0;
    c5_i = 2U;
    c5_b_i = 2U;
    while (c5_b_i <= c5_u1) {
      c5_i = c5_b_i;
      CV_EML_FOR(0, 1, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 32);
      c5_u3 = c5_rem(chartInstance, (uint16_T)((uint32_T)c5_ck_a + (uint32_T)
        c5_b_dataSent_data[(uint8_T)sf_eml_array_bounds_check
        (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 1410, 11,
         MAX_uint32_T, (int32_T)c5_i, 1, c5_b_dataSent_sizes[1]) - 1]));
      if (CV_SATURATION_EVAL(4, 0, 2, 0, c5_u3 > 255)) {
        c5_u3 = 255U;
      }

      c5_ck_a = (uint8_T)c5_u3;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 33);
      c5_u4 = c5_rem(chartInstance, (uint16_T)((uint32_T)c5_ck_b + (uint32_T)
        c5_ck_a));
      if (CV_SATURATION_EVAL(4, 0, 3, 0, c5_u4 > 255)) {
        c5_u4 = 255U;
      }

      c5_ck_b = (uint8_T)c5_u4;
      c5_b_i = (uint8_T)((uint32_T)c5_b_i + 1U);
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 0, 0);
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 35);
    c5_x_sizes[0] = 1;
    c5_x_sizes[1] = c5_b_dataSent_sizes[1] + 2;
    c5_c_loop_ub = c5_b_dataSent_sizes[1] - 1;
    for (c5_i13 = 0; c5_i13 <= c5_c_loop_ub; c5_i13++) {
      c5_x_data[c5_x_sizes[0] * c5_i13] =
        c5_b_dataSent_data[c5_b_dataSent_sizes[0] * c5_i13];
    }

    c5_x_data[c5_x_sizes[0] * c5_b_dataSent_sizes[1]] = c5_ck_a;
    c5_x_data[c5_x_sizes[0] * (c5_b_dataSent_sizes[1] + 1)] = c5_ck_b;
    c5_b = (real_T)c5_x_sizes[1];
    c5_nbytes = (int32_T)c5_b;
    c5_a = c5_nbytes;
    c5_outlen = c5_a;
    c5_b_a = c5_outlen;
    c5_c = c5_b_a;
    if (c5_c == c5_nbytes) {
    } else {
      c5_y = NULL;
      sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 10, 0U, 1U, 0U, 2, 1, 45),
                    false);
      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
        1U, 1U, 14, c5_y));
    }

    c5_outsize[0] = 1;
    c5_outsize[1] = c5_outlen;
    c5_tmp_sizes[0] = 1;
    c5_tmp_sizes[1] = c5_outsize[1];
    c5_i17 = c5_tmp_sizes[0];
    c5_i19 = c5_tmp_sizes[1];
    c5_d_loop_ub = c5_outsize[1] - 1;
    for (c5_i20 = 0; c5_i20 <= c5_d_loop_ub; c5_i20++) {
      c5_tmp_data[c5_i20] = 0U;
    }

    for (c5_i22 = 0; c5_i22 < 2; c5_i22++) {
      c5_b_tmp_sizes[c5_i22] = c5_tmp_sizes[c5_i22];
    }

    memcpy(&c5_b_tmp_data[0], &c5_x_data[0], (size_t)c5_outlen * sizeof(uint8_T));
    _SFD_DIM_SIZE_GEQ_CHECK(20, c5_b_tmp_sizes[1], 2);
    c5_c_dataSent_sizes[0] = 1;
    c5_c_dataSent_sizes[1] = c5_b_tmp_sizes[1];
    c5_i_dataSent = c5_c_dataSent_sizes[0];
    c5_j_dataSent = c5_c_dataSent_sizes[1];
    c5_e_loop_ub = c5_b_tmp_sizes[0] * c5_b_tmp_sizes[1] - 1;
    for (c5_i24 = 0; c5_i24 <= c5_e_loop_ub; c5_i24++) {
      c5_c_dataSent_data[c5_i24] = c5_b_tmp_data[c5_i24];
    }

    _SFD_SYMBOL_SWITCH(7U, 12U);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 37);
    _SFD_DIM_SIZE_GEQ_CHECK(20, 0, 2);
    c5_c_dataSent_sizes[0] = 1;
    c5_c_dataSent_sizes[1] = 0;
    c5_c_dataSent = c5_c_dataSent_sizes[0];
    c5_d_dataSent = c5_c_dataSent_sizes[1];
    _SFD_SYMBOL_SWITCH(7U, 12U);
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -37);
  _SFD_SYMBOL_SCOPE_POP();
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 0, 1);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 1,
    c5_c_dataSent_sizes[1]);
  c5_i6 = (*chartInstance->c5_dataSent_sizes)[0];
  c5_i7 = (*chartInstance->c5_dataSent_sizes)[1];
  c5_b_loop_ub = c5_c_dataSent_sizes[0] * c5_c_dataSent_sizes[1] - 1;
  for (c5_i8 = 0; c5_i8 <= c5_b_loop_ub; c5_i8++) {
    (*chartInstance->c5_dataSent_data)[c5_i8] = c5_c_dataSent_data[c5_i8];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
}

static void initSimStructsc5_performMission(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  (void)c5_chartNumber;
  (void)c5_instanceNumber;
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c5_inData_data[], int32_T c5_inData_sizes[2])
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u_sizes[2];
  int32_T c5_u;
  int32_T c5_b_u;
  int32_T c5_loop_ub;
  int32_T c5_i25;
  const mxArray *c5_y = NULL;
  uint8_T c5_u_data[20];
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u_sizes[0] = 1;
  c5_u_sizes[1] = c5_inData_sizes[1];
  c5_u = c5_u_sizes[0];
  c5_b_u = c5_u_sizes[1];
  c5_loop_ub = c5_inData_sizes[0] * c5_inData_sizes[1] - 1;
  for (c5_i25 = 0; c5_i25 <= c5_loop_ub; c5_i25++) {
    c5_u_data[c5_i25] = c5_inData_data[c5_i25];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u_data, 3, 0U, 1U, 0U, 2,
    c5_u_sizes[0], c5_u_sizes[1]), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_emlrt_marshallIn(SFc5_performMissionInstanceStruct *chartInstance,
  const mxArray *c5_dataSent, const char_T *c5_identifier, uint8_T c5_y_data[],
  int32_T c5_y_sizes[2])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_dataSent), &c5_thisId,
                        c5_y_data, c5_y_sizes);
  sf_mex_destroy(&c5_dataSent);
}

static void c5_b_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  uint8_T c5_y_data[], int32_T c5_y_sizes[2])
{
  int32_T c5_i26;
  int32_T c5_i27;
  uint32_T c5_uv5[2];
  uint8_T c5_tmp_data[20];
  boolean_T c5_bv0[2];
  int32_T c5_tmp_sizes[2];
  static boolean_T c5_bv1[2] = { false, true };

  int32_T c5_y;
  int32_T c5_b_y;
  int32_T c5_loop_ub;
  int32_T c5_i28;
  (void)chartInstance;
  for (c5_i26 = 0; c5_i26 < 2; c5_i26++) {
    c5_uv5[c5_i26] = 1U + 19U * (uint32_T)c5_i26;
  }

  for (c5_i27 = 0; c5_i27 < 2; c5_i27++) {
    c5_bv0[c5_i27] = c5_bv1[c5_i27];
  }

  sf_mex_import_vs(c5_parentId, sf_mex_dup(c5_u), c5_tmp_data, 1, 3, 0U, 1, 0U,
                   2, c5_bv0, c5_uv5, c5_tmp_sizes);
  c5_y_sizes[0] = 1;
  c5_y_sizes[1] = c5_tmp_sizes[1];
  c5_y = c5_y_sizes[0];
  c5_b_y = c5_y_sizes[1];
  c5_loop_ub = c5_tmp_sizes[0] * c5_tmp_sizes[1] - 1;
  for (c5_i28 = 0; c5_i28 <= c5_loop_ub; c5_i28++) {
    c5_y_data[c5_i28] = c5_tmp_data[c5_i28];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, uint8_T c5_outData_data[],
  int32_T c5_outData_sizes[2])
{
  const mxArray *c5_dataSent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y_data[20];
  int32_T c5_y_sizes[2];
  int32_T c5_loop_ub;
  int32_T c5_i29;
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_dataSent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_dataSent), &c5_thisId,
                        c5_y_data, c5_y_sizes);
  sf_mex_destroy(&c5_dataSent);
  c5_outData_sizes[0] = 1;
  c5_outData_sizes[1] = c5_y_sizes[1];
  c5_loop_ub = c5_y_sizes[1] - 1;
  for (c5_i29 = 0; c5_i29 <= c5_loop_ub; c5_i29++) {
    c5_outData_data[c5_outData_sizes[0] * c5_i29] = c5_y_data[c5_y_sizes[0] *
      c5_i29];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, real_T
  c5_inData_data[], int32_T c5_inData_sizes[2])
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u_sizes[2];
  int32_T c5_u;
  int32_T c5_b_u;
  int32_T c5_loop_ub;
  int32_T c5_i30;
  const mxArray *c5_y = NULL;
  real_T c5_u_data[5];
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u_sizes[0] = 1;
  c5_u_sizes[1] = c5_inData_sizes[1];
  c5_u = c5_u_sizes[0];
  c5_b_u = c5_u_sizes[1];
  c5_loop_ub = c5_inData_sizes[0] * c5_inData_sizes[1] - 1;
  for (c5_i30 = 0; c5_i30 <= c5_loop_ub; c5_i30++) {
    c5_u_data[c5_i30] = c5_inData_data[c5_i30];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u_data, 0, 0U, 1U, 0U, 2,
    c5_u_sizes[0], c5_u_sizes[1]), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_c_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d5;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d5, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d5;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nargout;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_nargout = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c5_inData_data[], int32_T c5_inData_sizes[2])
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u_sizes[2];
  int32_T c5_u;
  int32_T c5_b_u;
  int32_T c5_loop_ub;
  int32_T c5_i31;
  const mxArray *c5_y = NULL;
  uint8_T c5_u_data[18];
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u_sizes[0] = 1;
  c5_u_sizes[1] = c5_inData_sizes[1];
  c5_u = c5_u_sizes[0];
  c5_b_u = c5_u_sizes[1];
  c5_loop_ub = c5_inData_sizes[0] * c5_inData_sizes[1] - 1;
  for (c5_i31 = 0; c5_i31 <= c5_loop_ub; c5_i31++) {
    c5_u_data[c5_i31] = c5_inData_data[c5_i31];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u_data, 3, 0U, 1U, 0U, 2,
    c5_u_sizes[0], c5_u_sizes[1]), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_d_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  uint8_T c5_y_data[], int32_T c5_y_sizes[2])
{
  int32_T c5_i32;
  int32_T c5_i33;
  uint32_T c5_uv6[2];
  uint8_T c5_tmp_data[18];
  boolean_T c5_bv2[2];
  int32_T c5_tmp_sizes[2];
  static boolean_T c5_bv3[2] = { false, true };

  int32_T c5_y;
  int32_T c5_b_y;
  int32_T c5_loop_ub;
  int32_T c5_i34;
  (void)chartInstance;
  for (c5_i32 = 0; c5_i32 < 2; c5_i32++) {
    c5_uv6[c5_i32] = 1U + 17U * (uint32_T)c5_i32;
  }

  for (c5_i33 = 0; c5_i33 < 2; c5_i33++) {
    c5_bv2[c5_i33] = c5_bv3[c5_i33];
  }

  sf_mex_import_vs(c5_parentId, sf_mex_dup(c5_u), c5_tmp_data, 1, 3, 0U, 1, 0U,
                   2, c5_bv2, c5_uv6, c5_tmp_sizes);
  c5_y_sizes[0] = 1;
  c5_y_sizes[1] = c5_tmp_sizes[1];
  c5_y = c5_y_sizes[0];
  c5_b_y = c5_y_sizes[1];
  c5_loop_ub = c5_tmp_sizes[0] * c5_tmp_sizes[1] - 1;
  for (c5_i34 = 0; c5_i34 <= c5_loop_ub; c5_i34++) {
    c5_y_data[c5_i34] = c5_tmp_data[c5_i34];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, uint8_T c5_outData_data[],
  int32_T c5_outData_sizes[2])
{
  const mxArray *c5_dataSent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y_data[18];
  int32_T c5_y_sizes[2];
  int32_T c5_loop_ub;
  int32_T c5_i35;
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_dataSent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_dataSent), &c5_thisId,
                        c5_y_data, c5_y_sizes);
  sf_mex_destroy(&c5_dataSent);
  c5_outData_sizes[0] = 1;
  c5_outData_sizes[1] = c5_y_sizes[1];
  c5_loop_ub = c5_y_sizes[1] - 1;
  for (c5_i35 = 0; c5_i35 <= c5_loop_ub; c5_i35++) {
    c5_outData_data[c5_outData_sizes[0] * c5_i35] = c5_y_data[c5_y_sizes[0] *
      c5_i35];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint8_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint8_T c5_e_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_i, const char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_i), &c5_thisId);
  sf_mex_destroy(&c5_i);
  return c5_y;
}

static uint8_T c5_f_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u6;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u6, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u6;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_i;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y;
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_i = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_i), &c5_thisId);
  sf_mex_destroy(&c5_i);
  *(uint8_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_performMission_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c5_nameCaptureInfo;
}

static real_T c5_mpower(SFc5_performMissionInstanceStruct *chartInstance, real_T
  c5_a)
{
  (void)chartInstance;
  (void)c5_a;
  return 1.0E+7;
}

static void c5_scalarEg(SFc5_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_dimagree(SFc5_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_typecast(SFc5_performMissionInstanceStruct *chartInstance,
  int32_T c5_x, uint8_T c5_y[4])
{
  (void)chartInstance;
  memcpy(&c5_y[0], &c5_x, (size_t)4 * sizeof(uint8_T));
}

static uint16_T c5_rem(SFc5_performMissionInstanceStruct *chartInstance,
  uint16_T c5_x)
{
  uint16_T c5_b_x;
  uint16_T c5_c_x;
  uint16_T c5_u0;
  (void)chartInstance;
  c5_b_x = c5_x;
  c5_c_x = c5_b_x;
  c5_u0 = c5_c_x;
  return (uint16_T)(c5_u0 % 256U);
}

static void c5_b_dimagree(SFc5_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_g_emlrt_marshallIn(SFc5_performMissionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i36;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i36, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i36;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static void init_dsm_address_info(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc5_performMissionInstanceStruct
  *chartInstance)
{
  chartInstance->c5_stage = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c5_payload_data = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_payload_sizes = (int32_T (*)[2])
    ssGetCurrentInputPortDimensions_wrapper(chartInstance->S, 1);
  sf_mex_size_one_check(((*chartInstance->c5_payload_sizes)[0U] == 0) &&
                        (!((*chartInstance->c5_payload_sizes)[1U] == 0)),
                        "payload");
  chartInstance->c5_dataSent_data = (uint8_T (*)[20])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c5_dataSent_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c5_performMission_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2497530181U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(651598725U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2633137128U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1461876788U);
}

mxArray* sf_c5_performMission_get_post_codegen_info(void);
mxArray *sf_c5_performMission_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ciL3xGhfPiV9r5k34lrgoE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(5);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(20);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c5_performMission_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_performMission_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_performMission_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("memcpy");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c5_performMission_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c5_performMission_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c5_performMission(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"dataSent\",},{M[8],M[0],T\"is_active_c5_performMission\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_performMission_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_performMissionInstanceStruct *chartInstance =
      (SFc5_performMissionInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _performMissionMachineNumber_,
           5,
           1,
           1,
           0,
           3,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_performMissionMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_performMissionMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _performMissionMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"stage");
          _SFD_SET_DATA_PROPS(1,1,1,0,"payload");
          _SFD_SET_DATA_PROPS(2,2,0,1,"dataSent");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,3,0,8,0,1,0,1,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1611);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,1214,-1,1233);
        _SFD_CV_INIT_EML_SATURATION(0,1,1,1351,-1,1364);
        _SFD_CV_INIT_EML_SATURATION(0,1,2,1380,-1,1436);
        _SFD_CV_INIT_EML_SATURATION(0,1,3,1453,-1,1502);
        _SFD_CV_INIT_EML_SATURATION(0,1,4,849,-1,868);
        _SFD_CV_INIT_EML_SATURATION(0,1,5,878,-1,900);
        _SFD_CV_INIT_EML_SATURATION(0,1,6,919,-1,941);
        _SFD_CV_INIT_EML_SATURATION(0,1,7,960,-1,982);
        _SFD_CV_INIT_EML_IF(0,1,0,489,509,1567,1609);
        _SFD_CV_INIT_EML_IF(0,1,1,624,637,998,1015);
        _SFD_CV_INIT_EML_IF(0,1,2,998,1015,-1,1015);
        _SFD_CV_INIT_EML_FOR(0,1,0,1343,1365,1511);

        {
          static int condStart[] = { 493 };

          static int condEnd[] = { 509 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,492,509,1,0,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,627,637,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,1005,1015,-1,0);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 5U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 20U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)
            c5_sf_marshallIn);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _performMissionMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_performMissionInstanceStruct *chartInstance =
      (SFc5_performMissionInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c5_stage);
        _SFD_SET_DATA_VALUE_PTR_VAR_DIM(1U, *chartInstance->c5_payload_data,
          (void *)chartInstance->c5_payload_sizes);
        _SFD_SET_DATA_VALUE_PTR_VAR_DIM(2U, *chartInstance->c5_dataSent_data,
          (void *)chartInstance->c5_dataSent_sizes);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sFOnX0uHF2rOkquaGiHqMOG";
}

static void sf_opaque_initialize_c5_performMission(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_performMissionInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c5_performMission((SFc5_performMissionInstanceStruct*)
    chartInstanceVar);
  initialize_c5_performMission((SFc5_performMissionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c5_performMission(void *chartInstanceVar)
{
  enable_c5_performMission((SFc5_performMissionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_performMission(void *chartInstanceVar)
{
  disable_c5_performMission((SFc5_performMissionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c5_performMission(void *chartInstanceVar)
{
  sf_gateway_c5_performMission((SFc5_performMissionInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c5_performMission(SimStruct* S)
{
  return get_sim_state_c5_performMission((SFc5_performMissionInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c5_performMission(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c5_performMission((SFc5_performMissionInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c5_performMission(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_performMissionInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_performMission_optimization_info();
    }

    finalize_c5_performMission((SFc5_performMissionInstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_performMission((SFc5_performMissionInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_performMission(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_performMission((SFc5_performMissionInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c5_performMission(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_performMission_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 5);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1165334381U));
  ssSetChecksum1(S,(3423121656U));
  ssSetChecksum2(S,(3696942803U));
  ssSetChecksum3(S,(4198819279U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_performMission(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_performMission(SimStruct *S)
{
  SFc5_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc5_performMissionInstanceStruct *)utMalloc(sizeof
    (SFc5_performMissionInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc5_performMissionInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c5_performMission;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c5_performMission;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c5_performMission;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_performMission;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_performMission;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c5_performMission;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c5_performMission;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c5_performMission;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_performMission;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_performMission;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_performMission;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c5_performMission(chartInstance);
}

void c5_performMission_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_performMission(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_performMission(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_performMission(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_performMission_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
