// C++ code
//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);
float premier_nombre = 0.0;
float deuxieme_nombre = 0.0;
char op;
int wait = 0;
int buffer = Serial.available();

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
}

void saisir_nombre()
{
  Wire.beginTransmission(0x20);
  char c;
  String s = "";
  while(buffer > 0)
  {
    c = Serial.read();
    s += c;
    buffer = Serial.available();
  }
  if(premier_nombre != 0.0)
  {
    deuxieme_nombre = s.toFloat();
    Wire.write((byte)deuxieme_nombre);
  }
  else
  {
    premier_nombre = s.toFloat();
    Wire.write((byte)premier_nombre);
  }
  //Wire.endTransmission();
  wait += 1;
}

void operateur()
{
  Wire.beginTransmission(0x20);
  char c;
  if(buffer > 0)
  {
    c = Serial.read();
  }
  op = c;
  Wire.write(op);
  //Wire.endTransmission();
  wait += 1;
}

void calcul()
{
  float resultat;
  Wire.beginTransmission(0x20);
  switch (op)
  {
    case '+':
    {
      resultat = premier_nombre + deuxieme_nombre;
      break;
    }
    case '-':
    {
      resultat = premier_nombre - deuxieme_nombre;
      break;
    }
    case '*':
    {
      resultat = premier_nombre * deuxieme_nombre;
      break;
    }
    case '/':
    {
      resultat = premier_nombre / deuxieme_nombre;
      break;
    }
  }
  //Serial.println(resultat);
  Wire.write((byte)resultat);
  //Wire.endTransmission();
  wait += 1;
}

void loop()
{
  if (wait == 0)
  {
    buffer = Serial.available();
    if (buffer > 0)
      saisir_nombre();
  }
  
  if (wait == 1)
  {
    buffer = Serial.available();
    if (buffer > 0)
      operateur();
  }
  
  if (wait == 2)
  {
    buffer = Serial.available();
    if (buffer > 0)
      saisir_nombre();
  }
  
  if (wait == 3)
  {
      calcul();
  }
}
