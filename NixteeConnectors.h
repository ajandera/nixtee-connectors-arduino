#ifndef NIXTEE_CLIENT_H
#define NIXTEE_CLIENT_H

#include <Arduino.h>
#include <WiFi.h>          // Replace with WiFiNINA.h if using WiFiNINA
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

class NixteeClient {
public:
    NixteeClient(const char* api_url, WiFiClient& wifi_client);

    bool authorize(const char* email, const char* password);
    String train(const char* model_data);
    String save(const char* model_id, const char* data);
    String load(const char* model_id);
    String predict(const char* model_id, const char* input_data);
    String classify(const char* model_id, const char* input_data);

private:
    String _api_url;
    WiFiClient& _wifi_client;
    HttpClient _http_client;
    String _token;

    String authorizedRequest(const char* method, const char* endpoint, const char* payload = nullptr);
};

#endif
