const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

// Function to blink morse code
void blinkMorse(String message) {
  // Morse code dictionary
  String morseCode[36] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", "--..--", ".-.-.-", "..--.." };
  
  for (int i = 0; i < message.length(); i++) {
    char c = message[i];
    if (c >= 'a' && c <= 'z') {
      String code = morseCode[c - 'a'];
      for (int j = 0; j < code.length(); j++) {
        if (code[j] == '.') {
          digitalWrite(LED, HIGH);
          delay(200);
          digitalWrite(LED, LOW);
          delay(200);
        } else if (code[j] == '-') {
          digitalWrite(LED, HIGH);
          delay(600);
          digitalWrite(LED, LOW);
          delay(200);
        }
      }
    }
    // If character is a number
    else if (c >= '0' && c <= '9') {
      String code = morseCode[c - '0' + 26];
      for (int j = 0; j < code.length(); j++) {
        if (code[j] == '.') {
          digitalWrite(LED, HIGH);
          delay(200);
          digitalWrite(LED, LOW);
          delay(200);
        } else if (code[j] == '-') {
          digitalWrite(LED, HIGH);
          delay(600);
          digitalWrite(LED, LOW);
          delay(200);
        }
      }
    }
    // Space between letters
    delay(400);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readString();
    blinkMorse(message);
  }
}
