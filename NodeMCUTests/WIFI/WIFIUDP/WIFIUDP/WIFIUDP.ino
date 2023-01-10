#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "firstClass";
const char* password = "11111111";

WiFiUDP Udp;
unsigned int port = 25666;
char packet[255];

IPAddress ip(192, 168, 43, 20);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.hostname("YVRB-01");
  WiFi.config(ip, gateway, subnet);

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connection Successful");
  Udp.begin(port);
  Serial.printf("Listener started at IP %s, at port %d", WiFi.localIP().toString().c_str(), port);
  Serial.println();
}

void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.printf("Received %d bytes from %s, port %d", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(packet, 255);
    if (len > 0)
    {
      packet[len] = 0;
    }
    Serial.printf("UDP packet contents: %s", packet);
    Serial.println();
  }

  Udp.beginPacket (Udp.remoteIP(), Udp.remotePort());
  Udp.write("Important data");
  Udp.endPacket();

  delay(300);
}
