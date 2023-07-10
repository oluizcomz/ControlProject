#define PWM_N                      5    //Pino do arduino que será ligado o BTS7960
#define PWM_P                      9    //Pino do arduino que será ligado o BTS7960
#define BOTTON                    12
#include <DHT.h> //INCLUSÃO DE BIBLIOTECA
 
#define DHTPIN 3 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
 
DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
float PWM = 0.0;
float PWM_calc = 0.0;
float temp_init = 0.0;
float time_init = 0.0;
float erro = 0.0;
float erro_before = 0.0;
float time_s = 0.0;
float temp = 0.0;
float ref = 0.0;

void setup()
{ 
    //Configura os pinos de saída
    pinMode(PWM_N, OUTPUT);
    pinMode(PWM_P, OUTPUT);
    pinMode(BOTTON,  INPUT_PULLUP);
    setPwmFrequency(PWM_P, 1);//64
    Serial.begin(2000000);
    dht.begin(); //INICIALIZA A 
    Serial.print("V38 - ");
    Serial.println(getFreq());
    Serial.println("temp;PWM_calc;time(s);ref;error");
    
}
const float ka = 0.0347;
const float kb = 0.02613;


void loop()
{
  time_s = ((millis()/1000.0));
  temp = dht.readTemperature();
  if(digitalRead(BOTTON)){
    ref = temp_init - 5.0;
    
    erro = temp - ref;
    PWM_calc = (ka*erro) - (kb*erro_before) + PWM ;
    erro_before = erro;
    PWM = constrain(PWM_calc, 18.0,80.0);
    
    digitalWrite(PWM_N, LOW);
    analogWrite(PWM_P, PWM*255.0/100);
      Serial.print(temp,2);
      Serial.print(";");
      Serial.print(PWM_calc);
      Serial.print(";");
      Serial.print((time_s - time_init));
      Serial.print(";");
      Serial.print(ref);
      Serial.print(";");
      Serial.println(erro);
      while ((millis()/1000.0 - time_s) < 0.05) {}
  }else{
    digitalWrite(PWM_P, LOW);
    digitalWrite(PWM_N, LOW);
    time_init = time_s;
    temp_init = (temp_init + temp)/2.0; // pegar 5 valor
  }
    
    
}
