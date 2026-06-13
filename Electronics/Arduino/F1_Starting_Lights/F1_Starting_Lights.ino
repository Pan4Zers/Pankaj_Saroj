int redPin = 4;
int yellowPin = 5;
int greenPin = 6;
int buzzerPin = 8;

int state = 0;
unsigned long prevMillis = 0;
unsigned long randomTime;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  randomSeed(analogRead(A0));
}

void loop()
{
  unsigned long currMillis = millis();

  switch (state)
  {
    case 0: // Red LED turns ON, start 2s timer
      digitalWrite(redPin, HIGH);
      prevMillis = currMillis;
      state = 1;          // ← advance state
      break;              // ← stop fall-through into case 1

    case 1: // Wait 2s, then turn Yellow ON
      if (currMillis - prevMillis >= 2000)
      {
        digitalWrite(yellowPin, HIGH);
        randomTime = random(1000, 3000);
        prevMillis = currMillis;
        state = 2;
      }
      break;

    case 2: // Wait random interval, then GO
      if (currMillis - prevMillis >= randomTime)
      {
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        prevMillis = currMillis;
        state = 3;
      }
      break;

    case 3:
      if (currMillis - prevMillis >= 500)   // beep duration in ms
      {
        digitalWrite(buzzerPin, LOW);
        state = 4;
      }
      break;

    case 4:
      break;   // final idle state
  }
}