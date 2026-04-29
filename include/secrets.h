//!Secrets.

#ifndef SECRETS_H
#define SECRETS_H

const char* WIFI_SSID = "SALA 09";
const char* WIFI_SENHA = "ifo@134";
//=======================
//MQTT
//=======================
const bool USAR_AWS_IOT = false;

const char* MQTT_BROKER = "broker.hivemq.com";
const int MQTT_PORTA = 1883;

const char* MQTT_CLIENT_ID = "esp32_fellipe_augusto";

const char* MQTT_USUARIO = "";
const char* MQTT_SENHA = "";

const bool MQTT_USAR_TLS = false;   //modo de conexao sem segurança

const char* MQTT_CERTIFICADO_CA = "";

const char* TOPICOS_PUBLICAR[] = {
    "senai/esp32/status",
    "senai/esp32/log",
    "senai/esp32/resposta"
};

const int TOTAL_TOPICOS_PUBLICAR =3;

const char* TOPICOS_RECEBER[] = {
    "senai/esp32/comando",
    "senai/esp32/config",
    "senai/esp32/display"
};

const int TOTAL_TOPICOS_RECEBER =3;   //quantos topicos eu posso receber







//====================================
//DEBUG
//====================================

// 0 = sem mensagens
// 1 = apenas erros
// 2 = todas as mensagens
#define DEBUG_NIVEL_INICIAL 2

// pino usado para forçar todas as mensagens na inicialização
#define PINO_HABILITA_DEBUG_COMPLETO 4



#endif