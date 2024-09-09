#include <SoftwareSerial.h>
// #include <Arduino_JSON.h>
// ################### Global
  #define PRINT_VARIABLE(var) Serial.print(#var " = "); Serial.println(var);

// ################### SoftwareSerial
  #define rxPin D5
  #define txPin D6
  SoftwareSerial SoftwareSerial_ESP8266(rxPin, txPin);
  bool const debug_read   = true;
  bool const debug_write  = false;
  int debug_numberofbytes_available = 0;
  char read_5bytes = 0;
  char read_bytes_empty = 0; 

  // ################### READ
    char received_data[50];
    int read_ctn = 0;     // type "byte" does not work
    int dummy = 0;    // type "byte" does not work
  // ################### SEND
    char data_to_send[50]; // Puffer für die Datenübertragung (max. Länge der Nachricht festlegen)
    int snd_ctn = 5; // type "byte" does not work

// ################### JSON
  // ################### READ JSON
    // String READ_JSON = "";
  // ################### SEND JSON
    // JSONVar json_send_output;
    // String SEND_JSON = "";
    // byte json_snd_ctn = 0;
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
        delay(50);  // Kurze Verzögerung, um sicherzustellen, dass alle Daten empfangen wurden

        // Empfange die Daten als String (bis zum Zeilenumbruch '\n')
        String incoming_data = SoftwareSerial_ESP8266.readStringUntil('\n');

        // Kopiere die empfangenen Daten in ein char-Array für sscanf()
        incoming_data.toCharArray(received_data, 50);
        PRINT_VARIABLE(received_data);

        // Dekodiere die Daten aus der CSV-ähnlichen Zeichenkette
        sscanf(received_data, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &read_ctn);
        PRINT_VARIABLE(read_ctn);
      }    
    // ################### JSON READ
      // SoftwareSerial_ESP8266.listen(); // Enable SoftwareSerial object to listen
      // if (SoftwareSerial_ESP8266.isListening()) {     
      //   while(int number_of_bytes = SoftwareSerial_ESP8266.available() > 0) {
      //     PRINT_VARIABLE(number_of_bytes);

      //     READ_JSON = SoftwareSerial_ESP8266.readString();
      //     PRINT_VARIABLE(READ_JSON);

      //     JSONVar json_read_string = JSON.parse(READ_JSON);

      //     // number_of_bytes = SoftwareSerial_ESP8266.available();
      //     // PRINT_VARIABLE(number_of_bytes);

      //     // // search within json string
      //     // if (json_read_string.hasOwnProperty("SEND0")) {
      //     //   PRINT_VARIABLE(json_read_string["SEND0"]);
      //     // }
      //     delay(100);
      //   }
      // }
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
      sprintf(data_to_send, "%u,111,222,333,444,555,666,777,888,999,1000", snd_ctn);
      SoftwareSerial_ESP8266.println(data_to_send);
      PRINT_VARIABLE(data_to_send);

    // ################### JSON SEND
      // // json_send_output["SEND0"] = 54321;
      // // json_send_output["SEND1"] = 0;
      // // json_send_output["SEND2"] = 0;
      // // json_send_output["SEND3"] = 0;
      // // json_send_output["SEND4"] = 0;
      // // json_send_output["SEND5"] = 0;
      // // json_send_output["SEND6"] = 0;
      // // json_send_output["SEND7"] = 0;
      // // json_send_output["SEND8"] = 0;
      // json_send_output["SEND9"] = snd_ctn;
      // // json_send_output["SEND10"] = 0;
      // // json_send_output["SEND11"] = 0;
      // // json_send_output["SEND12"] = 0;
      // // json_send_output["SEND13"] = 0;
      // // json_send_output["SEND14"] = 0;
      // // json_send_output["SEND15"] = 0;
      // // json_send_output["SEND16"] = 0;
      // // json_send_output["SEND17"] = 0;
      // // json_send_output["SEND18"] = 0;
      // // json_send_output["SEND19"] = 0;
      // // json_send_output["SEND20"] = 123;  
      // SEND_JSON = JSON.stringify(json_send_output);  // build JSON

      // PRINT_VARIABLE(SEND_JSON);
      
      // SoftwareSerial_ESP8266.print(SEND_JSON);  // send to interface (SoftwareSerial)
    
  }
}


  // if (debug_read == true) {
  //   if (SoftwareSerial_ESP8266.available() == 5) {
      
  //     debug_numberofbytes_available = SoftwareSerial_ESP8266.available();
  //     PRINT_VARIABLE(debug_numberofbytes_available);

  //     for (int i = 0; i < 5; i++) {
  //       read_5bytes = SoftwareSerial_ESP8266.read();
  //       PRINT_VARIABLE(read_5bytes);
  //     }
  //   }
  //   if (SoftwareSerial_ESP8266.available() > 5) {
      
  //     debug_numberofbytes_available = SoftwareSerial_ESP8266.available();
  //     PRINT_VARIABLE(debug_numberofbytes_available);

  //     for (int i = 0; i < debug_numberofbytes_available; i++) {
  //       read_bytes_empty = SoftwareSerial_ESP8266.read();
  //       PRINT_VARIABLE(read_bytes_empty);
  //     }
  //   }
  // }
  // delay(5);
  // Serial.println("LOOP - software serial");