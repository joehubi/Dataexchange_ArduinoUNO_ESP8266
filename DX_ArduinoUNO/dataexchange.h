// ################### Johannes Huber 
// ################### 17.09.2024

#ifndef dataexchange_H
#define dataexchange_H

#include <SoftwareSerial.h>

class dataexchange {
  public:
    // Konstruktor
    dataexchange(int rxPin, int txPin);

    // Initialisierung der seriellen Schnittstelle
    void begin(long baudrate);

    // Daten senden
    void txData(const char* data);

    // Daten empfangen
    bool rxData(char* buffer, int bufferSize);

  private:
    // Definition eines Zeigers für den Port. Dies ist notwendig, da der Port erst zur Laufzeit festlegt wird
    SoftwareSerial* serialPort; 
};

#endif
