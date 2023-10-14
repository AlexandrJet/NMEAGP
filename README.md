# NMEAGP
Library for NMEA GPS modules, like NEO-6M and NEO-7M.

How to start?
-------------
For instalation download last release and copy to project folder.


Compatible:
-------------
This library is compatible with NMEA-0183 standart. At this time this library support NMEA-0183 (v2.0).
For more information about NMEA-0183 standart read: [Link](https://docs.arduino.cc/learn/communication/gps-nmea-data-101#gps-nmea-0183-sentences-structure)

This library is compatible with ESP8266, STM32 and others Arduino-compatible platforms.

This library using UART serial connection between board and module.

You can make connection with using Software Serial (SWS) or Hardware Serial (HWS) (if compatible).


The main methods:
-------------
constuctor `NMEAGP()` the argument is pointer to HWS(if compatible) or SWS.

`connect()` the argument is timeout in milliseconds, standart is 1000ms.

`updateData()` this function dont wait the new data, and just check RX-buffer, if RX-buffer contains a new NMEA-string, then data is updated.

`updateData_force()` this function is wait the new data,when RX-buffer contains a new NMEA-string, then data is updated.

Public methods for obtaining data:
------------

`getTimeUTC()` returns the object of UTC time, with 3 fields: `.hours` , `.minuts` and `.seconds`.

`getDataStatus()` returns the current status of the data.

`getCoordinates()` returns the object of coordinates, with 2 subobjects: `.latitude` and `.longitude` with the same fields: `.value` and `.units` with . 

`getHeading()` returns the current cours of movement in degres.

`getStartDate()`

`getGroundSpeed_Kn()`

`getGroundSpeed_KMh()`

`getGroundSpeed_Ms()`

`getQualityIndicator()`

`getQualityIndicatorStr()`

`getsatellitesCount()`

`getUndulation()`

`getAgeCorectData()`

`getStaionID()`

`getModeFix()`

`getPrnNums()`

`getPositionDilutOfPres()`

`getHorizontalDilutOfPres()`

`getVerticalDilutOfPres()`
