#include <Arduino.h>

#define LNC_OP_GPIO_OUT  0

//Define output pins
const char gpio_out_pin1 = 2; //D4
const char gpio_out_pin2 = 4; //D2
const char gpio_out_pin3 = 5; //D1


void blinkLED(uint8_t pin,uint8_t state){
    uint8_t i = LNC_OP_GPIO_OUT;
    i = i << 4;
    i = i + pin;
    i = i << 1;
    i = i + state;

    Serial.print("<Gpio_out: ");
    Serial.println(i);
    Serial2.write(i);
    Serial2.flush();

    while(!Serial2.available()){

    }

    uint8_t r = Serial2.read();
    Serial.print("> ");
    Serial.println(r);
}

void setup() {
  
    Serial.begin(115200);
    Serial2.begin(115200);

}

void loop() {
    blinkLED(gpio_out_pin1, 1);
    delay(2000);
    blinkLED(gpio_out_pin2, 1);
    delay(2000);
    blinkLED(gpio_out_pin3, 1);
    delay(2000);

    blinkLED(gpio_out_pin1, 0);
    delay(2000);
    blinkLED(gpio_out_pin2, 0);
    delay(2000);
    blinkLED(gpio_out_pin3, 0);
    delay(2000);


}