

#include <WiFi.h>
#include "arduino_secrets.h"
#include "thingProperties.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <ESPping.h>


// declare the datatypes for  Information regarding to network and cloud server

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;  // your network key Index number (needed only for WEP)
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;





// declare and assign pins numbers to be used
int IrPin = 14;
const int trigPin = 27;
const int echoPin = 16;


// defines variables
long duration;
//String text;
float startTime;                  //will be used to calculate throughput
float endTime;                    //will be used to calculate throughput
float totalTime;                  //will be used to calculate throughput
float payloadSize;                //will be used to calculate throughput
int botRequestDelay = 1000;       //Checks for new messages every 1 second.
unsigned long lastTimeBotRan;
WiFiClient  client;               //define an instance of wifiClient to be used by thingspeak
WiFiClientSecure secured_client; //define an instance of secured wifi client to be used by telegrambot
UniversalTelegramBot bot(BOT_TOKEN, secured_client); //declare an instance of the Telegram bot 
const IPAddress remote_ip(9,9,9,9);

// function to send sensor values to telegram bot as String
String getReadings(bool a, int b){
  bool ir=a; int dist=b; char strdist[10];
  String irVal; String TxMsg;
    if (ir == 1){
    irVal = "LOW";
  }
   else
    irVal = "HIGH";
    
  itoa(dist, strdist, 10);
  
  TxMsg = "IR SENSOR: "+irVal+"; "+"DISTANCE: "+dist+"(cm)";

  return TxMsg;
}

// function to send network values to telegram bot as String
String getNetval(float c){
  String TxNet;
  float rtt_avr;
  Ping.ping(remote_ip);
  rtt_avr = Ping.averageTime();

  TxNet ="SSID: "+ String(WiFi.SSID())+" " + "; RSSI: "+" "+String(WiFi.RSSI())+ " dBm "+
  " "+ "; Average Round Trip Time: "+ String(rtt_avr)+ " ms"+", ;Throughput: "+String(c)+" Bps";
  return TxNet ;
}

// function to handle the event coming from the telegram bot

void handleNewMessages(int numNewMessages, bool a, int b,float c) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;
      if (text == "/start") {
        String welcome = "Welcome, " + from_name + ".\n";
        welcome += "Use the following command to get current readings.\n\n";
        welcome += "/sen \n";
        welcome += "/net \n";
        bot.sendMessage(chat_id, welcome, "");
    }
        if (text == "/sen") {
      String sen = getReadings(a,b);
      bot.sendMessage(chat_id,sen, "");
    }
    if (text == "/net") {
      String net = getNetval(c);
      bot.sendMessage(chat_id,net,"");
    }

  }
}

// setting up parameters and values for the code
void setup() {
  // for sensor pin
  pinMode(IrPin, INPUT);  // set IRsensor pin as input
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  // for thingspeak
  WiFi.mode(WIFI_STA);  
  //if (WiFi.config(localIP, gatewayIP, subnetMask) == false) {
   // Serial.println("Configuration failed.");
   // } 

   WiFi.begin(ssid, pass);
    // WiFi.begin(ssid);
    //Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
       delay(500);
        Serial.print(".");
    }
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  initProperties();
  
  //for arduinocloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection); //Connect to Arduino IoT Cloud
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

// main loop

void loop() {
  //arduino cloud
  ArduinoCloud.update();
  
  // data acquisition
  
  IrState = digitalRead(IrPin);  // set the LED state
 // if (IrState == 1){
 //   IrState = 0;
 // }
 //   if (IrState == 0){
  //  IrState = 1;
 // }
  IrState != IrState;
  Serial.print("IR PIN: ");
  Serial.print(IrPin);
  Serial.print("; PIN STATE: ");
  Serial.println(IrState);
  
  digitalWrite(trigPin, LOW); // Clears the trigPin
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  
  distance = duration * 0.034 / 2; // Calculating the distance
    
  Serial.print("Distance: "); // Prints the distance on the Serial Monitor
  Serial.println(distance);
  

  // Connect or reconnect to WiFi
  
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);// Connect to WPA/WPA2 network. Change this line if using open or WEP network
      secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

 // for thingspeak
 
  ThingSpeak.setField(1, IrState);
  ThingSpeak.setField(2, distance);
  ThingSpeak.setField(3, throughput);
  ThingSpeak.setField(4, rssi);
  ThingSpeak.setField(5, rtt_av);
 
  
    payloadSize = sizeof(IrState)+sizeof(distance)+sizeof(throughput)+sizeof(rssi)+sizeof(rtt_av);
    Serial.print("payloadsize: ");
    Serial.println(payloadSize);
 
  startTime = millis(); 
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
   endTime = millis();
   
   totalTime = (endTime - startTime);
   

  throughput = (payloadSize / totalTime)*1000;    // Calculate throughput
  
  Serial.print("Throughput: ");
  Serial.print(throughput);
  Serial.println(" bytes/second");
  
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(rssi);
  Ping.ping(remote_ip);
  rtt_av = Ping.averageTime();
  Serial.print("LOCAL IP: ");
  Serial.println(WiFi.localIP());

  // for telegrambot
  
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages,IrState,distance,throughput);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

 
 
}
