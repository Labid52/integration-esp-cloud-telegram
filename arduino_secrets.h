#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
// Use this file to store all of the private credentials 
// and connection details

#define SECRET_SSID "LabidIC"    // replace MySSID with your WiFi network name
#define SECRET_PASS "12345678"  // replace MyPassword with your WiFi password

#define SECRET_CH_ID 2129021     // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "NPY5Y3K4V29BO6W3"   // replace XYZ with your channel write API Key
#define BOT_TOKEN "XXXXXXXXX"  // replace with you own token
#define CHAT_ID "XXXXXXXX"


#if defined(BOARD_HAS_WIFI)
  #define SECRET_SSID "XXXXX"
  #define SECRET_PASS "XXXXXXX"
#endif

/* ESP8266 ESP32*/
#if defined(BOARD_ESP)
  #define SECRET_DEVICE_KEY "BWCBBUYVQLGO4UM79KPE"
#endif

/* MKR GSM 1400 */
#if defined(BOARD_HAS_GSM)
  #define SECRET_PIN ""
  #define SECRET_APN ""
  #define SECRET_LOGIN ""
  #define SECRET_PASS ""
#endif

/* MKR WAN 1300/1310 */
#if defined(BOARD_HAS_LORA)
  #define SECRET_APP_EUI ""
  #define SECRET_APP_KEY ""
#endif

/* MKR NB 1500 */
#if defined(BOARD_HAS_NB)
  #define SECRET_PIN ""
  #define SECRET_APN ""
  #define SECRET_LOGIN ""
  #define SECRET_PASS ""
#endif

/* Portenta H7 + Ethernet shield */
#if defined(BOARD_HAS_ETHERNET)
  #define SECRET_OPTIONAL_IP ""
  #define SECRET_OPTIONAL_DNS ""
  #define SECRET_OPTIONAL_GATEWAY ""
  #define SECRET_OPTIONAL_NETMASK ""
#endif
