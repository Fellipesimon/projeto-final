#include <Arduino.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"

#include <ArduinoJson.h>

const char TOPICO_COMANDO[] = "senai134/fellipe/esp32/comando";

void tratarMensagemRecebida(const char* topico, const String& mensagem);
void configurarLedRGB();
void alterarCorLedRGB(int vermelho, int verde, int azul);
void tratarJsonComando(const String &mensagem);

const uint8_t ESP_ID = 1;

uint8_t estado;
uint8_t temperatura;
uint8_t modo;
uint8_t vento;

void setup() 
{
  configurarDebug();

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

  if(doc["ar-condicionado"].is<JsonObject>())
  {
    JsonObject ar = doc["ar-condicionado"];

    if(ar["esp"].is<uint8_t>())
    {
        uint8_t esp = ar["esp"].as<uint8_t>();

        if(esp != 0 && esp != ESP_ID)
        {
            return;
        }
    }
    else
    {
        debugErro("ESP inválido.");
        return;
    }

    if(ar["estado"].is<uint8_t>())
    {
      estado = ar["estado"].as<uint8_t>();
      Serial.println(estado);
    }
    else
    {
      debugErro("Estado inválido.");
      return;
    }

    if(ar["temperatura"].is<uint8_t>())
    {
      temperatura = ar["temperatura"].as<uint8_t>();
      Serial.println(temperatura);
    }
    else
    {
      debugErro("Temperatura inválida.");
      return;
    }

    if(ar["modo"].is<uint8_t>())
    {
      modo = ar["modo"].as<uint8_t>();
      Serial.println(modo);
    }
    else
    {
      debugErro("modo inválido.");
      return;
    }

    if(ar["vento"].is<uint8_t>())
    {
      vento = ar["vento"].as<uint8_t>();
      Serial.println(vento);
    }
    else
    {
      debugErro("vento inválido.");
      return;
    }
  }
  else
  {
    debugErro("Objeto ar-condicionado inválido.");
    return;
  }
}

