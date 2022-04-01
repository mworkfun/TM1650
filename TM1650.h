//  Author:jieliang mo
//  Date:2 July, 2020
//  github: https://github.com/mworkfun/TM1650.git
//  Applicable Module:
//                   4 digital tube v1.0.0
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 1.0.0 of the License, or (at your option) any later version.
/*******************************************************************************/

#ifndef TM1650_H
#define TM1650_H
#include <inttypes.h>
#include <Arduino.h>

/***************definitions for TM1650*********************/
#define ADDR_DIS  0x48  //mode command
#define ADDR_KEY  0x49  //read key value command

/**************definitions for brightness******************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7

class TM1650
{
  public:
	TM1650(uint8_t Clk, uint8_t Data);
  void start(void);               //send start bits
  void stop(void);                //send stop bits
  void ack(void);                 //ACK function
	void writeByte(int8_t wr_data); //write 8bit data to tm1651
	void displayBit(uint8_t Bit, uint8_t Num);
	void clearBit(uint8_t Bit);
	void setBrightness(uint8_t brightness=BRIGHT_TYPICAL); //set brightness, 0---7
  void setMode(uint8_t segment=0);    //7 or 8 segment digital tube. 0=8segement. 1=7segement,all dot display
  void displayOnOFF(uint8_t OnOff=1); //display on or off, 0=display off, 1=display on
  void displayDot(uint8_t Bit, boolean OnOff);
  
  private:
	uint8_t Clkpin;
	uint8_t Datapin;
  uint8_t DisplayCommand;
};
#endif
