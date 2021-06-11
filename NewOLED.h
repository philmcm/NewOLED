//  
//  NewOLED.h - Header for Newhaven OLED Display.
//  Created for ENGG4201/8201 by Andrew Miller, Phil McMillan
//
// Based on sample code taken from https://www.newhavendisplay.com/resources_dataFiles/excode/txt/Arduino/slim_oled_code.txt
// Modifications made by Phil McMillan

#ifndef NEWOLED_H
#define NEWOLED_H

#define TX_PACKET_SIZE 20

#include "Arduino.h"

class NewOLED {
    public:
        NewOLED(char noledI2CA);
        void outputLine(int num, unsigned char *line);
        void oledSetup();
    private:
        unsigned char _noledI2CA;
        void _command(unsigned char c);
        void _data(unsigned char d);
        void _send_packet(unsigned char x);
        unsigned char _tx_packet[TX_PACKET_SIZE];
        unsigned char _line[17];

};
#endif