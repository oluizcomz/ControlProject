#define PWM5                      5    //Pino do arduino que será ligado o BTS7960
#define PWM6                      6    //Pino do arduino que será ligado o BTS7960
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire pino(3);
DallasTemperature barramento(&pino);
DeviceAddress sensor;
int i = 0;  
void setup()
{ 
    //Configura os pinos de saída
    pinMode(PWM5, OUTPUT);
    pinMode(PWM6, OUTPUT);
    setPwmFrequency(PWM6, 1);
    Serial.begin(9600);
    barramento.begin();
    barramento.getAddress(sensor, 0);  
}
  
void loop()
{   
    digitalWrite(PWM5, LOW);//3 - 2 u menos
    int valor_pwm = 90;//MAX 64
    analogWrite(PWM6, valor_pwm*255.0/100);
    int tempo = millis()/1000;
    if(tempo>i){
      barramento.requestTemperatures(); 
      float temperatura = barramento.getTempC(sensor);
      Serial.print(temperatura);
      Serial.print(" ");
      Serial.println(tempo);
      i++;
      }
    /*delay(500);
     digitalWrite(PWM3, LOW);
 
    //Aumenta a velocidade para o lado 1
    for (valor_pwm = 0; valor_pwm < 0256/2; valor_pwm++)
    {
        analogWrite(PWM2, valor_pwm);
        Serial.println("1ado1");
        Serial.println(valor_pwm);
        delay(TEMPO_DA_VELOCIDADE);
    }
 
    //Diminui a velocidade para o lado 1
    for (valor_pwm = 255/2; valor_pwm >= 0; valor_pwm--)
    {
      
        Serial.println("1ado1");
        Serial.println(valor_pwm);
        analogWrite(PWM2, valor_pwm);
        delay(TEMPO_DA_VELOCIDADE);
    }

/////////////////////////////////////////////////////////////////////////////

    digitalWrite(PWM2, LOW);

     //Aumenta a velocidade para o lado 2
    for (valor_pwm = 0; valor_pwm < 256/2; valor_pwm++)
    {
        analogWrite(PWM3, valor_pwm);
        
        Serial.println("1ado2");
        Serial.println(valor_pwm);
        delay(TEMPO_DA_VELOCIDADE);
    }
 
    //Diminui a velocidade para o lado 2
    for (valor_pwm = 255/2; valor_pwm >= 0; valor_pwm--)
    {
      
        Serial.println("1ado2");
        Serial.println(valor_pwm);
        analogWrite(PWM3, valor_pwm);
        delay(TEMPO_DA_VELOCIDADE);
    }
*/
}
