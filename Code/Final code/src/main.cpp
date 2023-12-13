#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <PubSubClient.h>
#include <WiFi.h>

#include <ArduinoJson.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "effects.h"
#include "info.h"

const char* mqtt_rgbw ="PM/RL/RL/rgbw";
const char* mqtt_command ="PM/RL/RL/command";
const char* mqtt_effect ="PM/RL/RL/effect";
const char* mqtt_brightness ="PM/RL/RL/brightness";

const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

#define PIN_LEDSTRIP1 2
#define PIN_LEDSTRIP2 3
#define PIN_LEDSTRIP3 4
#define PIN_LEDSTRIP4 5
#define PIN_BUTTON_WHITE 1
#define PIN_BUTTON_RED 0

const int MIN_BRIGHTNESS = 10;
const int MAX_BRIGHTNESS = 60;
const int NUMPIXELS = 60;
const int DEBOUNCE_DELAY = 50;

Adafruit_NeoPixel ledstrip1 = Adafruit_NeoPixel(NUMPIXELS, PIN_LEDSTRIP1, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ledstrip2 = Adafruit_NeoPixel(NUMPIXELS, PIN_LEDSTRIP2, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ledstrip3 = Adafruit_NeoPixel(NUMPIXELS, PIN_LEDSTRIP3, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ledstrip4 = Adafruit_NeoPixel(NUMPIXELS, PIN_LEDSTRIP4, NEO_GRBW + NEO_KHZ800);

Adafruit_NeoPixel LEDSTRIPS[] = {ledstrip1, ledstrip2, ledstrip3, ledstrip4};
int NUM_LEDSTRIPS = 4;

int cycle = 0;
String currentEffect = EFFECTS[0];
String previousEffect = EFFECTS[0];
int delayTime = 0;
bool redButtonState = false;
bool redButtonPreviousState = false;
bool whiteButtonState = false;
bool whiteButtonPreviousState = false;

bool mqttCommandReceived = false;
String mqttCommand;

int receivedR = -1;
int receivedG = -1;
int receivedB = -1;
int receivedW = -1;

bool effectRunning = false;

const Color fillColor = {0, 255, 0, 0};
const int dropAmount = 31; 
const int dropLength = 3; 
const String waveColor = "blue"; 

int drops[dropAmount] = {0};

long hue = 0;


int GetEffectIndex(String effect);
void SwitchToNextEffect();
void SwitchToPreviousEffect();

TaskHandle_t redButtonTask, whiteButtonTask;

void redButtonThread(void *pvParameters) {
  while (1) {
    bool currentState = digitalRead(PIN_BUTTON_RED);
    vTaskDelay(10 / portTICK_PERIOD_MS);

    if (currentState != redButtonState) {
      redButtonState = currentState;
      if (currentState == HIGH) {
        SwitchToNextEffect();
      }
    }
  }
}

void whiteButtonThread(void *pvParameters) {
  while (1) {
    bool currentState = digitalRead(PIN_BUTTON_WHITE);
    vTaskDelay(10 / portTICK_PERIOD_MS); 

    if (currentState != whiteButtonState) {
      whiteButtonState = currentState;
      if (currentState == HIGH) {
        SwitchToPreviousEffect();
      }
    }
  }
}


void callback(char *topic, byte *payload, unsigned int length) {
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    messageTemp += (char)payload[i];
  }

  Serial.print("Received message on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(messageTemp);

  // If the message is a command for the LEDs
  if (String(topic) == mqtt_command) {
    mqttCommandReceived = true;
    mqttCommand = messageTemp;
  }
   else if (String(topic) == mqtt_brightness) {
    int brightness = messageTemp.toInt();
    if (brightness >= 0 && brightness <= 255) {
      for (int i = 0; i < NUM_LEDSTRIPS; i++) {
        LEDSTRIPS[i].setBrightness(brightness);
        LEDSTRIPS[i].show();
      }
    }
  }
  // If the message is on the RGBW topic
  else if (String(topic) == mqtt_rgbw) {
    // Parse the message as an RGBW color
    sscanf(messageTemp.c_str(), "%d,%d,%d,%d", &receivedR, &receivedG, &receivedB, &receivedW);
    effectRunning = false;
  }
  else  if (String(topic) == mqtt_effect) {
    if (messageTemp == "waveFade" || messageTemp == "rainEffect" || messageTemp == "sunriseEffect" || messageTemp == "rippleEffect" || messageTemp == "blinkingStarlight" || messageTemp == "fire" || messageTemp == "breathingEffect") {
      currentEffect = messageTemp;
      effectRunning = true;
      Serial.println("Current effect: " + currentEffect); 
    }
  }
  
}

void setup() {
  pinMode(PIN_BUTTON_RED, INPUT);
  pinMode(PIN_BUTTON_WHITE, INPUT);

  xTaskCreate(redButtonThread, "RedButtonTask", 1000, NULL, 1, &redButtonTask);
  xTaskCreate(whiteButtonThread, "WhiteButtonTask", 1000, NULL, 1, &whiteButtonTask);
  ledstrip1.begin();
  ledstrip2.begin();
  ledstrip3.begin();
  ledstrip4.begin();
  ledstrip1.setBrightness(30);
  ledstrip2.setBrightness(30);
  ledstrip3.setBrightness(30);
  ledstrip4.setBrightness(30);
  fillAll(LEDSTRIPS, NUM_LEDSTRIPS, {0, 0, 0, 0});
  ledstrip1.show();
  ledstrip2.show();
  ledstrip3.show();
  ledstrip4.show();

  currentEffect = EFFECTS[0];
  effectRunning = true;

  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // Set MQTT server and callback function
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Subscribe to the MQTT topic
  client.subscribe(mqtt_rgbw);
  client.subscribe(mqtt_effect);
  client.subscribe(mqtt_command);
  client.subscribe(mqtt_brightness);
}

void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect("RL", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT broker");

      // Subscribe to the MQTT topic after reconnection
      client.subscribe(mqtt_rgbw);
      client.subscribe(mqtt_effect);
      client.subscribe(mqtt_command); 
      client.subscribe(mqtt_brightness);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retry in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  
  // Reconnect to MQTT broker if necessary
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

   if(mqttCommandReceived){
    if (mqttCommand == "ON") {
       Serial.println("Received MQTT command: ON");
      // Start the first effect
      currentEffect = "rainEffect";
      previousEffect = "";
    } else if (mqttCommand == "OFF") {
      Serial.println("Received MQTT command: OFF");
      // Turn off the LEDs
      fillAll(LEDSTRIPS, NUM_LEDSTRIPS, {0, 0, 0, 0});
      ledstrip1.show();
      ledstrip2.show();
      ledstrip3.show();
      ledstrip4.show();
      currentEffect = "";
  }
    mqttCommandReceived = false;
    } else if (receivedR != -1 && receivedG != -1 && receivedB != -1 && receivedW != -1) {
  // Create a Color object from the received RGBW values
  Color receivedColor = {receivedR, receivedG, receivedB, receivedW};
  // Set all LEDs to the received color
  fillAll(LEDSTRIPS, NUM_LEDSTRIPS, receivedColor);
  ledstrip1.show();
  ledstrip2.show();
  ledstrip3.show();
  ledstrip4.show();

  // Reset the received RGBW values
  receivedR = -1;
  receivedG = -1;
  receivedB = -1;
  receivedW = -1;
  currentEffect = "";
}
else if (effectRunning){
  if (currentEffect == "rainEffect") {
    
    if (currentEffect != previousEffect) {
      delayTime = Delays::rainEffect;
      previousEffect = currentEffect;
    }
    rainEffects(LEDSTRIPS, NUM_LEDSTRIPS);
  }
  else if (currentEffect == "waveFade") {
    if (currentEffect != previousEffect) {
      delayTime = Delays::waveFade;
    }
    waveFadeEffect(LEDSTRIPS, NUM_LEDSTRIPS, waveColor);
  }
  else if (currentEffect == "blinkingStarlight") {
    if (currentEffect != previousEffect) {
      delayTime = Delays::blinkingStarlight;
    }
    blinkingStarlights(LEDSTRIPS, 200);
  }
  else if (currentEffect == "sunriseEffect") { 
    if (currentEffect != previousEffect) {
      delayTime = Delays::sunrise;
    }
    sunriseEffect(LEDSTRIPS, NUM_LEDSTRIPS);
  }
  else if (currentEffect == "rippleEffect") {  
    if (currentEffect != previousEffect) {
      delayTime = Delays::rippleEffect;
    }
    rippleEffects(LEDSTRIPS, NUM_LEDSTRIPS, {152, 255, 152, 100});
  }
  else if (currentEffect == "fire"){
   if (currentEffect != previousEffect) {
      delayTime = Delays::other;
    }
    fireEffect(LEDSTRIPS, NUM_LEDSTRIPS);
  }
  else if (currentEffect == "breathingEffect"){
    if (currentEffect != previousEffect) {
      delayTime = Delays::other;
    }
    breathingEffect(LEDSTRIPS, NUM_LEDSTRIPS);
  }
  else {
    fillAll(LEDSTRIPS, NUM_LEDSTRIPS, {0,0,0,0});
    delayTime = 0;
  }
  for (int i = 0; i < NUM_LEDSTRIPS; i++) {
    LEDSTRIPS[i].show();
  }
}
}


int GetEffectIndex(String effect) {
  int numEffects = sizeof(EFFECTS) / sizeof(EFFECTS[0]);
  for (int i = 0; i < numEffects; i++) {
    if (EFFECTS[i] == effect) {
      return i;
    }
  }
  return -1;
}

void SwitchToNextEffect() {
  int numEffects = sizeof(EFFECTS) / sizeof(EFFECTS[0]);
  int index = GetEffectIndex(currentEffect);
  if (index == -1 || index == numEffects - 1) {
    currentEffect = EFFECTS[0];
  } else {
    currentEffect = EFFECTS[index + 1];
  }
}

void SwitchToPreviousEffect() {
  int numEffects = sizeof(EFFECTS) / sizeof(EFFECTS[0]);
  int index = GetEffectIndex(currentEffect);
  if (index == -1 || index == 0) {
    currentEffect = EFFECTS[numEffects - 1];
  } else {
    currentEffect = EFFECTS[index - 1];
  }
}
