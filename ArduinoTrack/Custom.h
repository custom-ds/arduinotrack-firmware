#ifndef Custom_h
#define Custom_h





void customInit();
bool customLoop(GPS& GPSParser);
void customSendPositionSingleLine(bool transmitCustom, TNC& oTNC, GPS& GPSParser);
void customExercise();

#endif
