/*
 * WiFi Distance Data Receiver Example
 * 
 * This example shows how to receive distance data from a DW3000 UWB node
 * that is transmitting distance measurements via WiFi.
 * 
 * Hardware: ESP32 Development Board
 * 
 * The transmitting UWB node sends JSON packets like:
 * {"node":10,"distance":1.23,"timestamp":12345}
 */

#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>

// WiFi credentials - change these to match your network
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// UDP settings
const int udpPort = 8888;  // Must match the port used by UWB transmitter
WiFiUDP udp;

// Buffer for receiving UDP packets
char packetBuffer[255];

void setup() {
  Serial.begin(115200);
  Serial.println("UWB Distance Data Receiver");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("WiFi connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Listening on port: ");
  Serial.println(udpPort);
  
  // Start UDP
  udp.begin(udpPort);
  Serial.println("UDP server started");
  Serial.println("Waiting for distance data...");
  Serial.println("Format: [Timestamp] Node ID: Distance");
  Serial.println("----------------------------------------");
}

void loop() {
  // Check for incoming UDP packets
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    // Read the packet
    int len = udp.read(packetBuffer, sizeof(packetBuffer) - 1);
    if (len > 0) {
      packetBuffer[len] = '\0';  // Null terminate
    }
    
    // Parse JSON data
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, packetBuffer);
    
    if (!error) {
      // Extract data
      int nodeId = doc["node"];
      double distance = doc["distance"];
      unsigned long timestamp = doc["timestamp"];
      
      // Display the data
      Serial.printf("[%lu] Node %d: %.2f m\n", timestamp, nodeId, distance);
      
      // Optional: Process the distance data here
      // Example: Store in array, send to cloud, trigger actions, etc.
      processDistanceData(nodeId, distance, timestamp);
    } else {
      Serial.print("JSON parse error: ");
      Serial.println(error.c_str());
      Serial.print("Raw data: ");
      Serial.println(packetBuffer);
    }
  }
  
  delay(10);  // Small delay to prevent watchdog issues
}

void processDistanceData(int nodeId, double distance, unsigned long timestamp) {
  // Example processing function
  // You can customize this based on your application needs
  
  // Example 1: Alert if distance is too close
  if (distance < 0.5) {
    Serial.printf("WARNING: Node %d is very close (%.2f m)!\n", nodeId, distance);
  }
  
  // Example 2: Log data (you could save to SD card, send to cloud, etc.)
  // logDistanceData(nodeId, distance, timestamp);
  
  // Example 3: Control other devices based on distance
  // if (distance < 1.0) {
  //   digitalWrite(LED_PIN, HIGH);  // Turn on LED when close
  // } else {
  //   digitalWrite(LED_PIN, LOW);   // Turn off LED when far
  // }
}

void printWiFiStatus() {
  // Utility function to print WiFi connection status
  Serial.print("WiFi Status: ");
  switch (WiFi.status()) {
    case WL_CONNECTED:
      Serial.println("Connected");
      break;
    case WL_NO_SHIELD:
      Serial.println("No WiFi shield");
      break;
    case WL_IDLE_STATUS:
      Serial.println("Idle");
      break;
    case WL_NO_SSID_AVAIL:
      Serial.println("No SSID available");
      break;
    case WL_SCAN_COMPLETED:
      Serial.println("Scan completed");
      break;
    case WL_CONNECT_FAILED:
      Serial.println("Connection failed");
      break;
    case WL_CONNECTION_LOST:
      Serial.println("Connection lost");
      break;
    case WL_DISCONNECTED:
      Serial.println("Disconnected");
      break;
    default:
      Serial.println("Unknown");
      break;
  }
}