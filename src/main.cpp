#include <Arduino.h>

// Arrays of pin numbers. Fill these in with the pins to which you connected
// your anode (+) wires and cathode (-) wires.
const byte ROW_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte COL_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

void setup() {
  // TODO: configure all anode (+) and cathode (-) wires to outputs
  // TODO: turn "off" all the LEDs
  for (byte i = 0; i < 8; i++) {
    pinMode(ROW_PINS[i], OUTPUT);
    pinMode(COL_PINS[i], OUTPUT);
  }

  for (byte i = 0; i < 8; i++) {
    digitalWrite(COL_PINS[i], LOW);
    digitalWrite(ROW_PINS[i], LOW);
  }

  // Initialize serial communication
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void display(byte pattern[8][8]) {
  
  for (byte x = 0; x < 8; x++) {
    for (byte y = 0; y < 8; y++) {
      if (pattern[x][y]) {
        digitalWrite(COL_PINS[y], LOW);
      } else {
        digitalWrite(COL_PINS[y], HIGH);
      }
    }
    digitalWrite(ROW_PINS[x], LOW);
    delayMicroseconds(1000);
    digitalWrite(ROW_PINS[x], HIGH);
  }
}

void movePatternDown(byte pattern[8][8], byte pattern1[8][8]) {

  for (byte x = 0; x < 8; x++)
  {
    for (byte y = 0; y < 8; y++)
    {
      if (pattern[x][y])
      {
        if (x != 7)
        {
          pattern1[x + 1][y] = 1;
        }
      }
      
    }
  }
}

void chooseRandomInTopRow(byte pattern[8][8])
{
  int r = random(0, 7);

  pattern[0][r] = 1;
}

void loop() {

  // use 'static' so that it retains its value between successive calls of loop()
  static byte pattern1[8][8];
  static byte pattern2[8][8];

  static unsigned long Time = millis();

  static byte state;
  byte user_input = 0;

  if (Serial.available() > 0)
  {
    user_input = Serial.read();
    state = user_input;
  }

  switch (state)
  {
  case 'g':
    if (millis() - Time >= 1000)
    {
      movePatternDown(pattern1, pattern2);

      for (byte x = 0; x < 8; x++)
      {
        for (byte y = 0; y < 8; y++)
        {
          pattern1[x][y] = pattern2[x][y];

          pattern2[x][y] = 0;
        }
      }

      chooseRandomInTopRow(pattern1);

      Time = millis();
    }
    break;
  case 'p':
    // No code is needed in this case
    break;
  case 's':
    for (byte x = 0; x < 8; x++)
    {
      for (byte y = 0; y < 8; y++)
      {
        pattern1[x][y] = 0;
        pattern2[x][y] = 0;
      }
    }
    break;
  }

  display(pattern1);
}
