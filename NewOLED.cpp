// Based on sample code taken from https://www.newhavendisplay.com/resources_dataFiles/excode/txt/Arduino/slim_oled_code.txt
// Modifications made by Phil McMillan

#include "Arduino.h"
#include "NewOLED.h"
#include <Wire.h>
#include <math.h>


NewOLED::NewOLED(char noledI2CA) {
  _noledI2CA = noledI2CA;
  for (int i=0; i < TX_PACKET_SIZE; i++)
    _tx_packet[i] = (unsigned char) 0;
  for (int i=0; i < 16; i++)
    _line[i] = (unsigned char) 'A';  
}

void NewOLED::_command(unsigned char c)
{
  unsigned char i, temp;
  _tx_packet[0] = 0x00;
  _tx_packet[1] = c;
  _send_packet(2);
}

void NewOLED::_data(unsigned char d)
{
  unsigned char i, temp;
  _tx_packet[0] = 0x40;
  _tx_packet[1] = d;
  _send_packet(2);
}

void NewOLED::_send_packet(unsigned char x)
{
  unsigned char ix;
  
  Wire.beginTransmission(_noledI2CA);
  for(ix=0; ix<x; ix++) {
    Wire.write(_tx_packet[ix]);
  }
  Wire.endTransmission();
}

void NewOLED::outputLine(int num, unsigned char *line)
{
  int i = 0;
  unsigned char *ptr = line;

  while (*ptr != 0)     // copy the received string
    _line[i++] = *ptr++;

  for (i; i < 16; i++)  // fill remaining chars with ' '
    _line[i] = ' ';

  if (num == 1) {
    _command(0x80);
    for(i=0;i<16;i++) {
      _data(_line[i]);
    }
  }
  else {
    _command(0xC0);
    for(i=0;i<16;i++){
      _data(_line[i]);
    }
  }
}

void NewOLED::oledSetup() 
{
  delay(10);
  Wire.begin();
  delay(10);
  _command(0x2A);  //function set (extended command set)
  _command(0x71);  //function selection A, disable internal Vdd regualtor
  _data(0x00);
  _command(0x28);  //function set (fundamental command set)
  _command(0x08);  //display off, cursor off, blink off
  _command(0x2A);  //function set (extended command set)
  _command(0x79);  //OLED command set enabled
  _command(0xD5);  //set display clock divide ratio/oscillator frequency
  _command(0x70);  //set display clock divide ratio/oscillator frequency
  _command(0x78);  //OLED command set disabled
  _command(0x08);  //extended function set (2-lines)
  _command(0x06);  //COM SEG direction
  _command(0x72);  //function selection B, disable internal Vdd regualtor
  _data(0x00);     //ROM CGRAM selection
  _command(0x2A);  //function set (extended command set)
  _command(0x79);  //OLED command set enabled
  _command(0xDA);  //set SEG pins hardware configuration
  _command(0x10);  //set SEG pins hardware configuration
  _command(0xDC);  //function selection C
  _command(0x00);  //function selection C
  _command(0x81);  //set contrast control
  _command(0x7F);  //set contrast control
  _command(0xD9);  //set phase length
  _command(0xF1);  //set phase length
  _command(0xDB);  //set VCOMH deselect level
  _command(0x40);  //set VCOMH deselect level
  _command(0x78);  //OLED command set disabled
  _command(0x28);  //function set (fundamental command set)
  _command(0x01);  //clear display
  _command(0x80);  //set DDRAM address to 0x00
  _command(0x0C);  //display ON
  delay(100);
}
