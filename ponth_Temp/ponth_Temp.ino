#define PWM_N                      5    //Pino do arduino que será ligado o BTS7960
#define PWM_P                      9    //Pino do arduino que será ligado o BTS7960
#define BOTTON                    12
#include <DHT.h> //INCLUSÃO DE BIBLIOTECA
 
#define DHTPIN 3 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
 
DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
int PWM = 70;
int i = 0;
float timi_init = 0.0;

void setup()
{ 
    //Configura os pinos de saída
    pinMode(PWM_N, OUTPUT);
    pinMode(PWM_P, OUTPUT);
    pinMode(BOTTON,  INPUT_PULLUP);
    setPwmFrequency(PWM_P, 1);//64
    Serial.begin(9600);
    dht.begin(); //INICIALIZA A 
    Serial.print("V29 - ");
    Serial.println(getFreq());
    Serial.println("temp;pwm;time(s)");
    
}
  
void loop()
{
  float time_s = ((millis()/1000.0));//*2*(980/getFreq()));///62500HZ->36.98
  if(digitalRead(BOTTON)){
    
    float temp = dht.readTemperature();
    
    //7812,5HZ -> 10
    //980/fp/div
    
    digitalWrite(PWM_N, LOW);//3 - 2 u menos
    //PWM = 0;
    analogWrite(PWM_P, PWM*255.0/100);
    
    //if((time_s- timi_init) > i && !isnan(temp)){
      Serial.print(temp);
      Serial.print(";");
      Serial.print(PWM);
      Serial.print(";");
      Serial.println((time_s- timi_init));
    //  i =  i+1;
    //}
  }else{
    digitalWrite(PWM_P, LOW);
    digitalWrite(PWM_N, LOW);
    timi_init = time_s;
    i = 0;
    
  }
    
    
}
