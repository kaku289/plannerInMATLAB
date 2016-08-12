/* Include files */

#include "performMission_sfun.h"
#include "c1_performMission.h"
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
static const char * c1_debug_family_names[23] = { "ac_id", "block_id", "route",
  "coordinates", "wp_id", "val", "nargin", "nargout", "destinations", "Q",
  "wp_ids", "t", "dataReceived", "Stage", "Payload", "ct_route", "tStep",
  "ct_customer", "isRouteFinished", "tol", "stage", "stateChange",
  "presentRoute" };

/* Function Declarations */
static void initialize_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance);
static void initialize_params_c1_performMission
  (SFc1_performMissionInstanceStruct *chartInstance);
static void enable_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance);
static void disable_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_performMission
  (SFc1_performMissionInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_performMission
  (SFc1_performMissionInstanceStruct *chartInstance);
static void set_sim_state_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance);
static void sf_gateway_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance);
static void mdl_start_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance);
static void c1_chartstep_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance);
static void initSimStructsc1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_b_presentRoute, const char_T *c1_identifier,
  boolean_T *c1_svPtr);
static real_T c1_b_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  boolean_T *c1_svPtr);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[], int32_T c1_inData_sizes[2]);
static void c1_c_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_Payload, const char_T *c1_identifier, real_T
  c1_y_data[], int32_T c1_y_sizes[2]);
static void c1_d_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y_data[], int32_T c1_y_sizes[2]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[], int32_T
  c1_outData_sizes[2]);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_e_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_b_Stage, const char_T *c1_identifier);
static real_T c1_f_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c1_inData_data[], int32_T c1_inData_sizes[2]);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real32_T c1_g_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_h_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3]);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[], int32_T c1_inData_sizes[2]);
static void c1_i_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y_data[], int32_T c1_y_sizes[2]);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[], int32_T
  c1_outData_sizes[2]);
static void c1_indexShapeCheck(SFc1_performMissionInstanceStruct *chartInstance,
  int32_T c1_matrixSize);
static real32_T c1_typecast(SFc1_performMissionInstanceStruct *chartInstance,
  uint8_T c1_x[4]);
static real32_T c1_abs(SFc1_performMissionInstanceStruct *chartInstance,
  real32_T c1_x);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_j_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_k_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_performMission, const char_T *
  c1_identifier);
static uint8_T c1_l_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_performMissionInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc1_performMissionInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc1_performMission(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_ct_route_not_empty = false;
  chartInstance->c1_tStep_not_empty = false;
  chartInstance->c1_ct_customer_not_empty = false;
  chartInstance->c1_isRouteFinished_not_empty = false;
  chartInstance->c1_tol_not_empty = false;
  chartInstance->c1_stage_not_empty = false;
  chartInstance->c1_stateChange_not_empty = false;
  chartInstance->c1_presentRoute_not_empty = false;
  chartInstance->c1_is_active_c1_performMission = 0U;
}

static void initialize_params_c1_performMission
  (SFc1_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_performMission
  (SFc1_performMissionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c1_performMission
  (SFc1_performMissionInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  const mxArray *c1_b_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_f_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_e_u;
  const mxArray *c1_g_y = NULL;
  real_T c1_f_hoistedGlobal;
  real_T c1_f_u;
  const mxArray *c1_h_y = NULL;
  real_T c1_g_hoistedGlobal;
  real_T c1_g_u;
  const mxArray *c1_i_y = NULL;
  real_T c1_h_hoistedGlobal;
  real_T c1_h_u;
  const mxArray *c1_j_y = NULL;
  real_T c1_i_hoistedGlobal;
  real_T c1_i_u;
  const mxArray *c1_k_y = NULL;
  uint8_T c1_j_hoistedGlobal;
  uint8_T c1_j_u;
  const mxArray *c1_l_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(11, 1), false);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", *chartInstance->c1_Payload_data, 0,
    0U, 1U, 0U, 2, (*chartInstance->c1_Payload_sizes)[0],
    (*chartInstance->c1_Payload_sizes)[1]), false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = *chartInstance->c1_Stage;
  c1_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_b_hoistedGlobal = chartInstance->c1_ct_customer;
  c1_b_u = c1_b_hoistedGlobal;
  c1_d_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_c_hoistedGlobal = chartInstance->c1_ct_route;
  c1_c_u = c1_c_hoistedGlobal;
  c1_e_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_d_hoistedGlobal = chartInstance->c1_isRouteFinished;
  c1_d_u = c1_d_hoistedGlobal;
  c1_f_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_e_hoistedGlobal = chartInstance->c1_presentRoute;
  c1_e_u = c1_e_hoistedGlobal;
  c1_g_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_f_hoistedGlobal = chartInstance->c1_stage;
  c1_f_u = c1_f_hoistedGlobal;
  c1_h_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_g_hoistedGlobal = chartInstance->c1_stateChange;
  c1_g_u = c1_g_hoistedGlobal;
  c1_i_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_h_hoistedGlobal = chartInstance->c1_tStep;
  c1_h_u = c1_h_hoistedGlobal;
  c1_j_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_i_hoistedGlobal = chartInstance->c1_tol;
  c1_i_u = c1_i_hoistedGlobal;
  c1_k_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_k_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_i_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_j_hoistedGlobal = chartInstance->c1_is_active_c1_performMission;
  c1_j_u = c1_j_hoistedGlobal;
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_j_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 10, c1_l_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_tmp_data[5];
  int32_T c1_tmp_sizes[2];
  int32_T c1_i0;
  int32_T c1_i1;
  int32_T c1_loop_ub;
  int32_T c1_i2;
  chartInstance->c1_doneDoubleBufferReInit = true;
  c1_u = sf_mex_dup(c1_st);
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("Payload", c1_u,
    0)), "Payload", c1_tmp_data, c1_tmp_sizes);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 2, 0, 1);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 2, 1, c1_tmp_sizes
    [1]);
  c1_i0 = (*chartInstance->c1_Payload_sizes)[0];
  c1_i1 = (*chartInstance->c1_Payload_sizes)[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i2 = 0; c1_i2 <= c1_loop_ub; c1_i2++) {
    (*chartInstance->c1_Payload_data)[c1_i2] = c1_tmp_data[c1_i2];
  }

  *chartInstance->c1_Stage = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Stage", c1_u, 1)), "Stage");
  chartInstance->c1_ct_customer = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("ct_customer", c1_u, 2)), "ct_customer",
    &chartInstance->c1_ct_customer_not_empty);
  chartInstance->c1_ct_route = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("ct_route", c1_u, 3)), "ct_route",
    &chartInstance->c1_ct_route_not_empty);
  chartInstance->c1_isRouteFinished = c1_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("isRouteFinished", c1_u, 4)), "isRouteFinished",
    &chartInstance->c1_isRouteFinished_not_empty);
  chartInstance->c1_presentRoute = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("presentRoute", c1_u, 5)), "presentRoute",
    &chartInstance->c1_presentRoute_not_empty);
  chartInstance->c1_stage = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("stage", c1_u, 6)), "stage",
    &chartInstance->c1_stage_not_empty);
  chartInstance->c1_stateChange = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("stateChange", c1_u, 7)), "stateChange",
    &chartInstance->c1_stateChange_not_empty);
  chartInstance->c1_tStep = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("tStep", c1_u, 8)), "tStep",
    &chartInstance->c1_tStep_not_empty);
  chartInstance->c1_tol = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("tol", c1_u, 9)), "tol", &chartInstance->c1_tol_not_empty);
  chartInstance->c1_is_active_c1_performMission = c1_k_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c1_performMission",
       c1_u, 10)), "is_active_c1_performMission");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_performMission(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  int32_T c1_loop_ub;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  int32_T c1_b_loop_ub;
  int32_T c1_i6;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_loop_ub = (*chartInstance->c1_dataReceived_sizes)[0] *
    (*chartInstance->c1_dataReceived_sizes)[1] - 1;
  for (c1_i3 = 0; c1_i3 <= c1_loop_ub; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c1_dataReceived_data)[c1_i3],
                          4U, 1U, 0U, chartInstance->c1_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_t, 3U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  for (c1_i4 = 0; c1_i4 < 3; c1_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_wp_ids)[c1_i4], 2U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Q, 1U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  for (c1_i5 = 0; c1_i5 < 18; c1_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_destinations)[c1_i5], 0U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_performMission(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_performMissionMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Stage, 5U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  c1_b_loop_ub = (*chartInstance->c1_Payload_sizes)[0] *
    (*chartInstance->c1_Payload_sizes)[1] - 1;
  for (c1_i6 = 0; c1_i6 <= c1_b_loop_ub; c1_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_Payload_data)[c1_i6], 6U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }
}

static void mdl_start_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_chartstep_c1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  int32_T c1_i7;
  real_T c1_b_Q;
  real_T c1_b_destinations[18];
  int32_T c1_i8;
  real_T c1_b_t;
  real_T c1_b_wp_ids[3];
  int32_T c1_b_dataReceived_sizes[2];
  int32_T c1_dataReceived;
  int32_T c1_b_dataReceived;
  int32_T c1_loop_ub;
  int32_T c1_i9;
  uint32_T c1_debug_family_var_map[23];
  uint8_T c1_b_dataReceived_data[255];
  real_T c1_ac_id;
  real_T c1_block_id;
  real_T c1_route_data[18];
  int32_T c1_route_sizes[2];
  real_T c1_coordinates[3];
  real_T c1_wp_id;
  real32_T c1_val;
  real_T c1_nargin = 5.0;
  real_T c1_nargout = 2.0;
  real_T c1_b_Stage;
  real_T c1_b_Payload_data[5];
  int32_T c1_b_Payload_sizes[2];
  real_T c1_c_hoistedGlobal;
  real_T c1_B;
  real_T c1_y;
  real_T c1_b_y;
  real_T c1_c_y;
  real_T c1_d_hoistedGlobal;
  real_T c1_b_B;
  real_T c1_d_y;
  real_T c1_e_y;
  real_T c1_f_y;
  boolean_T c1_b0;
  real_T c1_d0;
  boolean_T c1_b1;
  real_T c1_d1;
  boolean_T c1_b2;
  boolean_T c1_b3;
  boolean_T c1_b4;
  int32_T c1_i10;
  boolean_T c1_b5;
  int32_T c1_i11;
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_b_loop_ub;
  int32_T c1_i14;
  int32_T c1_i15;
  int32_T c1_c_loop_ub;
  int32_T c1_i16;
  int32_T c1_Payload;
  int32_T c1_b_Payload;
  int32_T c1_tmp_sizes;
  int32_T c1_d_loop_ub;
  int32_T c1_i17;
  int32_T c1_e_loop_ub;
  int32_T c1_i18;
  int32_T c1_f_loop_ub;
  uint8_T c1_tmp_data[255];
  int32_T c1_i19;
  int32_T c1_g_loop_ub;
  int32_T c1_i20;
  int32_T c1_h_loop_ub;
  int32_T c1_i21;
  int32_T c1_i_loop_ub;
  int32_T c1_i22;
  int32_T c1_i23;
  int32_T c1_i24;
  int32_T c1_j_loop_ub;
  int32_T c1_i25;
  int32_T c1_k_loop_ub;
  int32_T c1_c_Payload;
  int32_T c1_i26;
  int32_T c1_l_loop_ub;
  int32_T c1_d_Payload;
  int32_T c1_i27;
  int32_T c1_i28;
  real_T c1_b_wp_id[5];
  int32_T c1_m_loop_ub;
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_e_Payload;
  int32_T c1_f_Payload;
  int32_T c1_n_loop_ub;
  int32_T c1_i31;
  int32_T c1_i32;
  int32_T c1_g_Payload;
  int32_T c1_i33;
  int32_T c1_o_loop_ub;
  int32_T c1_h_Payload;
  int32_T c1_p_loop_ub;
  int32_T c1_i34;
  int32_T c1_i35;
  int32_T c1_i36;
  int32_T c1_i37;
  int32_T c1_i38;
  int32_T c1_i39;
  int32_T c1_i40;
  uint8_T c1_uv0[4];
  uint8_T c1_uv1[4];
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  boolean_T guard4 = false;
  boolean_T guard5 = false;
  boolean_T guard6 = false;
  boolean_T guard7 = false;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *chartInstance->c1_Q;
  c1_b_hoistedGlobal = *chartInstance->c1_t;
  for (c1_i7 = 0; c1_i7 < 18; c1_i7++) {
    c1_b_destinations[c1_i7] = (*chartInstance->c1_destinations)[c1_i7];
  }

  c1_b_Q = c1_hoistedGlobal;
  for (c1_i8 = 0; c1_i8 < 3; c1_i8++) {
    c1_b_wp_ids[c1_i8] = (*chartInstance->c1_wp_ids)[c1_i8];
  }

  c1_b_t = c1_b_hoistedGlobal;
  c1_b_dataReceived_sizes[0] = (*chartInstance->c1_dataReceived_sizes)[0];
  c1_b_dataReceived_sizes[1] = 1;
  c1_dataReceived = c1_b_dataReceived_sizes[0];
  c1_b_dataReceived = c1_b_dataReceived_sizes[1];
  c1_loop_ub = (*chartInstance->c1_dataReceived_sizes)[0] *
    (*chartInstance->c1_dataReceived_sizes)[1] - 1;
  for (c1_i9 = 0; c1_i9 <= c1_loop_ub; c1_i9++) {
    c1_b_dataReceived_data[c1_i9] = (*chartInstance->c1_dataReceived_data)[c1_i9];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 23U, 23U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ac_id, 0U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_block_id, 1U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_route_data, (const int32_T *)
    &c1_route_sizes, NULL, 0, 2, (void *)c1_h_sf_marshallOut, (void *)
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_coordinates, 3U, c1_e_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wp_id, 4U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_val, 5U, c1_g_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 6U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 7U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_destinations, 8U, c1_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_Q, 9U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_wp_ids, 10U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_t, 11U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN(c1_b_dataReceived_data, (const int32_T *)
    &c1_b_dataReceived_sizes, NULL, 1, 12, (void *)c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_Stage, 13U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_b_Payload_data, (const int32_T *)
    &c1_b_Payload_sizes, NULL, 0, 14, (void *)c1_b_sf_marshallOut, (void *)
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_ct_route, 15U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_tStep, 16U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_ct_customer, 17U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_isRouteFinished, 18U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_tol, 19U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_stage, 20U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_stateChange, 21U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_presentRoute, 22U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c1_ct_customer_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
    chartInstance->c1_ct_customer = 1.0;
    chartInstance->c1_ct_customer_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c1_tStep_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 27);
    chartInstance->c1_tStep = 5.0;
    chartInstance->c1_tStep_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 29);
  if (CV_EML_IF(0, 1, 2, !chartInstance->c1_isRouteFinished_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 30);
    chartInstance->c1_isRouteFinished = 1.0;
    chartInstance->c1_isRouteFinished_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  if (CV_EML_IF(0, 1, 3, !chartInstance->c1_tol_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
    chartInstance->c1_tol = 0.001;
    chartInstance->c1_tol_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 35);
  if (CV_EML_IF(0, 1, 4, !chartInstance->c1_stage_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 36);
    chartInstance->c1_stage = 1.0;
    chartInstance->c1_stage_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
  if (CV_EML_IF(0, 1, 5, !chartInstance->c1_presentRoute_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 39);
    chartInstance->c1_presentRoute = 1.0;
    chartInstance->c1_presentRoute_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 41);
  if (CV_EML_IF(0, 1, 6, !chartInstance->c1_ct_route_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
    chartInstance->c1_ct_route = 1.0;
    chartInstance->c1_ct_route_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 45);
  chartInstance->c1_stateChange = 0.0;
  chartInstance->c1_stateChange_not_empty = true;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 46);
  c1_ac_id = 202.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 47);
  c1_block_id = 7.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 57);
  c1_c_hoistedGlobal = chartInstance->c1_ct_route;
  c1_B = c1_b_Q;
  c1_y = c1_B;
  c1_b_y = c1_y;
  c1_c_y = 6.0 / c1_b_y;
  c1_d_hoistedGlobal = chartInstance->c1_ct_route;
  c1_b_B = c1_b_Q;
  c1_d_y = c1_b_B;
  c1_e_y = c1_d_y;
  c1_f_y = 6.0 / c1_e_y;
  if (CV_EML_IF(0, 1, 7, CV_RELATIONAL_EVAL(4U, 0U, 0, c1_c_hoistedGlobal,
        c1_c_y, -1, 3U, c1_d_hoistedGlobal <= c1_f_y))) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 58);
    c1_d0 = (chartInstance->c1_ct_route - 1.0) * c1_b_Q + 1.0;
    c1_d1 = chartInstance->c1_ct_route * c1_b_Q;
    c1_b3 = (c1_d0 > c1_d1);
    c1_b4 = c1_b3;
    c1_b5 = c1_b4;
    if (c1_b5) {
      c1_i11 = 1;
      c1_i12 = 0;
    } else {
      c1_i11 = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 1568, 27, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 1568U, 27U, c1_d0), 1, 6);
      c1_i12 = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 1568, 27, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 1568U, 27U, c1_d1), 1, 6);
    }

    c1_route_sizes[0] = (c1_i12 - c1_i11) + 1;
    c1_route_sizes[1] = 3;
    for (c1_i14 = 0; c1_i14 < 3; c1_i14++) {
      c1_c_loop_ub = c1_i12 - c1_i11;
      for (c1_i16 = 0; c1_i16 <= c1_c_loop_ub; c1_i16++) {
        c1_route_data[c1_i16 + c1_route_sizes[0] * c1_i14] = c1_b_destinations
          [((c1_i11 + c1_i16) + 6 * c1_i14) - 1];
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 60);
    c1_b0 = (1.0 > c1_b_Q);
    c1_b1 = c1_b0;
    c1_b2 = c1_b1;
    if (c1_b2) {
      c1_i10 = 0;
    } else {
      c1_i10 = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 1630, 3, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 1630U, 3U, c1_b_Q), 1, 6);
    }

    c1_route_sizes[0] = c1_i10;
    c1_route_sizes[1] = 3;
    for (c1_i13 = 0; c1_i13 < 3; c1_i13++) {
      c1_b_loop_ub = c1_i10 - 1;
      for (c1_i15 = 0; c1_i15 <= c1_b_loop_ub; c1_i15++) {
        c1_route_data[c1_i15 + c1_route_sizes[0] * c1_i13] =
          c1_b_destinations[c1_i15 + 6 * c1_i13];
      }
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 63);
  _SFD_DIM_SIZE_GEQ_CHECK(5, 0, 2);
  c1_b_Payload_sizes[0] = 1;
  c1_b_Payload_sizes[1] = 0;
  c1_Payload = c1_b_Payload_sizes[0];
  c1_b_Payload = c1_b_Payload_sizes[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 64);
  if (CV_EML_IF(0, 1, 8, CV_RELATIONAL_EVAL(4U, 0U, 1, chartInstance->c1_stage,
        1.0, -1, 0U, chartInstance->c1_stage == 1.0))) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 66);
    c1_tmp_sizes = c1_b_dataReceived_sizes[0];
    c1_d_loop_ub = c1_b_dataReceived_sizes[0] - 1;
    for (c1_i17 = 0; c1_i17 <= c1_d_loop_ub; c1_i17++) {
      c1_tmp_data[c1_i17] = c1_b_dataReceived_data[c1_i17];
    }

    guard5 = false;
    guard6 = false;
    guard7 = false;
    if (!CV_EML_COND(0, 1, 0, c1_tmp_sizes == 0)) {
      c1_tmp_sizes = c1_b_dataReceived_sizes[0];
      c1_g_loop_ub = c1_b_dataReceived_sizes[0] - 1;
      for (c1_i20 = 0; c1_i20 <= c1_g_loop_ub; c1_i20++) {
        c1_tmp_data[c1_i20] = c1_b_dataReceived_data[c1_i20];
      }

      (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 1787, 15, MAX_uint32_T, 3, 1, c1_tmp_sizes);
      if (CV_EML_COND(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 2, (real_T)
            c1_tmp_data[2], 202.0, -1, 0U, (real_T)c1_tmp_data[2] == 202.0))) {
        c1_tmp_sizes = c1_b_dataReceived_sizes[0];
        c1_j_loop_ub = c1_b_dataReceived_sizes[0] - 1;
        for (c1_i25 = 0; c1_i25 <= c1_j_loop_ub; c1_i25++) {
          c1_tmp_data[c1_i25] = c1_b_dataReceived_data[c1_i25];
        }

        (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
          chartInstance->S, 1U, 1813, 15, MAX_uint32_T, 4, 1, c1_tmp_sizes);
        if (CV_EML_COND(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 3, (real_T)
              c1_tmp_data[3], 49.0, -1, 0U, (real_T)c1_tmp_data[3] == 49.0))) {
          c1_tmp_sizes = c1_b_dataReceived_sizes[0];
          c1_m_loop_ub = c1_b_dataReceived_sizes[0] - 1;
          for (c1_i30 = 0; c1_i30 <= c1_m_loop_ub; c1_i30++) {
            c1_tmp_data[c1_i30] = c1_b_dataReceived_data[c1_i30];
          }

          (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
            chartInstance->S, 1U, 1836, 15, MAX_uint32_T, 5, 1, c1_tmp_sizes);
          if (CV_EML_COND(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 4, (real_T)
                c1_tmp_data[4], c1_b_wp_ids[(int32_T)
                chartInstance->c1_ct_customer - 1], -1, 0U, (real_T)c1_tmp_data
                [4] == c1_b_wp_ids[(int32_T)chartInstance->c1_ct_customer - 1])))
          {
            CV_EML_MCDC(0, 1, 0, true);
            CV_EML_IF(0, 1, 9, true);
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 68);
            chartInstance->c1_ct_customer++;
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 69);
            if (CV_EML_IF(0, 1, 10, CV_RELATIONAL_EVAL(4U, 0U, 5,
                  chartInstance->c1_ct_customer, c1_b_Q, -1, 4U,
                  chartInstance->c1_ct_customer > c1_b_Q))) {
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 70);
              chartInstance->c1_ct_customer = 1.0;
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 71);
              chartInstance->c1_stage = 2.0;
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 72);
              chartInstance->c1_stateChange = 1.0;
            }
          } else {
            guard5 = true;
          }
        } else {
          guard6 = true;
        }
      } else {
        guard7 = true;
      }
    } else {
      guard7 = true;
    }

    if (guard7 == true) {
      guard6 = true;
    }

    if (guard6 == true) {
      guard5 = true;
    }

    if (guard5 == true) {
      CV_EML_MCDC(0, 1, 0, false);
      CV_EML_IF(0, 1, 9, false);
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 75);
    c1_i23 = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 2110, 11, MAX_uint32_T, (int32_T)
      chartInstance->c1_ct_customer, 1, c1_route_sizes[0]) - 1;
    for (c1_i24 = 0; c1_i24 < 3; c1_i24++) {
      c1_coordinates[c1_i24] = c1_route_data[c1_i23 + c1_route_sizes[0] * c1_i24];
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 76);
    c1_wp_id = c1_b_wp_ids[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 2138, 19, MAX_uint32_T, (int32_T)
      chartInstance->c1_ct_customer, 1, 3) - 1];
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 77);
    c1_b_wp_id[0] = c1_wp_id;
    c1_b_wp_id[1] = 202.0;
    for (c1_i29 = 0; c1_i29 < 3; c1_i29++) {
      c1_b_wp_id[c1_i29 + 2] = c1_coordinates[c1_i29];
    }

    c1_b_Payload_sizes[0] = 1;
    c1_b_Payload_sizes[1] = 5;
    c1_g_Payload = c1_b_Payload_sizes[0];
    c1_h_Payload = c1_b_Payload_sizes[1];
    for (c1_i35 = 0; c1_i35 < 5; c1_i35++) {
      c1_b_Payload_data[c1_i35] = c1_b_wp_id[c1_i35];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 78);
    if (CV_EML_IF(0, 1, 11, CV_RELATIONAL_EVAL(4U, 0U, 6,
          chartInstance->c1_stage, 2.0, -1, 0U, chartInstance->c1_stage == 2.0)))
    {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 79);
      c1_tmp_sizes = c1_b_dataReceived_sizes[0];
      c1_e_loop_ub = c1_b_dataReceived_sizes[0] - 1;
      for (c1_i18 = 0; c1_i18 <= c1_e_loop_ub; c1_i18++) {
        c1_tmp_data[c1_i18] = c1_b_dataReceived_data[c1_i18];
      }

      guard3 = false;
      guard4 = false;
      if (!CV_EML_COND(0, 1, 4, c1_tmp_sizes == 0)) {
        c1_tmp_sizes = c1_b_dataReceived_sizes[0];
        c1_h_loop_ub = c1_b_dataReceived_sizes[0] - 1;
        for (c1_i21 = 0; c1_i21 <= c1_h_loop_ub; c1_i21++) {
          c1_tmp_data[c1_i21] = c1_b_dataReceived_data[c1_i21];
        }

        (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
          chartInstance->S, 1U, 2253, 15, MAX_uint32_T, 3, 1, c1_tmp_sizes);
        if (CV_EML_COND(0, 1, 5, CV_RELATIONAL_EVAL(4U, 0U, 7, (real_T)
              c1_tmp_data[2], 202.0, -1, 0U, (real_T)c1_tmp_data[2] == 202.0)))
        {
          c1_tmp_sizes = c1_b_dataReceived_sizes[0];
          c1_k_loop_ub = c1_b_dataReceived_sizes[0] - 1;
          for (c1_i26 = 0; c1_i26 <= c1_k_loop_ub; c1_i26++) {
            c1_tmp_data[c1_i26] = c1_b_dataReceived_data[c1_i26];
          }

          (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
            chartInstance->S, 1U, 2279, 15, MAX_uint32_T, 4, 1, c1_tmp_sizes);
          if (CV_EML_COND(0, 1, 6, CV_RELATIONAL_EVAL(4U, 0U, 8, (real_T)
                c1_tmp_data[3], 24.0, -1, 0U, (real_T)c1_tmp_data[3] == 24.0)))
          {
            CV_EML_MCDC(0, 1, 1, true);
            CV_EML_IF(0, 1, 12, true);
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 80);
            c1_tmp_sizes = c1_b_dataReceived_sizes[0];
            c1_n_loop_ub = c1_b_dataReceived_sizes[0] - 1;
            for (c1_i32 = 0; c1_i32 <= c1_n_loop_ub; c1_i32++) {
              c1_tmp_data[c1_i32] = c1_b_dataReceived_data[c1_i32];
            }

            c1_indexShapeCheck(chartInstance, c1_tmp_sizes);
            c1_i37 = c1_tmp_sizes;
            for (c1_i38 = 0; c1_i38 < 4; c1_i38++) {
              c1_uv0[c1_i38] = c1_tmp_data[sf_eml_array_bounds_check
                (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 2322, 17,
                 MAX_uint32_T, (int32_T)(5.0 + (real_T)c1_i38), 1, c1_i37) - 1];
            }

            c1_val = c1_typecast(chartInstance, c1_uv0);
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 81);
            if (CV_EML_IF(0, 1, 13, CV_RELATIONAL_EVAL(4U, 0U, 9, (real_T)c1_abs
                  (chartInstance, c1_val), 0.001, -1, 2U, (real_T)c1_abs
                  (chartInstance, c1_val) < 0.001))) {
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 82);
              chartInstance->c1_stage = 3.0;
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 83);
              chartInstance->c1_stateChange = 1.0;
            }
          } else {
            guard3 = true;
          }
        } else {
          guard4 = true;
        }
      } else {
        guard4 = true;
      }

      if (guard4 == true) {
        guard3 = true;
      }

      if (guard3 == true) {
        CV_EML_MCDC(0, 1, 1, false);
        CV_EML_IF(0, 1, 12, false);
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 86);
      _SFD_DIM_SIZE_GEQ_CHECK(5, 2, 2);
      c1_b_Payload_sizes[0] = 1;
      c1_b_Payload_sizes[1] = 2;
      c1_c_Payload = c1_b_Payload_sizes[0];
      c1_d_Payload = c1_b_Payload_sizes[1];
      for (c1_i28 = 0; c1_i28 < 2; c1_i28++) {
        c1_b_Payload_data[c1_i28] = 7.0 + 195.0 * (real_T)c1_i28;
      }
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 87);
      CV_EML_IF(0, 1, 14, CV_RELATIONAL_EVAL(4U, 0U, 10, chartInstance->c1_stage,
                 3.0, -1, 0U, chartInstance->c1_stage == 3.0));
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 88);
      c1_tmp_sizes = c1_b_dataReceived_sizes[0];
      c1_f_loop_ub = c1_b_dataReceived_sizes[0] - 1;
      for (c1_i19 = 0; c1_i19 <= c1_f_loop_ub; c1_i19++) {
        c1_tmp_data[c1_i19] = c1_b_dataReceived_data[c1_i19];
      }

      guard1 = false;
      guard2 = false;
      if (!CV_EML_COND(0, 1, 7, c1_tmp_sizes == 0)) {
        c1_tmp_sizes = c1_b_dataReceived_sizes[0];
        c1_i_loop_ub = c1_b_dataReceived_sizes[0] - 1;
        for (c1_i22 = 0; c1_i22 <= c1_i_loop_ub; c1_i22++) {
          c1_tmp_data[c1_i22] = c1_b_dataReceived_data[c1_i22];
        }

        (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
          chartInstance->S, 1U, 2532, 15, MAX_uint32_T, 3, 1, c1_tmp_sizes);
        if (CV_EML_COND(0, 1, 8, CV_RELATIONAL_EVAL(4U, 0U, 11, (real_T)
              c1_tmp_data[2], 202.0, -1, 0U, (real_T)c1_tmp_data[2] == 202.0)))
        {
          c1_tmp_sizes = c1_b_dataReceived_sizes[0];
          c1_l_loop_ub = c1_b_dataReceived_sizes[0] - 1;
          for (c1_i27 = 0; c1_i27 <= c1_l_loop_ub; c1_i27++) {
            c1_tmp_data[c1_i27] = c1_b_dataReceived_data[c1_i27];
          }

          (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
            chartInstance->S, 1U, 2558, 15, MAX_uint32_T, 4, 1, c1_tmp_sizes);
          if (CV_EML_COND(0, 1, 9, CV_RELATIONAL_EVAL(4U, 0U, 12, (real_T)
                c1_tmp_data[3], 24.0, -1, 0U, (real_T)c1_tmp_data[3] == 24.0)))
          {
            CV_EML_MCDC(0, 1, 2, true);
            CV_EML_IF(0, 1, 15, true);
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 89);
            c1_tmp_sizes = c1_b_dataReceived_sizes[0];
            c1_o_loop_ub = c1_b_dataReceived_sizes[0] - 1;
            for (c1_i34 = 0; c1_i34 <= c1_o_loop_ub; c1_i34++) {
              c1_tmp_data[c1_i34] = c1_b_dataReceived_data[c1_i34];
            }

            c1_indexShapeCheck(chartInstance, c1_tmp_sizes);
            c1_i39 = c1_tmp_sizes;
            for (c1_i40 = 0; c1_i40 < 4; c1_i40++) {
              c1_uv1[c1_i40] = c1_tmp_data[sf_eml_array_bounds_check
                (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 2601, 17,
                 MAX_uint32_T, (int32_T)(5.0 + (real_T)c1_i40), 1, c1_i39) - 1];
            }

            c1_val = c1_typecast(chartInstance, c1_uv1);
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 90);
            if (CV_EML_IF(0, 1, 16, CV_RELATIONAL_EVAL(4U, 0U, 13, (real_T)
                  c1_abs(chartInstance, c1_val - 1.0F), 0.001, -1, 2U, (real_T)
                  c1_abs(chartInstance, c1_val - 1.0F) < 0.001))) {
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 91);
              chartInstance->c1_stage = 1.0;
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 92);
              chartInstance->c1_stateChange = 1.0;
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 95);
              chartInstance->c1_ct_route++;
            }
          } else {
            guard1 = true;
          }
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }

      if (guard2 == true) {
        guard1 = true;
      }

      if (guard1 == true) {
        CV_EML_MCDC(0, 1, 2, false);
        CV_EML_IF(0, 1, 15, false);
      }
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 100);
  c1_b_Stage = chartInstance->c1_stage;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 104);
  if (CV_EML_IF(0, 1, 17, chartInstance->c1_stateChange != 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 105);
    _SFD_DIM_SIZE_GEQ_CHECK(5, 0, 2);
    c1_b_Payload_sizes[0] = 1;
    c1_b_Payload_sizes[1] = 0;
    c1_e_Payload = c1_b_Payload_sizes[0];
    c1_f_Payload = c1_b_Payload_sizes[1];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -105);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c1_Stage = c1_b_Stage;
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 2, 0, 1);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 2, 1,
    c1_b_Payload_sizes[1]);
  c1_i31 = (*chartInstance->c1_Payload_sizes)[0];
  c1_i33 = (*chartInstance->c1_Payload_sizes)[1];
  c1_p_loop_ub = c1_b_Payload_sizes[0] * c1_b_Payload_sizes[1] - 1;
  for (c1_i36 = 0; c1_i36 <= c1_p_loop_ub; c1_i36++) {
    (*chartInstance->c1_Payload_data)[c1_i36] = c1_b_Payload_data[c1_i36];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_performMission(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)c1_machineNumber;
  (void)c1_chartNumber;
  (void)c1_instanceNumber;
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_presentRoute_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_b_presentRoute, const char_T *c1_identifier,
  boolean_T *c1_svPtr)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_presentRoute),
    &c1_thisId, c1_svPtr);
  sf_mex_destroy(&c1_b_presentRoute);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  boolean_T *c1_svPtr)
{
  real_T c1_y;
  real_T c1_d2;
  (void)chartInstance;
  if (mxIsEmpty(c1_u)) {
    *c1_svPtr = false;
  } else {
    *c1_svPtr = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d2, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d2;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_presentRoute;
  const char_T *c1_identifier;
  boolean_T *c1_svPtr;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_b_presentRoute = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_svPtr = &chartInstance->c1_presentRoute_not_empty;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_presentRoute),
    &c1_thisId, c1_svPtr);
  sf_mex_destroy(&c1_b_presentRoute);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[], int32_T c1_inData_sizes[2])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u_sizes[2];
  int32_T c1_u;
  int32_T c1_b_u;
  int32_T c1_loop_ub;
  int32_T c1_i41;
  const mxArray *c1_y = NULL;
  real_T c1_u_data[5];
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u_sizes[0] = 1;
  c1_u_sizes[1] = c1_inData_sizes[1];
  c1_u = c1_u_sizes[0];
  c1_b_u = c1_u_sizes[1];
  c1_loop_ub = c1_inData_sizes[0] * c1_inData_sizes[1] - 1;
  for (c1_i41 = 0; c1_i41 <= c1_loop_ub; c1_i41++) {
    c1_u_data[c1_i41] = c1_inData_data[c1_i41];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 0, 0U, 1U, 0U, 2,
    c1_u_sizes[0], c1_u_sizes[1]), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_Payload, const char_T *c1_identifier, real_T
  c1_y_data[], int32_T c1_y_sizes[2])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Payload), &c1_thisId,
                        c1_y_data, c1_y_sizes);
  sf_mex_destroy(&c1_Payload);
}

static void c1_d_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y_data[], int32_T c1_y_sizes[2])
{
  int32_T c1_i42;
  int32_T c1_i43;
  uint32_T c1_uv2[2];
  real_T c1_tmp_data[5];
  boolean_T c1_bv0[2];
  int32_T c1_tmp_sizes[2];
  static boolean_T c1_bv1[2] = { false, true };

  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i44;
  (void)chartInstance;
  for (c1_i42 = 0; c1_i42 < 2; c1_i42++) {
    c1_uv2[c1_i42] = 1U + ((uint32_T)c1_i42 << 2);
  }

  for (c1_i43 = 0; c1_i43 < 2; c1_i43++) {
    c1_bv0[c1_i43] = c1_bv1[c1_i43];
  }

  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 0, 0U, 1, 0U,
                   2, c1_bv0, c1_uv2, c1_tmp_sizes);
  c1_y_sizes[0] = 1;
  c1_y_sizes[1] = c1_tmp_sizes[1];
  c1_y = c1_y_sizes[0];
  c1_b_y = c1_y_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i44 = 0; c1_i44 <= c1_loop_ub; c1_i44++) {
    c1_y_data[c1_i44] = c1_tmp_data[c1_i44];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[], int32_T
  c1_outData_sizes[2])
{
  const mxArray *c1_Payload;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y_data[5];
  int32_T c1_y_sizes[2];
  int32_T c1_loop_ub;
  int32_T c1_i45;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_Payload = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Payload), &c1_thisId,
                        c1_y_data, c1_y_sizes);
  sf_mex_destroy(&c1_Payload);
  c1_outData_sizes[0] = 1;
  c1_outData_sizes[1] = c1_y_sizes[1];
  c1_loop_ub = c1_y_sizes[1] - 1;
  for (c1_i45 = 0; c1_i45 <= c1_loop_ub; c1_i45++) {
    c1_outData_data[c1_outData_sizes[0] * c1_i45] = c1_y_data[c1_y_sizes[0] *
      c1_i45];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_e_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_b_Stage, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Stage), &c1_thisId);
  sf_mex_destroy(&c1_b_Stage);
  return c1_y;
}

static real_T c1_f_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d3;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d3, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d3;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_Stage;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_b_Stage = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Stage), &c1_thisId);
  sf_mex_destroy(&c1_b_Stage);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c1_inData_data[], int32_T c1_inData_sizes[2])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u_sizes[2];
  int32_T c1_u;
  int32_T c1_b_u;
  int32_T c1_loop_ub;
  int32_T c1_i46;
  const mxArray *c1_y = NULL;
  uint8_T c1_u_data[255];
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u_sizes[0] = c1_inData_sizes[0];
  c1_u_sizes[1] = 1;
  c1_u = c1_u_sizes[0];
  c1_b_u = c1_u_sizes[1];
  c1_loop_ub = c1_inData_sizes[0] * c1_inData_sizes[1] - 1;
  for (c1_i46 = 0; c1_i46 <= c1_loop_ub; c1_i46++) {
    c1_u_data[c1_i46] = c1_inData_data[c1_i46];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 3, 0U, 1U, 0U, 2,
    c1_u_sizes[0], c1_u_sizes[1]), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i47;
  const mxArray *c1_y = NULL;
  real_T c1_u[3];
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i47 = 0; c1_i47 < 3; c1_i47++) {
    c1_u[c1_i47] = (*(real_T (*)[3])c1_inData)[c1_i47];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i48;
  int32_T c1_i49;
  const mxArray *c1_y = NULL;
  int32_T c1_i50;
  real_T c1_u[18];
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i48 = 0;
  for (c1_i49 = 0; c1_i49 < 3; c1_i49++) {
    for (c1_i50 = 0; c1_i50 < 6; c1_i50++) {
      c1_u[c1_i50 + c1_i48] = (*(real_T (*)[18])c1_inData)[c1_i50 + c1_i48];
    }

    c1_i48 += 6;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 6, 3), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real32_T c1_g_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real32_T c1_y;
  real32_T c1_f0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_f0, 1, 1, 0U, 0, 0U, 0);
  c1_y = c1_f0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_val;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real32_T c1_y;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_val = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_val), &c1_thisId);
  sf_mex_destroy(&c1_val);
  *(real32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static void c1_h_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3])
{
  real_T c1_dv0[3];
  int32_T c1_i51;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv0, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c1_i51 = 0; c1_i51 < 3; c1_i51++) {
    c1_y[c1_i51] = c1_dv0[c1_i51];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_coordinates;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i52;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_coordinates = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_coordinates), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_coordinates);
  for (c1_i52 = 0; c1_i52 < 3; c1_i52++) {
    (*(real_T (*)[3])c1_outData)[c1_i52] = c1_y[c1_i52];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[], int32_T c1_inData_sizes[2])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u_sizes[2];
  int32_T c1_u;
  int32_T c1_b_u;
  int32_T c1_loop_ub;
  int32_T c1_i53;
  const mxArray *c1_y = NULL;
  real_T c1_u_data[18];
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u_sizes[0] = c1_inData_sizes[0];
  c1_u_sizes[1] = 3;
  c1_u = c1_u_sizes[0];
  c1_b_u = c1_u_sizes[1];
  c1_loop_ub = c1_inData_sizes[0] * c1_inData_sizes[1] - 1;
  for (c1_i53 = 0; c1_i53 <= c1_loop_ub; c1_i53++) {
    c1_u_data[c1_i53] = c1_inData_data[c1_i53];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 0, 0U, 1U, 0U, 2,
    c1_u_sizes[0], c1_u_sizes[1]), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_i_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y_data[], int32_T c1_y_sizes[2])
{
  int32_T c1_i54;
  int32_T c1_i55;
  uint32_T c1_uv3[2];
  real_T c1_tmp_data[18];
  boolean_T c1_bv2[2];
  int32_T c1_tmp_sizes[2];
  static boolean_T c1_bv3[2] = { true, false };

  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i56;
  (void)chartInstance;
  for (c1_i54 = 0; c1_i54 < 2; c1_i54++) {
    c1_uv3[c1_i54] = 6U + (uint32_T)(-3 * c1_i54);
  }

  for (c1_i55 = 0; c1_i55 < 2; c1_i55++) {
    c1_bv2[c1_i55] = c1_bv3[c1_i55];
  }

  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 0, 0U, 1, 0U,
                   2, c1_bv2, c1_uv3, c1_tmp_sizes);
  c1_y_sizes[0] = c1_tmp_sizes[0];
  c1_y_sizes[1] = 3;
  c1_y = c1_y_sizes[0];
  c1_b_y = c1_y_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i56 = 0; c1_i56 <= c1_loop_ub; c1_i56++) {
    c1_y_data[c1_i56] = c1_tmp_data[c1_i56];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[], int32_T
  c1_outData_sizes[2])
{
  const mxArray *c1_route;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y_data[18];
  int32_T c1_y_sizes[2];
  int32_T c1_i57;
  int32_T c1_loop_ub;
  int32_T c1_i58;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_route = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_route), &c1_thisId,
                        c1_y_data, c1_y_sizes);
  sf_mex_destroy(&c1_route);
  c1_outData_sizes[0] = c1_y_sizes[0];
  c1_outData_sizes[1] = 3;
  for (c1_i57 = 0; c1_i57 < 3; c1_i57++) {
    c1_loop_ub = c1_y_sizes[0] - 1;
    for (c1_i58 = 0; c1_i58 <= c1_loop_ub; c1_i58++) {
      c1_outData_data[c1_i58 + c1_outData_sizes[0] * c1_i57] = c1_y_data[c1_i58
        + c1_y_sizes[0] * c1_i57];
    }
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_performMission_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c1_nameCaptureInfo;
}

static void c1_indexShapeCheck(SFc1_performMissionInstanceStruct *chartInstance,
  int32_T c1_matrixSize)
{
  int32_T c1_size1;
  boolean_T c1_b;
  boolean_T c1_b6;
  boolean_T c1_c;
  boolean_T c1_b_c;
  const mxArray *c1_y = NULL;
  static char_T c1_u[30] = { 'C', 'o', 'd', 'e', 'r', ':', 'F', 'E', ':', 'P',
    'o', 't', 'e', 'n', 't', 'i', 'a', 'l', 'V', 'e', 'c', 't', 'o', 'r', 'V',
    'e', 'c', 't', 'o', 'r' };

  (void)chartInstance;
  c1_size1 = c1_matrixSize;
  c1_b = !(c1_size1 != 1);
  c1_b6 = c1_b;
  c1_c = c1_b6;
  c1_b_c = c1_c;
  if (!c1_b_c) {
  } else {
    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 30),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 1U, 14, c1_y));
  }
}

static real32_T c1_typecast(SFc1_performMissionInstanceStruct *chartInstance,
  uint8_T c1_x[4])
{
  real32_T c1_y;
  (void)chartInstance;
  memcpy(&c1_y, &c1_x[0], (size_t)1 * sizeof(real32_T));
  return c1_y;
}

static real32_T c1_abs(SFc1_performMissionInstanceStruct *chartInstance,
  real32_T c1_x)
{
  real32_T c1_b_x;
  real32_T c1_c_x;
  (void)chartInstance;
  c1_b_x = c1_x;
  c1_c_x = c1_b_x;
  return muSingleScalarAbs(c1_c_x);
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_j_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i59;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i59, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i59;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_k_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_performMission, const char_T *
  c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_performMission), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_performMission);
  return c1_y;
}

static uint8_T c1_l_emlrt_marshallIn(SFc1_performMissionInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_performMissionInstanceStruct
  *chartInstance)
{
  chartInstance->c1_Stage = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_destinations = (real_T (*)[18])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_Payload_data = (real_T (*)[5])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_Payload_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 2);
  chartInstance->c1_Q = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c1_wp_ids = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_t = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    3);
  chartInstance->c1_dataReceived_data = (uint8_T (*)[255])
    ssGetInputPortSignal_wrapper(chartInstance->S, 4);
  chartInstance->c1_dataReceived_sizes = (int32_T (*)[2])
    ssGetCurrentInputPortDimensions_wrapper(chartInstance->S, 4);
  sf_mex_size_one_check(((*chartInstance->c1_dataReceived_sizes)[1U] == 0) &&
                        (!((*chartInstance->c1_dataReceived_sizes)[0U] == 0)),
                        "dataReceived");
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

void sf_c1_performMission_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1826419152U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1108514953U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4061498368U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2682368586U);
}

mxArray* sf_c1_performMission_get_post_codegen_info(void);
mxArray *sf_c1_performMission_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("a1Or114G3aZnlUnBFPvhOG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(3);
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
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(3);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(255);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_performMission_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_performMission_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_performMission_jit_fallback_info(void)
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

mxArray *sf_c1_performMission_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_performMission_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c1_performMission(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[5],T\"Payload\",},{M[1],M[14],T\"Stage\",},{M[4],M[0],T\"ct_customer\",S'l','i','p'{{M1x2[657 668],M[0],}}},{M[4],M[0],T\"ct_route\",S'l','i','p'{{M1x2[642 650],M[0],}}},{M[4],M[0],T\"isRouteFinished\",S'l','i','p'{{M1x2[669 684],M[0],}}},{M[4],M[0],T\"presentRoute\",S'l','i','p'{{M1x2[707 719],M[0],}}},{M[4],M[0],T\"stage\",S'l','i','p'{{M1x2[689 694],M[0],}}},{M[4],M[0],T\"stateChange\",S'l','i','p'{{M1x2[695 706],M[0],}}},{M[4],M[0],T\"tStep\",S'l','i','p'{{M1x2[651 656],M[0],}}},{M[4],M[0],T\"tol\",S'l','i','p'{{M1x2[685 688],M[0],}}}}",
    "100 S'type','srcId','name','auxInfo'{{M[8],M[0],T\"is_active_c1_performMission\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 11, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_performMission_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_performMissionInstanceStruct *chartInstance =
      (SFc1_performMissionInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _performMissionMachineNumber_,
           1,
           1,
           1,
           0,
           7,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"destinations");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Q");
          _SFD_SET_DATA_PROPS(2,1,1,0,"wp_ids");
          _SFD_SET_DATA_PROPS(3,1,1,0,"t");
          _SFD_SET_DATA_PROPS(4,1,1,0,"dataReceived");
          _SFD_SET_DATA_PROPS(5,2,0,1,"Stage");
          _SFD_SET_DATA_PROPS(6,2,0,1,"Payload");
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
        _SFD_CV_INIT_EML(0,1,1,0,18,0,0,0,0,0,10,3);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2997);
        _SFD_CV_INIT_EML_IF(0,1,0,923,946,-1,971);
        _SFD_CV_INIT_EML_IF(0,1,1,972,989,-1,1008);
        _SFD_CV_INIT_EML_IF(0,1,2,1009,1036,-1,1065);
        _SFD_CV_INIT_EML_IF(0,1,3,1066,1081,-1,1102);
        _SFD_CV_INIT_EML_IF(0,1,4,1103,1120,-1,1139);
        _SFD_CV_INIT_EML_IF(0,1,5,1140,1164,-1,1190);
        _SFD_CV_INIT_EML_IF(0,1,6,1191,1211,-1,1233);
        _SFD_CV_INIT_EML_IF(0,1,7,1505,1542,1600,1641);
        _SFD_CV_INIT_EML_IF(0,1,8,1665,1678,2202,2219);
        _SFD_CV_INIT_EML_IF(0,1,9,1758,1872,-1,2085);
        _SFD_CV_INIT_EML_IF(0,1,10,1966,1984,-1,2077);
        _SFD_CV_INIT_EML_IF(0,1,11,2202,2219,2481,2818);
        _SFD_CV_INIT_EML_IF(0,1,12,2224,2298,-1,2447);
        _SFD_CV_INIT_EML_IF(0,1,13,2360,2375,-1,2439);
        _SFD_CV_INIT_EML_IF(0,1,14,2481,2498,-1,2498);
        _SFD_CV_INIT_EML_IF(0,1,15,2503,2577,-1,2814);
        _SFD_CV_INIT_EML_IF(0,1,16,2639,2656,-1,2806);
        _SFD_CV_INIT_EML_IF(0,1,17,2952,2966,-1,2996);

        {
          static int condStart[] = { 1762, 1787, 1813, 1836 };

          static int condEnd[] = { 1783, 1809, 1832, 1872 };

          static int pfixExpr[] = { 0, -1, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,1761,1872,4,0,&(condStart[0]),&(condEnd[0]),
                                8,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2228, 2253, 2279 };

          static int condEnd[] = { 2249, 2275, 2298 };

          static int pfixExpr[] = { 0, -1, 1, -3, 2, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,2227,2298,3,4,&(condStart[0]),&(condEnd[0]),
                                6,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2507, 2532, 2558 };

          static int condEnd[] = { 2528, 2554, 2577 };

          static int pfixExpr[] = { 0, -1, 1, -3, 2, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,2,2506,2577,3,7,&(condStart[0]),&(condEnd[0]),
                                6,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,1508,1542,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,1668,1678,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,1787,1809,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,1813,1832,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,4,1836,1872,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,5,1969,1984,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,6,2209,2219,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,7,2253,2275,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,8,2279,2298,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,9,2363,2375,-1,2);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,10,2488,2498,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,11,2532,2554,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,12,2558,2577,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,13,2642,2656,-1,2);

        {
          unsigned int dimVector[2];
          dimVector[0]= 6U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 255U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 5U;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
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
    SFc1_performMissionInstanceStruct *chartInstance =
      (SFc1_performMissionInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c1_Stage);
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c1_destinations);
        _SFD_SET_DATA_VALUE_PTR_VAR_DIM(6U, *chartInstance->c1_Payload_data,
          (void *)chartInstance->c1_Payload_sizes);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c1_Q);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c1_wp_ids);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c1_t);
        _SFD_SET_DATA_VALUE_PTR_VAR_DIM(4U, *chartInstance->c1_dataReceived_data,
          (void *)chartInstance->c1_dataReceived_sizes);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sOlHMRy5uWc0FuJPZziRjqC";
}

static void sf_opaque_initialize_c1_performMission(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_performMissionInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_performMission((SFc1_performMissionInstanceStruct*)
    chartInstanceVar);
  initialize_c1_performMission((SFc1_performMissionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_performMission(void *chartInstanceVar)
{
  enable_c1_performMission((SFc1_performMissionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_performMission(void *chartInstanceVar)
{
  disable_c1_performMission((SFc1_performMissionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_performMission(void *chartInstanceVar)
{
  sf_gateway_c1_performMission((SFc1_performMissionInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_performMission(SimStruct* S)
{
  return get_sim_state_c1_performMission((SFc1_performMissionInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_performMission(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c1_performMission((SFc1_performMissionInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c1_performMission(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_performMissionInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_performMission_optimization_info();
    }

    finalize_c1_performMission((SFc1_performMissionInstanceStruct*)
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
  initSimStructsc1_performMission((SFc1_performMissionInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_performMission(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_performMission((SFc1_performMissionInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c1_performMission(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_performMission_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 1);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1312320064U));
  ssSetChecksum1(S,(1422442587U));
  ssSetChecksum2(S,(3227970191U));
  ssSetChecksum3(S,(1486480826U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_performMission(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_performMission(SimStruct *S)
{
  SFc1_performMissionInstanceStruct *chartInstance;
  chartInstance = (SFc1_performMissionInstanceStruct *)utMalloc(sizeof
    (SFc1_performMissionInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc1_performMissionInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_performMission;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_performMission;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_performMission;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_performMission;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_performMission;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_performMission;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_performMission;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_performMission;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_performMission;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_performMission;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_performMission;
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
  mdl_start_c1_performMission(chartInstance);
}

void c1_performMission_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_performMission(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_performMission(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_performMission(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_performMission_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
