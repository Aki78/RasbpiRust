const int buttonPin = 2;
String message = "";
unsigned long previousMillis = 0;
unsigned long interButtonDelay = 200;
unsigned long dotDuration = 0;
unsigned long dashDuration = 0;
bool learning = true;

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
        if (dotDuration == 0) {
          dotDuration = currentMillis - previousMillis;
        } else if (dashDuration == 0) {
          dashDuration = currentMillis - previousMillis;
          learning = false;
          Serial.println("Learning complete. Dot duration: " + String(dotDuration) + "ms, Dash duration: " + String(dashDuration) + "ms");
        }
      } else {
        if (currentMillis - previousMillis <= dotDuration) {
          message += ".";
        } else if (currentMillis - previousMillis <= dashDuration) {
          message += "-";
        } else {
          Serial.println(translateMorse(message));
          message = "";
        }
      }
    }
  }
}

String translateMorse(String morse) {
  String result = "";
  String currentLetter = "";
  for (int i = 0; i < morse.length(); i++) {
    currentLetter += morse[i];
    if (morse[i] == ' ' || i == morse.length() - 1) {
      for (int j = 0; j < 36; j++) {
        if (morseCode[j] == currentLetter) {
          if (j < 26) {
            result += (char)(j + 'a');
          } else {
            result += (char)(j - 26 + '0');
          }
          break;
        }
      }
      currentLetter = "";
    }
  }
  return result;
}
