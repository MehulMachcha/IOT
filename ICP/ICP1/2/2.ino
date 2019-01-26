// Initialized a varaible to hold the switch state
int switchState = 0;

void setup()
{
  // Set pin 3, 4, 5 for output (link to LED lights)
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  // Set pin 2 for input (link to button)
  pinMode(2, INPUT);
}

void loop()
{
  // Read input (check if button is pressed)
  switchState = digitalRead(2);
  
  if (switchState == LOW)
  {
    // The button is not press
    digitalWrite(3, HIGH); // Green LED on
    digitalWrite(4, LOW); // Red LED(1) off
    digitalWrite(5, LOW); // Red LED(2) off
  }
  else
  {
    // The button is pressed
    // Loop for 6 times 
    for(int l=0; l<=5; l++)
    {
      digitalWrite(3, HIGH); // Green LED on
      digitalWrite(4, LOW); // Red LED(1) off
      digitalWrite(5, LOW); // Red LED(2) off
      delay(250); // Sleep for 250ms
      digitalWrite(3, LOW); // Green LED off
      digitalWrite(4, HIGH); // Red LED(1) on
      digitalWrite(5, LOW); // Red LED(2) off
      delay(250); // Sleep for 250ms
      digitalWrite(3, LOW); // Green LED off
      digitalWrite(4, LOW); // Red LED(1) off
      digitalWrite(5, HIGH); // Red LED(2) on
      delay(250); // Sleep for 250ms
    }
  }
}
