// C++ code
//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);
float nb1,nb2;
char operateur;

void setup()
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
}

void loop()
{
if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n'); 
		int pos;
		pos = input.indexOf('+'); if (pos == -1){ pos = input.indexOf('*');} if (pos == -1){ pos = input.indexOf('/');} if (pos == -1){ pos = input.indexOf('-');} 
  		nb1 = input.substring(0, pos).toFloat();
		nb2 = input.substring(pos+1, input.length()).toFloat();
  		operateur = input[pos];
  		Serial.println(nb1);
        Serial.println(nb2);
        Serial.println(operateur);
  
  	lcd.clear();
  
	if (operateur == '+'){
      lcd.setCursor(0,0);
      lcd.print(nb1+nb2);
    }else if (operateur == '-'){
      lcd.setCursor(0,0);
      lcd.print(nb1-nb2);
    }else if (operateur == '*'){
      lcd.setCursor(0,0);
      lcd.print(nb1*nb2);
    }else if (operateur == '/'){
      if (nb2 == 0){
        lcd.setCursor(0,0);
        lcd.print("error");
      }else{
        lcd.setCursor(0,0);
        lcd.print((float)nb1/nb2);
      }
    }
  
	}
}
