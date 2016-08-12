#ifndef __c1_performMission_h__
#define __c1_performMission_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#include <stddef.h>
#ifndef typedef_SFc1_performMissionInstanceStruct
#define typedef_SFc1_performMissionInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_performMission;
  real_T c1_ct_route;
  boolean_T c1_ct_route_not_empty;
  real_T c1_tStep;
  boolean_T c1_tStep_not_empty;
  real_T c1_ct_customer;
  boolean_T c1_ct_customer_not_empty;
  real_T c1_isRouteFinished;
  boolean_T c1_isRouteFinished_not_empty;
  real_T c1_tol;
  boolean_T c1_tol_not_empty;
  real_T c1_stage;
  boolean_T c1_stage_not_empty;
  real_T c1_stateChange;
  boolean_T c1_stateChange_not_empty;
  real_T c1_presentRoute;
  boolean_T c1_presentRoute_not_empty;
  real_T *c1_Stage;
  real_T (*c1_destinations)[18];
  real_T (*c1_Payload_data)[5];
  int32_T (*c1_Payload_sizes)[2];
  real_T *c1_Q;
  real_T (*c1_wp_ids)[3];
  real_T *c1_t;
  uint8_T (*c1_dataReceived_data)[255];
  int32_T (*c1_dataReceived_sizes)[2];
} SFc1_performMissionInstanceStruct;

#endif                                 /*typedef_SFc1_performMissionInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_performMission_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_performMission_get_check_sum(mxArray *plhs[]);
extern void c1_performMission_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
