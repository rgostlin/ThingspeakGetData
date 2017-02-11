#include <ESP8266WiFi.h>
 
const char* ssid     = "SHAW-EA9FCB";
const char* password = "274955397";
 
const char* host = "api.thingspeak.com";
 
int value = 1; 
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
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
  
}//end setup
  
void loop() {
  delay(5000);
  String data = "Not Found";
   
  //Serial.print("Connecting to ");
  //Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient Client;
  const int httpPort = 80;
  if (!Client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/channels/185443/feeds/last.txt";
  //Serial.print("Requesting URL: ");
  //Serial.println(host + url);
  //Serial.println(String("TRY: ") + value + ".");
  
  // This will send the request to the server
 //Client.print(String("GET ") + url + "&headers=false" + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  Client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(Client.available()){
  String line = Client.readStringUntil('\r');
  Serial.println(line);
  int StrLen = line.length();
  if (line.charAt(1) == '{'){                  //The data coming from thingspeak always starts a line with the {
    for (int i=0; i <= StrLen-6; i++){ 
      if (line.substring(i,i+6) == "field1") {
        data = line.substring(i+9,i+14);
      }
    } 
  }
  }
  Serial.println(data);
  //Serial.println("");
  //Serial.println(String("Try nr. ") + value + " is finished.");
  //Serial.println("Waiting for next try...");
  //Serial.println("");
  value = value + 1;
  delay(15000);
}
 

