// Project: m0user pedal
// Board: Arduino Leonardo

#include <Mouse.h>
#include <Wire.h>

#define CLICK_DELAY     30
#define CLICK_DURATION  10
#define EYE_CANDY       false

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

    // Check if BUTTON_1 is currently pressed
    if (state & BIT_BUTTON_1) { // BUTTON_1 is currently pressed
        if (last_state & BIT_BUTTON_1) { // Check if BUTTON_1 was pressed during previous iteration
            Mouse.release(BUTTON_1); // Release BUTTON_1 (mouse up)
            delay(CLICK_DELAY); // Sleep for X milliseconds
        }
        Mouse.press(BUTTON_1); // Press BUTTON_1 (mouse down)
        delay(CLICK_DURATION); // Sleep for X milliseconds
#if EYE_CANDY
        digitalWrite(LED_BUILTIN, HIGH); // Turn indicator LED on
#endif
    } else { // BUTTON_1 is currently not pressed
        if (last_state & BIT_BUTTON_1) { // BUTTON_1 was pressed during previous iteration
            Mouse.release(BUTTON_1); // Release BUTTON_1 (mouse up)
#if EYE_CANDY
            digitalWrite(LED_BUILTIN, LOW); // Turn indicator LED off
#endif
        }
    }

    if (state != last_state) {
        last_state = state;
    }
}
