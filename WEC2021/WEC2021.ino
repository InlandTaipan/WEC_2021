#include <Stepper.h>

#define PHOTORESISTOR A0
#define DONE_LED D2
#define COLOUR_THRESHOLD 630

#define DARK_BLUE true
#define LIGHT_BLUE false
#define STEPS90DEG 510

//Correct stepper order
Stepper motor(STEPS90DEG, 8, 10, 9, 11);

#define MAX_MARBLES 10
#define DONE_THRESHOLD 5

int numMarblesSorted = 0; // Number of marbles sorted

void setup() {
  //for debug
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // set the speed at 80 rpm:
  motor.setSpeed(80);
  // put your setup code here, to run once:
  pinMode(PHOTORESISTOR, INPUT); 
}

// Read photoresistor and determine colour of marble
bool spinDirection() {
  int reading = analogRead(PHOTORESISTOR);

  if (reading >= COLOUR_THRESHOLD)
    return DARK_BLUE;

  return LIGHT_BLUE;
}

// Debounce reading of spinDirection()
bool debounceSpinDirection() {
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

void spinMotor(bool direct)
{
  if (direct == DARK_BLUE)
  {
    //Clockwise
    motor.step(STEPS90DEG);
    delay(100);
  }
  else 
  {
    //CCW
    motor.step(-1*STEPS90DEG);
    delay(100);
  }
}

// Performs all necessary actions to sort one marble
void sortMarble() {

  spinMotor(debounceSpinDirection());

  numMarblesSorted++;
}

// Indicate that DONE_THRESHOLD marbles have been sorted
void doneMarble() {
  
}

// Kill the marble sorter
void terminateMarble() {
  
}

void loop() {
  
  sortMarble();

  if (numMarblesSorted == DONE_THRESHOLD) {
    doneMarble();
  } else if (numMarblesSorted == MAX_MARBLES) {
    terminateMarble();
    break;
  }
  
}
