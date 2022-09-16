#define PWM5                      5    //Pino do arduino que será ligado o BTS7960
#define PWM6                      6    //Pino do arduino que será ligado o BTS7960
#define DHTPIN                    10 //PINO DIGITAL UTILIZADO PELO DHT22

#include <OneWire.h>
#include <DallasTemperature.h>
OneWire pino(DHTPIN);
DallasTemperature barramento(&pino);
DeviceAddress sensor;
int PWM = 70; 
int i = 0;


void setup()
{ 
    //Configura os pinos de saída
    pinMode(PWM5, OUTPUT);
    pinMode(PWM6, OUTPUT);
    setPwmFrequency(PWM6, 1);//64
    Serial.begin(9600);
    barramento.begin();
    barramento.getAddress(sensor, 0); 
    
    Serial.print("V29 - ");
    Serial.println(getFreq());
    Serial.println("temp;pwm;time(s)");
    
}
  
void loop()
{   
    barramento.requestTemperatures(); 
    float temp = barramento.getTempC(sensor);
    float time_s = ((millis()/1000.0)*2*(980/getFreq()));///62500HZ->36.98
    //7812,5HZ -> 10
    //980/fp/div
    
    digitalWrite(PWM5, LOW);//3 - 2 u menos
    //PWM = 0;
    analogWrite(PWM6, PWM*255.0/100);
    
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
    
}
