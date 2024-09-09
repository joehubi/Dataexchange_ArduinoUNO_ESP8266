#include <SoftwareSerial.h>
// #include <Arduino_JSON.h>   // https://github.com/arduino-libraries/Arduino_JSON.git

// ################### Global
  #define PRINT_VARIABLE(var) Serial.print(#var " = "); Serial.println(var);
// ################### Software Serial
  #define rxPin 2
  #define txPin 3
  SoftwareSerial SoftwareSerial_Arduino(rxPin, txPin);
  bool const debug_read   = false;
  bool const debug_write  = true;
  int debug_bytes_send = 0;
  // ################### READ
    char received_data[50]; // Maximale Zeichen in der Variable
    int read_ctn = 0;
    int dummy = 0;    
  // ################### SEND
    char data_to_send[50]; // Puffer für die Datenübertragung (max. Länge der Nachricht festlegen)
    int snd_ctn = 0;

// ################### JSON
  // ################### READ JSON
    // String READ_JSON = "";  
  // ################### SEND JSON
    // JSONVar json_send_output;
    // String SEND_JSON = "";
    // byte json_snd_ctn = 0;
    // byte json_bytes_to_send = 0;  
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
      sprintf(data_to_send, "0,0,666,0,0,0,0,0,0,0,0,0,%u", snd_ctn);
      SoftwareSerial_Arduino.println(data_to_send);
      PRINT_VARIABLE(data_to_send);

    // ################### checking free dynamic memory
      // Serial.print("Freier Speicher: ");  
      // Serial.println(freeMemory());

    // ################### JSON SEND
      // json_snd_ctn++;

      // json_send_output["SEND0"] = json_snd_ctn;
      // json_send_output["SEND1"] = 0;
      // json_send_output["SEND2"] = 0;
      // json_send_output["SEND3"] = 0;
      // json_send_output["SEND4"] = 0;
      // json_send_output["SEND5"] = 0;
      // json_send_output["SEND6"] = 0;
      // json_send_output["SEND7"] = 0;
      // json_send_output["SEND8"] = 0;
      // json_send_output["SEND9"] = 0;
      // json_send_output["SEND10"] = 0;
      // json_send_output["SEND11"] = 0;
      // json_send_output["SEND12"] = 0;
      // json_send_output["SEND13"] = 0;
      // json_send_output["SEND14"] = 0;
      // json_send_output["SEND15"] = 0;
      // json_send_output["SEND16"] = 0;
      // json_send_output["SEND17"] = 0;
      // json_send_output["SEND18"] = 0;
      // json_send_output["SEND19"] = 0;
      // json_send_output["SEND20"] = 99;  

      // Serial.println("json_send_output:");
      // for (int i = 0; i <= 20; i++) {
      //   Serial.print("SEND");
      //   Serial.print(i);
      //   Serial.print(" = ");
      //   Serial.println(json_send_output["SEND" + String(i)]);
      // }

      // SEND_JSON = JSON.stringify(json_send_output);  // build JSON
      // if (SEND_JSON.length() == 0) {
      //     Serial.println("Error: JSON.stringify() returned an empty string.");
      // }
      // else {
      //   PRINT_VARIABLE(SEND_JSON);
      //   json_bytes_to_send = SoftwareSerial_Arduino.print(SEND_JSON);  // send to interface (SoftwareSerial)
      //   // PRINT_VARIABLE(json_bytes_to_send);
      // }

    // 1000 ms Timer
      if (debug_timers == true) {
        Serial.println("End 1000 ms");
      }   
  }

// ################### 50 ms
  if (millisec - cycle_50ms_dt >= cycle_50ms) {
    // ################### 50 ms Timer
      cycle_50ms_dt = millisec;

    // ################### READ
      if (SoftwareSerial_Arduino.available()) {
        delay(50);  // Kurze Verzögerung, um sicherzustellen, dass alle Daten empfangen wurden

        // // Empfange die Daten als String (bis zum Zeilenumbruch '\n')
        String incoming_data = SoftwareSerial_Arduino.readStringUntil('\n');
        int _lenght = incoming_data.length();
        PRINT_VARIABLE(_lenght);

        // Kopiere die empfangenen Daten in ein char-Array für sscanf()
        incoming_data.toCharArray(received_data, 50);
        // SoftwareSerial_Arduino.readStringUntil('\n').toCharArray(received_data, 50);
        PRINT_VARIABLE(received_data);

        // Dekodiere die Daten aus der CSV-ähnlichen Zeichenkette
        byte _number_of_items = sscanf(received_data, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", &read_ctn, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy);
        PRINT_VARIABLE(_number_of_items);
        PRINT_VARIABLE(read_ctn);
      }

    // ################### JSON READ
      // SoftwareSerial_Arduino.listen(); // Enable SoftwareSerial object to listen
      
      // if (SoftwareSerial_Arduino.isListening()) {
        
      //   while(int number_of_bytes = SoftwareSerial_Arduino.available() > 0) {
      //     PRINT_VARIABLE(number_of_bytes);
      //     READ_JSON = SoftwareSerial_Arduino.readString(); // read complete Interface empty
      //     PRINT_VARIABLE(READ_JSON);

      //     JSONVar json_read_string = JSON.parse(READ_JSON);

          // number_of_bytes = SoftwareSerial_Arduino.available();
          // PRINT_VARIABLE(number_of_bytes);

          // // search within json string
          // if (json_read_string.hasOwnProperty("SEND9")) {
          //   PRINT_VARIABLE(json_read_string["SEND9"]);
          // }
      //   }
      // }
      // delay(100); // without this, communication will not work (at the moment, i can not explain)
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



  // if (debug_read == true) {
  //   if (SoftwareSerial_Arduino.available() > 0) {
  //     delay(500);

  //     int number_of_bytes = SoftwareSerial_Arduino.available();
  //     PRINT_VARIABLE(number_of_bytes);

  //     char c = SoftwareSerial_Arduino.read();
  //     PRINT_VARIABLE(c);    
  //   }
  // }

  // if (debug_write == true) {
  //   debug_bytes_send = SoftwareSerial_Arduino.write("hello");
  //   PRINT_VARIABLE(debug_bytes_send);
  //   delay(5000);
  // }    
  // Serial.println("LOOP - software serial");