# WiFi Distance Data Transmission

This directory contains examples for receiving distance data from DW3000 UWB nodes via WiFi.

## Overview

The main DW3000 UWB ranging code in `src/dm_sstwr/uwb.cpp` has been enhanced with WiFi functionality to transmit distance measurements to other ESP32 devices over WiFi.

## How it Works

1. **UWB Node (Transmitter)**: The DW3000 ESP32 calculates distances using UWB ranging and sends the data via WiFi UDP packets
2. **Receiver ESP32**: Another ESP32 receives and processes the distance data

## Data Format

Distance data is transmitted as JSON over UDP:
```json
{
  "node": 10,
  "distance": 1.23,
  "timestamp": 12345
}
```

- `node`: UWB node ID (e.g., 10, 14, 18, etc.)
- `distance`: Distance in meters (2 decimal places)
- `timestamp`: Arduino millis() timestamp

## Setup Instructions

### 1. Configure the UWB Transmitter

In `src/dm_sstwr/uwb.cpp`, update these WiFi settings:

```cpp
const char* ssid = "YOUR_WIFI_SSID";        // Your WiFi network name
const char* password = "YOUR_WIFI_PASSWORD"; // Your WiFi password
const char* target_ip = "192.168.1.100";    // IP of receiving ESP32
const int target_port = 8888;               // UDP port (must match receiver)
```

### 2. Setup the Receiver ESP32

1. Upload `wifi_receiver.ino` to your receiving ESP32
2. Update WiFi credentials in the receiver code
3. Note the IP address assigned to the receiver
4. Update `target_ip` in the transmitter code to match

### 3. Arduino IDE Library Requirements

For the receiver, install these libraries in Arduino IDE:
- **ArduinoJson** by Benoit Blanchon (for JSON parsing)

## Usage

1. Power on both ESP32 devices
2. The UWB transmitter will connect to WiFi and start ranging
3. The receiver will display incoming distance data:
```
[12345] Node 10: 1.23 m
[12367] Node 14: 2.45 m
[12389] Node 18: 0.87 m
```

## Network Configuration

- Both devices must be on the same WiFi network
- Use a static IP for the receiver for consistent communication
- Default UDP port is 8888 (can be changed in both transmitter and receiver)

## Customization

The receiver example includes a `processDistanceData()` function where you can:
- Store data to SD card
- Send data to cloud services
- Control other devices based on distance
- Implement alerts for proximity detection

## Troubleshooting

1. **No data received**: Check WiFi credentials and IP addresses
2. **JSON parse errors**: Verify UDP packet isn't corrupted
3. **Connection issues**: Use WiFi signal strength indicators
4. **Performance**: UDP is fast but not guaranteed delivery; consider TCP for critical applications

## Performance Notes

- WiFi transmission is non-blocking to avoid interfering with UWB timing
- Failed WiFi sends are silently ignored to maintain UWB performance
- Consider the network latency when using distance data for real-time applications