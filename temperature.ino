#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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
  { 1024, "        " }  // no key pressed
};
 
// Initialize
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
//  Serial.println("Ini..");

  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Done!!");
  delay(100);
  
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(A0, INPUT);
}
 
void loop() {
  int z = read_key();
  float temp, lum;

  switch  (z){
    case  0:
    break;
    case  1:
      lum = read_light();

      Serial.print("Luminosity: ");
      Serial.println(lum);
    break;
    case  2:
      read_temp();
    break;
    case  3:
    break;
    case  4:
    break;
    case  5:
    break;
  }

  // read sensors
  // read key
  // read flag to change
  // display menu
  
  read_temp();
  delay (1000);
}

int read_key(){
  static int teclaAnt = -1;   // last key
 
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
 
  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // converttion based on the datasheet
 
//  Serial.print("Temperature: ");
  Serial.print(temperature);
//  Serial.println(" C");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.setCursor(6, 1);
  lcd.print((char)223); 
  lcd.print("C");
}

float  read_light(){
  int light = analogRead(A5);

  float Rsensor = (1023-light)*10/light;

  return(Rsensor);
  
//  Serial.print("Luminosity: ");
//  Serial.println(Rsensor);
}
