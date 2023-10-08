# NMEAGP
Library for NMEA GPS modules, like NEO-6M.

How to start?
-------------
For instalation just download last release.


Compatible:
-------------
This library is compatible with NMEA-0183 standart. At this time this library support NMEA-0183 (v2.0).
For more information about NMEA-0183 standart read: [Link](https://docs.arduino.cc/learn/communication/gps-nmea-data-101#gps-nmea-0183-sentences-structure)

This library is compatible with ESP8266, STM32 and others Arduino-compatible platforms.

This library using UART serial connection between board and module.

You can make connection with using Software Serial (SWS) or Hardware Serial (HWS) (if compatible).


The main methods:
-------------
constuctor `NMEA()` the argument is pointer to HWS(if compatible) or SWS

`connection()` the argument is timeout in milliseconds, standart is 1000ms

`updateData()` this function dont wait the new data, and just check RX-buffer, if RX-buffer contains a new NMEA-string, then data is updated.

`updateData_force()` this function is wait the new data,when RX-buffer contains a new NMEA-string, then data is updated.

Methods for getting data:
------------

`getTimeUTC()`

`getDataStatus()`

`getCoordinates()`

`getHeading()`

`getStartDate()`

`getGroundSpeed_Kn()`

`getGroundSpeed_KMh()`

`getGroundSpeed_Ms()`

`getQualityIndicator()`

`getQualityIndicatorStr()`

