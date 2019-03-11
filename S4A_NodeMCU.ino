#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "FrenGP_S4A";
const char* password = "RobotTesting";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
int LEDPin = 13;
void setup(void) {
  //the HTML of the web page
  page = "<h1>Robot control</h1><p><a href=\"StateL\"><button>Left</button></a>&nbsp;<a href=\"StateF\"><button>Fwd</button></a>&nbsp<a href=\"StateR\"><button>Right</button></a></p><p>&nbsp&nbsp&nbsp&nbsp<a href=\"StateB\"><button>Backward</button></a></p>";

  pinMode(FPin, OUTPUT);
  digitalWrite(FPin, LOW);

  delay(1000);
  Serial.begin(115200);
  WiFi.softAP(ssid, password); //begin WiFi access point
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Created hotspot: ");
  Serial.print(ssid);
  Serial.print(" Passowrd: ");
  Serial.println(password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.send(200, "text/html", page);
    Serial.println("On default page");
  });
  server.on("/StateF", []() {
    server.send(200, "text/html", page);
    Serial.println("Forward");
  });
  server.on("/StateR", []() {
    server.send(200, "text/html", page);
    Serial.println("Right");
  });
  server.on("/StateL", []() {
    server.send(200, "text/html", page);
    Serial.println("Left");
  });
  server.on("/StateB", []() {
    server.send(200, "text/html", page);
    Serial.println("Backward");
  });
  server.on("/StateS", []() {
    server.send(200, "text/html", page);
    Serial.println("Stop");
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  server.handleClient();
  
}
