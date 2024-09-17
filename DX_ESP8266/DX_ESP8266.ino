// ################### Johannes Huber 
// ################### 17.09.2024

// ################### DEFINITION
  // ################### Lib
    #include <dataexchange.h>
  // ################### macros
    #define PRINT_VARIABLE(var) Serial.print(#var " = "); Serial.println(var);
  // ################### variables
    // ################### dataexchange
      #define rxPin D5
      #define txPin D6
      dataexchange DATAX_ARDU_ESP(rxPin, txPin);

      // ################### READ
        char received_data[50]; // max. number of signs in data string
        int read_ctn = 0;         
        int dummy = 0;            // type "byte" does not work
      // ################### SEND
        char data_to_send[50];
        int snd_ctn = 5;          

    // ################### Timer for timed loops
      struct timer {
        int cycle_ms            = 1000;      
        unsigned long cycle_dt  = 0;    
        const bool debug        = false;  
      };

      timer t1000ms;    // build instance of timer
      timer t1500ms;
      timer t50ms;

      unsigned long millisec;           // arduino time-ms

// ################### SETUP
  void setup() {
    // ################### Debug Monitor
      Serial.begin(9600);
      while (!Serial) {
        ; // wait for serial port to connect
      }

    // ################### SoftwareSerial
      pinMode(rxPin, INPUT);
      pinMode(txPin, OUTPUT);
      DATAX_ARDU_ESP.begin(9600);
    // ################### timers
      t1000ms.cycle_ms = 1000;  
      t1500ms.cycle_ms = 1500;  
      t50ms.cycle_ms = 50;    
  }
// ################### LOOP
  void loop() {

    millisec = millis();      // get time from arduino-clock (time since arduino is running in ms)

  // ################### 50 ms
    if (millisec - t50ms.cycle_dt >= t50ms.cycle_ms) {
        t50ms.cycle_dt = millisec;

      // ################### dataexchange READ
      if (DATAX_ARDU_ESP.rxData(received_data, 50)) {  // check if data is available and get data
        PRINT_VARIABLE(received_data);  // debugging
      }

      sscanf(received_data, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &read_ctn);
      PRINT_VARIABLE(read_ctn);
  
    }

  // ################### 1000 ms
    if (millisec - t1000ms.cycle_dt >= t1000ms.cycle_ms) {
      // ################### 1000 ms Timer
        t1000ms.cycle_dt = millisec;
        if (t1000ms.debug == true) {
          Serial.println("Start 1000 ms");
        }
    }

  // ################### 1500 ms
    if (millisec - t1500ms.cycle_dt >= t1500ms.cycle_ms) {
      // ################### 1500 ms Timer
        t1500ms.cycle_dt = millisec;
        if (t1500ms.debug == true) {
          Serial.println("Start 1500 ms");
        }

      // ################### dataexchange SEND
        snd_ctn++;
        sprintf(data_to_send, "%u,111,222,333,444,555,666,777,888,999,1000", snd_ctn);
        DATAX_ARDU_ESP.txData(data_to_send);
        PRINT_VARIABLE(data_to_send); // debugging

    }
  }
