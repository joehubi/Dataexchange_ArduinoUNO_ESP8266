// ################### Johannes Huber 
// ################### 17.09.2024

#include "dataexchange.h"
#include <Arduino.h>

dataexchange::dataexchange(int rxPin, int txPin) {
  // Erzeuge die SoftwareSerial-Schnittstelle
  serialPort = new SoftwareSerial(rxPin, txPin);
}

void dataexchange::begin(long baudrate) {
  // Starte die serielle Kommunikation
  serialPort->begin(baudrate);
}

void dataexchange::txData(const char* data) {
  // Sende die Daten über SoftwareSerial
  serialPort->println(data);
}

bool dataexchange::rxData(char* buffer, int bufferSize) {
  // Überprüfe, ob Daten verfügbar sind
  if (serialPort->available()) {
    delay(50);  // Kurze Verzögerung, um sicherzustellen, dass alle Daten empfangen wurden

    // Lese die Daten als String und kopiere sie in das char-Array
    String incoming_data = serialPort->readStringUntil('\n');
    incoming_data.toCharArray(buffer, bufferSize);
    
    return true;
  }
  return false;
}
