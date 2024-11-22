#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init(); 
  lcd.backlight();
  Serial.begin(9600);
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT); 
}

void loop() {
  
  float humidite = analogRead(A0); 
  humidite = (humidite / 880.0) * 100.0; // Conversion en pourcentage 

  float tempCelsius = analogRead(A1) * (5.0 / 1023.0 * 100.0); // Température en °C
  float tempFahrenheit = tempCelsius * 1.8 + 32; // Conversion en °F

  // Calcul de l'indice de confort thermique
  float HI; 
  if (tempFahrenheit < 80 || humidite < 80) {
    // Formule simplifiée
    HI = 0.5 * (tempFahrenheit + 61.0 + ((tempFahrenheit - 68.0) * 1.2) + (humidite * 0.094));
  } else {
    // Formule complète
    HI = -42.379 
         + 2.04901523 * tempFahrenheit 
         + 10.14333127 * humidite 
         - 0.22475541 * tempFahrenheit * humidite 
         - 0.00683783 * pow(tempFahrenheit, 2) 
         - 0.05481717 * pow(humidite, 2) 
         + 0.00122874 * pow(tempFahrenheit, 2) * humidite 
         + 0.00085282 * tempFahrenheit * pow(humidite, 2) 
         - 0.00000199 * pow(tempFahrenheit, 2) * pow(humidite, 2);
  }

  // Conversion du résultat en Celsius pour l'affichage
  float Celsius = (HI - 32) / 1.8;

  // Affichage sur l'écran LCD
  
  lcd.setCursor(0, 0);
  lcd.print("Hum: ");
  lcd.print(humidite);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("HI: ");
  lcd.print(Celsius);
  lcd.print("C");

  
 
}
