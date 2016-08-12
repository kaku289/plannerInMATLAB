#ifndef __c5_performMission_h__
#define __c5_performMission_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#include <stddef.h>
#ifndef typedef_SFc5_performMissionInstanceStruct
#define typedef_SFc5_performMissionInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c5_sfEvent;
  boolean_T c5_doneDoubleBufferReInit;
  uint8_T c5_is_active_c5_performMission;
  real_T *c5_stage;
  real_T (*c5_payload_data)[5];
  int32_T (*c5_payload_sizes)[2];
  uint8_T (*c5_dataSent_data)[20];
  int32_T (*c5_dataSent_sizes)[2];
} SFc5_performMissionInstanceStruct;

#endif                                 /*typedef_SFc5_performMissionInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_performMission_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c5_performMission_get_check_sum(mxArray *plhs[]);
extern void c5_performMission_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
