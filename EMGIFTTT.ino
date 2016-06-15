#include <ESP8266WiFi.h>
 
const char* ssid     = "YourSSID";
const char* password = "YourPSWD";


const char* host = "maker.ifttt.com";
const String IFTTT_Event = "Your event name"; 
const int puertoHost = 80;
const String Maker_Key = "Your maker key";
String conexionIF = "POST /trigger/"+IFTTT_Event+"/with/key/"+Maker_Key +" HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" + 
                    "Content-Type: application/x-www-form-urlencoded\r\n\r\n";

 
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
 
void loop() {
  int level = analogRead(A0);
  if(level>500){
  mandarNot();
  Serial.print("ifttt"); Serial.println(level); 
  }
}

void mandarNot(){
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  if (!client.connect(host, puertoHost)) {
    Serial.println("Connection failed");
    return;
  }

  client.print(conexionIF);
  delay(10);
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("Closing connection");
}


