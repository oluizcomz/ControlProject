#define PWM_N                      5    //Pino do arduino que será ligado o BTS7960
#define PWM_P                      9    //Pino do arduino que será ligado o BTS7960
#define stepPWM                   60
#define BOTTON                    12
#include <DHT.h> //INCLUSÃO DE BIBLIOTECA
 
#define DHTPIN 3 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
 
DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
int PWM = 2; 
int i = PWM*stepPWM;
int time_init = PWM*stepPWM;


void setup()
{ 
    //Configura os pinos de saída
    pinMode(PWM_N, OUTPUT);
    pinMode(PWM_P, OUTPUT);
    pinMode(BOTTON,  INPUT_PULLUP);
    setPwmFrequency(PWM_P, 1);//64
    Serial.begin(9600);
    dht.begin(); //INICIALIZA A 
    Serial.print("V17 - ");
    Serial.println(getFreq());
    Serial.println("temp;pwm;time(s)");
    
}
  
void loop()
{   
  if(digitalRead(BOTTON)){
    float temp = dht.readTemperature();
    float time_s = ((millis()/1000.0)/**(980/getFreq())*/)+time_init;///62500HZ->36.98
    //7812,5HZ -> 10
    //980/fp/div
    
    digitalWrite(PWM_N, LOW);//3 - 2 u menos

    if(((i/(stepPWM*PWM)) >=1)&& (PWM < 99)){
      PWM = PWM+1;
    }

    analogWrite(PWM_P, PWM*255.0/100);
    
    
    if(time_s > i && !isnan(temp)){
      Serial.print(temp);
      Serial.print(";");
      Serial.print(PWM);
      Serial.print(";");
//      Serial.print(i);
//      Serial.print("==");
      Serial.println(time_s);
      i =  i+1;
    }
     }else{
    digitalWrite(PWM_P, LOW);
    digitalWrite(PWM_N, LOW);//3 - 2 u menos
  }///
    
}
