/* 
 * File:   main.c
 * Author: YOGESH J
 *
 * Created on 9 October, 2021, 11:44 AM
 */


#include "main.h"

#pragma config WDTE =OFF

unsigned char reset_mode, program_no = 0, water_level_index = 0;
char *washing_prog[]={" Daily ", "Heavy", "Delicates", "Whites", "Stainwash", "Eco cottons", "Woollens", "Beadsheets", "Rinse+Dry", "Dry only", "Wash only", "AquaStore"};

char *water_level_arr[]={"Auto","LOW","MEDIUM","HIGH","Max"};
static void init_config(void){

init_clcd();


init_digital_keypad();

}
void main(void){
    unsigned char key;
    unsigned char operation_mode= WASHING_PROGRAM_DISPLAY;
    init_config();
    
    clcd_print(" Press Key 5 TO ",LINE1(0));
    clcd_print("   POWER ON     ",LINE2(0));
    clcd_print(" WASHING MACHINE",LINE3(0));
    
    while( read_digital_keypad(STATE) != SW5)
    {
        ;
    }
    
    clear_screen();
    
   
    power_on_screen();
    
    reset_mode = WASHING_PROGRAM_DISPLAY_RESET;
    
    while(1){
        key = read_digital_keypad(STATE);
        
        if(key == LSW4 && operation_mode == WASHING_PROGRAM_DISPLAY)
        {
            operation_mode = WATER_LEVEL;
            reset_mode = WATER_LEVEL_RESET;
        }
        
        switch(operation_mode)
        {
            case WASHING_PROGRAM_DISPLAY:
                 washing_programs_display(key);
                 break;
            case WATER_LEVEL:
                water_level_display(key);
                break;
         }
        reset_mode = RESET_NOTHING;
    }
    
}

void clear_screen(void)
{
     clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(100);
}


void power_on_screen(void)
{
    for(unsigned char i = 0; i < 16; i++ )
    {
      clcd_putch(BLOCK,LINE1(i));
}
    clcd_print("  POWERING ON   ",LINE2(0));
    clcd_print(" Washing machine",LINE3(0));
    
    for( unsigned char i = 0; i < 16; i++ )
    {
      clcd_putch(BLOCK, LINE4(i));
}
    __delay_ms(3000);
           
}
   
void washing_programs_display(unsigned char key)
{
   if(reset_mode == WASHING_PROGRAM_DISPLAY_RESET)
   {
       clear_screen();
       program_no=0;
              
   }
   if(key == SW4)
   {
       program_no++;
       if(program_no== 12)
           program_no = 0;
       clear_screen();
   }
   clcd_print("Washing Programs",LINE1(0));
   clcd_putch('*',LINE2(0));
   if(program_no<=9)
   {
     
     clcd_print(washing_prog[program_no],LINE2(2));
     clcd_print(washing_prog[program_no + 1],LINE3(2));
     clcd_print(washing_prog[program_no + 2],LINE4(2));
   }
   else if(program_no==10)
  {
     clcd_print(washing_prog[program_no],LINE2(2));
     clcd_print(washing_prog[program_no + 1],LINE3(2));
      clcd_print(washing_prog[0],LINE4(2));
  }
   else if (program_no==11)
   {
   clcd_print(washing_prog[program_no],LINE2(2));
   clcd_print(washing_prog[0],LINE3(2));
   clcd_print(washing_prog[1],LINE4(2));
   }
}
void water_level_display(unsigned char key)
{
    if(reset_mode == WATER_LEVEL_RESET)
    {
        water_level_index = 0;
    }
    if(key == SW4)
    {
        water_level_index++;
        if(water_level_index == 5)
        {
            water_level_index=0;
        }
    }
    clcd_print("Water Level:",LINE1(0));
    clcd_putch('*',LINE2(0));
    if(water_level_index <=2)
    {
     clcd_print(water_level_arr[water_level_index], LINE2(2));
    clcd_print(water_level_arr[water_level_index +1], LINE3(2));
    clcd_print(water_level_arr[water_level_index + 2], LINE4(2));
}
    else if(water_level_index == 3)
    {
    clcd_print(water_level_arr[water_level_index], LINE2(2));
    clcd_print(water_level_arr[water_level_index +1], LINE3(2));
    clcd_print(water_level_arr[0], LINE4(2));
   
    }
    else if(water_level_index == 4)
    {
    clcd_print(water_level_arr[water_level_index], LINE2(2));
    clcd_print(water_level_arr[0], LINE3(2));
    clcd_print(water_level_arr[1], LINE4(2));
   
    }
}