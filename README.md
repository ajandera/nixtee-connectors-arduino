# NixteeClient for Arduino

This repository provides an Arduino library to interact with the Nixtee API, enabling tasks like user authentication, model training, saving/loading models, predictions, and classifications. The library replicates the functionality of the Python `nixtee-connectors-python` library in an Arduino-compatible way.

---

## Features

- **Token-based Authentication**: Login to the Nixtee API using email and password.
- **Model Management**:
  - Train models
  - Save and load models
  - Make predictions
  - Classify inputs
- **JSON Handling**: Uses the ArduinoJson library for efficient JSON parsing and creation.
- **HTTP Communication**: Supports GET and POST requests using ArduinoHttpClient.

---

## Installation

1. Clone or download this repository.
2. Copy the `NixteeClient` folder into your Arduino `libraries` directory.
   - On most systems, this is located in `~/Documents/Arduino/libraries/`.
3. Open the Arduino IDE and ensure the library appears under **Sketch > Include Library > Contributed Libraries**.

### Dependencies

Install the following libraries via the Arduino Library Manager (**Tools > Manage Libraries...**):

- **WiFi** or **WiFiNINA** (depending on your board)
- **ArduinoHttpClient**
- **ArduinoJson**

---

## Getting Started

### Example Usage

Here is a basic example sketch that demonstrates how to use the `NixteeClient` library:

```cpp
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
```

---

## API Reference

### Constructor

```cpp
NixteeClient(const char* api_url, WiFiClient& wifi_client);
```
- `api_url`: The base URL of the Nixtee API (e.g., `"api.nixtee.com"`).
- `wifi_client`: A reference to an initialized WiFi client.

### Methods

#### `bool authorize(const char* email, const char* password)`
Logs in to the API and retrieves an authorization token.

- `email`: User's email address.
- `password`: User's password.
- **Returns**: `true` on success, `false` on failure.

#### `String train(const char* model_data)`
Sends a training request to the API.

- `model_data`: JSON string containing the model's training data.
- **Returns**: The API's response as a JSON string.

#### `String save(const char* model_id, const char* data)`
Saves the model with the given ID.

- `model_id`: The ID of the model to save.
- `data`: JSON string containing the data to save.
- **Returns**: The API's response as a JSON string.

#### `String load(const char* model_id)`
Loads the model with the given ID.

- `model_id`: The ID of the model to load.
- **Returns**: The API's response as a JSON string.

#### `String predict(const char* model_id, const char* input_data)`
Sends a prediction request for the specified model.

- `model_id`: The ID of the model to use.
- `input_data`: JSON string containing the input data.
- **Returns**: The API's response as a JSON string.

#### `String classify(const char* model_id, const char* input_data)`
Sends a classification request for the specified model.

- `model_id`: The ID of the model to use.
- `input_data`: JSON string containing the input data.
- **Returns**: The API's response as a JSON string.

---

## Contributing

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes.
4. Push to your fork and submit a pull request.

---

## License

This library is licensed under the MIT License. See the `LICENSE` file for details.

---

## Troubleshooting

- **WiFi Connection Issues**: Ensure your credentials are correct and that the board supports the chosen WiFi library.
- **API Errors**: Check your API URL, credentials, and JSON formatting.
- **Memory Limitations**: Reduce JSON document size if you encounter memory issues on boards with limited RAM.

---

