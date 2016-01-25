/*
 * WidgetConfig.c
 *
 *  Created on: 21/ott/2015
 *      Author: admim
 */

#include "Widget.h"
#include "WidgetConfig.h"
#include "pictures.h"
#include <stdio.h>
#include "stm32f4_discovery_lcd.h"
#include "fonts.h"

ButtonIcon buttontime = {
		icontime_on, icontime_off, TIMEMODE
};

ButtonIcon buttontimer = {
		icontimer_on, icontimer_off, TIMERMODE
};

ButtonIcon buttonalarm = {
		iconalarm_on, iconalarm_off, ALARMMODE
};

ButtonIcon buttonswatch = {
		iconswatch_on, iconswatch_off, SWATCHMODE
};

ButtonIcon buttonplus = {
		0, 0, PLUS
};

ButtonIcon buttonminus = {
		0, 0, MINUS
};

ButtonIcon buttonstart = {
		iconstart, iconstart, START
};

ButtonIcon buttonstop = {
		iconstop, iconstop, STOP
};

Text txt = {
		&Font32x48, White
};

Text txt_t = {
		&Font12x12, Black
};

Image backg = {
	ImageBuffer
};


Image wake_up = {
	wakeup
};

Image cleaner_t = {
	cleaner
};

Image cleaner_txt_t = {
	cleaner_txt
};

const Widget MyWatchScr[NUMWIDGETS] = {
		{0, 0, 320, 240, BACKGROUND, (void *)&backg},
		{0, 0, 80, 45, BUTTONICON, (void *)&buttontime},
		{80, 0, 80, 45, BUTTONICON, (void *)&buttontimer},
		{160, 0, 80, 45, BUTTONICON, (void *)&buttonalarm},
		{240, 0, 80, 45, BUTTONICON, (void *)&buttonswatch},
		{240, 62, 55, 55, BUTTONICON, (void *)&buttonplus},
		{240, 133, 55, 55, BUTTONICON, (void *)&buttonminus},
//		{26, 76, 100, 32, RECTANGLE, (void *)&rectangle}
		{10, 90, 40, 40, TEXT, (void *)&txt}, // hours
		{80, 90, 40, 40, TEXT, (void *)&txt}, // minutes
		{150, 90, 40, 40, TEXT, (void *)&txt}, // seconds
		{215, 90, 40, 40, TEXT, (void *)&txt}, // tenths
		{60, 90, 40, 40, TEXT, (void *)&txt}, // :
		{130, 90, 40, 40, TEXT, (void *)&txt},// :
		{200, 90, 40, 40, TEXT, (void *)&txt},// .
		{50, 55, 40, 40, TEXT, (void *)&txt_t},
		{40, 165, 80, 30, BUTTONICON, (void *)&buttonstart},
		{150, 165, 80, 30, BUTTONICON, (void *)&buttonstop},
		{250, 165, 48, 48, IMAGE, (void *)&wake_up},
		{250, 165, 48, 48, IMAGE, (void *)&cleaner_t},
		{50, 55, 150, 25, IMAGE, (void *)&cleaner_txt_t},
};

