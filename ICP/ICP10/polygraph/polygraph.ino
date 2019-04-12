
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(4, HIGH);
  delay(500);
}

void loop() {
  if (analogRead(A0) > 60)
{
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
}
else
{
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
}

  Serial.println(analogRead(A0));
  delay(20);
}
