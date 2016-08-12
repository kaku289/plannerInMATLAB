#ifndef __c4_performMission_h__
#define __c4_performMission_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#include <stddef.h>
#ifndef typedef_SFc4_performMissionInstanceStruct
#define typedef_SFc4_performMissionInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c4_sfEvent;
  boolean_T c4_doneDoubleBufferReInit;
  uint8_T c4_is_active_c4_performMission;
  real_T c4_ct_route;
  boolean_T c4_ct_route_not_empty;
  real_T c4_tStep;
  boolean_T c4_tStep_not_empty;
  real_T c4_ct_customer;
  boolean_T c4_ct_customer_not_empty;
  real_T c4_isRouteFinished;
  boolean_T c4_isRouteFinished_not_empty;
  real_T c4_tol;
  boolean_T c4_tol_not_empty;
  real_T c4_stage;
  boolean_T c4_stage_not_empty;
  real_T c4_stateChange;
  boolean_T c4_stateChange_not_empty;
  real_T c4_presentRoute;
  boolean_T c4_presentRoute_not_empty;
  real_T *c4_Stage;
  real_T (*c4_destinations)[18];
  real_T (*c4_Payload_data)[5];
  int32_T (*c4_Payload_sizes)[2];
  real_T *c4_Q;
  real_T (*c4_wp_ids)[3];
  real_T *c4_t;
  uint8_T (*c4_dataReceived_data)[255];
  int32_T (*c4_dataReceived_sizes)[2];
} SFc4_performMissionInstanceStruct;

#endif                                 /*typedef_SFc4_performMissionInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_performMission_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_performMission_get_check_sum(mxArray *plhs[]);
extern void c4_performMission_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
