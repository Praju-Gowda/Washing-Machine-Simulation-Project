/* 
 * File:   main.h
 * Author: YOGESH J
 *
 * Created on 9 October, 2021, 11:52 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include"clcd.h"
#include"digital_keypad.h"

#define WASHING_PROGRAM_DISPLAY       0x01
#define WATER_LEVEL                   0x02
#define WASHING_PROGRAM_DISPLAY_RESET 0x10
#define WATER_LEVEL_RESET             0X11
#define RESET_NOTHING                 0x00
void power_on_screen(void);
void clear_screen(void);
void washing_programs_display(unsigned char key);
void water_level_display(unsigned char key);

#endif	/* MAIN_H */

