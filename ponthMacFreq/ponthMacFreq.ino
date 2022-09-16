#define PWM5                      5    //Pino do arduino que será ligado o BTS7960
#define PWM6                      6    //Pino do arduino que será ligado o BTS7960
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire pino(3);
DallasTemperature barramento(&pino);
DeviceAddress sensor;
void setupPWM25khz();
void PWM25khz(char pino, int valor);  
void setup()
{ 
    //Configura os pinos de saída
    setupPWM25khz();  
    Serial.begin(9600);
    barramento.begin();
    barramento.getAddress(sensor, 0);  
}
  
void loop()
{   
    PWM25khz(5, 0);
    //digitalWrite(PWM5, LOW);//3 - 2 u menos
    int valor_pwm = 20;//MAX 64
    //analogWrite(PWM6, valor_pwm*255.0/100);
    PWM25khz(6, 50);
    barramento.requestTemperatures(); 
    float temperatura = barramento.getTempC(sensor);
    Serial.print(temperatura);
    Serial.print(" ");
    Serial.println((millis()/1000));
    //delay(500);
}
/*****************************************************************/

void setupPWM25khz(){
  /*  Configura timer 1 para fast PWM a 25KHz
   *   
   *  COM1A1=1, COM1B1=1, COM1A0=0, COM1B0=0:
   *  Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM (non-inverting mode)
   *  
   *  WGM13=1, WGM12=1, WGM11=1, WGM10=0: 
   *  Waveform Generation mode 14: Fast PWM, TOP = ICR1  
   *  
   *  CS12=0, CS11=0, CS10=1:
   *  clkI/O/1 (no prescaling)
   *  
   *  Frequência do PWM = 16000000/(ICR1+1)
   *  ex: ICR1 = 639:
   *  Frequência do PWM = 16000000/(639+1) = 25kHz
   *  
   *  valor min. ICR1 = 3, valor max. ICR1 = 65535
   */
   
    TCCR1A = 0;           // Limpa os registradores de configuração do timer 1
    TCCR1B = 0;           // 
    TCNT1  = 0;           // reseta o timer
    TCCR1A = _BV(COM1A1)  // canal A no modo non-inverting
           | _BV(COM1B1)  // canal B no modo non-inverting
           | _BV(WGM11);  // mode 14: Fast PWM, TOP = ICR1
    TCCR1B = _BV(WGM12)   // 
           | _BV(WGM13)   //
           | _BV(CS10);   // prescaler = 1
    ICR1   = 639;         // TOP = 639

    // configura os pinos do PWM como saída
    pinMode(PWM5, OUTPUT);
    pinMode(PWM6, OUTPUT);
}
/*****************************************************************/

void PWM25khz(char pino, int valor){
  switch (pino) {
    case 5:
        OCR1A = valor;
        break;
    case 6:
        OCR1B = valor;
        break;
  }
}
