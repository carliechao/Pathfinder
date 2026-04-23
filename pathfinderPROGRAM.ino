
int btns[] = {D1,D0,D3,D2};
int btnsLength = sizeof(btns)/sizeof(btns[0]);
int leds[] = {D10,D9,D8,D7};
int ledsLength = sizeof(leds)/sizeof(leds[0]);
// int led1 = D10;
// int led2 = D9;
// int led3 = D8;
// int led4 = D7;

void setup() {

  for (int i = 0; i < btnsLength; i++){
    pinMode(btns[i], INPUT_PULLUP);
  }

  for (int i = 0; i < ledsLength ; i++){
    pinMode(leds[i], OUTPUT);
  }

  //set a random seed so random is not predictable
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

int loopNumber = 1;
int ledsLit[50];


void loop() {
  // put your main code here, to run repeatedly:
  //sizeof() = total byes used by the whole array / sizeof(arr[i]) = bytes used by one element
  
   int randIndex = random(0,ledsLength);
   ledsLit[loopNumber-1] = randIndex;

  for (int i = 0; i < loopNumber; i++){
    digitalWrite(leds[ledsLit[i]],HIGH);
    delay(800);
    digitalWrite(leds[ledsLit[i]], LOW);
    delay(200);
  }


  for (int i = 0; i < loopNumber; i++ ){
    bool correct = false;
    unsigned long start = millis();
    //unsigned means that it is a positivie long so it does not
    //reserve space for negative
    while((millis()-start < 3000)&&!correct){
      for (int b = 0; b < btnsLength; b++) {
        if (digitalRead(btns[b]) == LOW) {
          delay(150);
          //low means it is pressed
          //wait for button to be released
          while(digitalRead(btns[b])==LOW){delay(5);}
          if (b == ledsLit[i]) {
            correct = true;
          } else {
            gameOver();
            return;
          }
          break;
        }
      }
    }
    if (!correct){
      gameOver();
      return;
    }
  }
  if (loopNumber<50){
    loopNumber++;
  }
  delay(500);
}

void gameOver(){
  Serial.println("GAME OVER!");
  for (int i = 0; i < 4 ; i++){
    for (int j = 0; j < ledsLength ; j++){
    digitalWrite(leds[j], HIGH);
    }
    delay(200);
    for (int j = 0; j < ledsLength ; j++){
    digitalWrite(leds[j], LOW);
    }
    delay(200);
  }
  loopNumber=1;
  Serial.println("GAME START!");
}

