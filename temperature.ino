#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

const int B = 4275;
const int R0 = 100000;

struct {
  int limite;
  char *nome;
} teclas[] = {
  {   50, "Right" },
  {  300, "Up" },
  {  500, "Down" },
  {  750, "Left" },
  {  850, "Select" },
  { 1024, "        " }  // nenhuma tecla apertada
};
 
// Iniciação
void setup() {
  Serial.begin(9600);
  Serial.println("Ini..");

  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Done!!");
  delay(100);
  
  pinMode(A5, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(A0, INPUT);
  
  buzz(2);
}
 
void loop() {
  int z = read_key();
  float temp;

  switch  (z){
    case  0:
      read_temp();
    break;
    case  1:
      read_light();
    break;
    case  2:
    break;
    case  3:
    break;
    case  4:
    break;
    case  5:
    break;
  }
  
  delay (100);
}

int read_key(){
  static int teclaAnt = -1;   // última tecla detectada
 
  int leitura = analogRead(A0);
 
  int teclaNova;
  for (teclaNova = 0; ; teclaNova++) {
    if (leitura < teclas[teclaNova].limite) {
      break;
    }
  }
  
  if (teclaNova != teclaAnt) {
//    lcd.setCursor(0,1);
//    lcd.print(teclas[teclaNova].nome);
//    Serial.println(teclas[teclaNova].nome);
    return (teclaNova);
    teclaAnt = teclaNova;
  }  
}

void  read_temp(){
  int temp = analogRead(A4);
  float R = 1023.0/temp-1.0;
  R = R0*R;
 
  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
 
  Serial.print("Teamperature: ");
  Serial.println(temperature);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Teamperature: ");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
}

void  read_light(){
  int light = analogRead(A5);

  float Rsensor = (1023-light)*10/light;

  Serial.print("Luminosity: ");
  Serial.println(Rsensor);
}

void buzz(int f){
  int i = 0;
  for(i = 0; i < 50; i++){
    digitalWrite(A5, HIGH);
    delay(f);
    digitalWrite(A5, LOW);
    delay(f);
  }
}
