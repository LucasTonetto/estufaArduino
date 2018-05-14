#include <EEPROM.h>
#include <dht.h>

#define dht_dpin A1 //Pino DATA do Sensor ligado na porta Analogica A1

dht DHT; //Inicializa o sensor

int aquecer = 4;
int luz = 8;
int agua = 9;
int minuto = 0;
int hora = 0;
int umidade;
int verificaTemp = false;

void setup()
{
  //EEPROM.write(0, 0);
  Serial.begin(9600);
  delay(1000);//Aguarda 1 seg antes de acessar as informações do sensor
  pinMode(aquecer, OUTPUT);
  pinMode(luz, OUTPUT);
  pinMode(agua, OUTPUT);
  digitalWrite(aquecer, LOW);
  digitalWrite(agua, LOW);
  digitalWrite(luz, LOW);

  hora = EEPROM.read(0);
  
}

void loop()
{
Serial.println(hora);
  umidade = analogRead(A0);
 int Porcento = map(umidade, 1023, 0, 0, 100);
 DHT.read11(dht_dpin);
  if(minuto == 60) {
    minuto = 0;
    hora++;
    Serial.println(DHT.temperature); 
    EEPROM.write(0, hora);
    Serial.println(EEPROM.read(0));
  }
  if(hora == 24) {
    hora = 0;
  }
  

  if(hora <= 12) {
    if(DHT.temperature < 24 && verificaTemp == false) {
        digitalWrite(aquecer, HIGH);
    } else { 
       digitalWrite(aquecer, LOW);
    }
    if(DHT.temperature >= 24) {
      verificaTemp = true;
    } else if(DHT.temperature <= 18) {
      verificaTemp = false;
    }
  } else {
      if(DHT.temperature < 19 && verificaTemp == false) {
        digitalWrite(aquecer, HIGH);
      } else { 
         digitalWrite(aquecer, LOW);
      }
      if(DHT.temperature >= 19) {
        verificaTemp = true;
      } else if(DHT.temperature <= 14){
        verificaTemp = false;
      }
   }

/* luz*/ 
  if(hora >= 8 && hora <= 15) {
    digitalWrite(luz, HIGH);
  } else {
    digitalWrite(luz, LOW);
  }

/* bomba de agua */ 
  if(hora <= 12) {
    if(Porcento > 80) {
      digitalWrite(agua, HIGH);
      delay(15000);
      digitalWrite(agua, LOW);
    }
  } else {
     if(Porcento > 65) {
      digitalWrite(agua, HIGH);
      delay(15000);
      digitalWrite(agua, LOW);
    }
  }

  minuto++;
  delay(60000);
  
}
