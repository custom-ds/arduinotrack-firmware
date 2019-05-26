/*
TNC Data Collector for Project: Traveler Flight Controllers
Copywrite 2011-2019 - Zack Clobes (W0ZC), Custom Digital Services, LLC

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef TNC_h
#define TNC_h

#include "Arduino.h"
#include <string.h>
#include <SoftwareSerial.h>

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


// 16MHz / 666 = 24.024kHz.  24kHz / 20 / 1201Hz baud
#define TIMER1_SEED 666


#define MAX_SZXMIT_SIZE 200

class TNC {
  public:
    TNC(void);
    void initInternal(int pinPTT);
    void initKISS(int pinTx, int pinRx);
    void xmitStart(char *szDest, char destSSID, char *szCall, char callSSID, char *szPath1, char path1SSID, char *szPath2, char path2SSID, bool usePath);
    void xmitEnd();
    void xmitString(char *sz);
    void xmitChar(char c);
    void xmitFloat(float f);
    void xmitLong(long lNumToSend, boolean bLeadingZero);
    boolean getNextBit(void);
    boolean noBitStuffing(void);
    int xmitLen(void);
    void xmitFlush(void);

    void setTransmitterType(char transmitterType);
    void setTxDelay(unsigned int txDelay);
    void setCourtesyTone(char courtesyTone);
    void keyTransmitter(bool transmit);
  private:
    void _calcCRC(byte iBit);
    boolean _getNextBit(void);
    void _configTimers(void);
    void _startTimer1ISR(void);
    void _stopTimer1ISR(void);
  
    // member variables
    bool _modulateInternally;
    char _szXmit[MAX_SZXMIT_SIZE];    //array to hold the data to be transmitted
    int _iSZLen;    //Tracks the current size of the szXmit buffer  
    int _pinTx;
    int _pinRx;
    int _pinPTT;

    char _transmitterType;
    unsigned int _txDelay;
    char _courtesyTone;


    byte _iSZPos = 0;    //Tracks the current byte being modulated out of the modem
    int _iTxDelayRemaining = 0;
    boolean _bNoStuffing = false;
    unsigned int _CRC;
    byte _iTxState = 0;

  
};


#endif
