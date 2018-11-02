#include "Mux.h"

void muxSetup(void)
{
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
}

float readMuxTemp(DHT &dht, uint8_t muxPin)
{
  int8_t r0 = bitRead(muxPin, 0);
  int8_t r1 = bitRead(muxPin, 1);
  int8_t r2 = bitRead(muxPin, 2);

  digitalWrite(MUX_S0, r0);
  digitalWrite(MUX_S1, r1);
  digitalWrite(MUX_S2, r2);

  //delay(50);

  return dht.readTemperature(false, true);
};

float readMuxHum(DHT &dht, uint8_t muxPin)
{
  int8_t r0 = bitRead(muxPin, 0);
  int8_t r1 = bitRead(muxPin, 1);
  int8_t r2 = bitRead(muxPin, 2);

  digitalWrite(MUX_S0, r0);
  digitalWrite(MUX_S1, r1);
  digitalWrite(MUX_S2, r2);

  //delay(50);

  dht.readTemperature(false, true);
  return dht.readHumidity(true);
};
