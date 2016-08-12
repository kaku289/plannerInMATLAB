#ifndef __c3_performMission_h__
#define __c3_performMission_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#include <stddef.h>
#ifndef typedef_SFc3_performMissionInstanceStruct
#define typedef_SFc3_performMissionInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_performMission;
  real_T *c3_stage;
  real_T (*c3_payload_data)[5];
  int32_T (*c3_payload_sizes)[2];
  uint8_T (*c3_dataSent_data)[20];
  int32_T (*c3_dataSent_sizes)[2];
} SFc3_performMissionInstanceStruct;

#endif                                 /*typedef_SFc3_performMissionInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_performMission_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_performMission_get_check_sum(mxArray *plhs[]);
extern void c3_performMission_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
