
#include <Arduino.h>
#include <WiFiManager.h>
#include <MQTTManager.h>
#include "DebugManager.h"

/*
autor:fellipe augusto
mqtt
data:24/04/2026
*/

void tratarMensagemRecebida(const char* topico, const String& mensagem);



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

}