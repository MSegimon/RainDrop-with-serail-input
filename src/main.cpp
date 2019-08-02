#include <Arduino.h>

// Arrays of pin numbers. Fill these in with the pins to which you connected
// your anode (+) wires and cathode (-) wires.
const byte ROW_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte COL_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

byte pattern1[8][8];

void setup() {
  // TODO: configure all anode (+) and cathode (-) wires to outputs
  // TODO: turn "off" all the LEDs
  // Hint: You did the same thing in everylight.ino.
  for (byte i = 0; i < 8; i++) {
    pinMode(ROW_PINS[i], OUTPUT);
    pinMode(COL_PINS[i], OUTPUT);
  }

  for (byte i = 0; i < 8; i++) {
    digitalWrite(COL_PINS[i], LOW);
    digitalWrite(ROW_PINS[i], LOW);
  }

  // Initialize serial communication
  // (to be read by Serial Monitor on your computer)
  Serial.begin(9600);
  Serial.setTimeout(100);

  //this is for testing
  pattern1[0][3] = !pattern1[0][3];
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
  // TODO : Write code to move the pattern down by one row , and turn the
  // top row off.
  // Here 's a doubly - nested for loop to get you started , but you can modify
  // or replace this if you wish :

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

void loop() {

  // use 'static' so that it retains its value between successive calls of loop()
  //static byte pattern[8][8];
  static byte pattern2[8][8];

  static unsigned long Time = millis();

  // Toggle the LED state
  //pattern[x][y] = !pattern[x][y];
  
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

    Time = millis();
  }
  
  Serial.println(Time);
  display(pattern1);
}
