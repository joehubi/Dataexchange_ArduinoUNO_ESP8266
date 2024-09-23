// ################### Johannes Huber 
// ################### 17.09.2024

// ################### DEFINITION
  // ################### lib
    #include <dataexchange.h>   // https://github.com/joehubi/dataexchange.git
  // ################### macros
    #define PRINT_VARIABLE(var) Serial.print(#var " = "); Serial.println(var);

  // ################### variables
    // ################### dataexchange
      #define rxPin 12
      #define txPin 13

      dataexchange DATAX_ARDU_ESP(rxPin, txPin);

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

  // ################### functions
    // ################### free memory
      extern int __heap_start, *__brkval;
      int freeMemory() {
          int v;
          return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
      }
  // ################### Timer for timed loops

    struct timer {
      int cycle_ms            = 1000;      
      unsigned long cycle_dt  = 0;    
      const bool debug        = false;  
    };

    timer t1000ms;    // build instance of timer
    timer t50ms;

    unsigned long millisec;           // arduino time-ms

// ################### SETUP
  void setup() {
    // ################### debug monitor
      Serial.begin(9600);
      while (!Serial) {
        ; // wait for serial port to connect
      }

    // ################### dataexchange
      pinMode(rxPin, INPUT);
      pinMode(txPin, OUTPUT);
      DATAX_ARDU_ESP.begin(9600);
    // ################### timers
      t1000ms.cycle_ms = 1000;  
      t50ms.cycle_ms = 50;      
  }

// ################### LOOP
  void loop() {
    millisec = millis();      // get time from arduino-clock (time since arduino is running in ms)
    // ################### 1000 ms
      if (millisec - t1000ms.cycle_dt >= t1000ms.cycle_ms) {
          t1000ms.cycle_dt = millisec;
          if (t1000ms.debug == true) {
            Serial.println("Start 1000 ms");
          }

        snd_ctn++;

        // ################### dataexchange SEND
          sprintf(data_to_send, "0,0,666,0,0,0,0,0,0,0,0,0,%u", snd_ctn);
          DATAX_ARDU_ESP.txData(data_to_send);
          PRINT_VARIABLE(data_to_send); // debugging


          if (t1000ms.debug == true) {
            Serial.println("End 1000 ms");
          }   
      }

    // ################### 50 ms
      if (millisec - t50ms.cycle_dt >= t50ms.cycle_ms) {
          t50ms.cycle_dt = millisec;

        // ################### dataexchange READ
          if (DATAX_ARDU_ESP.rxData(received_data, 50)) {  // check if data is available and get data
            PRINT_VARIABLE(received_data);  // debugging
          }

          // Dekodiere die Daten aus der CSV-ähnlichen Zeichenkette
          byte _number_of_items = sscanf(received_data, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", &read_ctn, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy);
          // PRINT_VARIABLE(_number_of_items);
          // PRINT_VARIABLE(read_ctn);
      }

  }

// ################### END
