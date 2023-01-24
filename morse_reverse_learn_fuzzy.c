const int buttonPin = 2;
String message = "";
unsigned long previousMillis = 0;
unsigned long interButtonDelay = 200;
unsigned long dotDuration = 0;
unsigned long dashDuration = 0;
bool learning = true;
unsigned long dotDurationSum = 0;
unsigned long dashDurationSum = 0;
unsigned long dotPressCount = 0;
unsigned long dashPressCount = 0;

String morseCode[36] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", "--..--", ".-.-.-", "..--.." };

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interButtonDelay) {
      previousMillis = currentMillis;
      if (learning) {
        unsigned long buttonDuration = currentMillis - previousMillis;
        if (buttonDuration >= dotDuration - 50 && buttonDuration <= dotDuration + 50) {
          dotDurationSum += buttonDuration;
          dotPressCount++;
        } else if (buttonDuration >= dashDuration - 50 && buttonDuration <= dashDuration + 50) {
          dashDurationSum += buttonDuration;
          dashPressCount++;
        } else {
          Serial.println("Invalid button press duration. Please try again.");
        }
        if (dotPressCount >= 5 && dashPressCount >= 5) {
          dotDuration = dotDurationSum / dotPressCount;
          dashDuration = dashDurationSum / dashPressCount;
          learning = false;
          Serial.println("Learning complete. Dot duration: " + String(dotDuration) + "ms, Dash duration: " + String(dashDuration) + "ms");
        }
      } else {
        if (currentMillis - previousMillis >= dotDuration - 50 && currentMillis - previousMillis <= dotDuration + 50) {
          message += ".";
        } else if (currentMillis - previousMillis >= dashDuration - 50 && currentMillis - previousMillis <= dashDuration + 50) {
          message += "-";
        } else {
          Serial.println(translateMorse(message));
          message = "";
        }
      }
    }
  }
}
