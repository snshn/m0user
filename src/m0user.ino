// Project: m0user pedal

#include <Mouse.h>
#include <Wire.h>

#define CLICK_DELAY    4
#define CLICK_DURATION 8

enum _bits_buttons {
    BIT_BUTTON_1 = 1,
};

enum _pins {
    PIN_BUTTON_1 = 11,
};

enum _buttons {
    BUTTON_1 = MOUSE_LEFT,
};

void setup() {
    Mouse.begin();
    pinMode(PIN_BUTTON_1, INPUT_PULLUP);
}

uint8_t state = 0;
uint8_t last_state = state;

void loop() {
    if (digitalRead(PIN_BUTTON_1) == HIGH) {
      state |= BIT_BUTTON_1;
    } else {
      state = (state & BIT_BUTTON_1) ? state ^ BIT_BUTTON_1 : state;
    }

    if (state & BIT_BUTTON_1) {
        if (last_state & BIT_BUTTON_1) {
            Mouse.release(BUTTON_1);
            delay(CLICK_DELAY);
        }
        Mouse.press(BUTTON_1);
        delay(CLICK_DURATION);
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        if (last_state & BIT_BUTTON_1) {
            Mouse.release(BUTTON_1);
            digitalWrite(LED_BUILTIN, LOW);
        }
    }

    if (state != last_state) {
        last_state = state;
    }
}
