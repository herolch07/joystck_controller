const int NUM_RELAYS = 5;
const int relayPins[NUM_RELAYS] = {22, 24, 25, 27, 28};

// Current wiring uses active-high relay inputs.
// HIGH = ON, LOW = OFF
const int RELAY_ON[NUM_RELAYS]  = {HIGH, HIGH, HIGH, HIGH, HIGH};
const int RELAY_OFF[NUM_RELAYS] = {LOW, LOW, LOW, LOW, LOW};

String input = "";

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_RELAYS; i++) {
    digitalWrite(relayPins[i], RELAY_OFF[i]);  // Write safe state before enabling output.
    pinMode(relayPins[i], OUTPUT);
  }

  Serial.println("Relay test ready");
  Serial.println("Input format: [1,0,1,0,1]");
  Serial.println("1 = ON, 0 = OFF");
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();
    input.replace(" ", "");

    Serial.print("Received: ");
    Serial.println(input);

    if (isValidCommand(input)) {
      for (int i = 0; i < NUM_RELAYS; i++) {
        int value = input.charAt(1 + i * 2) - '0';

        if (value == 1) {
          digitalWrite(relayPins[i], RELAY_ON[i]);
          Serial.print("Relay ");
          Serial.print(i + 1);
          Serial.print(" / Pin ");
          Serial.print(relayPins[i]);
          Serial.println(": ON");
        } else {
          digitalWrite(relayPins[i], RELAY_OFF[i]);
          Serial.print("Relay ");
          Serial.print(i + 1);
          Serial.print(" / Pin ");
          Serial.print(relayPins[i]);
          Serial.println(": OFF");
        }
      }

      Serial.println("Command OK");
      Serial.println();
    } else {
      Serial.println("Invalid format");
      Serial.println("Use format like: [1,0,1,0,1]");
      Serial.println();
    }
  }
}

bool isValidCommand(String cmd) {
  // Expected format: [1,0,1,0,1]
  // 5 values, length = 11
  int expectedLen = 1 + NUM_RELAYS * 2;  // 1 + 5*2 = 11

  if (cmd.length() != expectedLen) return false;

  if (cmd.charAt(0) != '[') return false;
  if (cmd.charAt(expectedLen - 1) != ']') return false;

  // For 5 relays, comma positions are 2, 4, 6, 8.
  for (int i = 2; i < expectedLen - 1; i += 2) {
    if (cmd.charAt(i) != ',') return false;
  }

  // For 5 relays, value positions are 1, 3, 5, 7, 9.
  for (int i = 1; i < expectedLen - 1; i += 2) {
    char c = cmd.charAt(i);
    if (c != '0' && c != '1') return false;
  }

  return true;
}
