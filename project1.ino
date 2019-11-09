#include <TinyGPS++.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

double longitude;
double latitude;

int temp = 0;

int switcher = 8; //vibrating sensor pin to 8 no ewmp pin in arduino

int c = 0;

int a = 0;

int GPSBAUD = 9600; //default gpsbaud rate

TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);   //setting at 0,0
  lcd.print("Starting");  // prints at display of lcd screen
  lcd.setCursor(0, 1);
  lcd.print("Tracking Vehicle");
  delay(1500);          // 1.5 second code stops running
  Serial.begin(9600);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
    while(Serial.available()>0)
    if (gps.encode(Serial.read()));
         displayInfo();
  if (millis() > 5000  &&  gps.charsProcessed() < 10  )
  { 
    Serial.println(F("NO GPS DETECTED"));
    while(true);
  }
  else
  {
    Serial.println("NO GPS DETECTED");
    }
  if (temp == 1)
  {
    if (c < a)
    {
      Serial.begin(9600);
      lcd.print("ARE YOU SAFE");
      delay(2000);
      lcd.clear();
      lcd.print("PRESS RESET");
      delay(10000);
      Serial.println("AT+CMGF=1"); // sets gsm module to text mode
      delay(1000);
      Serial.println("AT+CMGF=\"+916302258516\"\r");
      delay(1000);
      Serial.println("Accident Happend At this place");
      delay(1000);
      Serial.println("LATITUDE");
      delay(100);
      Serial.println(latitude);
      delay(100);
      Serial.println("LONGITUDE");
      delay(100);
      Serial.println(longitude);
      delay(100);
      Serial.println("http://www.google.com/maps/place/gps.location.lat(),gps.location.lng()");
      delay(100);
      Serial.print("HELP THEM");
      delay(100);
      Serial.println((char)26);  //sends message
      delay(1000);
      c++;

    }
  }

}

void displayInfo()
{
  if (digitalRead(switcher) == 1) //if sensor is shaken
  {
    temp = 1;
    Serial.println("Accident Has Happend");

    delay(1000);
  }
  else
  {
    Serial.println("Vehicle is ok");

  }

  Serial.print(F("loaction"));

  if (gps.location.isValid()) //checking gps validity
  {
    Serial.print(gps.location.lat(), 6);
    latitude = gps.location.lat();
    lcd.println("LAT:");
    lcd.print(latitude);
    delay(500);
    lcd.clear();
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    longitude = gps.location.lng();
    lcd.println("LONG:");
    lcd.print(longitude);
    delay(500);
    lcd.clear();
  }
  else {
    Serial.println(F("INVALID"));
  }
}
