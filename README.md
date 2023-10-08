# NMEAGP
Library for NMEA GPS modules, like NEO-6M.

How to start?
-------------
For instalation just download last release.


Compatible:
-------------
This library is compatible with all NMEA-0183 standart. At this time this library support NMEA-0183 (v2.0).
This library is compatible with ESP8266, STM32 and others Arduino-compatible platforms.

This library using UART serial connection between board and module.

You can make connection with using Software Serial (SWS) or Hardware Serial (HWS) (if compatible).


The main methods:
-------------
`connection()` the argument is pointer to SWS  or HWS

`updateData()` this function dont wait the new data, and just check RX-buffer, if RX-buffer contains a new NMEA-string, then data is updated.

`updateData_forse()` this function is wait the new data,when RX-buffer contains a new NMEA-string, then data is updated.
