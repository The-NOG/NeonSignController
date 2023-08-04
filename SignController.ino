// C++ code
//

const int buttonPin = 2;  // the number of the pushbutton pin
const int topLED = 11;
const int midLED = 10;
const int lowLED = 9;
int buttonState = 0;
int mode = 0;
const int maxMode = 5;
int lastButtonState = 0;
const int framerate = 30;
int frame = 1;
int maxFrame = 30000;
int baseMode = 0;
long randomNumber = 0;
int result = 0;

void setup()
{
  Serial.begin(9600);
  //INIT PINS
  pinMode(topLED, OUTPUT);
  pinMode(midLED, OUTPUT);
  pinMode(lowLED, OUTPUT);
  pinMode(buttonPin, INPUT);
  //check if button is pressed
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    baseMode = 1;
    randomSeed(analogRead(A0));
  }
}

int oneafter(){
  if (frame > 0 & frame < framerate * 2){
    digitalWrite(lowLED, LOW);
    digitalWrite(topLED, HIGH);
  }
  else if (frame > framerate * 2 & frame < framerate * 4){
    digitalWrite(topLED, LOW);
    digitalWrite(midLED, HIGH);
  }
  else if (frame > framerate * 4 & frame < framerate * 6){
    digitalWrite(midLED, LOW);
    digitalWrite(lowLED, HIGH);
  }
  else if (frame > framerate * 6){
    resetFrameCounter();
    return 1;
  }
  return 0;
}
int oneafter_fast(){
  if (frame > 0 & frame < framerate * 1){
    digitalWrite(lowLED, LOW);
    digitalWrite(topLED, HIGH);
  }
  else if (frame > framerate * 1 & frame < framerate * 2){
    digitalWrite(topLED, LOW);
    digitalWrite(midLED, HIGH);
  }
  else if (frame > framerate * 2 & frame < framerate * 3){
    digitalWrite(midLED, LOW);
    digitalWrite(lowLED, HIGH);
  }
  else if (frame > framerate * 3){
    resetFrameCounter();
    return 1;
  }
  return 0;
}
int bounce(){
  if (frame > 0 & frame < framerate * 2){
    digitalWrite(midLED, LOW);
    digitalWrite(topLED, HIGH);
  }
  else if (frame > framerate * 2 & frame < framerate * 4){
    digitalWrite(topLED, LOW);
    digitalWrite(midLED, HIGH);
  }
  else if (frame > framerate * 4 & frame < framerate * 6){
    digitalWrite(midLED, LOW);
    digitalWrite(lowLED, HIGH);
  }
  else if (frame > framerate * 6 & frame < framerate * 8){
    digitalWrite(lowLED, LOW);
    digitalWrite(midLED, HIGH);
  }
  else if (frame > framerate * 8){
    resetFrameCounter();
    return 1;
  }
  return 0;
}
int bounce_fast(){
  if (frame > 0 & frame < framerate * 1){
    digitalWrite(midLED, LOW);
    digitalWrite(topLED, HIGH);
  }
  else if (frame > framerate * 1 & frame < framerate * 2){
    digitalWrite(topLED, LOW);
    digitalWrite(midLED, HIGH);
  }
  else if (frame > framerate * 2 & frame < framerate * 3){
    digitalWrite(midLED, LOW);
    digitalWrite(lowLED, HIGH);
  }
  else if (frame > framerate * 3 & frame < framerate * 4){
    digitalWrite(lowLED, LOW);
    digitalWrite(midLED, HIGH);
  }
  else if (frame > framerate * 4){
    resetFrameCounter();
    return 1;
  }
  return 0;
}
void fullon(){
  digitalWrite(topLED, HIGH);
  digitalWrite(midLED, HIGH);
  digitalWrite(lowLED, HIGH);
}
void fulloff(){
  digitalWrite(topLED, LOW);
  digitalWrite(midLED, LOW);
  digitalWrite(lowLED, LOW);
}
int breath(){
  int length = 5;
  if(frame < (framerate * length)){
    int PWMammount = constrain((frame*(int)1.7),10,254);
    analogWrite(topLED, PWMammount);
    analogWrite(midLED, PWMammount);
    analogWrite(lowLED, PWMammount);
  }
  else if(frame > (framerate * length) & frame < ((framerate * length)*2)){
    int downframe = frame - (framerate * length);
    int PWMammount = constrain(255-(downframe*(int)1.7),10,254);
    analogWrite(topLED, PWMammount);
    analogWrite(midLED, PWMammount);
    analogWrite(lowLED, PWMammount);
  }
  else if(frame > ((framerate * length)*2)){
    resetFrameCounter();
    return 1;
  }
  return 0;
}
int breath_fast(){
  int length = 2;
  if(frame < (framerate * length)){
    int PWMammount = constrain((frame*(int)4),10,254);
    analogWrite(topLED, PWMammount);
    analogWrite(midLED, PWMammount);
    analogWrite(lowLED, PWMammount);
  }
  else if(frame > (framerate * length) & frame < ((framerate * length)*2)){
    int downframe = frame - (framerate * length);
    int PWMammount = constrain(255-(downframe*(int)4),10,254);
    analogWrite(topLED, PWMammount);
    analogWrite(midLED, PWMammount);
    analogWrite(lowLED, PWMammount);
  }
  else if(frame > ((framerate * length)*2)){
    resetFrameCounter();
    return 1;
  }
  return 0;
}

void resetFrameCounter(){
  frame = 1;
}

void randomPlay(){
  if(frame == maxFrame){
    resetFrameCounter();
  }
  else{
    frame = frame + 1;
  }
  switch(randomNumber){
      case 0:
        result = oneafter_fast();
        break;
      case 1:
        result = bounce_fast();
        break;
      case 2:
        result = breath_fast();
        break;
  }
  if(result == 1){
    fulloff();
    randomNumber = random(-1,3);
  }
  delay(40);
}

void loop(){
  if(baseMode == 1){
    if(frame == maxFrame){
      resetFrameCounter();
    }
    else{
      frame = frame + 1;
    }
    buttonState = digitalRead(buttonPin);
    if (buttonState != lastButtonState){
      if (buttonState == HIGH){
        if(mode == maxMode){
          mode = 0;
        }
        else{
          mode += 1;
        }
        resetFrameCounter();
        fulloff();
      }
    }
    lastButtonState = buttonState;
    switch (mode){
      case 0:
        oneafter();
        break;
      case 1:
        oneafter_fast();
        break;
      case 2:
        bounce();
        break;
      case 3:
        bounce_fast();
        break;
      case 4:
        fullon();
        break;
      case 5:
        breath_fast();
        break;
      case 6:
        breath();
        break;
    }
    delay(40);
  }
  else{
    randomPlay();
  }
}
