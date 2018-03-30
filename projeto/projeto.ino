#include <dht.h>

#define dht_dpin A1 //Pino DATA do Sensor ligado na porta Analogica A1

dht DHT; //Inicializa o sensor

int umidade;

void setup()
{
  Serial.begin(9600);
  delay(1000);//Aguarda 1 seg antes de acessar as informações do sensor
}

void loop()
{
  umidade = analogRead(A0);
  int Porcento = map(umidade, 1023, 0, 0, 100);
  
  DHT.read11(dht_dpin); //Lê as informações do sensor
  Serial.print("Umidade = ");
  Serial.print(DHT.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura = ");
  Serial.print(DHT.temperature); 
  Serial.println(" °C  ");
  Serial.print("  Umidade do Solo = ");
  Serial.print(Porcento);
  Serial.println(" %");

  //Não diminuir o valor abaixo. O ideal é a leitura a cada 2 segundos
  delay(2000);  
}
