#include <WiFi.h> // Replace with WiFiNINA.h if needed
#include "NixteeClient.h"

// WiFi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// API URL
const char* api_url = "api.nixtee.com";

// Initialize the NixteeClient
WiFiClient wifi_client;
NixteeClient nixtee(api_url, wifi_client);

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Connect to WiFi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");

    // Authorize with the server
    if (nixtee.authorize("your_email@example.com", "your_password")) {
        Serial.println("Authorization successful!");

        // Train a model
        String response = nixtee.train("{\"model_name\": \"example_model\"}");
        Serial.println("Train response: " + response);

        // Predict using the model
        response = nixtee.predict("model_id", "{\"input\": \"example_input\"}");
        Serial.println("Predict response: " + response);
    } else {
        Serial.println("Authorization failed.");
    }
}

void loop() {
    // Nothing to do here
}
