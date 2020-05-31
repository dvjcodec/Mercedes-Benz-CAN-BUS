// Pulse to CAN-BUS merrage for W203 MB cluster
// Tested on Mega2560 + CAN-BUS shield + square signal generator
// Krzysztof Dymianiuk @ Seaside Customs Garage / dvjcodec@gmail.co
// Part of code by:
// https://matthewcmcmillan.blogspot.com
// Twitter: @matthewmcmillan


#include "mcp_can.h"
#include <SPI.h>

MCP_CAN CAN(10); //CAN CS  pin

float pulsewidth = 0;
int canValue = 0;
int pulseValue = 0;

void setup()
{
  Serial.begin(115200);
  if(CAN.begin(CAN_500KBPS) ==CAN_OK) Serial.print("CAN init ok\r\n");
  else Serial.print("CAN init failed\r\n");
}

void loop()
{
  pulsewidth = pulseIn (14, HIGH) / 650; // 650 - this value can be changed to fit pulses to canValue
  pulseValue = pulsewidth;
  canValue = pulseValue;
  Serial.print("canValue: ");
  Serial.print(canValue);
  Serial.println();
  unsigned char canMsg[8] = {0x00, canValue, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF};
  CAN.sendMsgBuf(0x308, 0, 8, canMsg);
  Serial.print("Pulse: ");
  Serial.println(pulseValue);
  delay(20);
}
