#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <U8g2lib.h>
#include <string>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, D1, D2);
int x = 3;
WiFiClientSecure client;
HTTPClient http;
// const char* gql = R"({"query":"{stop(id:"HSL:1100206"){name stoptimesWithoutPatterns(numberOfDepartures:10){realtimeDeparture headsign trip{route{shortName}}}}}"})";
// const char* gql = R"({"query":"{stop(id:\"HSL:1100206\"){name stoptimesWithoutPatterns(numberOfDepartures:10){realtimeDeparture headsign trip{route{shortName}}}}}"})";
const char* gql = R"({"query":"{stop(id:\"HSL:1100206\"){name stoptimesWithoutPatterns(numberOfDepartures:2){realtimeDeparture headsign trip{route{shortName}}}}}"})";



void setup() {
  Serial.begin(9600);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.begin("Hive Stud", "shifterambiancefinlesskilt");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected!!!!!!");
  }
  u8g2.begin();
  client.setInsecure();
  http.begin(client, "https://api.digitransit.fi/routing/v2/hsl/gtfs/v1");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("digitransit-subscription-key", "xxxx"); // Insert your digitransit api key to the second argument.
 /*  int httpcode = http.POST((uint8_t *)gql, strlen(gql));
  if (httpcode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.printf("HTTP POST failed %s\n", http.errorToString(httpcode));
  } */
}

void loop() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  int httpCode = http.POST((uint8_t *)gql, strlen(gql));
  if (httpCode <= 0) {
    u8g2.clearBuffer();
    u8g2.drawStr(32, 32, "Failed to fetch data :(");
    u8g2.sendBuffer();
  }
  else {
    u8g2.clearBuffer();
    String response = http.getString();
    const size_t capacity = 4096;
    DynamicJsonDocument doc(capacity);

    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print(F("JSON parse failed: "));
      Serial.println(error.f_str());
    }
    else {
      const char* stopName = doc["data"]["stop"]["name"];
      u8g2.drawStr(2, 10, stopName);
      u8g2.sendBuffer();
      JsonArray departures = doc["data"]["stop"]["stoptimesWithoutPatterns"];
      int x = 2;
      int y = 25;
      for (JsonObject d : departures) {
        int arrivalTime = d["realtimeDeparture"];
        int arrivalHour = arrivalTime / 3600;
        int arrivalMin = (arrivalTime % 3600) / 60;
        String time("Leaving at: " + String(arrivalHour) + ":" + String(arrivalMin));
        u8g2.drawStr(x, y + 10, time.c_str());
        const char* headsign = d["headsign"];
        String sign(headsign);
        const char* busName = d["trip"]["route"]["shortName"];
        String name(busName);
        name += " " + sign;
        u8g2.drawStr(x, y, name.c_str());
        if (y < 128) {
          u8g2.sendBuffer();
        }
        y += 25;
      }
    }
  }
  delay(60000);
  u8g2.clearBuffer();
}
