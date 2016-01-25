/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

#include "ee.h"
#include "ee_irq.h"
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "stm32f4xx.h"

#include "STMPE811QTR.h"
#include "pictures.h"
#include "Widget.h"
#include "WidgetConfig.h"
#include "Touch.h"
#include "Event.h"
#include "SWatch.h"
#include "lcd_add.h"
#include "fonts.h"
#include "debug.h"

/* State variables for generated code */
RT_MODEL_SWatch_T SWatch_state;
char_T errorSig[6];
PrevZCX_SWatch_T ZCSig;
DW_SWatch_T DWork;

int ran = 0;
boolean_T Btime, Btimer, Balarm, Bswatch, Bplus, Bminus, Bstart, Bstop;
uint8_T hours=0, minutes=0, seconds=0, tenths=0, mode, alarm_signal=0, timer_exp=0;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/*
 * TASK LCD
 */
TASK(TaskLCD)
{
	unsigned int px, py;
	TPoint p;
	if (GetTouch_SC_Async(&px, &py)) {
		p.x = px;
		p.y = py;
		OnTouch(MyWatchScr, &p);
	}
}

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
	unsigned char watchstr[20];
	setTimeString(watchstr, hours, minutes, seconds, tenths, mode);

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(Blue);
	//LCD_DrawFullRect(25, 100, 106, 32);

	/*	WPrint(&MyWatchScr[TIMESTR], watchstr); */
}

void UpdateMode(unsigned char om, unsigned char m)
{
	switch(om) {
	case 2:
		DrawOff(&MyWatchScr[BALARM]);
		break;
	case 1:
		DrawOff(&MyWatchScr[BTIMER]);
		break;
	case 0:
		DrawOff(&MyWatchScr[BTIME]);
		break;
	case 3:
		DrawOff(&MyWatchScr[BSWATCH]);
		break;
	}
	switch(m) {
	case 2:
		DrawOn(&MyWatchScr[BALARM]);
		break;
	case 1:
		DrawOn(&MyWatchScr[BTIMER]);
		break;
	case 0:
		DrawOn(&MyWatchScr[BTIME]);
		break;
	case 3:
		DrawOn(&MyWatchScr[BSWATCH]);
		break;
	}
}

void strencode2digit(char *str, int digit)
{
	str[2]=0;
	str[0]=digit/10+'0';
	str[1]=digit%10+'0';
}

void tenths2digit(char *str, int digit)
{
	str[1]=0;
	str[0]=digit%10+'0';
}

void drawdigits(char *tstr,const Widget *ws, int digits, int x, int y)
{
	strencode2digit(tstr, digits);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(x, y, 62, 48);
	WPrint(ws, tstr);
}

// For visualizing the correct digits in the mode

void handling_digits(char *tstr)
{
	if (mode == 2) {
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(140, 80, 110, 56);
	}
	else {
		WPrint(&MyWatchScr[SEP1STR], ":");
		WPrint(&MyWatchScr[SEP2STR], ":");
		if (mode == 1 ) {
			LCD_SetTextColor(Black);
			LCD_SetBackColor(Black);
			LCD_DrawFullRect(210, 80, 40, 56);
			drawdigits(tstr,&MyWatchScr[SECSTR], 0, 150, 80);
		}
		if (mode == 3) {
			drawdigits(tstr,&MyWatchScr[SECSTR], 0, 150, 80);
			tenths2digit(tstr, 0);
			LCD_SetTextColor(Black);
			LCD_SetBackColor(Black);
			LCD_DrawFullRect(208, 80, 35, 48);
			WPrint(&MyWatchScr[DOT], ".");
			WPrint(&MyWatchScr[TTSSTR], tstr);
		}
		if (mode == 0) {
			LCD_SetTextColor(Black);
			LCD_SetBackColor(Black);
			LCD_DrawFullRect(210, 80, 40, 56);
		}
	}
}

// Updating digits after every step

void update_digits(char *tstr, unsigned char *oh, unsigned char *om,
		unsigned char *os, unsigned char *ot) {
	if (hours!=*oh) {
		drawdigits(tstr,&MyWatchScr[HRSSTR],(int)hours, 10, 80);
		*oh=hours;
		WPrint(&MyWatchScr[SEP1STR], ":");
	}

	if (minutes!=*om) {
		drawdigits(tstr,&MyWatchScr[MINSTR],(int)minutes, 80, 80);
		*om=minutes;
		if(mode!=1 && mode != 2)
			WPrint(&MyWatchScr[SEP2STR], ":");
	}
	if (seconds!= *os && mode!=2) {
		drawdigits(tstr,&MyWatchScr[SECSTR],(int)seconds, 150, 80);
		*os=seconds;
	}
	if (mode == 3 && tenths != *ot) {
		tenths2digit(tstr, (int)tenths);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(208, 80, 35, 48);
		WPrint(&MyWatchScr[DOT], ".");
		WPrint(&MyWatchScr[TTSSTR], tstr);
		*ot=tenths;
	}
}

void blinking_digits(char *tstr, unsigned char *oh, unsigned char *om,
		unsigned char *os, unsigned char *ot) {

		drawdigits(tstr,&MyWatchScr[HRSSTR],(int)hours, 10, 80);
		*oh=hours;
		WPrint(&MyWatchScr[SEP1STR], ":");

		drawdigits(tstr,&MyWatchScr[MINSTR],(int)minutes, 80, 80);
		*om=minutes;
		if(mode!=1 && mode != 2)
			WPrint(&MyWatchScr[SEP2STR], ":");

	if (mode!=2) {
		drawdigits(tstr,&MyWatchScr[SECSTR],(int)seconds, 150, 80);
		*os=seconds;
	}
	if (mode == 3) {
		tenths2digit(tstr, (int)tenths);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(208, 80, 35, 48);
		WPrint(&MyWatchScr[DOT], ".");
		WPrint(&MyWatchScr[TTSSTR], tstr);
		*ot=tenths;
	}
}

void handling_events()
{
	if (IsEvent(TIMEMODE))
		Btime=1;
	else
		Btime=0;

	if (IsEvent(TIMERMODE))
		Btimer=1;
	else
		Btimer=0;

	if (IsEvent(ALARMMODE))
		Balarm=1;
	else
		Balarm=0;

	if (IsEvent(SWATCHMODE))
		Bswatch=1;
	else
		Bswatch=0;

	if (IsEvent(PLUS))
		Bplus=1;
	else
		Bplus=0;

	if (IsEvent(MINUS))
		Bminus=1;
	else
		Bminus=0;

	if (IsEvent(START))
		Bstart=1;
	else
		Bstart=0;

	if (IsEvent(STOP))
		Bstop=1;
	else
		Bstop=0;
}

TASK(TaskClock)
{
	int rand = 0, t = 0;
	unsigned char i;
	static int oldmode=8;
	static unsigned char oh=99, om=99, os=99, ot=99;
	char tstr[3];

	handling_events();

	SWatch_step(&SWatch_state,
			Bplus, Bminus, Btime, Btimer, Balarm, Bswatch, Bstart, Bstop,
			&hours, &minutes, &seconds, &tenths, &mode, &alarm_signal,&timer_exp);

	ClearEvents();
	Bplus=Bminus=Btime=Btimer=Balarm=Bswatch=0;

	update_digits(tstr, &oh, &om, &os, &ot);

	if (alarm_signal) {
		if (!ran) {
			ran = 1;
			DrawOff(&MyWatchScr[17]);
		}
		else {
			ran = 0;
			DrawOff(&MyWatchScr[18]);
		}
	}
		else DrawOff(&MyWatchScr[18]);


	if(timer_exp)
		WPrint(&MyWatchScr[14], "Timer Expired");
	else
		DrawOff(&MyWatchScr[19]);
	if (mode != oldmode) {
		handling_digits(tstr);
		UpdateMode(oldmode, mode);
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
	//GPIO_InitTypeDef GPIO_InitStructure;

	SystemInit();
	/*Initializes Erika related stuffs*/
	EE_system_init();

	SWatch_state.errorStatus = errorSig;
	SWatch_state.ModelData.prevZCSigState = &ZCSig;
	SWatch_state.ModelData.dwork = &DWork;

	/* init state machine */
	SWatch_initialize(&SWatch_state,
			&Bplus, &Bminus, &Btime, &Btimer, &Balarm, &Bswatch, &Bstart, &Bstop,
			&hours, &minutes, &seconds, &tenths, &mode, &alarm_signal, &timer_exp);

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	/* Initializes LCD and touchscreen */
	IOE_Config();
	/* Initialize the LCD */
	STM32f4_Discovery_LCD_Init();

	//	LCD_Clear(White);

	/* Set the LCD Text size */
	//	LCD_SetFont(&Font8x12);
	//	Lcd_Touch_Calibration();
	InitTouch(-0.102, 0.0656, -335, 10);

	/* Draw the background */
	DrawInit(MyWatchScr);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(10, 80, 240, 56);
	WPrint(&MyWatchScr[SEP1STR], ":");
	WPrint(&MyWatchScr[SEP2STR], ":");


	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmTaskLCD, 10, 50);
	SetRelAlarm(AlarmTaskClock, 10, 100);

	/* Forever loop: background activities (if any) should go here */
	for (;;) { 
	}

}


