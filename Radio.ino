///
/// \file  TestTEA5767.ino
/// \brief An Arduino sketch to operate a TEA5767 chip based radio using the Radio library.
///
/// \author Matthias Hertel, http://www.mathertel.de
/// \copyright Copyright (c) 2014 by Matthias Hertel.\n
/// This work is licensed under a BSD style license.\n
/// See http://www.mathertel.de/License.aspx
///
/// \details
/// This sketch implements a "as simple as possible" radio without any possibility to modify the settings after initializing the chip.\n
/// The radio chip is initialized and setup to a fixed band and frequency. These settings can be changed by modifying the 
/// FIX_BAND and FIX_STATION definitions. 
///
/// Open the Serial console with 57600 baud to see the current radio information.
///
/// Wiring
/// ------ 
/// Arduino port | TEA5767 signal
/// ------------ | ---------------
///         3.3V | VCC
///          GND | GND
///           A5 | SCLK
///           A4 | SDIO
///           D2 | RST
///
/// More documentation is available at http://www.mathertel.de/Arduino
/// Source Code is available on https://github.com/mathertel/Radio
///
/// History:
/// --------
/// * 15.09.2014 created.
/// * 15.11.2015 wiring corrected.

#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>

/// The band that will be tuned by this sketch is FM.
#define FIX_BAND RADIO_BAND_FM

/// The station that will be tuned by this sketch is 8930 -> 89.30 MHz.
#define FIX_STATION1 9460
#define FIX_STATION2 8820

TEA5767 radio;    // Create an instance of Class for Si4703 Chip

//pin pro výběr stanice
int pinStaniceVyber = 3;                //digitalni pin D3
int aktualniHodnotaPinStaniceVyber=1; // aktualni hodnota podle prepinace
int posledniHodnotaPinStaniceVyber=1; // posledni hodnota stanice


/// Setup a FM only radio configuration
/// with some debugging on the Serial port
void setup() {
  // open the Serial port
  Serial.begin(57600);
  Serial.println("Radio...");
  delay(200);

  // Initialize the Radio 
  radio.init();

  // HERE: adjust the frequency to a local sender
  radio.setBandFrequency(FIX_BAND, FIX_STATION1);
  radio.setVolume(1);
  radio.setMono(true);

//iniciace pinu pro výběr stanice
pinMode(pinStaniceVyber, INPUT);           // 
digitalWrite(pinStaniceVyber, HIGH);       // HIGH->stanice 1, LOW->stanice 2

} // setup


/// show the current chip data every 3 seconds.
void loop() {

aktualniHodnotaPinStaniceVyber = digitalRead(pinStaniceVyber);    //precteni hodnoty prepinace
if (aktualniHodnotaPinStaniceVyber != posledniHodnotaPinStaniceVyber){      //pokud je hodnota prepinace jina nez posledni vybrana hodnota
  switch (aktualniHodnotaPinStaniceVyber) {    //vyber stanice podle hodnoty prepinace
  case 1:
    radio.setBandFrequency(FIX_BAND, FIX_STATION1);
    posledniHodnotaPinStaniceVyber = 1;
    break;
  case 0:
    radio.setBandFrequency(FIX_BAND, FIX_STATION2);
    posledniHodnotaPinStaniceVyber = 0;
    break;
  }
}
//pokud je hodnota prepinace stejna jako posledni vybrana hodnota, tak se nic nedela
}
