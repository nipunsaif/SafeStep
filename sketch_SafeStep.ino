const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const int BUZZER_PIN = 11;
const int LED_PIN = 12;  

float duration_us, distance_cm;

void setup() {   
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {   
  // Trigger the ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo duration
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // Convert to distance in cm
  distance_cm = 0.017 * duration_us;

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  int delay_time = 0;

  // New threshold conditions
  if (distance_cm <= 25) {
    delay_time = 200;   // 0.2 second
  }
  else if (distance_cm <= 50) {
    delay_time = 500;   // 0.5 second
  }
  else if (distance_cm <= 80) {
    delay_time = 1000;  // 1 second
  }
  else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    delay(300);
    return;
  }

  // Buzzer + LED synchronized blink
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
  delay(100);          // short blink/beep

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  delay(delay_time);   // distance-based delay
}
