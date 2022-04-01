/***********************************************************
  Author: jieliang mo
  Date:   2 July, 2020
  github: https://github.com/mworkfun/TM1650.git
  IDE:	  Arduino-1.8.12
  Version: 1.0.0
  project: 4 digital tube
***************************************************************/

#include "TM1650.h"
#define CLK 3    //pins definitions for TM1650 and can be changed to other ports       
#define DIO 4
TM1650 DigitalTube(CLK,DIO);

void displayFloatNum(float num){
  if(num > 999.9)
    return;
  int dat = num*10;
   DigitalTube.displayDot(2,true); //Bit0 display dot. Use before displayBit().
  if(dat/1000 != 0){
    DigitalTube.displayBit(0, dat/1000);  
    DigitalTube.displayBit(1, dat%1000/100);
    DigitalTube.displayBit(2, dat%100/10);
    DigitalTube.displayBit(3, dat%10);
    return;
  }
  if(dat%1000/100 != 0){
    DigitalTube.clearBit(0); 
    DigitalTube.displayBit(1, dat%1000/100); 
    DigitalTube.displayBit(2, dat%100/10);
    DigitalTube.displayBit(3, dat%10);
    return;
  }
  DigitalTube.clearBit(0); 
  DigitalTube.clearBit(1);
  DigitalTube.displayBit(2, dat%100/10);
  DigitalTube.displayBit(3, dat%10);	
}

void setup(){
  //DigitalTube.setBrightness();  //set brightness, 0---7, default : 2
  //DigitalTube.displayOnOFF();   //display on or off, 0=display off, 1=display on, default : 1
  for(char b=1;b<5;b++){
    DigitalTube.clearBit(b);      //DigitalTube.clearBit(0 to 3); Clear bit display.
  }
  // DigitalTube.displayDot(1,true); //Bit0 display dot. Use before displayBit().
  DigitalTube.displayBit(1,0);    //DigitalTube.Display(bit,number); bit=0---3  number=0---9
}

void loop(){
  for(int num=0; num<10; num++){
    DigitalTube.displayBit(3,num);
    delay(1000);
  }
}
