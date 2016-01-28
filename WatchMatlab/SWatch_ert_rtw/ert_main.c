/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'SWatch'.
 *
 * Model version                  : 1.151
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Jan 28 14:52:28 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "SWatch.h"                    /* Model's header file */
#include "rtwtypes.h"
#include "zero_crossing_types.h"

static RT_MODEL_SWatch_T SWatch_M_;
static RT_MODEL_SWatch_T *const SWatch_M = &SWatch_M_;/* Real-time model */
static B_SWatch_T SWatch_B;            /* Observable signals */
static DW_SWatch_T SWatch_DW;          /* Observable states */
static PrevZCX_SWatch_T SWatch_PrevZCX;/* Triggered events */

/* '<Root>/Bplus' */
static boolean_T SWatch_U_Bplus;

/* '<Root>/Bminus' */
static boolean_T SWatch_U_Bminus;

/* '<Root>/Btime' */
static boolean_T SWatch_U_Btime;

/* '<Root>/Btimer' */
static boolean_T SWatch_U_Btimer;

/* '<Root>/Balarm' */
static boolean_T SWatch_U_Balarm;

/* '<Root>/Bswatch' */
static boolean_T SWatch_U_Bswatch;

/* '<Root>/Bstart' */
static boolean_T SWatch_U_Bstart;

/* '<Root>/Bstop' */
static boolean_T SWatch_U_Bstop;

/* '<Root>/hours' */
static uint8_T SWatch_Y_hours;

/* '<Root>/minutes' */
static uint8_T SWatch_Y_minutes;

/* '<Root>/seconds' */
static uint8_T SWatch_Y_seconds;

/* '<Root>/tenths' */
static uint8_T SWatch_Y_tenths;

/* '<Root>/mode' */
static uint8_T SWatch_Y_mode;

/* '<Root>/Alarm_signal' */
static uint8_T SWatch_Y_Alarm_signal;

/* '<Root>/Timer_exp' */
static uint8_T SWatch_Y_Timer_exp;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL_SWatch_T *const SWatch_M);
void rt_OneStep(RT_MODEL_SWatch_T *const SWatch_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(SWatch_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  SWatch_step(SWatch_M, SWatch_U_Bplus, SWatch_U_Bminus, SWatch_U_Btime,
              SWatch_U_Btimer, SWatch_U_Balarm, SWatch_U_Bswatch,
              SWatch_U_Bstart, SWatch_U_Bstop, &SWatch_Y_hours,
              &SWatch_Y_minutes, &SWatch_Y_seconds, &SWatch_Y_tenths,
              &SWatch_Y_mode, &SWatch_Y_Alarm_signal, &SWatch_Y_Timer_exp);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Pack model data into RTM */
  SWatch_M->ModelData.blockIO = &SWatch_B;
  SWatch_M->ModelData.dwork = &SWatch_DW;
  SWatch_M->ModelData.prevZCSigState = &SWatch_PrevZCX;

  /* Initialize model */
  SWatch_initialize(SWatch_M, &SWatch_U_Bplus, &SWatch_U_Bminus, &SWatch_U_Btime,
                    &SWatch_U_Btimer, &SWatch_U_Balarm, &SWatch_U_Bswatch,
                    &SWatch_U_Bstart, &SWatch_U_Bstop, &SWatch_Y_hours,
                    &SWatch_Y_minutes, &SWatch_Y_seconds, &SWatch_Y_tenths,
                    &SWatch_Y_mode, &SWatch_Y_Alarm_signal, &SWatch_Y_Timer_exp);

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.1 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep(SWatch_M);
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(SWatch_M) == (NULL)) {
    /*  Perform other application tasks here */
  }

  /* Disable rt_OneStep() here */
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
