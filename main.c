/* ###*B*###
 * ###*E*### */

#include <stdio.h>
#include "rtmodel.h"
#include "SWatch.h"

/* State variables for generated code */
RT_MODEL_SWatch_T SWatch_state;
char_T errorSig[6];
PrevZCX_SWatch_T ZCSig;
DW_SWatch_T DWork;

boolean_T Btime, Btimeset, Balarm, Bswatch, Bplus, Bminus;
uint8_T hours=0, minutes=0, seconds=0, tenths=0, mode;

void setTimeString(char *watchstr, uint8_T hours, uint8_T minutes, uint8_T seconds, uint8_T tenths, uint8_T mode)
{
	sprintf(watchstr, "%2d:%2d:%2d", hours, minutes, seconds);
}
/*
 * TASK Clock
 */
unsigned char IsUpdateTime()
{
	unsigned char res;
	static unsigned char oh=0, om=0, os=0;
	if (hours!=oh || minutes!=om || seconds!= os)
		res = 1;
	else
		res = 0;
	oh = hours;
	om = minutes;
	os = seconds;
	return res;
}

void UpdateTime()
{
	char watchstr[20];
	setTimeString(watchstr, hours, minutes, seconds, tenths, mode);
}

void strencode2digit(char *str, int digit)
{
	str[2]=0;
	str[0]=digit/10+'0';
	str[1]=digit%10+'0';
}

void TaskClock()
{
	unsigned char i;
	static int oldmode=8;
	static unsigned char oh=99, om=99, os=99;
	char tstr[3];

	SWatch_step(&SWatch_state,
			  Bplus, Bminus, Btime, Btimeset, Balarm, Bswatch,
			  &hours, &minutes, &seconds, &tenths, &mode);

	Bplus=Bminus=Btime=Btimeset=Balarm=Bswatch=0;

	if (hours!=oh) {
		strencode2digit(tstr, (int)hours);
		printf("%s ", tstr);
		oh=hours;
	}
	if (minutes!=om) {
		strencode2digit(tstr, (int)minutes);
		printf("%s ", tstr);
		om=minutes;
	}
	if (seconds!= os) {
		strencode2digit(tstr, (int)seconds);
		printf("%s\n", tstr);
		os=seconds;
	}

	if (mode != oldmode) {
		oldmode = mode;
	}
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */



/*
 * MAIN TASK
 */
int main(void)
{
  int i=0;

  SWatch_state.errorStatus = errorSig;
  SWatch_state.ModelData.defaultParam = &SWatch_P;
  SWatch_state.ModelData.prevZCSigState = &ZCSig;
  SWatch_state.ModelData.dwork = &DWork;
    
  /* init state machine */
	SWatch_initialize(&SWatch_state,
	  &Bplus, &Bminus, &Btime, &Btimeset, &Balarm, &Bswatch,
	  &hours, &minutes, &seconds, &tenths, &mode);

	for (i=0;i<100;i++) { 
	  TaskClock();
	}

}


