#include <SD.h>
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;
Sd2Card sdCard;

#define SD_CARD_PORT 10 // SD card port (CS)
#define SPEAKER_PORT 9 // Speaker port
#define TEST_FILE "test.wav"
#define SPEAKER_VOLUME 5

void setup()
{
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


}
