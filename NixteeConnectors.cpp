#include "NixteeClient.h"

NixteeClient::NixteeClient(const char* api_url, WiFiClient& wifi_client)
    : _api_url(api_url), _wifi_client(wifi_client), _http_client(wifi_client, api_url, 80) {}

bool NixteeClient::authorize(const char* email, const char* password) {
    String endpoint = "/auth/login";
    String payload = String("{\"email\":\"") + email + "\",\"password\":\"" + password + "\"}";

    _http_client.beginRequest();
    _http_client.post(endpoint);
    _http_client.sendHeader("Content-Type", "application/json");
    _http_client.sendHeader("Content-Length", payload.length());
    _http_client.print(payload);
    _http_client.endRequest();

    int statusCode = _http_client.responseStatusCode();
    String response = _http_client.responseBody();

    if (statusCode == 200) {
        DynamicJsonDocument doc(512);
        deserializeJson(doc, response);
        _token = doc["token"].as<String>();
        return true;
    } else {
        Serial.print("Authorization failed: ");
        Serial.println(response);
        return false;
    }
}

String NixteeClient::authorizedRequest(const char* method, const char* endpoint, const char* payload) {
    if (_token.length() == 0) {
        Serial.println("Error: Missing authorization token.");
        return "";
    }

    _http_client.beginRequest();
    if (String(method) == "POST") {
        _http_client.post(endpoint);
    } else if (String(method) == "GET") {
        _http_client.get(endpoint);
    }
    _http_client.sendHeader("Authorization", "Bearer " + _token);
    _http_client.sendHeader("Content-Type", "application/json");
    if (payload) {
        _http_client.sendHeader("Content-Length", String(strlen(payload)));
        _http_client.print(payload);
    }
    _http_client.endRequest();

    int statusCode = _http_client.responseStatusCode();
    String response = _http_client.responseBody();

    if (statusCode >= 200 && statusCode < 300) {
        return response;
    } else {
        Serial.print("Request failed: ");
        Serial.println(response);
        return "";
    }
}

String NixteeClient::train(const char* model_data) {
    return authorizedRequest("POST", "/train", model_data);
}

String NixteeClient::save(const char* model_id, const char* data) {
    String endpoint = String("/models/") + model_id + "/save";
    return authorizedRequest("POST", endpoint.c_str(), data);
}

String NixteeClient::load(const char* model_id) {
    String endpoint = String("/models/") + model_id + "/load";
    return authorizedRequest("GET", endpoint.c_str());
}

String NixteeClient::predict(const char* model_id, const char* input_data) {
    String endpoint = String("/models/") + model_id + "/predict";
    return authorizedRequest("POST", endpoint.c_str(), input_data);
}

String NixteeClient::classify(const char* model_id, const char* input_data) {
    String endpoint = String("/models/") + model_id + "/classify";
    return authorizedRequest("POST", endpoint.c_str(), input_data);
}
