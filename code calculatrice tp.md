```C++
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String choix1 = "";
String choix2 = "";
String choix3 = "";
String valide[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "." };
String operation[] = { "*", "+", "-", "/" };
bool commandeTrouvee = false;
bool saisieNombreAffichee = false;  
bool erreurAffichee = false; 
bool commande1 = false;
bool commande2 = false;
bool commande3 = false;

void setup() {
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
}

void saisie() {
   
    bool nouvelleOperation = true;  

    while (nouvelleOperation) {
        if (!commande1 && !saisieNombreAffichee) { 
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Saisir un nombre");
            lcd.setCursor(0, 1);
            lcd.print("!");
            saisieNombreAffichee = true; 
        }
        
        if (!commande1) {
            verifnombre1();  
        }
        
        if (commande1 && !commande2 ) {  
            if (!saisieNombreAffichee) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Saisir un second");
                lcd.setCursor(0, 1);
                lcd.print("nombre !");
                saisieNombreAffichee = true;
            }
            verifnombre2();  
        }

        if (commande1 && commande2) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Nb1: ");
            lcd.print(choix1);
            lcd.setCursor(0, 1);
            lcd.print("Nb2: ");
            lcd.print(choix2);
            delay(1000);
        }

        if (commande1 && commande2) {  
            if (!saisieNombreAffichee) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Saisir une");
                lcd.setCursor(0, 1);
                lcd.print("operation !");
                saisieNombreAffichee = true;
            }
            verifope(); 
        }  

        if (commande1 && commande2 && commande3) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Operation: ");
            lcd.print(choix3);
            delay(1000);
            
           
            float resultat = calcul();
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Resultat: ");
            lcd.print(resultat);
            delay(3000);
            
           
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Nouvelle ");
          	lcd.setCursor(0, 1);
          	lcd.print("operation? (O/N)");
            delay(2000); 
            while (Serial.available() == 0); 
            char choix = Serial.read(); 

            if (choix == 'O' || choix == 'o') {
              
                choix1 = "";
                choix2 = "";
                choix3 = "";
                commande1 = false;
                commande2 = false;
                commande3 = false;
                nouvelleOperation = true; 
            } else {
                nouvelleOperation = false; 
            }
        }
    }
}


void verifnombre1() {
    String choix = "";
    
    while (Serial.available() > 0) {
        char receivedChar = Serial.read();
        choix = receivedChar;

        if (choix.length() > 0) {
            int i = 0;
            commandeTrouvee = false;

            while (i < 11) {
                if (valide[i] == choix) {
                    choix1 += receivedChar;
                    commandeTrouvee = true;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Nombre: ");
                    lcd.print(choix1);  
                    saisieNombreAffichee = false; 
                    erreurAffichee = false;  
                    commande1 = true;
                }
                i++;
            }

            if (!commandeTrouvee && !erreurAffichee) {
                lcd.clear();
                lcd.print("Commande inconnue");
                erreurAffichee = true; 
                delay(1000);
                lcd.clear();
                saisieNombreAffichee = false;  
            }
        }
    }
    delay(2000);
}

void verifnombre2() {
    String choix = "";
    
    while (Serial.available() > 0) {
        char receivedChar = Serial.read();
        choix = receivedChar;

        if (choix.length() > 0) {
            int i = 0;
            commandeTrouvee = false;

            while (i < 11) {
                if (valide[i] == choix) {
                    choix2 += receivedChar;
                    commandeTrouvee = true;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Nombre: ");
                    lcd.print(choix2);  
                    delay(2000);
                    saisieNombreAffichee = false; 
                    erreurAffichee = false;
                    commande2 = true;
                }
                i++;
            }

            if (!commandeTrouvee && !erreurAffichee) {
                lcd.clear();
                lcd.print("Commande inconnue");
                erreurAffichee = true; 
                delay(1000);
                lcd.clear();
                saisieNombreAffichee = false;  
            }
        }
    }
}

void verifope() {
    String choix = "";
    while (Serial.available() > 0) {
        char receivedChar = Serial.read();  
         choix = receivedChar; 

        if (choix.length() > 0) {
            int i = 0;
            commandeTrouvee = false;

            while (i < 4) { 
                if (operation[i] == choix) {  
                    choix3 = choix;  
                    commandeTrouvee = true;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Operation: ");
                    lcd.print(choix3);  
                    delay(2000);
                    saisieNombreAffichee = false; 
                    erreurAffichee = false;
                    commande3 = true;  
                }
                i++;
            }

            if (!commandeTrouvee && !erreurAffichee) {
                lcd.clear();
                lcd.print("Commande inconnue");
                erreurAffichee = true; 
                delay(1000);
                lcd.clear();
                saisieNombreAffichee = false;  
            }
        }
    }
}

float calcul() {
    float nombre1 = choix1.toFloat();
    float nombre2 = choix2.toFloat();
    float resultat = 0.0;

    if (choix3 == "+") {
        resultat = nombre1 + nombre2;
    } else if (choix3 == "-") {
        resultat = nombre1 - nombre2;
    } else if (choix3 == "*") {
        resultat = nombre1 * nombre2;
    } else if (choix3 == "/") {
        if (nombre2 != 0) {
            resultat = nombre1 / nombre2;
        } else {
            lcd.clear();
            lcd.print("Erreur: Division");
            lcd.setCursor(0, 1);
            lcd.print("par 0 !");
            delay(3000);
            return 0; 
        }
    }

    return resultat; 
}


void loop() {
    saisie();
}


```
