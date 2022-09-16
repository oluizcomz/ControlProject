#define PWM5                      5    //Pino do arduino que será ligado o BTS7960
#define PWM6                      6    //Pino do arduino que será ligado o BTS7960

#include <DHT.h> //INCLUSÃO DE BIBLIOTECA
 
#define DHTPIN 3 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
 
DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
 
int i = 0;  
void setup()
{ 
    //Configura os pinos de saída
    pinMode(PWM5, OUTPUT);
    pinMode(PWM6, OUTPUT);
    Serial.begin(9600);
   dht.begin(); //INICIALIZA A FUNÇÃO
}
  
void loop()
{   
    digitalWrite(PWM5, LOW);//3 - 2 u menos
    int valor_pwm = 60;//MAX 64
    analogWrite(PWM6, valor_pwm*255.0/100);
    int tempo = millis()/1000;
    if(tempo>i){
      Serial.print(dht.readTemperature(), 0);
      Serial.print(" ");
      Serial.println(tempo);
      i++;
      }
}
