int umidade;
  
void setup()
{
 Serial.begin(9600);
}
void loop()
{
 umidade = analogRead(A0);
 int Porcento = map(umidade, 1023, 0, 0, 100);
  
 Serial.print(Porcento);
 Serial.println("%");
 delay(1000);
}
