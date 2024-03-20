/*
Controle de leds via WIFI
Projeto Desenvolvido por:
Erasmo Junior (github.com/Blackdev23) - Programador do servidor WEB
Guilherme Maynart (github.com/guizwtx) e Luiz Filipe (github.com/luiz-filipe077) - Montadores do sistema físico
Gustavo Dantas (github.com/ggustavodl) - Programador do aplicativo
*/

#include <ESP8266WebServer.h> 
#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 
#include <PubSubClient.h>
 
ESP8266WebServer server(80); // Criação do servidor
 
//Definindo credencias do wifi local que será utilizado para controlar os leds
const char *ssid = "EMIDES3AM";
const char *password = "tmjsenai";

//Definindo as portas GPI dos LEDS
const byte LED1 = 16;
int statusLED1 = LOW;
const byte LED2 = 0;
int statusLED2 = LOW;


// ----------------------------------------------------------------------------------------------------------------- Constantes do Servidor WEB
const String HtmlHtml = "<html style=\"display: inline-block; margin: 0px auto; text-align: center;\"><head>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlTitulo = "<h1>Controle de leds via WIFI</h1><br/>\n";

const String HtmlLed1Desligado = "<big>LED Vermelho está <b>DESLIGADO</b></big><br/><br/>\n";
const String HtmlLed1Ligado = "<big>LED Vermelho está <b>LIGADO</b></big><br/><br/>\n";
const String HtmlBotoesLed1 = 
"<a href=\"LED1On\"><button style=\"background-color:green;color:white;width:20%;height:5%;\">ON </button></a>\n"
"<a href=\"LED1Off\"><button style=\"background-color:red;color:white;width:20%;height:5%;\">OFF </button></a><br/>";

const String HtmlLed2Desligado = "<big>LED Verde está <b>DESLIGADO</b></big><br/><br/>\n";
const String HtmlLed2Ligado = "<big>LED Verde está <b>LIGADO</b></big><br/><br/>\n";
const String HtmlBotoesLed2 = 
"<a href=\"LED2On\"><button style=\"background-color:green;color:white;width:20%;height:5%;\">ON </button></a>\n"
"<a href=\"LED2Off\"><button style=\"background-color:red;color:white;width:20%;height:5%;\">OFF </button></a><br/>";
const String HtmlHtmlFechar = "</html>";
// -----------------------------------------------------------------------------------------------------------------

//Funcões
void ligarLedVermelho() {
  statusLED1 = HIGH; // condição para ligar a led
  digitalWrite(LED1, statusLED1);
  Serial.println("NodeMCU ESP8266 : LED Vermelho está ligado");
  response();
}

void desligarLedVermelho() {
  statusLED1 = LOW; // condição para desligar a led
  digitalWrite(LED1, statusLED1);
  Serial.println("NodeMCU ESP8266 : LED Vermelho está desligado");
  response();
}

void ligarLedVerde() {
  statusLED2 = HIGH;
  digitalWrite(LED2, statusLED2);
  Serial.println("NodeMCU ESP8266 : LED Verde está ligado");
  response();
}

void desligarLedVerde() {
  statusLED2 = LOW;
  digitalWrite(LED2, statusLED2);
  Serial.println("NodeMCU ESP8266 : LED Verde está desligado");
  response();
}

// Montagem da página WEB com as constantes
void response(){
  String htmlRes = HtmlHtml + HtmlTitulo;
  if(statusLED1 == LOW){
    htmlRes += HtmlLed1Desligado;
  }else{
    htmlRes += HtmlLed1Ligado;
  }
  htmlRes += HtmlBotoesLed1;
  
  if(statusLED2 == LOW){
    htmlRes += HtmlLed2Desligado;
  }else{
    htmlRes += HtmlLed2Ligado;  
  }

  htmlRes += HtmlBotoesLed2;
  
  htmlRes += HtmlHtmlFechar;
 
  server.send(200, "text/html", htmlRes); // Envio das informações para o servidor
}

void setup() {
  
    delay(1000); 
    Serial.begin(115200);
    Serial.println();

    WiFi.softAP(ssid, password); // Criação do wifi
 
    IPAddress apip = WiFi.softAPIP(); // Buscando o IP
    Serial.print("Conecte ao WIFI: ");
    Serial.println(ssid);
    Serial.print("Após conectado, visite este IP: ");
    Serial.print(apip); // IP que deverá ser acessado para ter informação da página
    Serial.println(" no seu navegador.");
    
    // Funções OnClick
    server.on("/", response); 
    server.on("/LED1On", ligarLedVermelho);
    server.on("/LED1Off", desligarLedVermelho);
    server.on("/LED2On", ligarLedVerde);
    server.on("/LED2Off", desligarLedVerde);
 
    server.begin(); // Inicia o servidor local
    Serial.println("Servidor HTTP foi iniciado");

    // Declaração das portas
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    digitalWrite(LED1, statusLED1);
    digitalWrite(LED2, statusLED2);
}

void loop() {
  server.handleClient();
}
