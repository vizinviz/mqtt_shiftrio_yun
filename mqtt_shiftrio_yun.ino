// This example uses an Arduino Yun or a Yun-Shield
// and the MQTTClient to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <Bridge.h>
#include <BridgeClient.h>
#include <MQTT.h>

BridgeClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("connecting...");
  while (!client.connect("arduino-yun-vizinviz", "ac4b9437", "253599623a0a0034")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!!!!!");

 client.subscribe("/velo");
  client.subscribe("/hello");
  client.subscribe("/temperature");
 
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Bridge.begin();
  Serial.begin(115200);
Serial.println("\nhi");
  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 2000) {
    lastMillis = millis();
    client.publish("/hello", "world");
    client.publish("/velo", "moto");
    String temp = "";
    temp += random(20,30);
    client.publish("/temperature", temp);
  }


}
