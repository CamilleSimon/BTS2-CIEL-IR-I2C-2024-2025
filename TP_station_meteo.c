// C++ code
//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>



// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);
int humidite = 0;
int temp = 0;
int hisimp = 0;
int hicomp = 0;


void setup()
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  
  // initialisation capteur
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  
  Serial.begin(9600);
}

void loop()
{
  humidite = analogRead(A3)*(5.0/1024.0);
  temp = round(analogRead(A2)*(5.0/1024.0)*100-50)*9/5+32;
  
  hisimp = 0.5 * (temp + 61.0 + ((temp-68.0)*1.2) + (humidite*0.094));
  hicomp = -42.379 + 2.04901523*temp + 10.14333127*humidite - 0.22475541*temp*humidite - 0.00683783*pow(temp,2) - 0.05481717*pow(humidite,2) + 0.00122874*pow(5,2)*humidite + 0.00085282*temp*pow(humidite,2) - 0.00000199*pow(temp,2)*pow(humidite,2);
  Serial.println(temp);
  lcd.setCursor(0,0);
  lcd.print("hiSimp : ");
  lcd.print(hisimp);
  lcd.print(" F     ");
  lcd.setCursor(0,1);
  lcd.print("hicomp : ");
  lcd.print(hicomp);
  lcd.print(" F   ");
  delay(200);
	
  
  
}
