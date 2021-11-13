#include <Servo.h>

#define PHOTORESISTOR A0
#define COLOUR_THRESHOLD 630

#define DARK_BLUE true
#define LIGHT_BLUE false

void setup() {
  // put your setup code here, to run once:
  #define pinMode(PHOTORESISTOR, INPUT); 
  serial.begin()
}

// Read photoresistor and determine colour of marble
bool spinDirection() {
  int reading = digitalRead(PHOTORESISTOR);

  if (reading >= COLOUR_THRESHOLD)
    return DARK_BLUE;

  return LIGHT_BLUE;
}

// Debounce reading of spinDirection()
bool debounceSpin() {
  const int DEBOUNCE_ITERATIONS = 20; // Number of times to call spinDirection() for debouncing
  int counter = 0;                    // Increment if DARK_BLUE, decrement if LIGHT_BLUE
  bool directionReading;              // Value returned from spinDirection

  // Debounce spinDirection()
  for (int i = 0; i < DEBOUNCE_ITERATIONS; i++) {
    directionReading = spinDirection();

    if (directionReading == DARK_BLUE) {
      counter++;
    } else {
      counter--;
    }
    
  }

  // If counter is positive then DARK_BLUE, otherwise LIGHT_BLUE
  if (counter >= 0) {
    return DARK_BLUE;
  }
  return LIGHT_BLUE;
}

void loop() {
  // put your main code here, to run repeatedly:
  serial.printf(digitalRead(PHOTORESISTOR));
  delay(10);
}
