#include <SoftwareSerial.h>

// ################### Global
  #define PRINT_VARIABLE(var) Serial.print(#var " = "); Serial.println(var);

// ################### SoftwareSerial
  #define rxPin D5
  #define txPin D6
  SoftwareSerial SoftwareSerial_ESP8266(rxPin, txPin);
  // ################### READ
    char incoming_char_array[50]; // max. number of signs in data string
    int read_ctn = 0;         
    int dummy = 0;            // type "byte" does not work
  // ################### SEND
    char send_char_array[50];
    int snd_ctn = 5;          

// ############################ Timer for timed loops
  const bool debug_timers = false;

  const int cycle_50ms          = 50;
  unsigned long cycle_50ms_dt   = 0;

  const int cycle_1000ms          = 1000;      
  unsigned long cycle_1000ms_dt   = 0;

  const int cycle_1500ms          = 1500;
  unsigned long cycle_1500ms_dt   = 0;

  unsigned long millisec;           // arduino time-ms

void setup() {
  // ################### Debug Monitor
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect
    }

  // ################### SoftwareSerial
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    SoftwareSerial_ESP8266.begin(9600);

  Serial.println("SETUP - software serial ESP8266");
}

void loop() {

  millisec = millis();      // get time from arduino-clock (time since arduino is running in ms)

// ################### 50 ms
  if (millisec - cycle_50ms_dt >= cycle_50ms) {
    // 50 ms Timer
      cycle_50ms_dt = millisec;
    // ################### READ
      if (SoftwareSerial_ESP8266.available()) {
        delay(50);  // short delay that all received data is present at the Rx
        String _incoming_string = SoftwareSerial_ESP8266.readStringUntil('\n'); // read Rx until \n
        _incoming_string.toCharArray(incoming_char_array, 50); // copy data to char-Array (for sscanf)
        PRINT_VARIABLE(incoming_char_array);  //debugging

        // decode data from char-array
        sscanf(incoming_char_array, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &read_ctn);
        PRINT_VARIABLE(read_ctn);
      }    
  }

// ################### 1000 ms
  if (millisec - cycle_1000ms_dt >= cycle_1000ms) {
    // ################### 1000 ms Timer
      cycle_1000ms_dt = millisec;
      if (debug_timers == true) {
        Serial.println("Start 1000 ms");
      }
  }

// ################### 1500 ms
  if (millisec - cycle_1500ms_dt >= cycle_1500ms) {
    // ################### 1500 ms Timer
      cycle_1500ms_dt = millisec;
      if (debug_timers == true) {
        Serial.println("Start 1500 ms");
      }

    snd_ctn++;

    // ################### SEND
      sprintf(send_char_array, "%u,111,222,333,444,555,666,777,888,999,1000", snd_ctn);
      SoftwareSerial_ESP8266.println(send_char_array);
      PRINT_VARIABLE(send_char_array);

  }
}
