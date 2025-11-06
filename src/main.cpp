#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"
#include <TFT_eSPI.h>
#include <Arduino.h>
TFT_eSPI tft;

#define BUTTON_PIN 33 //gpio button trigger for sensor test

void sendIFTTT(String msg){
    if(WiFi.status() == WL_CONNECTED){
        HTTPClient http;

        String url = String("https://maker.ifttt.com/trigger/") + IFTTT_EVENT + "/with/key/" + IFTTT_KEY;
        //Serial.print("URL = ["); //Serial.print(url); //Serial.print("]");
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

void setup(){
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    //connect wifi
    // Serial.print("ssid=");
    // Serial.print(WIFI_SSID);
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

