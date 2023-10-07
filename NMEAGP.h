
 /*
 NMEAGP - Hardware serial library for Wiring
  Copyright (c) 2023 Aleksandr Aleksandrov.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library;
  */


#pragma once
//This segment and the same is activated when the selected board is a ESP8266 or STM32, 
//WARNING: NOT RECOMENDED TO CHANGE DEFINED MACROS IF YOU DON`T SURE THAT YOUR BOARD can 
//SUPPORT THE HARDWARESERIAL LIBRARY
#if defined ESP8266 || defined ARDUINO_ARCH_STM32

#include <HardwareSerial.h>

#endif

#include <inttypes.h>
#include <SoftwareSerial.h>



float numToFloat(int num, uint8_t fractLenght) {
	return float(num) / pow(10, fractLenght);
}


uint8_t fractLenght;
char tmpChr;
uint32_t tmpNum = 0;

//Struct data
struct quantity {
	quantity(float val, char uni);
	float value;
	char unit;
};


quantity::quantity(float val, char uni) {
	value = val;
	unit = uni;
}


struct TimeUTC {
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
};


struct coordinate {
	quantity latitude = quantity(0, 0);
	quantity longitude = quantity(0, 0);
};
//Struct data_


//GPRMC
struct GPRMC {

	void load(uint8_t *contWrd) {
		switch (*contWrd) {
		case 1:
			timeUTC.hours = tmpNum / 1000000;
			timeUTC.minutes = (tmpNum % 1000000) / 10000;
			timeUTC.seconds = (tmpNum % 10000) / 100;
			break;

		case 2:
			status = tmpChr;
			break;

		case 3:
			coord.latitude.value = numToFloat(tmpNum, fractLenght);
			break;

		case 4:
			coord.latitude.unit = tmpChr;
			break;

		case 5:
			coord.longitude.value = numToFloat(tmpNum, fractLenght);
			break;

		case 6:
			coord.longitude.unit = tmpChr;
			break;

			/*case 7:
				speed = numToFloat(tmpNum, fractLenght);
				break;*/

		case 8:
			heading = numToFloat(tmpNum, fractLenght);
			break;

		case 9:
			startDate = tmpNum;
			break;

		default:
			break;
		}
	}
	TimeUTC timeUTC;

	char status;

	coordinate coord;

	//float speed;
	float heading;
	 
	uint32_t startDate;

};
//GPRMC_


//GPVTG
struct GPVTG {
	void load(uint8_t *contWrd) {
		switch (*contWrd) {

		case 1:
			trueHeading.value = numToFloat(tmpNum, fractLenght);
			break;

		case 2:
			trueHeading.unit = tmpChr;
			break;

		case 3:
			magneticHeading.value = numToFloat(tmpNum, fractLenght);
			break;

		case 4:
			magneticHeading.unit = tmpChr;
			break;

		case 5:
			groundSpeedKn.value = numToFloat(tmpNum, fractLenght);
			break;

		case 6:
			groundSpeedKn.unit = tmpChr;
			break;

		case 7:
			groundSpeedKMh.value = numToFloat(tmpNum, fractLenght);
			break;

		case 8:
			groundSpeedKMh.unit = tmpChr;
			break;

		default:
			break;
		}
	}

	quantity trueHeading = quantity(0, 0);
	quantity magneticHeading = quantity(0, 0);
	quantity groundSpeedKn = quantity(0, 0);
	quantity groundSpeedKMh = quantity(0, 0);

};
//GPVTG_


//GPGGA
struct GPGGA {
	void load(uint8_t *contWrd) {
		switch (*contWrd) {
		case 7:
			qualityIndicator = tmpNum;
			break;

		case 8:
			satsCount = tmpNum;
			break;

		case 9:
			horizonDilutOfPrecis = numToFloat(tmpNum, fractLenght);
			break;

		case 10:
			altitude.value = numToFloat(tmpNum, fractLenght);
			break;

		case 11:
			altitude.unit = tmpChr;
			break;

		case 12:
			undulation.value = numToFloat(tmpNum, fractLenght);
			break;

		case 13:
			undulation.unit = tmpChr;
			break;

		case 14:
			ageCorectData = tmpNum;
			break;

		case 15:
			staionID = tmpNum;
			break;

		default:
			break;
		}
	};
	//TimeUTC timeUTC;

	//char status;

	//Coordinate coordinate;

	uint8_t qualityIndicator;
	uint8_t satsCount;

	float horizonDilutOfPrecis;
	quantity altitude = quantity(0, 0);
	quantity undulation = quantity(0, 0);
	uint8_t ageCorectData;
	uint16_t staionID;

};
//GPGGA_


//GPGSA
struct GPGSA {
	void load(uint8_t *contWrd) {
			switch (*contWrd) {
		case 1:
			modeFix.unit = tmpChr;
			break;

		case 2:
			modeFix.value = numToFloat(tmpNum, fractLenght);
			break;

		case 15:
			posDilutOfPres = numToFloat(tmpNum, fractLenght);
			break;

		case 16:
			horDilutOfPres = numToFloat(tmpNum, fractLenght);
			break;

		case 17:
			verDilutOfPres = numToFloat(tmpNum, fractLenght);
			break;

		default:
			if (*contWrd <= 13 && *contWrd >= 2)prnNums[*contWrd - 2] = numToFloat(tmpNum, fractLenght);
			break;
		}
	};

	quantity modeFix = quantity(0, 0);
	uint8_t prnNums[12];
	float posDilutOfPres;
	float horDilutOfPres;
	float verDilutOfPres;
};
//GPGSA_ 


GPRMC rmc;
GPVTG vtg;
GPGGA gga;
GPGSA gsa;


class GPNMEA
{
	SoftwareSerial *SWS;
	
	//READ WARNING!!!
#if defined ESP8266 || defined ARDUINO_ARCH_STM32
	HardwareSerial *HWS;
#endif


	//publuc segment
public:
	GPNMEA(SoftwareSerial *SoftwareS);

#if defined ESP8266 || defined ARDUINO_ARCH_STM32
	GPNMEA(HardwareSerial *HardwareS);
#endif


	//Grouping the output methods according to their standart strings 
	//GPRMC
	TimeUTC getTimeUTC() {
		return rmc.timeUTC;
	}

	bool getDataStatus() {
		if (rmc.status = 'A')return true;
		else return false;
	}

	coordinate getCoordinates() {
		return rmc.coord;
	}

	/*float getSpeed() {
		return rmc.speed;
	}*/

	float getHeading() {
		return rmc.heading;
	}

	uint32_t getStartDate() {
		return rmc.startDate;
	}
	//GPRMC_

	//GPVTG
	quantity getGroundSpeed_Kn() {
		return vtg.groundSpeedKn;
	}

	quantity getGroundSpeed_KMh() {
		return vtg.groundSpeedKMh;
	}


	quantity getGroundSpeed_Ms() {
		return quantity(vtg.groundSpeedKMh.value / 3.6, 'M');
	}
	//GPVTG_

	//GPGGA
	uint8_t getQualityIndicator() {
		return gga.qualityIndicator;
	}

	String getQualityIndicatorStr() {
		switch (gga.qualityIndicator)
		{
		case 0:
			return "Fix not valid";
			break;

		case 1:
			return "GPS fix";
			break;

		case 2:
			return "Differential GPS fix (DGNSS)";
			break;

		case 3:
			return "Not applicable";
			break;

		case 4:
			return "RTK Fixed";
			break;

		case 5:
			return "RTK Float";
			break;

		case 6:
			return "INS Dead reckoning";
			break;

		default:
			break;
		}
	}

	uint8_t getsatellitesCount() {
		return gga.satsCount;
	}

	quantity getUndulation() {
		return gga.undulation;
	}

	uint8_t getAgeCorectData() {
		return gga.ageCorectData;
	}

	uint16_t getStaionID() {
		return gga.staionID;
	}
	//GPGGA_

	//GPGSA

	quantity getModeFix() {
		return gsa.modeFix;
	}

	uint8_t getPrnNums(uint8_t index) {
		if (index > 11) index = 11;
		return gsa.prnNums[index];
	}

	float getPositionDilutOfPres() {
		return gsa.posDilutOfPres;
	}

	float getHorizontalDilutOfPres() {
		return gsa.horDilutOfPres;
	}

	float getVerticalDilutOfPres() {
		return gsa.verDilutOfPres;
	};
	//GPGSA_


	bool connect(uint32_t timeout = 1000) {
		uint32_t s = millis();
		while (millis() - s <= timeout) {
			
			//READ WARNING!!!
#if defined ESP8266 || defined ARDUINO_ARCH_STM32
			if (HWS == nullptr) {
				if (SWS == nullptr) { return 0; }
				else if (SWS->available()) {
						updateData_force();
						return 1;
					}
			}
			else if (HWS->available()) {
				updateData_force();
				return 1;
			}
#else
			if (SWS == nullptr) { return 0; }
			else if (SWS->available()) { 
					updateData_force();
					if (flg) return 1;
					else return 0;
				}	
#endif
		}
	}


	void updateData_force() {
#if defined ESP8266 || defined ARDUINO_ARCH_STM32
		if (HWS == nullptr) { 
			if (SWS != nullptr) { 
				while (!SWS->available()) {};
				while (SWS->available())getMessages(char(SWS->read()));
			}
		}
		else {
			while (!HWS->available()) {};
			while (HWS->available())  getMessages(char(HWS->read()));
			
		}
#else
		while (!SWS->available()) {};
		while (SWS->available())getMessages(char(SWS->read()));
#endif
	}


	void updateData() {
		//READ WARNING!!!
#if defined ESP8266 || defined ARDUINO_ARCH_STM32
		if (HWS == nullptr) {
			if (SWS != nullptr) while (SWS->available()) getMessages(char(SWS->read()));
		}
		else while (HWS->available()) getMessages(char(HWS->read()));
#else
		if (SWS == nullptr) while (SWS->available())getMessages(char(SWS->read()));
#endif	
	}
	//publuc segment_

	//private segment
private:
	char inputChr;
	uint8_t j=0;
	bool fractFlg;
	char strGP[2];
	uint8_t numGP=255;
	uint8_t contWrd=0;


	//Converting the NMEA standart strings of GPS to comfortable format
	void getMessages(char inputChr) {
		if (inputChr == '$' || j) {

			//Detection of GP-s strings headings  
			if (j >= 4) { strGP[j - 4] = inputChr; numGP = 255; }
			if (j == 5) {
				if (strGP[0] == 'M' && strGP[1] == 'C')numGP = 0; //GPRMC
				else if (strGP[0] == 'T' && strGP[1] == 'G')numGP = 1; //GPVTG
				else if (strGP[0] == 'G' && strGP[1] == 'A')numGP = 2; //GPGGA
				else if (strGP[0] == 'S' && strGP[1] == 'A')numGP = 3; //GPGSA
				j = 0; contWrd = 0;
			}
			else j++;
		}
		else {
			if (inputChr == '.')fractFlg = 1;
			else if ('/' < inputChr && inputChr < ':') {
				tmpNum = tmpNum * 10 + uint32_t(inputChr) - 48;
				if (fractFlg)fractLenght++;
			}
			else if ('@' < inputChr && inputChr < '[') {
				tmpChr = inputChr;
				strGP[0] = 0;
				strGP[1] = 0;
			}
			else if (inputChr == ',') {
				switch (numGP) { //Loading data according to their standart strings
				case 0:
					rmc.load(&contWrd);
					break;

				case 1:
					vtg.load(&contWrd);
					break;

				case 2:
					gsa.load(&contWrd);
					break;
				default:
					break;
				}
				contWrd++;
				tmpNum = 0;
				fractFlg = 0;
				fractLenght = 0;
			}
		}
	}
	//private segment_
};



//Constructors 
GPNMEA::GPNMEA(SoftwareSerial *SoftwareS) {
	SWS = SoftwareS;
}

//READ WARNING!!!
#if defined ESP8266 || defined ARDUINO_ARCH_STM32 
GPNMEA::GPNMEA(HardwareSerial *HardwareS) {
	HWS = HardwareS;
}
#endif


