#include <Arduino.h>
#include <Keyboard.h>  // HID keyboard

// Rows and columns
const int ROWS = 3;
const int COLS = 4;

// Row pins
const int rowPins[ROWS] = {6, 7, 0};  // GP6, GP7, GP0

// Column pins
const int colPins[COLS] = {26, 27, 28, 29}; // GP26-GP29

// Key mapping - HID keycodes for F1-F12
const uint8_t keys[ROWS][COLS] = {
  {KEY_F1, KEY_F2, KEY_F3, KEY_F4},
  {KEY_F5, KEY_F6, KEY_F7, KEY_F8},
  {KEY_F9, KEY_F10, KEY_F11, KEY_F12}
};

void setup() {
  // Init keyboard HID
  Keyboard.begin();

  // Rows output
  for (int r = 0; r < ROWS; r++) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);  // idle HIGH
  }

  // Columns input with pull-up
  for (int c = 0; c < COLS; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }
}

void loop() {
  for (int r = 0; r < ROWS; r++) {
    digitalWrite(rowPins[r], LOW);  // activate row

    for (int c = 0; c < COLS; c++) {
      if (digitalRead(colPins[c]) == LOW) {  // key pressed
        Keyboard.press(keys[r][c]);          // send HID key
      } else {
        Keyboard.release(keys[r][c]);        // release when not pressed
      }
    }

    digitalWrite(rowPins[r], HIGH);  // deactivate row
  }

  delay(5); // tiny delay for debounce & stability
}
