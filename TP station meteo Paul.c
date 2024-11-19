#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int capteur = A0; // Capteur branché sur la pin analogique 0
const int humidityPin = A1; // Capteur d'humidité sur A2
int temperature = 0;
int valeur = 0;
float volt = 0.0;
int humidity = 0;
float heatIndex = 0.0;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    lcd.init();          // Initialisation de l'écran LCD
    lcd.backlight();     // Activation du rétroéclairage
    pinMode(humidityPin, INPUT); // Définir la broche A2 comme entrée
}

void loop()
{
    mesurerTemperature();
    delay(20);
    mesurerHumidity();
    delay(20);
    calculerHeatIndex();
    delay(100);
}

void mesurerTemperature() {
    valeur = analogRead(capteur);
    volt = (valeur / 1024.0) * 5.0;
    temperature = (volt - 0.5) * 100;

    // Affichage des données sur le port série
    Serial.print("Valeur : ");
    Serial.println(valeur);
    Serial.print("Température : ");
    Serial.print(temperature);
    Serial.println(" degrés");
    Serial.println("---------------------");

    // Affichage des données sur l'écran LCD
    lcd.clear(); // Efface l'écran avant d'afficher de nouvelles données
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");
}

void mesurerHumidity() {
    humidity = analogRead(humidityPin);

    // Affichage des données sur le port série
    Serial.print("Humidité : ");
    Serial.println(humidity);

    // Affichage des données sur l'écran LCD
    lcd.setCursor(0, 1); // Ligne 1 (deuxième ligne de l'écran LCD)
    lcd.print("Humidite: ");
    lcd.print(humidity);

    // Calculer et afficher l'indice de chaleur

}

void calculerHeatIndex() {
    // Conversion Celsius -> Fahrenheit
    float tempF = (temperature * 9.0 / 5.0) + 32.0;

    // Calcul de l'indice de chaleur simplifié
    if (tempF < 80.0) {
        heatIndex = 0.5 * (tempF + 61.0 + ((tempF - 68.0) * 1.2) + (humidity * 0.094));
    } else {
        // Formule complète
        heatIndex = -42.379 + 2.04901523 * tempF + 10.14333127 * humidity - 0.22475541 * tempF * humidity - 0.00683783 * pow(tempF, 2) - 0.05481717 * pow(humidity, 2) + 0.00122874 * pow(tempF, 2) * humidity+ 0.00085282 * tempF * pow(humidity, 2) - 0.00000199 * pow(tempF, 2) * pow(humidity, 2);
    }

    // Conversion Fahrenheit -> Celsius
    heatIndex = (heatIndex - 32.0) * 5.0 / 9.0;

    // Affichage des données
    Serial.print("Indice de chaleur : ");
    Serial.print(heatIndex);
    Serial.println(" °C");

    lcd.clear(); // Efface l'écran avant d'afficher de nouvelles données
    lcd.setCursor(0, 0);
    lcd.print("Heat Index:");
    lcd.setCursor(0, 1);
    lcd.print(heatIndex);
    lcd.print(" C");
}
