//Arduino Piano With OLED indicator
//Project by AHMAD FAJRIL FALAH
//KELAS = XII-F11
//ABSEN = 03

#include "pitches.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SPEAKER_PIN 8

const uint8_t buttonPins[] = {12, 11, 10, 9, 7, 6, 5, 4};
const int buttonTones[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};
const char* noteNames[] = {
  "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5"
};
const int numTones = sizeof(buttonPins) / sizeof(buttonPins[0]);

void setup() {
  for (uint8_t i = 0; i < numTones; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(SPEAKER_PIN, OUTPUT);

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C adalah alamat I2C OLED
    Serial.println("OLED tidak terdeteksi!");
    for (;;); // Hentikan program jika OLED tidak terdeteksi
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Ready");
  display.display();
}

void loop() {
  int pitch = 0;
  const char* currentNote = "";

  for (uint8_t i = 0; i < numTones; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      pitch = buttonTones[i];
      currentNote = noteNames[i];
    }
  }

  if (pitch) {
    tone(SPEAKER_PIN, pitch);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Note: ");
    display.print(currentNote);
    display.display();
  } else {
    noTone(SPEAKER_PIN);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Press key!");
    display.display();
  }
}
