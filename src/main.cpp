#include <Arduino.h>

#define PIN_OUTPUT 3 // needs pwm support
#define PIN_INPUT 0
#define PIN_VISUAL_OUT 13
#define UPDATE_PWM_TIMER 100 //micros

#define DEBUG

void setup() {
    pinMode(PIN_OUTPUT, OUTPUT);
    pinMode(PIN_VISUAL_OUT, OUTPUT);

#ifdef DEBUG
    Serial.begin(115200);
#endif
}


unsigned long microsSinceLastUpdate = 0;
int16_t lastReading = -1;


void loop() {

    int16_t curReading = analogRead(PIN_INPUT);

    if (micros() - microsSinceLastUpdate > UPDATE_PWM_TIMER && lastReading != -1) {
        int16_t filtredReading = curReading * 0.7 + lastReading * 0.3;

        int16_t output = map(filtredReading, 0, 1023, 0, 255);

        analogWrite(PIN_OUTPUT, output);
        analogWrite(PIN_VISUAL_OUT, output);

#ifdef DEBUG
        Serial.println(output);
#endif

        microsSinceLastUpdate = micros();
    }


    lastReading = curReading;
}
