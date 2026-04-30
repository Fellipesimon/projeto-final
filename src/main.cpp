
#include <Arduino.h>
#include "WiFiManager.h"
#include "MQTTManager.h"
#include "DebugManager.h"

#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
/*
autor:fellipe augusto
mqtt
data:24/04/2026
*/

const int PINO_LED_RGB = 48; // para o pino
const int QUANTIDADE_LEDS = 1; //quantidade

Adafruit_NeoPixel ledRGB(
  QUANTIDADE_LEDS,
  PINO_LED_RGB,
  NEO_GRB + NEO_KHZ800 // NAO EXPLICOU
);

void configurarLedRGB();
void alterarCorLedRGB(int vermelho, int verde, int azul);
void tratarJsonLedRGB(const String &mensagem);

void tratarMensagemRecebida(const char* topico, const String& mensagem);



void setup() 
{
  configurarDebug();

  configurarLedRGB();//explicar na proxima aula

  conectarWiFi();
  configurarMQTT();
  registrarCallbackMensagem(tratarMensagemRecebida);
  conectarMQTT();
}

void loop()
{
  garantirWiFiConectado();
  garantirMQTTConectado();
  loopMQTT();
}

void tratarMensagemRecebida(const char* topico, const String& mensagem)
{

}


void configurarLedRGB()
{
  ledRGB.begin();
  ledRGB.setBrightness(); //colocamos a qntd de brilho 0 a 255
  ledRGB.clear();
  ledRGB.show()//explicar na proxima aula
}

void alterarCorLedRGB(int vermelho, int verde, int azul)
{
}

void tratarJsonLedRGB(const String &mensagem)
{}