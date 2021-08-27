/*
 * File:   main.c
 * Author: ragab
 *
 * Created on February 26, 2019, 6:37 PM
 */

// PIC16F819 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB3/PGM pin has PGM function, Low-Voltage Programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB2      // CCP1 Pin Selection bit (CCP1 function on RB2)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.




#include <xc.h>
//#include "pic16f819.h"
#define _XTAL_FREQ 8000000UL
//#include <16F819.h>// header file
//#use delay (clock=8000000)
//#fuses INTRC_IO,NOWDT,NOPROTECT,MCLR,NOBROWNOUT
//#byte STATUS=0X03

int  counta, countb;
unsigned char  pc_track, pc_end_graphics;
int   vram_1,vram_2,vram_3,vram_4,vram_5,vram_6,vram_7,vram_8;
int   vtemp_1,vtemp_2,vtemp_3,vtemp_4,vtemp_5,vtemp_6,vtemp_7,vtemp_8;
int repeat_frame,car_data,button_timer,button_adjust,stop_repeat,level,speed,end_hold,i=0;
int press = 0;
 unsigned char track_data();
 unsigned char end_data();
 void display();
 void check_collision();
 void collided();
 void collided_data();
 void car();
 void joystick();
 void delay();
 void go_left();
 void go_right();
 void button_time();
 void fill_vram();
 void setup();
void setup()
{
     TRISA= (0b11110111);
     PORTA=( 0b00001000);
     PORTB=(0X00);
     
     vram_1= 0X00;
     vram_2= 0X00;
     vram_3= 0X00;
     vram_4= 0X00;
     vram_5= 0X00;
     vram_6= 0X00;
     vram_7= 0X00;
     vram_8= 0X00;


     stop_repeat = 0;
     pc_track    = 0;
     pc_end_graphics = 0;
     car_data        = 0b00010000;
     button_adjust   = 8;
     level           = 1;
     speed           = 10;
     end_hold        = 50;
}


void collided_data()
{

for( i =0; i<7;i++)
{

end_data();
delay();
//PORTA = PORTA+1;

}

end_data();
delay();
collided();
return;

}

void collided()
{
loop:PORTB=(0X00) ;
     PORTB=(0b00001000);

     if((level & 0X01 )== 0X01)
        {
         pc_end_graphics = 0;

        }
     if((level & 0X02 )== 0X02)
       {
       pc_end_graphics = 8;

       }
    if((level & 0X04 )== 0X04)
       {
         pc_end_graphics = 16;

       }
    if((level & 0X08 )== 0X08)
      {
        pc_end_graphics = 24;

      }
    if((level & 0X10 )== 0X10)
      {
       pc_end_graphics = 32;

      }
      if((level & 0X20 )== 0X20)
      {
       pc_end_graphics = 40;

      }
    if((level & 0X40 )== 0X40)
      {
      pc_end_graphics = 48;

      }
     if((level & 0X80 )== 0X80)
     {
      pc_end_graphics = 56;

     }


    end_hold--;
    if(end_hold!=0)
    {
      for( i =0; i<7;i++)
    {
      end_data();
     // PORTA = PORTA+1;

    }
    end_data();
    goto loop;
    }        //
    end_hold = 1;

if(PORTAbits.RA7==0X00)
{
 setup();
}

if(PORTAbits.RA6==0X00)
{
setup()  ;
}


}

void main()
{

   TRISB=(0b00000000);
   TRISA=(0b11110000);
  

   PORTB=(0b11110000);
   PORTA=(0X00);
                      // initialize UART1 module
 // Delay_ms(100);

  setup();
   while(1)
  {
  start:   PORTAbits.RA3=1;;
           //PORTA = 0b00001000;
           pc_end_graphics = 16;
           collided_data();
           pc_end_graphics = 8 ;
           collided_data();
           pc_end_graphics = 0;
           collided_data();
  display();
  fill_vram();
  while((PORTAbits.RA7==1) && (PORTAbits.RA6 == 1))//while(PORTA & 0b10000000 == 0X80) && (PORTA & 0b10000000 == 0X80)
  {
  press = 1;
  }
  if(press == 1)
  {
    press = 0;
    goto start;
  }

}
}

void delay()
{

  counta = 3;
  countb = 3;
  while(counta != 0)
  {
   counta--;
  }
  while(countb != 0)
  {
   countb--;
  }
 
}

unsigned char end_data()
{

 pc_end_graphics++;          //   correct here

 switch(pc_end_graphics)
 {

case 1:         PORTB=(0b00011000); break;
case 2:         PORTB=(0b00111000); break;
case 3:         PORTB=(0b01111000); break;
case 4:         PORTB=(0b00011000); break;
case 5:         PORTB=(0b00011000); break;
case 6:         PORTB=(0b00011000); break;
case 7:         PORTB=(0b01111110); break;
case 8:         PORTB=(0b01111110); break;
 //draws 2;

case 9:         PORTB=(0b00111000); break; //this draws the number 1
case 10:        PORTB=(0b01111100); break;
case 11:        PORTB=(0b11000110); break;
case 12:        PORTB=(0b00001100); break;
case 13:        PORTB=(0b00011000); break;
case 14:        PORTB=(0b00110000); break;
case 15:        PORTB=(0b01111110); break;
case 16:        PORTB=(0b11111110); break;

//; three
case 17:        PORTB=(0b00111100); break;//        this draws the number 3
case 18:        PORTB=(0b01111110); break;
case 19:        PORTB=(0b00000110); break;
case 20:        PORTB=(0b00111110); break;
case 21:        PORTB=(0b00111110); break;
case 22:        PORTB=(0b00000110); break;
case 23:        PORTB=(0b01111110); break;
case 24:        PORTB=(0b00111100); break;
//; four
case 25:        PORTB=(0b01100110);break;//        this draws the number 4
case 26:        PORTB=(0b01100110);break;
case 27:        PORTB=(0b01100110);break;
case 28:        PORTB=(0b01100110);break;
case 29:        PORTB=(0b01111110);break;
case 30:        PORTB=(0b00111110);break;
case 31:        PORTB=(0b00000110);break;
case 32:        PORTB=(0b00000110);break;
//; five
case 33:        PORTB=(0b01111110);break;//;        this draws the number 5
case 34:        PORTB=(0b01111110);break;
case 35:        PORTB=(0b01100000);break;
case 36:        PORTB=(0b01111100);break;
case 37:        PORTB=(0b01111110);break;
case 38:        PORTB=(0b00000110);break;
case 39:        PORTB=(0b01111110);break;
case 40:        PORTB=(0b01111100);break;
//; six
case 41:        PORTB=(0b00111110);break;//;        this draws the number 6
case 42:        PORTB=(0b01111110);break;
case 43:        PORTB=(0b01100000);break;
case 44:        PORTB=(0b01111100);break;
case 45:        PORTB=(0b01111110);break;
case 46:        PORTB=(0b01100110);break;
case 47:        PORTB=(0b01111110);break;
case 48:        PORTB=(0b00111100);break;
//; seven
case 49:        PORTB=(0b01111111);break;//;        this draws the number 7
case 50:        PORTB=(0b01111111);break;
case 51:        PORTB=(0b00000011);break;
case 52:        PORTB=(0b00000110);break;
case 53:        PORTB=(0b00001100);break;
case 54:        PORTB=(0b00011000);break;
case 55:        PORTB=(0b00110000);break;
case 56:        PORTB=(0b01100000);break;
//; end
case 57:        PORTB=(0b00111100);break; //; this draws a smiley face to say we have finished!
case 58:        PORTB=(0b01000010);break;
case 59:        PORTB=(0b10100101);break;
case 60:        PORTB=(0b10000001);break;
case 61:        PORTB=(0b10100101);break;
case 62:        PORTB=(0b10011001);break;
case 63:        PORTB=(0b01000010);break;
case 64:        PORTB=(0b00111100);break;
default : break;
}
}

void display()
{

repeat_frame = speed;
car();

while(repeat_frame !=0)
{
PORTA=(0b00001000);
PORTB=(vram_1);//PORTB = vram_1;
delay();
PORTB=(0X00);//PORTB = 0X00;

PORTA=(0b00001001);//PORTA = 0b00001001;
PORTB=(vram_2);
delay();
PORTB=(0X00);

PORTA=(0b00001010);
PORTB=(vram_3);
delay();
PORTB=(0X00);


PORTA=(0b00001011);
PORTB=(vram_4);
delay();
PORTB=(0X00);

PORTA=(0b00001100);
PORTB=(vram_5);
delay();
PORTB=(0X00);

PORTA=(0b00001101);
PORTB=(vram_6);
delay();
PORTB=(0X00);

PORTA=(0b00001110);
PORTB=(vram_7);
delay();
PORTB=(0X00);

PORTA=(0b00001111);
PORTB=(vram_8);
delay();
PORTB=(0X00);
 if((stop_repeat & 0b00000010 ) == 1)
  {
  button_time();
 check_collision();


  }
 repeat_frame--;
 }
 return;
}

void check_collision()
{
vram_8 = vram_8 & car_data;
if((STATUS & 0b00000100) == 0b00000000)
{
collided();
}
//return;

}


void car()
{
joystick();
PORTA=(0b11111011);
PORTB=(car_data);
delay();
//PORTA.3 = 1;
PORTAbits.RA3=1;
return;

}

void go_left()
{
if ((stop_repeat & 0X01)==0X01)
{
return;
}
car_data = car_data>>1;
stop_repeat = 0X03;
button_timer= button_adjust;
return;
}

void go_right()
{
if ((stop_repeat & 0X01)==0X01)
{
return;
}
car_data = car_data<<1;
stop_repeat|= 0X03;
button_timer= button_adjust;
return;
}
void joystick()
{
if(PORTAbits.RA7==0)
{
go_left();
}

if(PORTAbits.RA6==0)
{
go_right();
}
return;
}

void button_time()
{
button_timer--;
if(button_timer!=0)
{
return;
}
stop_repeat|=0X03;
//stop_repeat|=0X02;
return;

}

unsigned char track_data()      // EDIT LATER
{

   
  pc_track = pc_track + 1 ;
  switch(pc_track)
  {

   case 1:  vram_1=(0b10000001);  break;
   case 2:  vram_1=(0b10000001);  break;
   case 3:  vram_1=(0b11000001);  break;
   case 4:  vram_1=(0b11100001);  break;
   case 5:  vram_1=(0b11100001);  break;
   case 6:  vram_1=(0b11110001);  break;
   case 7:  vram_1=(0b11110001);  break;
   case 8:  vram_1=(0b11111001);  break;
   case 9:  vram_1=(0b11110001);  break;
   case 10:  vram_1=(0b11100001); break;
   case 11:  vram_1=(0b11000011); break;
   case 12:  vram_1=(0b10000111); break;
   case 13:  vram_1=(0b10001111); break;
   case 14:  vram_1=(0b10000111); break;
   case 15:  vram_1=(0b10000011); break;
   case 16:  vram_1=(0b10110001); break;
   case 17:  vram_1=(0b10111001); break;
   case 18:  vram_1=(0b10111001); break;
   case 19:  vram_1=(0b10111001); break;
   case 20:  vram_1=(0b10010001); break;
   case 21:  vram_1=(0b10000001); break;
   case 22:  vram_1=(0b10000001); break;
   case 23:  vram_1=(0b11000011); break;
   case 24:  vram_1=(0b11100111); break;
   case 25:  vram_1=(0b11000011); break;
   case 26:  vram_1=(0b10000001); break;
   case 27:  vram_1=(0b10011001); break;
   case 28:  vram_1=(0b10011001); break;
   case 29:  vram_1=(0b10111101); break;
   case 31:  vram_1=(0b10011001); break;
   case 32:  vram_1=(0b10011001); break;
   case 33:  vram_1=(0b10000001); break;
   case 34:  vram_1=(0b11000011); break;
   case 35:  vram_1=(0b11100111); break;
   case 36:  vram_1=(0b11000011); break;
   case 37:  vram_1=(0b10000001); break;
   case 38:  vram_1=(0b10000001); break;
   case 39:  vram_1=(0b10010001); break;
   case 40:  vram_1=(0b10110001); break;
   case 41:  vram_1=(0b10111001); break;
   case 42:  vram_1=(0b10111001); break;
   case 43:  vram_1=(0b10011001); break;
   case 44:  vram_1=(0b10000001); break;
   case 45:  vram_1=(0b10000011); break;
   case 46:  vram_1=(0b10000111); break;
   case 47:  vram_1=(0b10001111); break;
   case 48:  vram_1=(0b10000111); break;
   case 49:  vram_1=(0b11000001); break;
   case 50:  vram_1=(0b11100001); break;
   case 51:  vram_1=(0b11110001); break;
   case 52:  vram_1=(0b11111001); break;
   case 55:  vram_1=(0b11111101); break;
   case 56:  vram_1=(0b11111001); break;
   case 57:  vram_1=(0b11110001); break;
   case 58:  vram_1=(0b10000001); break;
   case 59:  vram_1=(0b10000001); break;
   case 60:  vram_1=(0b10110001); break;
   case 61:  vram_1=(0b10110001); break;
   case 62:  vram_1=(0b10110001); break;
default : break;
  }
  level = level<< 1;
  PORTA=(0b00001000);
  delay();
  PORTA=(0b00000000);
  if((level & 0b01000000) == 0b01000000)
   {
      collided();
   }
   else
   {
    speed --;
   }

   pc_track = 0X01;
   return (0b10000001);
}

void fill_vram()
{

  vtemp_1 = vram_1 ;
  vtemp_2 = vram_2 ;
  vtemp_3 = vram_3 ;
  vtemp_4 = vram_4 ;
  vtemp_5 = vram_5 ;
  vtemp_6 = vram_6 ;
  vtemp_7 = vram_7 ;


   track_data();

  vram_2     = vtemp_1;
  vram_3     = vtemp_2;
  vram_4     = vtemp_3;
  vram_5     = vtemp_4;
  vram_6     = vtemp_5;
  vram_7     = vtemp_6;
  vram_8     = vtemp_7;

 // return;




}