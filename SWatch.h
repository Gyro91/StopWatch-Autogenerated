/*
 * File: SWatch.h
 *
 * Code generated for Simulink model 'SWatch'.
 *
 * Model version                  : 1.124
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Mon Jan 25 15:09:01 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SWatch_h_
#define RTW_HEADER_SWatch_h_
#include <string.h>
#ifndef SWatch_COMMON_INCLUDES_
# define SWatch_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* SWatch_COMMON_INCLUDES_ */

#include "SWatch_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T Output_DSTATE;               /* '<S2>/Output' */
  uint8_T is_Control;                  /* '<S1>/SWatch' */
  uint8_T is_timermode;                /* '<S1>/SWatch' */
  uint8_T is_Timer;                    /* '<S1>/SWatch' */
  uint8_T is_swatchmode;               /* '<S1>/SWatch' */
  uint8_T is_alarmmode;                /* '<S1>/SWatch' */
  uint8_T is_TimeCount;                /* '<S1>/SWatch' */
  uint8_T is_Timeset;                  /* '<S1>/SWatch' */
  uint8_T hours;                       /* '<S1>/SWatch' */
  uint8_T minutes;                     /* '<S1>/SWatch' */
  uint8_T seconds;                     /* '<S1>/SWatch' */
  uint8_T tenths;                      /* '<S1>/SWatch' */
  uint8_T Ahours;                      /* '<S1>/SWatch' */
  uint8_T Aminutes;                    /* '<S1>/SWatch' */
  uint8_T Aseconds;                    /* '<S1>/SWatch' */
  uint8_T Atenths;                     /* '<S1>/SWatch' */
  uint8_T Alarm_h;                     /* '<S1>/SWatch' */
  uint8_T Alarm_m;                     /* '<S1>/SWatch' */
  uint8_T Alarm_state;                 /* '<S1>/SWatch' */
  uint8_T mutex;                       /* '<S1>/SWatch' */
} DW_SWatch_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState SWatch_Trig_ZCE[9];       /* '<S1>/SWatch' */
} PrevZCX_SWatch_T;

/* Real-time Model Data Structure */
struct tag_RTM_SWatch_T {
  const char_T * volatile errorStatus;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    PrevZCX_SWatch_T *prevZCSigState;
    DW_SWatch_T *dwork;
  } ModelData;
};

/* Model entry point functions */
extern void SWatch_initialize(RT_MODEL_SWatch_T *const SWatch_M, boolean_T
  *SWatch_U_Bplus, boolean_T *SWatch_U_Bminus, boolean_T *SWatch_U_Btime,
  boolean_T *SWatch_U_Btimer, boolean_T *SWatch_U_Balarm, boolean_T
  *SWatch_U_Bswatch, boolean_T *SWatch_U_Bstart, boolean_T *SWatch_U_Bstop,
  uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds,
  uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode, uint8_T
  *SWatch_Y_Alarm_signal, uint8_T *SWatch_Y_Timer_exp);
extern void SWatch_step(RT_MODEL_SWatch_T *const SWatch_M, boolean_T
  SWatch_U_Bplus, boolean_T SWatch_U_Bminus, boolean_T SWatch_U_Btime, boolean_T
  SWatch_U_Btimer, boolean_T SWatch_U_Balarm, boolean_T SWatch_U_Bswatch,
  boolean_T SWatch_U_Bstart, boolean_T SWatch_U_Bstop, uint8_T *SWatch_Y_hours,
  uint8_T *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths,
  uint8_T *SWatch_Y_mode, uint8_T *SWatch_Y_Alarm_signal, uint8_T
  *SWatch_Y_Timer_exp);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('NewWatch/SWatch')    - opens subsystem NewWatch/SWatch
 * hilite_system('NewWatch/SWatch/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'NewWatch'
 * '<S1>'   : 'NewWatch/SWatch'
 * '<S2>'   : 'NewWatch/SWatch/Counter Limited'
 * '<S3>'   : 'NewWatch/SWatch/SWatch'
 * '<S4>'   : 'NewWatch/SWatch/Counter Limited/Increment Real World'
 * '<S5>'   : 'NewWatch/SWatch/Counter Limited/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_SWatch_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
