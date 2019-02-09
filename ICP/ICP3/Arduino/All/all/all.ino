#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial esp8266(9,10); 

#include <LiquidCrystal_PCF8574.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define SSID "Pixel"     // "SSID-WiFiname" 
#define PASS "12345678"       // "password"
#define IP "184.106.153.149"// thingspeak.com ip
String msg = "GET /update?key=LX6QMDTEACPB8T2R"; //change it with your api key like "GET /update?key=Your Api Key"

Adafruit_BMP280 bmp; // I2C

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 2000; 
unsigned long lowpulseoccupancy = 0;
float ratio = 0;

//Libraries
#include <DHT.h>

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float pressure;
float altitude;
float concentration = 0;
int light;
float temp2;
float Vsig;

void setup() {
  Serial.begin(115200);

  lcd.setBacklight(255);
  lcd.begin(16, 2);
  lcd.print("Start...");
  delay(500);
  
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  pinMode(8,INPUT);
  starttime = millis(); 

  pinMode(A0,INPUT);

  dht.begin();

  esp8266.begin(115200);
  esp8266.println("AT");

  if(esp8266.find("OK")){
    connectWiFi();
    Serial.println("Connect to Internet");
  } else{
    Serial.println("Unable to connect to Internet");
  }
}

void loop() {
  run_barometer();
  run_dust();
  run_light();
  run_temperature();
  run_uv();

  updatebeat();
  delay(10000);
}

void run_barometer() {
  lcd.clear();
  lcd.println("run_barometer...");
  delay(2000);
  
  Serial.println("Begin run_barometer...");
  
  temp = bmp.readTemperature();
  String std_output = "Temp = " + String(temp) + " *C";
  Serial.println(std_output);
  
  lcd.clear();
  lcd.print("Temp = ");
  lcd.setCursor(0, 1);
  lcd.print(String(temp) + " *C");
  delay(2000);

  pressure = bmp.readPressure();
  std_output = "Pressure = " + String(pressure) + " Pa";
  Serial.print(std_output);
  
  lcd.clear();
  lcd.print("Pressure = ");
  lcd.setCursor(0, 1);
  lcd.print(String(pressure) + " Pa");
  delay(2000);

  altitude = bmp.readAltitude(1013.25);
  std_output = "Altitude = " + String(altitude) + " m";
  Serial.print(std_output);

  lcd.clear();
  lcd.print("Altitude = ");
  lcd.setCursor(0, 1);
  lcd.print(String(altitude) + " m");
  delay(2000);

  Serial.println("End run_barometer...");

  lcd.clear();
  lcd.println("Begin run_barometer...");
  delay(2000);
}

void run_dust() {
  lcd.clear();
  lcd.println("run_dust...");
  delay(2000);
  
  Serial.println("Begin run_dust...");
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) >= sampletime_ms) //if the sampel time = = 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; 
    Serial.print("Concentration = ");
    Serial.print(concentration);
    Serial.println(" pcs/0.01cf");
    Serial.println("\n");
    
    lcd.clear();
    lcd.print("Concentration = ");
    lcd.setCursor(0, 1);
    lcd.print(concentration);
    lcd.print(" pcs/0.01cf");
    delay(2000);
    lowpulseoccupancy = 0;
    starttime = millis();
  }
  Serial.println("End run_dust...");
  delay(2000);
}

void run_light() {
  lcd.clear();
  lcd.println("run_dust...");
  
  Serial.println("Begin run_light...");
  light=analogRead(A0);
  Serial.println("Light = " + String(light));
  lcd.clear();
  lcd.print("Light = ");
  lcd.setCursor(0, 1);
  lcd.print(light);
  delay(2000);
  Serial.println("End run_light...");
  delay(2000);
}

void run_temperature() {
  lcd.clear();
  lcd.println("run_temperature...");
  
  Serial.println("Begin run_temperature...");
  delay(2000);
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp2= dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp2);
  Serial.println(" Celsius");

  lcd.clear();
  lcd.print("Humidity = ");
  lcd.setCursor(0, 1);
  lcd.print(hum);
  delay(2000);

  lcd.clear();
  lcd.print("Temp2 = ");
  lcd.setCursor(0, 1);
  lcd.print(temp2);
  delay(2000);

  Serial.println("End run_temperature...");
  delay(2000);
}

void run_uv() {
  lcd.clear();
  lcd.println("run_uv...");
  
    int sensorValue;
  long  sum=0;
  for(int i=0;i<1024;i++)
   {  
      sensorValue=analogRead(A1);
      sum=sensorValue+sum;
      delay(2);
   }   
 sum = sum >> 10;
 Vsig = sum*4980.0/1023.0; // Vsig is the value of voltage measured from the SIG pin of the Grove interface
 Serial.print("The voltage value: ");
 Serial.print(Vsig);
 Serial.print(" mV    --   ");

  lcd.clear();
  lcd.print("Voltage = ");
  lcd.setCursor(0, 1);
  lcd.print(Vsig);
  lcd.print(" mV");
  delay(2000);
 
   delay(2000);
}

boolean connectWiFi(){
  Serial.println("AT+CWMODE=1");
  esp8266.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  esp8266.println(cmd);
  delay(5000);
  if(esp8266.find("OK")){
    Serial.println("OK");
    return true;    
  }else{
    return false;
  }
}

void updatebeat(){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  esp8266.println(cmd);
  delay(2000);
  if(esp8266.find("Error")){
    return;
  }
  cmd = msg ;
  cmd += "&field1=";   
  cmd += temp;
  cmd += "&field2=";   
  cmd += pressure;
  cmd += "&field3=";   
  cmd += altitude;
  cmd += "&field4=";   
  cmd += concentration;
  cmd += "&field5=";   
  cmd += light;
  cmd += "&field6=";   
  cmd += hum;
  cmd += "&field7=";   
  cmd += temp2;
  cmd += "&field8=";   
  cmd += Vsig;
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  esp8266.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  esp8266.println(cmd.length());
  Serial.print(cmd);
  esp8266.print(cmd);
}
