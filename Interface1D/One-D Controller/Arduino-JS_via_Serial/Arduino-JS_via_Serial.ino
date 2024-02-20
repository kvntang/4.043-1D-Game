//Controller 1
#define C1_Button 2
#define C1_LED  3

//Controller 2
#define C2_Button 5
#define C2_LED  6

void setup() {
  pinMode(C1_Button, INPUT_PULLUP);
  pinMode(C1_LED, OUTPUT);
  pinMode(C2_Button, INPUT_PULLUP);
  pinMode(C2_LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  //Controller 1
  static unsigned long C1_lastDebounceTime = 0;
  static bool C1_lastButtonState = HIGH;
  bool C1_currentButtonState = digitalRead(C1_Button);
  if (C1_currentButtonState != C1_lastButtonState && (millis() - C1_lastDebounceTime) > 50) {
    C1_lastDebounceTime = millis();
    if (C1_currentButtonState == LOW) { // Assuming the button is active low
      Serial.println("0 1 1");
    }
  }
  C1_lastButtonState = C1_currentButtonState;



  //Controller 2
  static unsigned long C2_lastDebounceTime = 0;
  static bool C2l_astButtonState = HIGH;
  bool C2_currentButtonState = digitalRead(C2_Button);

  if (C2_currentButtonState != C2_lastButtonState && (millis() - C2_lastDebounceTime) > 50) {
    C2_lastDebounceTime = millis();
    if (C2_currentButtonState == LOW) { // Assuming the button is active low
      Serial.println("0 2 1");
    }
  }
  C2_lastButtonState = C2_currentButtonState;


  // Check for incoming serial command
  if (Serial.available() > 0) {
      // Assuming each number is a single digit and we're receiving three numbers
      String data = Serial.readStringUntil('\n'); // Read the incoming line
  
      // Ensure we have exactly 3 characters (for 3 numbers)
      int command[3]; // Array to store the three numbers

      // Convert each character to an integer and store it
      command[0] = data.charAt(0) - '0'; // Convert first character to int
      command[1] = data.charAt(1) - '0'; // Convert second character to int
      command[2] = data.charAt(2) - '0'; // Convert third character to int
      
      if (command[0] == 1) { //incoming message
        if (command[1] == 1){
          //To Controller 1
          if (command[2] == 1){
            digitalWrite(C1_LED, HIGH);
          } else {
            digitalWrite(C1_LED, LOW);
          }

          
        } else if (command[1] == 2) {
          //To Controller 2
          if (command[2] == 1){
            digitalWrite(C2_LED, HIGH);
          } else {
            digitalWrite(C2_LED, LOW);
          }

          
        }
        
      }

    }
}
