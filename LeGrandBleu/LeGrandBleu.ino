//**********************************************************************************
//**********************************************************************************
//**********************************************************************************
//************************* Copyright(C) Chips Molle 2023 **************************
//**********************************************************************************
//**********************************************************************************
//**********************************************************************************

#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS      7      // VS1053 chip select pin (output)
#define SHIELD_DCS     6      // VS1053 Data/command select pin (output)
#define CARDCS         4      // Card chip select pin
#define DREQ           3 
#define RELAY_PIN      2
#define MAX_TRACK      5      // Max track available on SD
#define VOLUME         3      // Volume - Lower=Louder

using namespace std;
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

const char* tracks[MAX_TRACK] = { "/track001.mp3", "/track002.mp3", "/track003.mp3", "/track004.mp3", "/track005.mp3" };

bool playTrack(const char* track)
{
  return musicPlayer.startPlayingFile(track);
}

int randomTrackIndex()
{
  return random(MAX_TRACK);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Le Grand Bleu");

  // Init relay
  pinMode(RELAY_PIN, OUTPUT);
  
  if (!musicPlayer.begin())
  {
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     return;
  }

  Serial.println(F("VS1053 found"));
  
  if (!SD.begin(CARDCS))
  {
    Serial.println(F("SD failed, or not present"));
    return;
  }
 
  // Set volume for left, right channels.
  musicPlayer.setVolume(VOLUME,VOLUME);

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  randomSeed(analogRead(0));
  while(!playTrack(tracks[randomTrackIndex()]))
  {
    Serial.println(F("Couldn't start playing track."));
  }
}

void loop()
{
  digitalWrite(RELAY_PIN, HIGH);

  // File is playing in the background
  if (musicPlayer.stopped())
  {
    playTrack(tracks[randomTrackIndex()]);
  }
}
