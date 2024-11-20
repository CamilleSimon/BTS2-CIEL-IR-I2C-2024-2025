// C++ code
#include <LiquidCrystal_I2C.h>

// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);
float nombre_1;
float nombre_2;
String operation;
float resultat;

void setup()
{
lcd.begin(16,2);
lcd.init();
lcd.backlight();
Serial.begin(9600);
String s = "20.05";
float a = s.toFloat();
Serial.print(a);
}

String rentrerVal(string S)
{
  int buff= serial.available();
  Serial.print(s);
  if(buff>0)
  {
    return Serial.read();
  }
}

nombre_1= rentrerVal("Rentrez le premier nombre:");
nombre_2= rentrerVal("Rentrez le deuxième nombre:");

void operation()
{
  switch (operation)
  {
    case '+':
    {
      resultat = nombre_1 + nombre_2;
      break;
    }
    case '-':
    {
      resultat = nombre_1 - nombre_2;
      break;
    }
    case '*':
    {
      resultat = nombre_1 * nombre_2;
      break;
    }
    case '/':
    {
      resultat = nombre_1 / nombre_2;
      break;
    }
  }
}

void loop ()
{
  nombre_1();
  nombre_2();
  operation();
  resultat();
}
