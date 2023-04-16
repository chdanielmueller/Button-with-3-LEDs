#include <Arduino.h>
#include <TeensyThreads.h>

const int buttonPin = 0;
// Common Anode (+) LED
const int whiteLedPin = 1;
const int greenLedPin = 2;
const int redLedPin = 3;

enum LED { NONE, WHITE, GREEN, RED };
volatile LED activeLed = NONE;

volatile int btnLastState = LOW; // The previous state from the input pin

void buttonThread() {
  int currentState;
  while(1) {
    // Read the state of the switch/button:
    currentState = digitalRead(buttonPin);
    if (btnLastState == LOW && currentState == HIGH) {
      switch(activeLed) {
        case NONE:
          activeLed = WHITE;
          break;
        case WHITE:
          activeLed = GREEN;
          break;
        case GREEN:
          activeLed = RED;
          break;
        case RED:
          activeLed = NONE;
          break;
        default:
          break;
      }
    }  
    // Save the last state
    btnLastState = currentState;
    threads.yield();
  }
}

void setup() {
  pinMode(whiteLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(whiteLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, HIGH);

  pinMode(buttonPin, INPUT);
  threads.addThread(buttonThread);
}

void loop() {

  switch(activeLed) {
    case NONE:
      digitalWrite(whiteLedPin, HIGH);
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, HIGH);
      break;
    case WHITE:
      digitalWrite(whiteLedPin, LOW);
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, HIGH);
      break;
    case GREEN:
      digitalWrite(whiteLedPin, HIGH);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(redLedPin, HIGH);
      break;
    case RED:
      digitalWrite(whiteLedPin, HIGH);
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, LOW);
      break;
    default:
      break;
  }
}


