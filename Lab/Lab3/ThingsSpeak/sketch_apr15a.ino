#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial esp8266(9,10); 




#define SSID "Pixel"     // "SSID-WiFiname" 
#define PASS "12345678"       // "password"
#define IP "184.106.153.149"// thingspeak.com ip
String msg = "GET /update?key=4Q9EJB5HO1J245FQ"; //change it with your api key like "GET /update?key=Your Api Key"

//Libraries
#include <DHT.h>

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
float temp; //Stores temperature value


void setup() {
  Serial.begin(115200);
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
  run_temperature();
  updatebeat();
  delay(10000);
}

void run_temperature() {  
  Serial.println("Begin run_temperature...");
  delay(2000);
  //Read data and store it to variables hum and temp
  temp= dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  Serial.println("End run_temperature...");
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
 
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  esp8266.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  esp8266.println(cmd.length());
  Serial.print(cmd);
  esp8266.print(cmd);
}
