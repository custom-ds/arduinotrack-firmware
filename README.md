# ArduinoTrack Firmware
The firmware for the ArduinoTrack and ArduinoTrack Flex APRS trackers is based on the Arduino development environment. for
instructions on how to install the firmware, refer to the [Project: Traveler ArduinoTrack Firmware](https://www.projecttraveler.org/arduinotrack-firmware) web page. 

[ArduinoTrack (original)](https://github.com/custom-ds/arduinotrack-hardware)

[ArduinoTrack Flex (2nd generation)](https://github.com/custom-ds/ArduinoTrack-Flex-Hardware)

The ArduinoTrack Configurator tools is used to adjust the settings on the ArduinoTrack board once the initial firmware is burned on the ATMega.  To download the compiled version of the Configurator tool installer, visit the Project: Traveler website.

[ArduinoTrack Configurator](https://www.projecttraveler.org/arduinotrack/arduinotrack-configurator)


## Version History Information prior to v3.0.0
* Version 2.1.10 - October 18, 2015 - Fixed bug in GPS object where strings were exceeding their buffers.  Fixing the buffer overflow fixed an issue with temp/pressure showing 0 with GPS lock.
* Version 2.1.9 - October 7, 2015 - Reduced the maximum transmit size from 250 to 200 bytes in TNC.h.  Fixed bug with long tx-delays on Simple time and on Speed-based beaconing.
* Version 2.1.8 - August 31, 2015 - Minor fix to correct IAT/Pressure from not transmitting.  Altering instructions to reflect Arduino 1.6.5 IDE change.
* Version 2.1.7 - August 13, 2015 - Added support for TMP102 outside air temp.  Also added piezo speaker to exercise routines.
* Version 2.1.5 - June 9, 2015 - Added exercising routine to test new boards.
* Version 2.1.4 - June 6, 2015 - Fixed a small logic error, and eliminated some serial debugging no longer needed.  Added a manual configuration option to reset configs to defaults.
* Version 2.1.3 - May 23, 2015 - Fix issue with Ublox fix quality showing up as 'na'.  Initializing greeting now displays firmware version.  Adjusted the firmware programming instructions.
* Version 2.1.0 - May 3, 2015 - Several changes to accomidate the version 1.10 of the PCB, including support for Ublox GPS's, switching from 1-wire to SPI for temp/baro pressure, and enabling more IO pins to be available for addons.
* Version 2.0.3 - March 29, 2015 - Simple change to instructions only to accomidate Arduino IDE 1.6.2.  Also changed high fuse to keep eeprom values from being reset during firmware flash.
* Version 2.0.2 - February 27, 2015 - Added a configuration annunciation, altered the GPS constructor.  Altered the HighBit to prevent the erasure of eeprom data after firmware updates. Uploaded firmware to GitHub.
Version 2.0.1 - February 14, 2015 - Updated tnc.cpp to include additional debugging and fixed an issue with PWM audio on PIN_AUDIO_OUT.  Numerous small changes to sync codebase between ArduinoTrack and Combined.
* Version 2.0.0 - January 15, 2015 - Integrated the common TNC library into the Combined Sketch.  Licensed ArduinoTrack_Combined under the GPL3 license.
* Version 1.2.1 - January 8, 2015 - All functionality back and operations for combined tracker.
* Version 1.2.0 - January 5, 2015 - Basic functionality now running on standalone (combined) tracker.
* Version 1.1.0 - November 8, 2014 - Modifications to run with ArduinoTrack Shield version 1.0.0.  Adjusted timing delays on annunciator to sound more natural.
* Version 1.0.2 - September 12, 2014 - Fixed issue with altitude based tracking transmitting continuously.  Fixed negative temperatures being transmitted incorrectly.
* Version 1.0.1 - July 1, 2014 -
* Version 1.0.0 - June 7, 2014 - Finalized the configuration for GPSL 2014.
* Version 0.9.5 - March 9, 2014 - Introduced the PC-based "Configurator" tool.  Saves all configs to EEPROM.
* Version .900 - July 16, 2011 - Ready for GPSL Traveler Flight 2011b
* Version .901 - August 27, 2011 - Added mycall and Path statements to the KPC3 Init TNC, split the SSID's out into separate Chars,
* Version .950 - May 31, 2012
 * Numerous fixes to get Arudino Track to compile in the v1.0 IDE
 * Switched to stock SoftwareSerial.h library instead of stand-alone
 * Changed time slots for PT-2012a (GPSL) flight.
* Version .951 - Oct 18, 2012
* Updated for 2012b flight.
* Removed the SSID's that were split in .901.  Decided that it was easier to have a single Char array when it comes to dumping the values out to the TNC's
