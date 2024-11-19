#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create an LCD object with the I2C address of the screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
}

void loop()
{
    String nombre1 = "";
    String nombre2 = "";
    String operation = "";

    lcd.setCursor(0,0);
    lcd.print("Entrez le ");
    lcd.setCursor(0,1);
    lcd.print("premier nombre :");

    while (nombre1 == "") {
        while (Serial.available() > 0) {
            char readChar = Serial.read();
            if (readChar == '\n') break;
            nombre1 += readChar;
        }
        delay(10);
    }

    // Vérification du premier nombre
    if (!validerNombre(nombre1)) {
 		lcd.clear();
      	lcd.setCursor(0,0);
        lcd.print("Erreur ");
        lcd.print(0,1);
      	lcd.print(" Nombre invalide");
        delay(2000);
        lcd.clear();
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Entrez le ");
    lcd.setCursor(0,1);
    lcd.print("second nombre :");

    while (nombre2 == "") {
        while (Serial.available() > 0) {
            char readChar = Serial.read();
            if (readChar == '\n') break;
            nombre2 += readChar;
        }
        delay(10);
    }

    // Vérification du second nombre
    if (!validerNombre(nombre2)) {
        lcd.clear();
      	lcd.setCursor(0,0);
        lcd.print("Erreur :");
        lcd.print(0,1);
      	lcd.print(" Nombre invalide");
        delay(2000);
        lcd.clear();
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("operation : ");
    lcd.setCursor(0,1);
    lcd.print("+, -, *, /");

    while (operation == "") {
        while (Serial.available() > 0) {
            char readChar = Serial.read();
            if (readChar == '\n') break;
            operation += readChar;
        }
        delay(10);
    }

    // Vérification de l'opération
    if (!validerOperation(operation)) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Erreur: ");
      	lcd.setCursor(0,1);
        lcd.print("Operation invalide");
        delay(2000);
        lcd.clear();

    }

    lcd.clear();
    lcd.setCursor(0,0);

    float nombre1conv = nombre1.toFloat();
    float nombre2conv = nombre2.toFloat();
    float result = 0.0;

    if (operation == "+") {
        result = nombre1conv + nombre2conv;
    } else if (operation == "-") {
        result = nombre1conv - nombre2conv;
    } else if (operation == "*") {
        result = nombre1conv * nombre2conv;
    } else if (operation == "/") {
        if (nombre2conv != 0) {
            result = nombre1conv / nombre2conv;
        } else {
            lcd.print("Erreur");
            delay(2000);
            return;
        }
    }
	lcd.setCursor(0,0);
    lcd.print(nombre1 + " " + operation + " " + nombre2 + " = ");
  	lcd.setCursor(0,1);
    lcd.print(String(result));


    delay(4000);
    lcd.clear();
}

// Fonction pour valider si l'entrée est un nombre valide
bool validerNombre(String message) {
    bool pointTrouve = false;
    bool virguleTrouve = false;
    for (int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (c >= '0' && c <= '9') {
            continue;
        } else if (c == '-' && i == 0 && !virguleTrouve) {
            virguleTrouve = true; // Un seul signe moins autorisé au début
        } else if (c == '.' && !pointTrouve) {
            pointTrouve = true;  // Un seul point décimal autorisé
        } else {
            return false;  // Caractère non valide trouvé
        }
    }
    return true;
}


// Fonction pour valider si l'opération est valide
bool validerOperation(String operation) {
    return (operation == "+" || operation == "-" || operation == "*" || operation == "/");
}
