/* ################################################## */

// Useful libraries
#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_fr_FR.h>

/* ################################################## */

// Keyboard Key definitions
#define BUTTON_KEY1 KEY_F13
#define BUTTON_KEY2 KEY_F14
#define BUTTON_KEY3 KEY_F15
#define BUTTON_KEY4 KEY_F16
#define BUTTON_KEY5 KEY_F17
#define BUTTON_KEY6 KEY_F18
#define BUTTON_KEY7 KEY_F19
#define BUTTON_KEY8 KEY_F20

// Pin definitions
#define BUTTON_PIN1 2
#define BUTTON_PIN2 3
#define BUTTON_PIN3 4
#define BUTTON_PIN4 5
#define BUTTON_PIN5 6
#define BUTTON_PIN6 7
#define BUTTON_PIN7 8
#define BUTTON_PIN8 9

/* ################################################## */

// Button helper class for handling press/release and debouncing
class button {
  public:
    const char key;
    const uint8_t pin;

  button(uint8_t k, uint8_t p) : key(k), pin(p){}

  void press(boolean state){
    if(state == pressed ||(millis() - lastPressed <= debounceTime)){
       return; //Nothing to do;
     }

    lastPressed = millis();

    state ? Keyboard.press(key) : Keyboard.release(key);

    pressed = state;
  }

    void update(){
      press(!digitalRead(pin));
    }

  private:
    const unsigned long debounceTime = 30;
    unsigned long lastPressed = 0;
    boolean pressed = 0;
};

button buttons[] = {
  {BUTTON_KEY1, BUTTON_PIN1},
  {BUTTON_KEY2, BUTTON_PIN2},
  {BUTTON_KEY3, BUTTON_PIN3},
  {BUTTON_KEY4, BUTTON_PIN4},
  {BUTTON_KEY5, BUTTON_PIN5},
  {BUTTON_KEY6, BUTTON_PIN6},
  {BUTTON_KEY7, BUTTON_PIN7},
  {BUTTON_KEY8, BUTTON_PIN8},
};

const uint8_t NumButtons = sizeof(buttons)/sizeof(button);
const uint8_t ledPin = 17;

void failSafe(){
  for(;;){} //Just going to hang out here for a while
}

void setup() {
  // put your setup code here, to run once:
  //Safety check. Ground pin #1 (RX) to cancel keyboard inputs.
  pinMode(1, INPUT_PULLUP);
  if (!digitalRead(1))
  {
    failSafe();
  }
  
  //Set LEDs Off, Active low.
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,HIGH);
  TXLED0;

  for (int i = 0; i < NumButtons; i++)
  {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NumButtons; i++)
  {
    buttons[i].update();
  }
}
