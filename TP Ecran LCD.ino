//#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);

int buff = Serial.available();
float premierNombre = 0.0;
float deuxiemeNombre = 0.0;
float resultat = 0.0;
char operation;
int att = 0;


void setup()
{
  Serial.begin(9600);
  Wire.begin(); // Initialise le bus I2C
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
}


void saisirNombre()
{
  String s = "";
  char readChar;
  while(buff > 0)
    {
        readChar = Serial.read(); // lecture du caractère
        delay(10);
        s += readChar;
    	buff = Serial.available();
  	}
  if(premierNombre != 0.0)
  	deuxiemeNombre = s.toFloat();
  else
    premierNombre = s.toFloat();
  att += 1;
}


void saisirOperation()
{
  char readChar;
  if(buff > 0)
    {
        readChar = Serial.read(); // lecture du caractère
        delay(10);
        operation = readChar;
  	} 
  att += 1;
}


void calcul()
{
  if(operation == '+')
    resultat = premierNombre + deuxiemeNombre;
  if(operation == '-')
    resultat = premierNombre - deuxiemeNombre;
  if(operation == '*')
    resultat = premierNombre * deuxiemeNombre;
  if(operation == '/')
    resultat = premierNombre / deuxiemeNombre;
}


void loop()
{
  	if(att == 0)
    {
      	Serial.println("Instruction calculatrice :");
  		Serial.println("Saisir (un par un) un nombre, une operation (+-*/), un nombre :");
  		att += 1;
    }
  	if(att == 1)
    {  
   		buff = Serial.available(); 
      	if(buff > 0)
			saisirNombre();
    }
  
	if(att == 2)
   	{
     	buff = Serial.available();
     	if(buff > 0)
			saisirOperation();
   	}
  
  	if(att == 3)
   	{
     	buff = Serial.available();
     	if(buff > 0)
			saisirNombre();
   	}
 
  	if(att == 4)
   	{
    	calcul();
      	Serial.print(premierNombre);
      	Serial.print(" ");
      	Serial.print(operation);
      	Serial.print(" ");
      	Serial.print(deuxiemeNombre);
      	Serial.print(" = ");
      	Serial.println(resultat);
      	premierNombre = 0.0;
 		att = 0;
   	}
}
