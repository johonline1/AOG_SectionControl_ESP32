
#include "Arduino.h"
#include <Adafruit_PCF8575.h> //"PCF8574.h"




#define maxPCFs 4
Adafruit_PCF8575 PCF_[maxPCFs];
int PCFs = 0;
int PCF_Pins = 0;
 
int scanPCF (TwoWire *pWire) {
//Adafruit_PCF8574* PCF_p;
  Serial.println("");  Serial.print("Init pcf8574 boards... ");
  for (uint8_t i = 0x19; ((i < 0x38) && (PCFs < maxPCFs)); i++){
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0) {
      PCF_[PCFs].begin(i, pWire);
      Serial.println(); Serial.print("found PCF_"); Serial.print(PCFs); Serial.print(" at adr. "); Serial.print(i);
      if (++PCFs >= maxPCFs) {/*
  for*/ break;        
      }
    }
  }
  PCF_Pins = PCFs*16;
  Serial.println(); Serial.print("found "); Serial.print(PCF_Pins); Serial.println(" PCF-Pins!"); 
  return PCFs;
}



bool _pinMode  (uint8_t pin, uint8_t mode) {
  if ((pin & 0b10000000) == 0){
    pinMode( pin, mode);
    Serial.print("Set HW -Pin ");Serial.print(pin);Serial.print(" to Mode ");Serial.println(mode);
    return true;
  } else {
    int PCF_no = (pin & 0b110000) >> 4;
    if (PCF_no < PCFs) {
      return PCF_[PCF_no].pinMode( (pin & 0b1111), mode);
      Serial.print("Set PCF-Pin ");Serial.print(pin & 0b111);Serial.print(" on PCF_");Serial.print(PCF_no);Serial.print(" to Mode ");Serial.println(mode);
    } else {
      Serial.print("wrong PCF-Pin ");Serial.print(pin);Serial.println(" Mode not set ");
      return false;
    }
  }
}


void _digitalWrite(uint8_t pin, uint8_t val) {
  if ((pin & 0b10000000) == 0){
    digitalWrite( pin, val);
  } else {
    int PCF_no = (pin & 0b110000) >> 4;
    if (PCF_no < PCFs) {
      PCF_[PCF_no].digitalWrite( (pin & 0b1111), val);
    }
  }
}

int _digitalRead(uint8_t pin) {
  if ((pin & 0b10000000) == 0){
    return digitalRead( pin );
  } else {
    int PCF_no = (pin & 0b110000) >> 4;
    if (PCF_no < PCFs) {
      return PCF_[PCF_no].digitalRead( (pin & 0b1111));
    } else {
      return false;
    }
  }
}


void _digitalWriteWord(int Pcf_no, uint16_t val) {
  PCF_[Pcf_no].digitalWriteWord(val);
}
