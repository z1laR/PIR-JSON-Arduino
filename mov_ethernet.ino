#include <Ethernet.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "RestClient.h"

const int PIR = 22; 
int pir_lectura = 0;

const int LED = 34;

int buzzer = 8;

#define IP "192.168.0.100"
#define PORT 3000

//String responseMovimiento = "On"; ---- 1

//String responseMovimiento; ---- 2

RestClient client = RestClient(IP, PORT);

void setup()
{
  Serial.begin(9600);
  
  Serial.println("connect to network");
  client.dhcp();

  Serial.print("IP de Placa Ethernet Shield ");
  Serial.println(Ethernet.localIP());
  
  //pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  
  Serial.println("Listo :D!");
}

void loop()
{
  //pir_lectura = digitalRead(PIR);

  String responseMovimiento = "On";
  
  digitalRead(PIR);
  if (pir_lectura == HIGH)
  {
    //digitalWrite(LED, HIGH);
    Serial.println("Movimiento detectado");

    postMov(responseMovimiento);
    
    delay(1000);
  }

  else
  {
    //digitalWrite(LED, LOW);
    Serial.println("No hay movimiento");

    delay(500);
  }
}

void postMov(String responseMovimiento)
{
  //responseMovimiento = "On";
  
  client.setHeader("Content-Type: application/json");
  
  StaticJsonBuffer<200> jsonBuffer;
  char json[256];  
  JsonObject& root = jsonBuffer.createObject();
  root["mov"] = responseMovimiento;
  Serial.println();
  root.printTo(json, sizeof(json));
  Serial.println(json);
  Serial.println();
  
  int statusCode = client.post("http://localhost:3000/api/movimiento/", json, &responseMovimiento);
  
  Serial.println("Status code from server: ");
  Serial.println(statusCode);
  Serial.println("responseMovimiento body from server: ");
  Serial.println(responseMovimiento);
  
  delay(3000);
}
