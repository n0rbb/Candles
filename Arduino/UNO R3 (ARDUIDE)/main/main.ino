#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
const int yellow = 9;
int light = 0;
int toggle = 0;
char name[] = "NOMBRE";


void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  pinMode(yellow, OUTPUT);
  lcd.print("Pulse para en_");
  lcd.setCursor(0, 1);
  lcd.print("cender una vela");
  Serial.begin(9600);
}

void loop() {
  light = digitalRead(switchPin);
  Serial.print(light);
  Serial.println(toggle);

  if(light == 1 && toggle == 0){
    lcd.clear();
    delay(500);
    toggle = 1;
    for(int i = 0; i < 256; i += 2){
      analogWrite(9, i);
      Serial.print("a");
      Serial.print(light);
      Serial.println(toggle);
      delay(50);
    }
    lcd.setCursor(2, 0);
    lcd.print("Mucha suerte,");
    lcd.setCursor((16 - sizeof(name) + 1) / 2, 1);
    lcd.print(name);
    delay(100);
  }

  light = digitalRead(switchPin);
  /* El valor de light se mantiene durante todo el ciclo de loop, 
    luego no forzar la lectura otra vez hace que el segundo IF siempre llegue con un 1 (HIGH) 
    aunque ya no se esté pulsando el interruptor. */

  if (light == 1 && toggle == 1){
    toggle = 0;
    digitalWrite(9, 0);
    lcd.clear();
    lcd.print("Pulse para en_");
    lcd.setCursor(0, 1);
    lcd.print("cender una vela");
    delay(100);
  }
  delay(100); 
  /*Todos estos delays vienen para compensar las oscilaciones del pulsador 
    (que no haya falsos positivos justo después de pulsar)*/
} 