/*este codigo fue diseñado por ing. edison viveros
 * es um ejemplo demostrativo del uso del sensor
 * este codigo no tiene calibracion de sensor, esta parte
 * es muy importante para el correcto funcionamiento
 * del sensor, tambien puede usar librerias
 * http://www.editronikx.com
 */

int s_analogica_mq135=0;
int aire =12;
int CO2=11;
int gas=10;

void setup() 
{
  Serial.begin(9600);
  pinMode(aire,OUTPUT);
  pinMode(CO2,OUTPUT);
  pinMode(gas,OUTPUT);
  
  digitalWrite(aire,LOW);
  digitalWrite(CO2,LOW);
  digitalWrite(gas,LOW);

}


void loop()   
{
  s_analogica_mq135 = analogRead(0);       
  Serial.println(s_analogica_mq135, DEC);
  Serial.println(" ppm");
  delay(250); 
  //aire 
  if(s_analogica_mq135<=55)
  {
  Serial.println("aire normal");
  digitalWrite(aire,LOW);
  digitalWrite(CO2,LOW);
  digitalWrite(gas,LOW);
  delay(50);
  }
//aire con dioxido humano
  if(s_analogica_mq135>=56 && s_analogica_mq135<=65)
  {
  Serial.println("aire con un poco de CO2");
  digitalWrite(aire,HIGH);
  digitalWrite(CO2,LOW);
  digitalWrite(gas,LOW);
  delay(50);
  }
 //dioxido de carbono
  if(s_analogica_mq135>=74 && s_analogica_mq135<=350)
  {
  Serial.println(" dioxido de carbono CO2");
  digitalWrite(aire,LOW);
  digitalWrite(CO2,HIGH);
  digitalWrite(gas,LOW);
  delay(50);
  }
  //gas propano y butano
  if(s_analogica_mq135>=400)
  {
  Serial.println("propano butano");
  digitalWrite(aire,LOW);
  digitalWrite(CO2,LOW);
  digitalWrite(gas,HIGH);
  delay(50);
  }
  
}

