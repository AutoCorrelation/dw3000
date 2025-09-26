#pragma once

// WiFi Configuration
// Update these settings for your network and target device

// WiFi network credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Target device settings
#define TARGET_IP "192.168.1.100"    // IP address of receiving ESP32
#define TARGET_PORT 8888             // UDP port number

// WiFi connection timeout (milliseconds)
#define WIFI_TIMEOUT_MS 10000

// Enable/disable WiFi functionality
// Set to 0 to disable WiFi transmission (for testing UWB only)
#define ENABLE_WIFI_TRANSMISSION 1