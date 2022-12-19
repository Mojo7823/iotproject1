#include <pt.h>
#include <Arduino.h>
#include <PZEM004Tv30.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

PZEM004Tv30 pzem(D7,D8);

// WiFi
const char *ssid = "HDC Clone 13 Mini"; // Enter your WiFi name
const char *password = "123456789";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.mqttdashboard.com";
const char *mqtt_username = "";
const char *mqtt_password = "";
const char *relayontp = "shock/relayon";
const char *relayofftp = "shock/relayoff";
const char *lockontp = "shock/lockon";
const char *lockofftp = "shock/lockoff";
const char *voltagetp = "shock/voltage";
const char *currenttp = "shock/current";
const char *powertp = "shock/power";
const char *relaystat = "shock/relaystatus";
const char *lockstat = "shock/lockstatus";

const int mqtt_port = 1883;


int ledlockon = D6;
int ledlockoff = D5;
int sensor = D4;              // the pin that the sensor is atteched to
int RelayPin = D2;

int relaystate = LOW;
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)


String switch1;
String strTopic;
String strPayload;

WiFiClient espClient;
PubSubClient client(espClient);

// Create your protothread(s)
static struct pt pt1, pt2, pt3;

// A protothread function
static int protothreadReadPZEM (struct pt *pt)
{
  static unsigned long lastTimeRead = 0;
  // Start a protothread
  PT_BEGIN(pt);
  /* Your code inside this thread */
    while(1) {
    lastTimeRead = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeRead > 5000);
      Serial.println("Measuring...");
      //Result Variables
      float volts = pzem.voltage();
      float amps = pzem.current();
      float watts = pzem.power();
      
  client.publish(voltagetp, String(volts,3).c_str());
  client.publish(currenttp, String(amps,3).c_str());
  client.publish(powertp, String(watts,3).c_str());
  

  Serial.println("Data Sent!!");  
  }
  // Stop a protothread 
  PT_END(pt);
}

static int protothreadChildLock(struct pt *pt)
{
  static unsigned long LastTimeSense = 0;
  val = digitalRead(sensor);   // read sensor value
  
  PT_BEGIN(pt);
  while(1) {
    if( digitalRead(ledlockon) ){      
    Serial.println("Child Lock ON \n");  
      if (val == HIGH) {           // check if the sensor is HIGH
        delay(500);                // delay 100 milliseconds        
        if (state == LOW) {
          Serial.println("Motion detected!"); 
          state = HIGH;       // update variable state to HIGH
          digitalWrite(RelayPin, HIGH);
            LastTimeSense = millis();
            PT_WAIT_UNTIL(pt, millis() - LastTimeSense > 500);
        }
      } 
      else {
            LastTimeSense = millis();
            PT_WAIT_UNTIL(pt, millis() - LastTimeSense > 500);          
          if (state == HIGH){
            Serial.println("Motion stopped!");
            state = LOW;       // update variable state to LOW
            digitalWrite(RelayPin, LOW);
        }
      }
    LastTimeSense = millis();
    PT_WAIT_UNTIL(pt, millis() - LastTimeSense > 2000);
    }  
  if( !digitalRead(ledlockon) )
    {
      Serial.println("Child Lock OFF \n");
      LastTimeSense = millis();
      PT_WAIT_UNTIL(pt, millis() - LastTimeSense > 1000);
    }
  }
  PT_END(pt);
}


static int protothreadCheckState (struct pt *pt)
{
  static unsigned long LastTimeCheck = 0;
  
  PT_BEGIN(pt);
  while(1) {
    LastTimeCheck = millis();
    
    if( digitalRead(ledlockon) == HIGH ){      
    client.publish(lockstat, "Child Lock ON");
     }
    else { 
    client.publish(lockstat, "Child Lock OFF");   
    }

    if( digitalRead(RelayPin) == LOW ){      
    client.publish(relaystat, "Plug Active");
     }
    else { 
    client.publish(relaystat, "Plug Inactive");
    }

    PT_WAIT_UNTIL(pt, millis() - LastTimeCheck > 3000 );    
  }
  PT_END(pt);
}

void setup() {
  Serial.begin(115200);
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, LOW);
  pinMode(ledlockon, OUTPUT);
  pinMode(ledlockoff, OUTPUT);
  pinMode(sensor, INPUT); // set arduino pin to input mode

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("Connected to network \n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Broker connected \n");
      } else {
          Serial.print("failed with state \n");
          Serial.print(client.state());
          delay(2000);
      }
  }
  // publish and subscribe
   client.subscribe(relayontp);
   client.subscribe(relayofftp);
   client.subscribe(lockontp);
   client.subscribe(lockofftp);
   client.subscribe(voltagetp);
   client.subscribe(currenttp);
   client.subscribe(powertp);
   client.subscribe(relaystat);
   client.subscribe(lockstat);
  
  // Init your protothread(s)
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic,"shock/relayon")==0) {
        Serial.println("Receive Command OK! Power OFF");
        digitalWrite(RelayPin, HIGH);
  }
  if (strcmp(topic,"shock/relayoff")==0) {
        Serial.println("Receive Command OK! Power ON!");
        digitalWrite(RelayPin, LOW);
  }  

  if (strcmp(topic,"shock/lockon")==0) {
        Serial.println("Receive Command OK! Lock ON");
        digitalWrite(ledlockon, HIGH);
        digitalWrite(ledlockoff, LOW);
  }

    if (strcmp(topic,"shock/lockoff")==0) {
        digitalWrite(ledlockon, LOW);
        digitalWrite(ledlockoff, HIGH);
        Serial.println("Receive Command OK! Lock Off");
  }
}

void loop() {
  client.loop();
  // Execute your protothread(s)
  protothreadReadPZEM(&pt1);
  protothreadChildLock(&pt2);
  protothreadCheckState(&pt3);
}
