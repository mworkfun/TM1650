//  Author:jieliang mo
//  Date:2 July, 2020
//  github: https://github.com/mworkfun/TM1650.git
//  Applicable Module:
//                     4 digital tube v1.0.0
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 1.0.0 of the License, or (at your option) any later version.
/*******************************************************************************/
#include "TM1650.h"
#include <Arduino.h>
int8_t NUM[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //number:0~9
int8_t DIG[] = {0x68,0x6a,0x6c,0x6e};
int8_t DOT[] = {0,0,0,0};

TM1650::TM1650(uint8_t Clk, uint8_t Data){
  Clkpin = Clk;
  Datapin = Data;
  setBrightness();
  setMode();
  displayOnOFF();
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
}

void TM1650::writeByte(int8_t wr_data){
  uint8_t i,count1;   
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(Clkpin,LOW);      
    if(wr_data & 0x80)
      digitalWrite(Datapin,HIGH);//LSB first
    else 
      digitalWrite(Datapin,LOW);
	  delayMicroseconds(3);
    wr_data <<= 1;      
    digitalWrite(Clkpin,HIGH);
	  delayMicroseconds(3);    
  }   
}
//send start signal to TM1650
void TM1650::start(void){
  digitalWrite(Clkpin,HIGH);//send start signal to TM1650
  digitalWrite(Datapin,HIGH);
  delayMicroseconds(2);
  digitalWrite(Datapin,LOW); 
  //delayMicroseconds(2);
  //digitalWrite(Clkpin,LOW); 
} 
//ack function
void TM1650::ack(void){
  int dy=0;
  digitalWrite(Clkpin,LOW); 
  delayMicroseconds(5);    
  pinMode(Datapin,INPUT);
  while(digitalRead(Datapin)){ //wait for the ACK
    delayMicroseconds(1);
    dy += 1;
    if(dy > 5000)  //Prevent infinite loop
      break;
  }
  digitalWrite(Clkpin,HIGH); 
  delayMicroseconds(2);    
  digitalWrite(Clkpin,LOW); 
  pinMode(Datapin,OUTPUT);   
}
//End of transmission
void TM1650::stop(void){
  digitalWrite(Clkpin,HIGH);
  digitalWrite(Datapin,LOW);
  delayMicroseconds(2);
  digitalWrite(Datapin,HIGH); 
}
//display number
void TM1650::displayBit(uint8_t Bit, uint8_t Num){
  if(Num > 9 || Bit > 4)return;  
  start();               //start signal sent to TM1650 from MCU
  writeByte(ADDR_DIS);   //send mode command
  ack();
  writeByte(DisplayCommand); //set display mode
  ack();
  stop();         
  start();          
  writeByte(DIG[Bit]);  //send the address
  ack();
  if(DOT[Bit] == 1){      //display dot
    writeByte(NUM[Num] | 0x80);     
  }
  else{                   
    writeByte(NUM[Num]);    //display data
  } 
  ack();
  stop();                     
}
//clear display
void TM1650::clearBit(uint8_t Bit){
  if(Bit > 4)return;  
  start();               //start signal sent to TM1650 from MCU
  writeByte(ADDR_DIS);   //send mode command
  ack();
  writeByte(DisplayCommand); //set display mode
  ack();
  stop();         
  start();          
  writeByte(DIG[Bit]);  //send the address
  ack();
  writeByte(0x00);        //display data
  ack();
  stop();
}
//set display brightness
void TM1650::setBrightness(uint8_t brightness){
  DisplayCommand = (DisplayCommand & 0x0f)+(brightness<<4);
}

//7 or 8 segment digital tube
void TM1650::setMode(uint8_t segment){
  DisplayCommand = (DisplayCommand & 0xf7)+(segment<<3);
}

//display on or off
void TM1650::displayOnOFF(uint8_t OnOff){
  DisplayCommand = (DisplayCommand & 0xfe)+OnOff;
}
//display dot
void TM1650::displayDot(uint8_t Bit, boolean OnOff){
  if(Bit > 4)return;  
  if(OnOff){
    DOT[Bit] = 1;
  }
  else{
    DOT[Bit] = 0;
  }
}
