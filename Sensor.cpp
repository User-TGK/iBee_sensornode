#include "Sensor.h"

DHT dht(MUX_PIN, DHT_TYPE);
DHT singleDht(SOLO_DHT_PIN, DHT_TYPE);

void sensorsSetup(void)
{
    muxSetup();
    pinMode(REEDPIN, INPUT);
    pinMode(POTPIN, INPUT);
    dht.begin();
    singleDht.begin();
}

void getPayload(float payload[NROFPAYLOADS], uint8_t messageId) {
    switch(messageId) {
        case 0:
            for (uint8_t i = 0; i < NROFPAYLOADS; i++) {
                //payload[i] = readMuxTemp(dht, i);
                payload[i] = 22.0;
            }
            break;

        case 1:
            //payload[0] = readMuxTemp(dht, NROFPAYLOADS);
            //payload[1] = singleDht.readTemperature();
            payload[0] = 22.0;
            payload[1] = 23.0;
            for (uint8_t i = 0; i < 5; i++) {
                //payload[i+2] = readMuxHum(dht, i);
                payload[i+2] = 30.0;
            }
            break;

        case 2:
            for (uint8_t i = 5; i < NROFPAYLOADS+1; i++)
            {
                //payload[i-5] = readMuxHum(dht, i);
                payload[i-5] = 40.0;
            }
            //payload[3] = singleDht.readHumidity();
            payload[3] = 40.0;
            //payload[4] = float(digitalRead(REEDPIN));
            payload[4] = 1.00;
            //payload[5] = getWeight();
            payload[5] = 30.0;
            payload[6] = 0.0;
            break;

        case 3:
            break;        
    }
}

float getWeight(void)
{
    uint16_t val = analogRead(POTPIN);
    val = map(val, 0, 1023, 0, 50);
    return float(val);
}