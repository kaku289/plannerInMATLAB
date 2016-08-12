/* Include files */

#include "performMission_sfun.h"
#include "c3_performMission.h"
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
static const char * c3_debug_family_names[12] = { "pprz_id", "dataL_overhead",
  "message_id", "dataL_payload", "ck_a", "ck_b", "i", "dataSent", "nargin",
  "nargout", "stage", "payload" };

/* Function Declarations */
static void initialize_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance);
static void initialize_params_c3_performMission
  (SFc3_performMissionInstanceStruct *chartInstance);
static void enable_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance);
static void disable_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance);
static void c3_update_debugger_state_c3_performMission
  (SFc3_performMissionInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_performMission
  (SFc3_performMissionInstanceStruct *chartInstance);
static void set_sim_state_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance);
static void sf_gateway_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance);
static void mdl_start_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance);
static void c3_chartstep_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance);
static void initSimStructsc3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c3_inData_data[], int32_T c3_inData_sizes[2]);
static void c3_emlrt_marshallIn(SFc3_performMissionInstanceStruct *chartInstance,
  const mxArray *c3_dataSent, const char_T *c3_identifier, uint8_T c3_y_data[],
  int32_T c3_y_sizes[2]);
static void c3_b_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  uint8_T c3_y_data[], int32_T c3_y_sizes[2]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, uint8_T c3_outData_data[],
  int32_T c3_outData_sizes[2]);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, real_T
  c3_inData_data[], int32_T c3_inData_sizes[2]);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_c_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c3_inData_data[], int32_T c3_inData_sizes[2]);
static void c3_d_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  uint8_T c3_y_data[], int32_T c3_y_sizes[2]);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, uint8_T c3_outData_data[],
  int32_T c3_outData_sizes[2]);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static uint8_T c3_e_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_i, const char_T *c3_identifier);
static uint8_T c3_f_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static real_T c3_mpower(SFc3_performMissionInstanceStruct *chartInstance, real_T
  c3_a);
static void c3_scalarEg(SFc3_performMissionInstanceStruct *chartInstance);
static void c3_dimagree(SFc3_performMissionInstanceStruct *chartInstance);
static void c3_typecast(SFc3_performMissionInstanceStruct *chartInstance,
  int32_T c3_x, uint8_T c3_y[4]);
static uint16_T c3_rem(SFc3_performMissionInstanceStruct *chartInstance,
  uint16_T c3_x);
static void c3_b_dimagree(SFc3_performMissionInstanceStruct *chartInstance);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_g_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void init_dsm_address_info(SFc3_performMissionInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc3_performMissionInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc3_performMission(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_is_active_c3_performMission = 0U;
}

static void initialize_params_c3_performMission
  (SFc3_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_performMission
  (SFc3_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c3_performMission
  (SFc3_performMissionInstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  const mxArray *c3_b_y = NULL;
  uint8_T c3_hoistedGlobal;
  uint8_T c3_u;
  const mxArray *c3_c_y = NULL;
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(2, 1), false);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", *chartInstance->c3_dataSent_data, 3,
    0U, 1U, 0U, 2, (*chartInstance->c3_dataSent_sizes)[0],
    (*chartInstance->c3_dataSent_sizes)[1]), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_hoistedGlobal = chartInstance->c3_is_active_c3_performMission;
  c3_u = c3_hoistedGlobal;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  uint8_T c3_tmp_data[20];
  int32_T c3_tmp_sizes[2];
  int32_T c3_i0;
  int32_T c3_i1;
  int32_T c3_loop_ub;
  int32_T c3_i2;
  chartInstance->c3_doneDoubleBufferReInit = true;
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("dataSent", c3_u,
    0)), "dataSent", c3_tmp_data, c3_tmp_sizes);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 0, 1);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 1, c3_tmp_sizes
    [1]);
  c3_i0 = (*chartInstance->c3_dataSent_sizes)[0];
  c3_i1 = (*chartInstance->c3_dataSent_sizes)[1];
  c3_loop_ub = c3_tmp_sizes[0] * c3_tmp_sizes[1] - 1;
  for (c3_i2 = 0; c3_i2 <= c3_loop_ub; c3_i2++) {
    (*chartInstance->c3_dataSent_data)[c3_i2] = c3_tmp_data[c3_i2];
  }

  chartInstance->c3_is_active_c3_performMission = c3_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c3_performMission",
       c3_u, 1)), "is_active_c3_performMission");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_performMission(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  int32_T c3_loop_ub;
  int32_T c3_i3;
  int32_T c3_b_loop_ub;
  int32_T c3_i4;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  c3_loop_ub = (*chartInstance->c3_payload_sizes)[0] *
    (*chartInstance->c3_payload_sizes)[1] - 1;
  for (c3_i3 = 0; c3_i3 <= c3_loop_ub; c3_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_payload_data)[c3_i3], 1U, 1U, 0U,
                          chartInstance->c3_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_stage, 0U, 1U, 0U,
                        chartInstance->c3_sfEvent, false);
  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_performMission(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_performMissionMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  c3_b_loop_ub = (*chartInstance->c3_dataSent_sizes)[0] *
    (*chartInstance->c3_dataSent_sizes)[1] - 1;
  for (c3_i4 = 0; c3_i4 <= c3_b_loop_ub; c3_i4++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c3_dataSent_data)[c3_i4], 2U,
                          1U, 0U, chartInstance->c3_sfEvent, false);
  }
}

static void mdl_start_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c3_chartstep_c3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  real_T c3_hoistedGlobal;
  real_T c3_b_stage;
  int32_T c3_b_payload_sizes[2];
  int32_T c3_payload;
  int32_T c3_b_payload;
  int32_T c3_loop_ub;
  int32_T c3_i5;
  uint32_T c3_debug_family_var_map[12];
  real_T c3_b_payload_data[5];
  real_T c3_pprz_id;
  real_T c3_dataL_overhead;
  real_T c3_message_id;
  real_T c3_dataL_payload;
  uint8_T c3_ck_a;
  uint8_T c3_ck_b;
  uint8_T c3_i;
  uint8_T c3_b_dataSent_data[18];
  int32_T c3_b_dataSent_sizes[2];
  real_T c3_nargin = 2.0;
  real_T c3_nargout = 1.0;
  uint8_T c3_c_dataSent_data[20];
  int32_T c3_c_dataSent_sizes[2];
  int32_T c3_dataSent;
  int32_T c3_b_dataSent;
  boolean_T c3_b0;
  int32_T c3_c_dataSent;
  int32_T c3_d_dataSent;
  int32_T c3_i6;
  int32_T c3_i7;
  int32_T c3_c_payload[1];
  int32_T c3_b_loop_ub;
  int32_T c3_d_payload;
  int32_T c3_e_payload[1];
  int32_T c3_i8;
  uint8_T c3_uv0[6];
  real_T c3_d0;
  uint32_T c3_q0;
  uint32_T c3_qY;
  int32_T c3_i9;
  int32_T c3_i10;
  uint32_T c3_u0;
  uint8_T c3_uv1[4];
  real_T c3_d1;
  int32_T c3_f_payload[1];
  uint8_T c3_u1;
  real_T c3_d2;
  int32_T c3_e_dataSent;
  uint8_T c3_b_i;
  int32_T c3_f_dataSent;
  uint8_T c3_u2;
  int32_T c3_i11;
  int32_T c3_i12;
  uint8_T c3_uv2[4];
  int32_T c3_x_sizes[2];
  int32_T c3_g_payload[1];
  uint16_T c3_u3;
  real_T c3_d3;
  int32_T c3_c_loop_ub;
  int32_T c3_i13;
  int32_T c3_i14;
  uint8_T c3_x_data[20];
  uint16_T c3_u4;
  uint8_T c3_uv3[4];
  real_T c3_b;
  int32_T c3_h_payload[1];
  int32_T c3_nbytes;
  int32_T c3_i_payload;
  int32_T c3_a;
  uint8_T c3_uv4[18];
  int32_T c3_outlen;
  int32_T c3_b_a;
  int32_T c3_c;
  int32_T c3_i15;
  const mxArray *c3_y = NULL;
  static char_T c3_u[45] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 't', 'y', 'p', 'e', 'c', 'a', 's', 't', 'c', '_', 'n', 'o',
    't', 'E', 'n', 'o', 'u', 'g', 'h', 'I', 'n', 'p', 'u', 't', 'E', 'l', 'e',
    'm', 'e', 'n', 't', 's' };

  int32_T c3_outsize[2];
  int32_T c3_i16;
  real_T c3_d4;
  int32_T c3_tmp_sizes[2];
  int32_T c3_i17;
  int32_T c3_i18;
  uint8_T c3_u5;
  int32_T c3_i19;
  int32_T c3_d_loop_ub;
  int32_T c3_i20;
  int32_T c3_i21;
  int32_T c3_i22;
  uint8_T c3_tmp_data[20];
  int32_T c3_g_dataSent;
  uint8_T c3_b_tmp_data[20];
  int32_T c3_b_tmp_sizes[2];
  int32_T c3_h_dataSent;
  int32_T c3_i23;
  int32_T c3_i_dataSent;
  int32_T c3_j_dataSent;
  int32_T c3_e_loop_ub;
  int32_T c3_i24;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  c3_hoistedGlobal = *chartInstance->c3_stage;
  c3_b_stage = c3_hoistedGlobal;
  c3_b_payload_sizes[0] = 1;
  c3_b_payload_sizes[1] = (*chartInstance->c3_payload_sizes)[1];
  c3_payload = c3_b_payload_sizes[0];
  c3_b_payload = c3_b_payload_sizes[1];
  c3_loop_ub = (*chartInstance->c3_payload_sizes)[0] *
    (*chartInstance->c3_payload_sizes)[1] - 1;
  for (c3_i5 = 0; c3_i5 <= c3_loop_ub; c3_i5++) {
    c3_b_payload_data[c3_i5] = (*chartInstance->c3_payload_data)[c3_i5];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 13U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_pprz_id, 0U, c3_c_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_dataL_overhead, 1U,
    c3_c_sf_marshallOut, c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_message_id, 2U, c3_c_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_dataL_payload, 3U,
    c3_c_sf_marshallOut, c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_ck_a, 4U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_ck_b, 5U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_i, 6U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c3_b_dataSent_data, (const int32_T *)
    &c3_b_dataSent_sizes, NULL, 0, -1, (void *)c3_d_sf_marshallOut, (void *)
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 8U, c3_c_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 9U, c3_c_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_b_stage, 10U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN(c3_b_payload_data, (const int32_T *)
    &c3_b_payload_sizes, NULL, 1, 11, (void *)c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c3_c_dataSent_data, (const int32_T *)
    &c3_c_dataSent_sizes, NULL, 0, -1, (void *)c3_sf_marshallOut, (void *)
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 10);
  c3_b_dataSent_sizes[0] = 1;
  c3_b_dataSent_sizes[1] = 0;
  c3_dataSent = c3_b_dataSent_sizes[0];
  c3_b_dataSent = c3_b_dataSent_sizes[1];
  _SFD_SYMBOL_SWITCH(7U, 7U);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 11);
  c3_b0 = (c3_b_payload_sizes[1] == 0);
  if (CV_EML_IF(0, 1, 0, CV_EML_MCDC(0, 1, 0, !CV_EML_COND(0, 1, 0, c3_b0)))) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
    c3_pprz_id = 153.0;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 13);
    c3_dataL_overhead = 6.0;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 14);
    if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 0, c3_b_stage, 1.0, -1, 0U,
          c3_b_stage == 1.0))) {
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 16);
      c3_message_id = 2.0;
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 17);
      c3_dataL_payload = 14.0;
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 18);
      (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 884, 10, MAX_uint32_T, 3, 1, c3_b_payload_sizes[1]);
      (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 925, 10, MAX_uint32_T, 4, 1, c3_b_payload_sizes[1]);
      (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 966, 10, MAX_uint32_T, 5, 1, c3_b_payload_sizes[1]);
      c3_e_payload[0] = c3_b_payload_sizes[1];
      c3_d0 = muDoubleScalarRound(c3_b_payload_data[2] * 1.0E+7);
      if (c3_d0 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(4, 0, 5, 1, c3_d0 >= -2.147483648E+9)) {
          c3_i9 = (int32_T)c3_d0;
        } else {
          c3_i9 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(4, 0, 5, 0, c3_d0 >= 2.147483648E+9)) {
        c3_i9 = MAX_int32_T;
      } else {
        c3_i9 = 0;
      }

      c3_typecast(chartInstance, c3_i9, c3_uv1);
      c3_f_payload[0] = c3_b_payload_sizes[1];
      c3_d2 = muDoubleScalarRound(c3_b_payload_data[3] * 1.0E+7);
      if (c3_d2 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(4, 0, 6, 1, c3_d2 >= -2.147483648E+9)) {
          c3_i12 = (int32_T)c3_d2;
        } else {
          c3_i12 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(4, 0, 6, 0, c3_d2 >= 2.147483648E+9)) {
        c3_i12 = MAX_int32_T;
      } else {
        c3_i12 = 0;
      }

      c3_typecast(chartInstance, c3_i12, c3_uv2);
      c3_g_payload[0] = c3_b_payload_sizes[1];
      c3_d3 = muDoubleScalarRound(c3_b_payload_data[4] * 1000.0);
      if (c3_d3 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(4, 0, 7, 1, c3_d3 >= -2.147483648E+9)) {
          c3_i14 = (int32_T)c3_d3;
        } else {
          c3_i14 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(4, 0, 7, 0, c3_d3 >= 2.147483648E+9)) {
        c3_i14 = MAX_int32_T;
      } else {
        c3_i14 = 0;
      }

      c3_typecast(chartInstance, c3_i14, c3_uv3);
      c3_h_payload[0] = c3_b_payload_sizes[1];
      c3_i_payload = c3_b_payload_sizes[1];
      c3_uv4[0] = 153U;
      c3_uv4[1] = 20U;
      c3_uv4[2] = 0U;
      c3_uv4[3] = 2U;
      for (c3_i15 = 0; c3_i15 < 2; c3_i15++) {
        c3_d4 = muDoubleScalarRound(c3_b_payload_data[sf_eml_array_bounds_check
          (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 855, 12,
           MAX_uint32_T, c3_i15 + 1, 1, c3_i_payload) - 1]);
        if (c3_d4 < 256.0) {
          if (CV_SATURATION_EVAL(4, 0, 4, 1, c3_d4 >= 0.0)) {
            c3_u5 = (uint8_T)c3_d4;
          } else {
            c3_u5 = 0U;
          }
        } else if (CV_SATURATION_EVAL(4, 0, 4, 0, c3_d4 >= 256.0)) {
          c3_u5 = MAX_uint8_T;
        } else {
          c3_u5 = 0U;
        }

        c3_uv4[c3_i15 + 4] = c3_u5;
      }

      for (c3_i16 = 0; c3_i16 < 4; c3_i16++) {
        c3_uv4[c3_i16 + 6] = c3_uv1[c3_i16];
      }

      for (c3_i18 = 0; c3_i18 < 4; c3_i18++) {
        c3_uv4[c3_i18 + 10] = c3_uv2[c3_i18];
      }

      for (c3_i21 = 0; c3_i21 < 4; c3_i21++) {
        c3_uv4[c3_i21 + 14] = c3_uv3[c3_i21];
      }

      c3_b_dataSent_sizes[0] = 1;
      c3_b_dataSent_sizes[1] = 18;
      c3_g_dataSent = c3_b_dataSent_sizes[0];
      c3_h_dataSent = c3_b_dataSent_sizes[1];
      for (c3_i23 = 0; c3_i23 < 18; c3_i23++) {
        c3_b_dataSent_data[c3_i23] = c3_uv4[c3_i23];
      }

      _SFD_SYMBOL_SWITCH(7U, 7U);
    } else {
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 20);
      if (CV_EML_IF(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 1, c3_b_stage, 2.0, -1,
            0U, c3_b_stage == 2.0))) {
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 22);
        c3_message_id = 5.0;
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 23);
        c3_dataL_payload = 2.0;
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 24);
        c3_c_payload[0] = c3_b_payload_sizes[1];
        c3_d_payload = c3_b_payload_sizes[1];
        c3_uv0[0] = 153U;
        c3_uv0[1] = 8U;
        c3_uv0[2] = 0U;
        c3_uv0[3] = 5U;
        for (c3_i10 = 0; c3_i10 < 2; c3_i10++) {
          c3_d1 = muDoubleScalarRound
            (c3_b_payload_data[sf_eml_array_bounds_check
             (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 1220, 12,
              MAX_uint32_T, c3_i10 + 1, 1, c3_d_payload) - 1]);
          if (c3_d1 < 256.0) {
            if (CV_SATURATION_EVAL(4, 0, 0, 1, c3_d1 >= 0.0)) {
              c3_u2 = (uint8_T)c3_d1;
            } else {
              c3_u2 = 0U;
            }
          } else if (CV_SATURATION_EVAL(4, 0, 0, 0, c3_d1 >= 256.0)) {
            c3_u2 = MAX_uint8_T;
          } else {
            c3_u2 = 0U;
          }

          c3_uv0[c3_i10 + 4] = c3_u2;
        }

        c3_b_dataSent_sizes[0] = 1;
        c3_b_dataSent_sizes[1] = 6;
        c3_e_dataSent = c3_b_dataSent_sizes[0];
        c3_f_dataSent = c3_b_dataSent_sizes[1];
        for (c3_i11 = 0; c3_i11 < 6; c3_i11++) {
          c3_b_dataSent_data[c3_i11] = c3_uv0[c3_i11];
        }

        _SFD_SYMBOL_SWITCH(7U, 7U);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
    c3_ck_a = 0U;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 30);
    c3_ck_b = 0U;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 31);
    (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 1351, 11, MAX_uint32_T, 2, 1, c3_b_dataSent_sizes[1]);
    c3_q0 = c3_b_dataSent_data[1];
    c3_qY = c3_q0 - 2U;
    if (CV_SATURATION_EVAL(4, 0, 1, 0, c3_qY > c3_q0)) {
      c3_qY = 0U;
    }

    c3_u0 = c3_qY;
    if (CV_SATURATION_EVAL(4, 0, 1, 0, c3_u0 > 255U)) {
      c3_u0 = 255U;
    }

    c3_u1 = (uint8_T)c3_u0;
    c3_i = 2U;
    c3_b_i = 2U;
    while (c3_b_i <= c3_u1) {
      c3_i = c3_b_i;
      CV_EML_FOR(0, 1, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 32);
      c3_u3 = c3_rem(chartInstance, (uint16_T)((uint32_T)c3_ck_a + (uint32_T)
        c3_b_dataSent_data[(uint8_T)sf_eml_array_bounds_check
        (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 1410, 11,
         MAX_uint32_T, (int32_T)c3_i, 1, c3_b_dataSent_sizes[1]) - 1]));
      if (CV_SATURATION_EVAL(4, 0, 2, 0, c3_u3 > 255)) {
        c3_u3 = 255U;
      }

      c3_ck_a = (uint8_T)c3_u3;
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 33);
      c3_u4 = c3_rem(chartInstance, (uint16_T)((uint32_T)c3_ck_b + (uint32_T)
        c3_ck_a));
      if (CV_SATURATION_EVAL(4, 0, 3, 0, c3_u4 > 255)) {
        c3_u4 = 255U;
      }

      c3_ck_b = (uint8_T)c3_u4;
      c3_b_i = (uint8_T)((uint32_T)c3_b_i + 1U);
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 0, 0);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 35);
    c3_x_sizes[0] = 1;
    c3_x_sizes[1] = c3_b_dataSent_sizes[1] + 2;
    c3_c_loop_ub = c3_b_dataSent_sizes[1] - 1;
    for (c3_i13 = 0; c3_i13 <= c3_c_loop_ub; c3_i13++) {
      c3_x_data[c3_x_sizes[0] * c3_i13] =
        c3_b_dataSent_data[c3_b_dataSent_sizes[0] * c3_i13];
    }

    c3_x_data[c3_x_sizes[0] * c3_b_dataSent_sizes[1]] = c3_ck_a;
    c3_x_data[c3_x_sizes[0] * (c3_b_dataSent_sizes[1] + 1)] = c3_ck_b;
    c3_b = (real_T)c3_x_sizes[1];
    c3_nbytes = (int32_T)c3_b;
    c3_a = c3_nbytes;
    c3_outlen = c3_a;
    c3_b_a = c3_outlen;
    c3_c = c3_b_a;
    if (c3_c == c3_nbytes) {
    } else {
      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 45),
                    false);
      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
        1U, 1U, 14, c3_y));
    }

    c3_outsize[0] = 1;
    c3_outsize[1] = c3_outlen;
    c3_tmp_sizes[0] = 1;
    c3_tmp_sizes[1] = c3_outsize[1];
    c3_i17 = c3_tmp_sizes[0];
    c3_i19 = c3_tmp_sizes[1];
    c3_d_loop_ub = c3_outsize[1] - 1;
    for (c3_i20 = 0; c3_i20 <= c3_d_loop_ub; c3_i20++) {
      c3_tmp_data[c3_i20] = 0U;
    }

    for (c3_i22 = 0; c3_i22 < 2; c3_i22++) {
      c3_b_tmp_sizes[c3_i22] = c3_tmp_sizes[c3_i22];
    }

    memcpy(&c3_b_tmp_data[0], &c3_x_data[0], (size_t)c3_outlen * sizeof(uint8_T));
    _SFD_DIM_SIZE_GEQ_CHECK(20, c3_b_tmp_sizes[1], 2);
    c3_c_dataSent_sizes[0] = 1;
    c3_c_dataSent_sizes[1] = c3_b_tmp_sizes[1];
    c3_i_dataSent = c3_c_dataSent_sizes[0];
    c3_j_dataSent = c3_c_dataSent_sizes[1];
    c3_e_loop_ub = c3_b_tmp_sizes[0] * c3_b_tmp_sizes[1] - 1;
    for (c3_i24 = 0; c3_i24 <= c3_e_loop_ub; c3_i24++) {
      c3_c_dataSent_data[c3_i24] = c3_b_tmp_data[c3_i24];
    }

    _SFD_SYMBOL_SWITCH(7U, 12U);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 37);
    _SFD_DIM_SIZE_GEQ_CHECK(20, 0, 2);
    c3_c_dataSent_sizes[0] = 1;
    c3_c_dataSent_sizes[1] = 0;
    c3_c_dataSent = c3_c_dataSent_sizes[0];
    c3_d_dataSent = c3_c_dataSent_sizes[1];
    _SFD_SYMBOL_SWITCH(7U, 12U);
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -37);
  _SFD_SYMBOL_SCOPE_POP();
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 0, 1);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 1,
    c3_c_dataSent_sizes[1]);
  c3_i6 = (*chartInstance->c3_dataSent_sizes)[0];
  c3_i7 = (*chartInstance->c3_dataSent_sizes)[1];
  c3_b_loop_ub = c3_c_dataSent_sizes[0] * c3_c_dataSent_sizes[1] - 1;
  for (c3_i8 = 0; c3_i8 <= c3_b_loop_ub; c3_i8++) {
    (*chartInstance->c3_dataSent_data)[c3_i8] = c3_c_dataSent_data[c3_i8];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_performMission(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)c3_machineNumber;
  (void)c3_chartNumber;
  (void)c3_instanceNumber;
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c3_inData_data[], int32_T c3_inData_sizes[2])
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u_sizes[2];
  int32_T c3_u;
  int32_T c3_b_u;
  int32_T c3_loop_ub;
  int32_T c3_i25;
  const mxArray *c3_y = NULL;
  uint8_T c3_u_data[20];
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u_sizes[0] = 1;
  c3_u_sizes[1] = c3_inData_sizes[1];
  c3_u = c3_u_sizes[0];
  c3_b_u = c3_u_sizes[1];
  c3_loop_ub = c3_inData_sizes[0] * c3_inData_sizes[1] - 1;
  for (c3_i25 = 0; c3_i25 <= c3_loop_ub; c3_i25++) {
    c3_u_data[c3_i25] = c3_inData_data[c3_i25];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u_data, 3, 0U, 1U, 0U, 2,
    c3_u_sizes[0], c3_u_sizes[1]), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_performMissionInstanceStruct *chartInstance,
  const mxArray *c3_dataSent, const char_T *c3_identifier, uint8_T c3_y_data[],
  int32_T c3_y_sizes[2])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_dataSent), &c3_thisId,
                        c3_y_data, c3_y_sizes);
  sf_mex_destroy(&c3_dataSent);
}

static void c3_b_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  uint8_T c3_y_data[], int32_T c3_y_sizes[2])
{
  int32_T c3_i26;
  int32_T c3_i27;
  uint32_T c3_uv5[2];
  uint8_T c3_tmp_data[20];
  boolean_T c3_bv0[2];
  int32_T c3_tmp_sizes[2];
  static boolean_T c3_bv1[2] = { false, true };

  int32_T c3_y;
  int32_T c3_b_y;
  int32_T c3_loop_ub;
  int32_T c3_i28;
  (void)chartInstance;
  for (c3_i26 = 0; c3_i26 < 2; c3_i26++) {
    c3_uv5[c3_i26] = 1U + 19U * (uint32_T)c3_i26;
  }

  for (c3_i27 = 0; c3_i27 < 2; c3_i27++) {
    c3_bv0[c3_i27] = c3_bv1[c3_i27];
  }

  sf_mex_import_vs(c3_parentId, sf_mex_dup(c3_u), c3_tmp_data, 1, 3, 0U, 1, 0U,
                   2, c3_bv0, c3_uv5, c3_tmp_sizes);
  c3_y_sizes[0] = 1;
  c3_y_sizes[1] = c3_tmp_sizes[1];
  c3_y = c3_y_sizes[0];
  c3_b_y = c3_y_sizes[1];
  c3_loop_ub = c3_tmp_sizes[0] * c3_tmp_sizes[1] - 1;
  for (c3_i28 = 0; c3_i28 <= c3_loop_ub; c3_i28++) {
    c3_y_data[c3_i28] = c3_tmp_data[c3_i28];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, uint8_T c3_outData_data[],
  int32_T c3_outData_sizes[2])
{
  const mxArray *c3_dataSent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y_data[20];
  int32_T c3_y_sizes[2];
  int32_T c3_loop_ub;
  int32_T c3_i29;
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_dataSent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_dataSent), &c3_thisId,
                        c3_y_data, c3_y_sizes);
  sf_mex_destroy(&c3_dataSent);
  c3_outData_sizes[0] = 1;
  c3_outData_sizes[1] = c3_y_sizes[1];
  c3_loop_ub = c3_y_sizes[1] - 1;
  for (c3_i29 = 0; c3_i29 <= c3_loop_ub; c3_i29++) {
    c3_outData_data[c3_outData_sizes[0] * c3_i29] = c3_y_data[c3_y_sizes[0] *
      c3_i29];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, real_T
  c3_inData_data[], int32_T c3_inData_sizes[2])
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u_sizes[2];
  int32_T c3_u;
  int32_T c3_b_u;
  int32_T c3_loop_ub;
  int32_T c3_i30;
  const mxArray *c3_y = NULL;
  real_T c3_u_data[5];
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u_sizes[0] = 1;
  c3_u_sizes[1] = c3_inData_sizes[1];
  c3_u = c3_u_sizes[0];
  c3_b_u = c3_u_sizes[1];
  c3_loop_ub = c3_inData_sizes[0] * c3_inData_sizes[1] - 1;
  for (c3_i30 = 0; c3_i30 <= c3_loop_ub; c3_i30++) {
    c3_u_data[c3_i30] = c3_inData_data[c3_i30];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u_data, 0, 0U, 1U, 0U, 2,
    c3_u_sizes[0], c3_u_sizes[1]), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static real_T c3_c_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d5;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d5, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d5;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c3_inData_data[], int32_T c3_inData_sizes[2])
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u_sizes[2];
  int32_T c3_u;
  int32_T c3_b_u;
  int32_T c3_loop_ub;
  int32_T c3_i31;
  const mxArray *c3_y = NULL;
  uint8_T c3_u_data[18];
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u_sizes[0] = 1;
  c3_u_sizes[1] = c3_inData_sizes[1];
  c3_u = c3_u_sizes[0];
  c3_b_u = c3_u_sizes[1];
  c3_loop_ub = c3_inData_sizes[0] * c3_inData_sizes[1] - 1;
  for (c3_i31 = 0; c3_i31 <= c3_loop_ub; c3_i31++) {
    c3_u_data[c3_i31] = c3_inData_data[c3_i31];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u_data, 3, 0U, 1U, 0U, 2,
    c3_u_sizes[0], c3_u_sizes[1]), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_d_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  uint8_T c3_y_data[], int32_T c3_y_sizes[2])
{
  int32_T c3_i32;
  int32_T c3_i33;
  uint32_T c3_uv6[2];
  uint8_T c3_tmp_data[18];
  boolean_T c3_bv2[2];
  int32_T c3_tmp_sizes[2];
  static boolean_T c3_bv3[2] = { false, true };

  int32_T c3_y;
  int32_T c3_b_y;
  int32_T c3_loop_ub;
  int32_T c3_i34;
  (void)chartInstance;
  for (c3_i32 = 0; c3_i32 < 2; c3_i32++) {
    c3_uv6[c3_i32] = 1U + 17U * (uint32_T)c3_i32;
  }

  for (c3_i33 = 0; c3_i33 < 2; c3_i33++) {
    c3_bv2[c3_i33] = c3_bv3[c3_i33];
  }

  sf_mex_import_vs(c3_parentId, sf_mex_dup(c3_u), c3_tmp_data, 1, 3, 0U, 1, 0U,
                   2, c3_bv2, c3_uv6, c3_tmp_sizes);
  c3_y_sizes[0] = 1;
  c3_y_sizes[1] = c3_tmp_sizes[1];
  c3_y = c3_y_sizes[0];
  c3_b_y = c3_y_sizes[1];
  c3_loop_ub = c3_tmp_sizes[0] * c3_tmp_sizes[1] - 1;
  for (c3_i34 = 0; c3_i34 <= c3_loop_ub; c3_i34++) {
    c3_y_data[c3_i34] = c3_tmp_data[c3_i34];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, uint8_T c3_outData_data[],
  int32_T c3_outData_sizes[2])
{
  const mxArray *c3_dataSent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y_data[18];
  int32_T c3_y_sizes[2];
  int32_T c3_loop_ub;
  int32_T c3_i35;
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_dataSent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_dataSent), &c3_thisId,
                        c3_y_data, c3_y_sizes);
  sf_mex_destroy(&c3_dataSent);
  c3_outData_sizes[0] = 1;
  c3_outData_sizes[1] = c3_y_sizes[1];
  c3_loop_ub = c3_y_sizes[1] - 1;
  for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
    c3_outData_data[c3_outData_sizes[0] * c3_i35] = c3_y_data[c3_y_sizes[0] *
      c3_i35];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  uint8_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(uint8_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static uint8_T c3_e_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_i, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_i), &c3_thisId);
  sf_mex_destroy(&c3_i);
  return c3_y;
}

static uint8_T c3_f_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u6;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u6, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u6;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_i;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y;
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_i = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_i), &c3_thisId);
  sf_mex_destroy(&c3_i);
  *(uint8_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_performMission_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c3_nameCaptureInfo;
}

static real_T c3_mpower(SFc3_performMissionInstanceStruct *chartInstance, real_T
  c3_a)
{
  (void)chartInstance;
  (void)c3_a;
  return 1.0E+7;
}

static void c3_scalarEg(SFc3_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_dimagree(SFc3_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_typecast(SFc3_performMissionInstanceStruct *chartInstance,
  int32_T c3_x, uint8_T c3_y[4])
{
  (void)chartInstance;
  memcpy(&c3_y[0], &c3_x, (size_t)4 * sizeof(uint8_T));
}

static uint16_T c3_rem(SFc3_performMissionInstanceStruct *chartInstance,
  uint16_T c3_x)
{
  uint16_T c3_b_x;
  uint16_T c3_c_x;
  uint16_T c3_u0;
  (void)chartInstance;
  c3_b_x = c3_x;
  c3_c_x = c3_b_x;
  c3_u0 = c3_c_x;
  return (uint16_T)(c3_u0 % 256U);
}

static void c3_b_dimagree(SFc3_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_g_emlrt_marshallIn(SFc3_performMissionInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i36;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i36, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i36;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static void init_dsm_address_info(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc3_performMissionInstanceStruct
  *chartInstance)
{
  chartInstance->c3_stage = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c3_payload_data = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_payload_sizes = (int32_T (*)[2])
    ssGetCurrentInputPortDimensions_wrapper(chartInstance->S, 1);
  sf_mex_size_one_check(((*chartInstance->c3_payload_sizes)[0U] == 0) &&
                        (!((*chartInstance->c3_payload_sizes)[1U] == 0)),
                        "payload");
  chartInstance->c3_dataSent_data = (uint8_T (*)[20])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c3_dataSent_sizes = (int32_T (*)[2])
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

void sf_c3_performMission_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2497530181U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(651598725U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2633137128U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1461876788U);
}

mxArray* sf_c3_performMission_get_post_codegen_info(void);
mxArray *sf_c3_performMission_get_autoinheritance_info(void)
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
    mxArray* mxPostCodegenInfo = sf_c3_performMission_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_performMission_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_performMission_jit_fallback_info(void)
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

mxArray *sf_c3_performMission_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c3_performMission_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c3_performMission(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"dataSent\",},{M[8],M[0],T\"is_active_c3_performMission\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_performMission_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_performMissionInstanceStruct *chartInstance =
      (SFc3_performMissionInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _performMissionMachineNumber_,
           3,
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
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 5U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 20U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
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
    SFc3_performMissionInstanceStruct *chartInstance =
      (SFc3_performMissionInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c3_stage);
        _SFD_SET_DATA_VALUE_PTR_VAR_DIM(1U, *chartInstance->c3_payload_data,
          (void *)chartInstance->c3_payload_sizes);
        _SFD_SET_DATA_VALUE_PTR_VAR_DIM(2U, *chartInstance->c3_dataSent_data,
          (void *)chartInstance->c3_dataSent_sizes);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sFOnX0uHF2rOkquaGiHqMOG";
}

static void sf_opaque_initialize_c3_performMission(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_performMissionInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_performMission((SFc3_performMissionInstanceStruct*)
    chartInstanceVar);
  initialize_c3_performMission((SFc3_performMissionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_performMission(void *chartInstanceVar)
{
  enable_c3_performMission((SFc3_performMissionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_performMission(void *chartInstanceVar)
{
  disable_c3_performMission((SFc3_performMissionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c3_performMission(void *chartInstanceVar)
{
  sf_gateway_c3_performMission((SFc3_performMissionInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c3_performMission(SimStruct* S)
{
  return get_sim_state_c3_performMission((SFc3_performMissionInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c3_performMission(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c3_performMission((SFc3_performMissionInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c3_performMission(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_performMissionInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_performMission_optimization_info();
    }

    finalize_c3_performMission((SFc3_performMissionInstanceStruct*)
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
  initSimStructsc3_performMission((SFc3_performMissionInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_performMission(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_performMission((SFc3_performMissionInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c3_performMission(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_performMission_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 3);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
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

static void mdlRTW_c3_performMission(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_performMission(SimStruct *S)
{
  SFc3_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc3_performMissionInstanceStruct *)utMalloc(sizeof
    (SFc3_performMissionInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc3_performMissionInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c3_performMission;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_performMission;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c3_performMission;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_performMission;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_performMission;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_performMission;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_performMission;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_performMission;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_performMission;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_performMission;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_performMission;
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
  mdl_start_c3_performMission(chartInstance);
}

void c3_performMission_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_performMission(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_performMission(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_performMission(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_performMission_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
