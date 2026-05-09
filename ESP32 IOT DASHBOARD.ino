#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

// --- 1. WiFi Credentials ---
const char* ssid = "U wantaa?";
const char* password = "in return what do i get";

// --- 2. Pin Definitions ---
#define DHTPIN 4       // HW-507 (S) Pin
#define DHTTYPE DHT11  // Change to DHT22 if your HW-507 has a white sensor
#define RELAY_PIN 10   // HW-482 (S) Pin

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);

// --- 3. HTML & CSS Dashboard ---
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head>
  <title>ESP32-C3 IoT Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: 'Segoe UI', sans-serif; text-align: center; background: #f4f7f6; color: #333; }
    .card { background: white; padding: 20px; border-radius: 15px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); display: inline-block; margin-top: 50px; width: 300px; }
    h1 { color: #2c3e50; }
    .data { font-size: 1.5rem; font-weight: bold; color: #2980b9; margin: 10px 0; }
    .btn { background: #e74c3c; color: white; border: none; padding: 15px 30px; font-size: 18px; border-radius: 10px; cursor: pointer; transition: 0.3s; }
    .btn:hover { background: #c0392b; }
    .btn:active { transform: scale(0.95); }
  </style>
</head>
<body>
  <div class="card">
    <h1>IoT Control</h1>
    <p>Temperature: <span id="temp" class="data">--</span> &deg;C</p>
    <p>Humidity: <span id="humi" class="data">--</span> %</p>
    <hr>
    <button class="btn" onclick="toggleRelay()">TOGGLE RELAY</button>
  </div>

<script>
// Function to toggle the HW-482 Relay
function toggleRelay() {
  fetch('/toggle');
}

// Update sensors every 2 seconds without refreshing
setInterval(function() {
  fetch('/data').then(response => response.json()).then(json => {
    document.getElementById('temp').innerHTML = json.temp;
    document.getElementById('humi').innerHTML = json.humi;
  });
}, 2000);
</script>
</body></html>)rawliteral";

// --- 4. Logic Functions ---
void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start with Relay OFF
  dht.begin();
  WiFi.setSleep(false); // Disables Wi-Fi power save mode
  WiFi.mode(WIFI_STA);  // Explicitly set to Station mode
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Server Route: Main Page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Server Route: Toggle Relay
  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN));
    request->send(200, "text/plain", "OK");
  });

  // Server Route: Get JSON Data
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (isnan(t) || isnan(h)) {
      request->send(200, "application/json", "{\"temp\":\"Err\",\"humi\":\"Err\"}");
    } else {
      String json = "{\"temp\":" + String(t) + ",\"humi\":" + String(h) + "}";
      request->send(200, "application/json", json);
    }
  });

  server.begin();
}

void loop() {
  // ESPAsyncWebServer handles everything in the background!
}
