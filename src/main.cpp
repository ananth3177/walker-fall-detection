#include <WiFi.h>
#include <HTTPClient.h>
//WIFI info
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const char* IFTT_EVENT = "walker_fall";
const char* IFTT_KEY = "YOUR_IFTTT_KEY";
//

#define BUTTON_PIN 33; //gpio button trigger for sensor test

void setup(){
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    //connect wifi
    Serial.print("connecting wifi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.println(".");
    }
    Serial.println("\nWi-Fi connected!");

}

void loop(){
    if(digitalRead(BUTTON_PIN)== LOW) {
        Serial.println("Button pressed -> sending SMS");
        sendIFTTT("Button pressed - sending SMS");
        delay(3000);
    }

}

void sendIFTTT(String msg){
    if(WiFi.status() == WL_CONNECTED){
        HTTPClient http;
        String url = String("https://maker.ifttt.com/trigger") + IFTTT_EVENT + "/with/key" + IFTTT_KEY;
        http.begin(url);
        http.addHeader("Content-Type", "application/json");
        String body = String("{\"value1\":\"")+ msg + "\"}";
        int code = http.POST(body);

        Serial.print("HTTP Response code: ");
        Serial.println(code);
        http.end();
    }
        else{
            Serial.println("Wi-Fi not connected");
        }


    
    
}
