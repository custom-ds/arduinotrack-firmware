/*
ArduinoTrack
Copywrite 2011-2018 - Zack Clobes (W0ZC), Custom Digital Services, LLC


This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

ArduinoTrack is a trademark of Custom Digital Services, LLC.


This file is intended to be modified by the end-user to accomidate any custom programming.

*/


#include <Arduino.h>
#include "TNC.h"
#include "GPS.h"


//include "TMP102.h"
//include "SparkFun_AS7265X.h"
#include "SparkFun_SHTC3.h"

/* Custom Global Variables */
#ifdef TMP102_h
TMP102 OAT;    //TMP102 sensor for outside air temp
#endif

#ifdef SF_SHTC3
SHTC3 HumiditySensor;
#endif

#ifdef _SPARKFUN_AS7265X_H
AS7265X LightSensor;
#endif




/* customInit()
 *  
 *  Called once during the boot/initialization process.  Generally used to initialize sensors and variables.
 *  
 */
void customInit() {
//  Enviro.initialize();
#ifdef TMP102_h
  Serial.println(F("Init'ing TMP102 sensor"));
  OAT.begin();
#endif


#ifdef SF_SHTC3
  Serial.println(F("Init'ing Humidity Sensor"));
  if(HumiditySensor.begin() == false)
  {
    Serial.println(F("  Humidity Sensor is missing..."));
  }
#endif


#ifdef _SPARKFUN_AS7265X_H
  Serial.println(F("Init'ing Light Sensor"));
  if(LightSensor.begin() == false)
  {
    Serial.println(F("  Light Sensor is missing..."));
  }
#endif



}


/* customLoop()
 *  
 *  Called continuously during the Arduino "Loop".  Practically speaking, this gets executed approximatley once a second, but can vary.  Returning true from
 *  this function will cause the transmitter to send a Single Line Position report.  Be careful returning true, as packets could be potentially sent continously
 *  which would drain the batter, and jam the APRS channel for other users.
 *  
 */
bool customLoop(GPS& GPSParser) {
  

  return false;   //Returning true will cause the transmitter to send a packet.  Be very careful how often this is transmitted.
}


/* customSendPositionSingleLine()
 *  
 *  Called towards the end of the packet send process, after any built-in telemetry data is sent (e.g. battery, temperature, etc) but before the comment string
 *  is transmitted.  Be aware that any custom output should be limited to roughly 50 characters max.
 *  
 */
void customSendPositionSingleLine(bool transmitCustom, TNC& oTNC, GPS& GPSParser) {

  if (!transmitCustom) return;    //we don't want to transmit anything custom here



#ifdef TMP102_h
  char statusOAT = 0;
  double outsideTemp;    //outside air temp
  statusOAT = OAT.getTemperature(outsideTemp);
  if (statusOAT != 0) {
    oTNC.xmitString((char *)" OAT=");
    oTNC.xmitFloat((float)outsideTemp);
  }  
#endif


#ifdef SF_SHTC3
  //Humidity and OAT from the SHTC3 Sensor
  SHTC3_Status_TypeDef result = HumiditySensor.update();
  delay(190);   //wait for the humidity reading

  if (HumiditySensor.lastStatus == SHTC3_Status_Nominal) {
    oTNC.xmitString((char *)" RH=");
    oTNC.xmitFloat(HumiditySensor.toPercent());

    oTNC.xmitString((char *)" OAT=");
    oTNC.xmitFloat(HumiditySensor.toDegC());
  }
#endif


#ifdef _SPARKFUN_AS7265X_H
  char szTemp[10];
  static uint8_t cycle=0;
  
  //Light Readings from the AS7265x sensors
  if (LightSensor.isConnected()) {

    LightSensor.takeMeasurements(); //This is a hard wait while all 18 channels are measured
    
    switch (cycle) {
      case 0:
        oTNC.xmitString((char *)" Lu=");
        sprintf(szTemp, "%04X", LightSensor.getA());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getB());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getC());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getD());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getE());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getF());
        oTNC.xmitString(szTemp);
        cycle = 1;
        break;
      case 1:
        oTNC.xmitString((char *)" Lv=");
        sprintf(szTemp, "%04X", LightSensor.getG());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getH());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getI());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getJ());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getK());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getL());
        oTNC.xmitString(szTemp);
        cycle = 2;
        break;
      case 2:
        oTNC.xmitString((char *)" Li=");
        sprintf(szTemp, "%04X", LightSensor.getR());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getS());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getT());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getU());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getV());
        oTNC.xmitString(szTemp);
        sprintf(szTemp, "%04X", LightSensor.getW());
        oTNC.xmitString(szTemp);
        cycle = 0;
        break;
      default:
        cycle = 0;
    }
  }
#endif
    
}


/* customExercise()
 *  
 *  Called during the exercise routines and is useful for testing hardware, and troubleshooting logic.  Any output should be Serial printed out to the 
 *  console.
 *  
 */
void customExercise() {
//  int iHumidity;
//
//  iHumidity = Enviro.readHumidity();   //0-99
//  Serial.print(F("Humidity: "));
//  Serial.println(percentHumidity);

  

#ifdef TMP102_h  
  double temp;
  char status;
  
  Serial.print(F("OAT: "));
  status = OAT.getTemperature(temp);
  if (status == 0) {
    Serial.println("n/a");
  } else {
    Serial.println(temp);
  }
#endif


#ifdef SF_SHTC3
  
#endif


#ifdef _SPARKFUN_AS7265X_H
  Serial.println("Light Sensor Testing");
  if (LightSensor.isConnected()) {
    LightSensor.takeMeasurements(); //This is a hard wait while all 18 channels are measured
  
    //Serial.println(LightSensor.getCalibratedA());
    Serial.println("getA");
    Serial.println(LightSensor.getA());
    Serial.println("getCalibratedB");
    
    //Serial.println(LightSensor.getCalibratedB());
    Serial.println(LightSensor.getB());
  } else {
    Serial.println(F("Light sensor not found."));
  }
#endif


}
