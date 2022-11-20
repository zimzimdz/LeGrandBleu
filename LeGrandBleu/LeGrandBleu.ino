#include <SD.h>
#include "TMRpcm.h"
#include "SPI.h"
#include <LiquidCrystal.h>
#include <DHT.h>

#define SD_CARD_PORT 10 // SD card port (CS)
#define SPEAKER_PORT 9 // Speaker port
#define TEST_FILE "test.wav"
#define SPEAKER_VOLUME 5
#define DHT11_PIN 6

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
TMRpcm tmrpcm;
Sd2Card sdCard;
DHT dht(DHT11_PIN, DHT11);

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Le Grand Bleu");

  Serial.begin(9600);
  Serial.println(F("SD card infos"));
  Serial.println(F("==============================================================="));
  Serial.println();

  // Check whether sd card is plugged in
  if (!sdCard.init(SPI_HALF_SPEED, SD_CARD_PORT)) 
  {
    Serial.println(F("Failed !"));
    Serial.println();
  } 
  else
  {
    Serial.println(F("SD card plugged in !"));
    Serial.println();

    if(!SD.begin(SD_CARD_PORT))
    {
      Serial.println(F("SD fail"));
      return;
    }

    Serial.println(F("Reading audio."));
    Serial.println();

    tmrpcm.speakerPin=SPEAKER_PORT;
    tmrpcm.setVolume(SPEAKER_VOLUME);
    tmrpcm.play(TEST_FILE);
  }
}

void loop()
{
  lcd.setCursor(1, 1);

  if(dht.read())
  {
    lcd.print(dht.readTemperature());
    lcd.print((char)223);
    lcd.print("C ");

    const int humidity = dht.readHumidity();
    lcd.print(humidity);
    lcd.print("%");
    delay(2000);
  }
}
