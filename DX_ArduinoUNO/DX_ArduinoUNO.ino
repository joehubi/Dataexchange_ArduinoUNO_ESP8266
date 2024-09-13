#include <SoftwareSerial.h>
// #include <Arduino_JSON.h>   // https://github.com/arduino-libraries/Arduino_JSON.git

// ################### Global
  #define PRINT_VARIABLE(var) Serial.print(#var " = "); Serial.println(var);
// ################### Software Serial
  #define rxPin 2
  #define txPin 3
  SoftwareSerial SoftwareSerial_Arduino(rxPin, txPin);
  // ################### READ
    char incoming_char_array[50]; // max. receive 50 sign's in one incoming string
    int read_ctn = 0;
    int dummy = 0;    
  // ################### SEND
    char send_char_array[50]; // Puffer für die Datenübertragung (max. Länge der Nachricht festlegen)
    int snd_ctn = 0;

// ################### Funktion - Speicher
  extern int __heap_start, *__brkval;
  int freeMemory() {
      int v;
      return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  }
// ############################ Timer for timed loops
  const bool debug_timers = false;

  const int cycle_1000ms          = 1000;      
  unsigned long cycle_1000ms_dt   = 0;

  const int cycle_50ms          = 50;
  unsigned long cycle_50ms_dt   = 0;

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
    SoftwareSerial_Arduino.begin(9600); 
  
  Serial.println("SETUP - software serial arduino uno");
}

void loop() {

  millisec = millis();      // get time from arduino-clock (time since arduino is running in ms)

// ################### 1000 ms
  if (millisec - cycle_1000ms_dt >= cycle_1000ms) {
    // ################### 1000 ms Timer
      cycle_1000ms_dt = millisec;
      if (debug_timers == true) {
        Serial.println("Start 1000 ms");
      }

    snd_ctn++;

    // ################### SEND SoftwareSerial
      sprintf(send_char_array, "0,0,666,0,0,0,0,0,0,0,0,0,%u", snd_ctn);
      SoftwareSerial_Arduino.println(send_char_array);
      PRINT_VARIABLE(send_char_array);

    // ################### checking free dynamic memory
      // Serial.print("Freier Speicher: ");  
      // Serial.println(freeMemory());

    // 1000 ms Timer
      if (debug_timers == true) {
        Serial.println("End 1000 ms");
      }   
  }

// ################### 50 ms
  if (millisec - cycle_50ms_dt >= cycle_50ms) {
    // ################### 50 ms Timer
      cycle_50ms_dt = millisec;

    // ################### READ SoftwareSerial
      if (SoftwareSerial_Arduino.available()) {
        delay(50);  // short delay, to be sure all data is present at the Rx

        String _incoming_string = SoftwareSerial_Arduino.readStringUntil('\n'); // read Rx

        int _lenght = _incoming_string.length();  // lenght for debugging
        PRINT_VARIABLE(_lenght);                  // lenght for debugging


        _incoming_string.toCharArray(incoming_char_array, 50);     // copy data to char-Array (for sscanf)

        PRINT_VARIABLE(incoming_char_array);

        // decode data from char-array
        byte _number_of_items = sscanf(incoming_char_array, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", &read_ctn, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy);

        PRINT_VARIABLE(_number_of_items);   // check number of items (here 11)
        PRINT_VARIABLE(read_ctn);           // print for debugging
      }
  }

// ################### 1500 ms
  if (millisec - cycle_1500ms_dt >= cycle_1500ms) {
    // 1500 ms Timer
      cycle_1500ms_dt = millisec;
      if (debug_timers == true) {
        Serial.println("Start 1500 ms");
      }  
  }
}
