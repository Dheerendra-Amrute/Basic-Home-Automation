#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR__AUTH_TOKEN"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>  
#include <ZMPT101B.h>

// WiFi Credentials
char ssid[] = "Your hotspot name";
char pass[] = "Your hotspot passward";

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
}
#define BUZZER_PIN 27  //GPIO27
// Touch Sensor Pins
#define TOUCH_PIN_1 T4  // GPIO13
#define TOUCH_PIN_2 T9  // GPIO32

// Relay Control Pins
#define RELAY_PIN_1 25
#define RELAY_PIN_2 26

// DHT11 Configuration
#define DHTPIN 15      // GPIO15 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//voltageconfiguration

ZMPT101B voltageSensor(35, 50.0);
int volt;

// Touch Threshold
const int touchThreshold = 20;
int touchVal1, touchVal2;

// Relay States
bool relay1State = false;
bool relay2State = false;

// Debounce variables
unsigned long lastTouch1 = 0;
unsigned long lastTouch2 = 0;
const unsigned long debounceDelay = 500;

// Sensor Update Interval
unsigned long previousMillis = 0;
const long interval = 2000;  // Update every 2 seconds

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);
  digitalWrite(RELAY_PIN_2, HIGH);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); 
  dht.begin();
  voltageSensor.setSensitivity(500.0f);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, syncBlynk);
}

void loop() {
  Blynk.run();
  timer.run();
  handleTouchInputs();
  readDHTSensor(); 
  voltage();
  printonserial();
  safetyCheck();
}

void handleTouchInputs() {
  touchVal1 = touchRead(TOUCH_PIN_1);
  touchVal2 = touchRead(TOUCH_PIN_2);
  // Handle Touch 1
  if (touchVal1 < touchThreshold && millis() - lastTouch1 > debounceDelay) {
    toggleRelay(1);
    lastTouch1 = millis();
    Blynk.virtualWrite(V0, relay1State);
  }
  // Handle Touch 2
  if (touchVal2 < touchThreshold && millis() - lastTouch2 > debounceDelay) {
    toggleRelay(2);
    lastTouch2 = millis();
    Blynk.virtualWrite(V1, relay2State);
  }
}

void toggleRelay(int relayNumber) {
  if (relayNumber == 1) {
    relay1State = !relay1State;
    //Relay 1
    if (relay1State) {
      digitalWrite(RELAY_PIN_1, LOW);  // Turn relay ON (active-low)
    } else {
      digitalWrite(RELAY_PIN_1, HIGH); // Turn relay OFF
    }
    Serial.println("Relay 1 Toggled");
  } else {
    relay2State = !relay2State;
    // Relay 2
    if (relay2State) {
      digitalWrite(RELAY_PIN_2, LOW);  // Turn relay ON (active-low)
    } else {
      digitalWrite(RELAY_PIN_2, HIGH); // Turn relay OFF
    }
    Serial.println("Relay 2 Toggled");
  }
}


void readDHTSensor() {
  static unsigned long lastUpdate = 0;
  
  if (millis() - lastUpdate > 2000) { 
    float h = dht.readHumidity();
    float t = dht.readTemperature();  // Celsius
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    String sensorData = String(t, 1) + "°C, " + String(h, 1) + "%";
    
    // Send to Blynk Virtual Pin V2
    Blynk.virtualWrite(V2, sensorData);
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print("°C\tHumidity: ");
    Serial.print(h);
    Serial.println("%");

    lastUpdate = millis();
  }
}

void voltage(){
  float voltage = voltageSensor.getRmsVoltage();
  (voltage > 50) ? volt = voltage : volt = 0;
}
void printonserial(){
  Serial.print("Voltage: ");
  Serial.print(volt);
  Serial.println(" V");
}

void safetyCheck() {
  float voltage = voltageSensor.getRmsVoltage();
  float temperature = dht.readTemperature();
  // Check temperature threshold for buzzer
  if (temperature > 50) {
    digitalWrite(BUZZER_PIN, HIGH);
    // Optional: Send alerts to Blynk
    Blynk.virtualWrite(V3, "SAFETY ALERT: High Temperature!");
    Serial.println("Safety Alert Triggered: Temperature Exceeded!");
  } else {
    // Safe conditions: Turn off the buzzer
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Voltage check remains for relay cutoff
  if ((voltage > 50 && voltage < 190) || (voltage > 240)) {
    // Turn off all relays for safety
    digitalWrite(RELAY_PIN_1, HIGH);
    digitalWrite(RELAY_PIN_2, HIGH);
    Blynk.virtualWrite(V3, "Relay Cutoff: Voltage Out of Range");
    Serial.println("Relay Cutoff Triggered: Voltage Out of Range!");
  }
}

// Sync Blynk with current states
void syncBlynk() {
  Blynk.virtualWrite(V0, relay1State);
  Blynk.virtualWrite(V1, relay2State);
  Blynk.virtualWrite(V3, volt);
}

// Blynk Virtual Pin Handlers
BLYNK_WRITE(V0) {
  int state = param.asInt();
  if (state != relay1State) {
    toggleRelay(1);
  }
}

BLYNK_WRITE(V1) {
  int state = param.asInt();
  if (state != relay2State) {
    toggleRelay(2);
  }
}