// C++ code


#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(32, 16, 2);
int buff = 0;
String string1 = "";
String string2= "";
String string3= "";
String string_restart = "";
String str= "";
char readChar;

void setup()
{
	
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
	Serial.begin(9600);
  	
}




void loop()
{	
  	etape0();
  	lcd.setCursor(0, 1);
  	int buff = Serial.available();
  
  	
  
  //ETAPE 0 --------------------------------
} 
void etape0()
{	
      	delay(1000);
    	string1 = "";
      	string2 = "";
      	string3 = "";
  		str="";
  		string_restart = "";
  		lcd.clear();
      	etape1();
  
}

  
  //ETAPE 1 ---------------------------------------
  
void etape1()
{
  		lcd.print("1er Nombre");
       string1 = message();
      	

      	if (string1 != "")
        {
         	delay(10);
          
            string1 = verif(string1);
          	if (string1 != "")
            {
              etape2();

            }
          
   	 	}
 
      if (string1="")
      {
        	etape0();
      }
         
}

  
  	//ETAPE 2 ------------------------------------
  
void etape2()
{
  	delay(500);
  	str = "";
  	lcd.clear();
  	lcd.print("2e Nombre");
  	string2 = message();
     
     if (string2 != "")
     {
         	delay(10);
          
            string2 = verif(string2);
          	if (string2 != "")
            {
              etape3();

           	}
          
   	 }
 
      if (string2="")
      {
        	etape2();
      }
         
}
  
    
  
  	//ETAPE 3 -------------------------------------
  
  
  
float etape3()
{		
  		delay(500);
  		lcd.clear();
  		str = "";
  		lcd.print("Donnez l'operant");
        string3 = message();
      	if (string3 != "")
        {
            if ( string3[0] ==43 || string3 == "/"  || string3== "*"  || string3== "-"  )
            {

              	lcd.print(calcul());
              	restart();
            }
          else
          {
            	lcd.clear();
            	lcd.print("Mauvais operant");
              	etape0();
              
          }
        }
 
  	if (string3 == "")
    {
    	etape3();
    }   
}





String message()
{
  	buff = Serial.available();
  	char readChar;
    if (buff >=1)
    {
      while(buff > 0) // tant qu'il reste des caractères dans le buffer
            {	
                delay(10);
                readChar = Serial.read();
                str = str + readChar;
                buff = Serial.available(); // mise à jour du nombre de caratères restant

            }
        return str;
    }
  	return ("");
}




String verif(String str)
{
	for (int i = 0; i< str.length() ; i++)
          	{

                if ( str[i] < 48 || str[i] > 57 )
                    {
                  		if (str[i] == 46)
                        {
                        }
                  
                  		else 
                        {  
                          lcd.clear();
                          lcd.print("Erreur de nombre");
                          etape0();
                          str = "";
                        }
                    }
 	
            }
  	return str;

}

float calcul()
{

    	lcd.setCursor(0, 1);
      	float res1 = string1.toFloat();
        float res2 = string2.toFloat();
  		delay(1000);
  		lcd.clear();
      
 //---------------- " + " ---------------------------
      	if (string3[0] == 43)
        {
          	float resultat = res1 + res2;
          	return resultat;
          
        }
//---------------- " - " ---------------------------
      	if (string3[0] == 45)
        {
          	float resultat = res1 - res2;
          	return resultat;
        }
      
 //---------------- " * " ---------------------------
      	if (string3[0] == 42)
        {
          	float resultat = res1 *res2;
          	return resultat;
          
        }
 //---------------- " / " ---------------------------
        if (string3[0] == 47)
        {
          	if (string2 == "0")
            {
              	lcd.clear();
            	lcd.print("Division par 0");
            }
          	else
            {
              float resultat = res1 / res2;
              return resultat;
            }
        }
     	
      		
  
}

void restart()
{
  	str="";
  	delay(2000);
  	lcd.clear();
	lcd.print("Restart O/N ?");
  	string_restart = message();
  
  	if (string_restart =="O"|| string_restart == "o")
    {
    	etape0();
    }
  
  	if (string_restart =="N" || string_restart == "n")
    {
      	lcd.clear();
    	lcd.print("A une prochaine !");
      	delay(1000);
      	lcd.clear();
      	while(1); //jai mis while(1) pour boucle infini pour qu'il reste sur cet etat clear
      	
    }
  	
  	if (string_restart == "")
    {
      restart();
    } 
}


