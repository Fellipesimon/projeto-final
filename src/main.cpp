
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

const int PINO_LAMPADA = 8;
const int PINO_LED_RGB = 48; // para o pino
const int QUANTIDADE_LEDS = 1; //quantidade

const char TOPICO_COMANDO[] = "senai134/fellipe/esp32/comando";

Adafruit_NeoPixel ledRGB(
  QUANTIDADE_LEDS,
  PINO_LED_RGB,
  NEO_GRB + NEO_KHZ800 
);

void configurarLedRGB();
void alterarCorLedRGB(int vermelho, int verde, int azul);
void tratarJsonComando(const String &mensagem);

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
  debugInfo("==============================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("==============================");

  if(topico == nullptr)
  {
    debugErro("Tópico MQTT inválido");
    return;
  }

  debugInfo("Tópico: " + String(topico));
  debugInfo("Mensagem: " + mensagem);

  if(strcmp(topico, TOPICO_COMANDO) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }

  debugErro("Tópico não tratado: " + String(topico));

}


void configurarLedRGB()
{
  ledRGB.begin();
  ledRGB.setBrightness(80); //colocamos a qntd de brilho 0 a 255
  ledRGB.clear();
  ledRGB.show();

  debugInfo("LED RGB configurado no GPIO" + String(PINO_LED_RGB));
}

void alterarCorLedRGB(int vermelho, int verde, int azul)
{
 vermelho = constrain(vermelho, 0, 255);
 verde = constrain(verde, 0, 255);
 azul = constrain(azul, 0, 255);

  ledRGB.setPixelColor(0, ledRGB.Color(vermelho, verde, azul));
  ledRGB.show();

  debugInfo("Cor aplicada no LED RGB");
  debugInfo("R:" + String(vermelho));
  debugInfo("G:" + String(verde));
  debugInfo("B:" + String(azul));
}

void tratarJsonComando(const String &mensagem)
{
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, mensagem);

  if(erro)
  {
  debugErro("Erro ao interpretar JSON.");
  debugErro(erro.c_str());
  return;
  }

  if(doc["led"].is<JsonObject>())
  {
    if(!doc["led"]["r"].is<int>() ||
     !doc["led"]["g"].is<int>() ||
      !doc["led"]["b"].is<int>())
    {
      debugErro("JSON INVALIDO. use led.r, led.g, led.b");
      return;
    }
    else
    {
      int vermelho = doc["led"]["r"].as<int>();
      int verde = doc["led"]["g"].as<int>();
      int azul = doc["led"]["b"].as<int>();
      
      alterarCorLedRGB(vermelho, verde, azul);
    }
  }

}

