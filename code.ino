// C++ code
#include <LiquidCrystal_I2C.h>
// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(32, 16, 2);

float num1, num2, result;
char operation;
String input;

void setup()
{
  	lcd.begin(16,2);
	lcd.init();
	lcd.backlight();
  	Serial.begin(9600);
}

void loop()
{
  // Initialise la communication série pour l'entrée de données
  Serial.begin(9600);
  
  // Initialise l'écran LCD
  lcd.begin(16, 2);
  lcd.setBacklight(1); // Allume le rétroéclairage de l'écran
  lcd.print("Bienvenue !");

  delay(2000); // Afficher un message d'accueil pendant 2 secondes
  lcd.clear();

  // Demander le premier nombre
  lcd.clear();
  lcd.print("Entrez le 1er nombre:");
  while (Serial.available() == 0);  // Attendre que l'utilisateur entre une valeur
  num1 = Serial.parseFloat(); // Lire le premier nombre
  Serial.println(num1); // Afficher sur le moniteur série pour confirmation

  // Demander le second nombre
  lcd.clear();
  lcd.print("Entrez le 2nd nombre:");
  while (Serial.available() == 0);
  num2 = Serial.parseFloat(); // Lire le second nombre
  Serial.println(num2); // Afficher sur le moniteur série pour confirmation

  // Demander l'opération
  lcd.clear();
  lcd.print("Choisissez op:");
  lcd.setCursor(0, 1);
  lcd.print("+ - * /");
  while (Serial.available() == 0);
  operation = Serial.read(); // Lire l'opération
  Serial.println(operation); // Afficher sur le moniteur série pour confirmation

  // Calculer le résultat en fonction de l'opération
  switch (operation) {
    case '+':
      result = num1 + num2;
      break;
    case '-':
      result = num1 - num2;
      break;
    case '*':
      result = num1 * num2;
      break;
    case '/':
      if (num2 == 0) {
        lcd.clear();
        lcd.print("Erreur div 0!");
        delay(2000);
        return;  // Si division par zéro, afficher une erreur et revenir
      }
      result = num1 / num2;
      break;
    default:
      lcd.clear();
      lcd.print("Opération invalide");
      delay(2000);
      return;
  }

  // Afficher le résultat
  lcd.clear();
  lcd.print("Resultat:");
  lcd.setCursor(0, 1);
  lcd.print(result);
  delay(2000);

  // Demander si l'utilisateur veut refaire une opération
  lcd.clear();
  lcd.print("Encore ? (y/n)");
  while (Serial.available() == 0);
  input = Serial.readString(); // Lire la réponse de l'utilisateur
  input.trim(); // Retirer les espaces superflus
  if (input != "y" && input != "Y") {
    lcd.clear();
    lcd.print("Au revoir!");
    delay(2000);
    return;  // Sortir de la boucle si l'utilisateur ne veut pas recommencer

  }
}
