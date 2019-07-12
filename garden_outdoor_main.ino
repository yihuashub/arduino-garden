 #include <LiquidCrystal.h>          //the liquid crystal libarry contains commands for printing to the display
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display

int relay = 6;
int delayTime = 1;
const int AirValue = 520;   //you need to replace this value with Value_1
const int WaterValue = 260;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;

void setup() {
  Serial. begin(9600); // open serial port, set the baud rate as 9600 bps

  
  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();  
  lcd.setCursor(0,0);  
  lcd.print("YIHUA HOME KIT");  
  
pinMode (relay, OUTPUT);
}
void loop() {
     delay(300);
      // clear the screen
    lcd.clear();   
    
    int val;
    val = analogRead(0); //connect sensor to Analog 0
    Serial.println(val); //print the value to serial port
    
    
    
    lcd.setCursor(0,1);  
    lcd.print(val); 
    
    
    delay(100);
    soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
    
    if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
    {
      Serial.println("Very Wet");
      digitalWrite (relay, LOW); // "NC" is now connected through
      lcd.setCursor(0,0);  
      lcd.print("Very Wet"); 
      delay (1000);
    }
    else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
    {
      Serial.println("Wet");
      digitalWrite (relay, LOW); // "NC" is now connected through
      lcd.setCursor(0,0);  
      lcd.print("Wet"); 
      delay (1000);
    }
    else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
    {
        Serial.println("Dry");
        lcd.setCursor(0,0);  
        lcd.print("Dry"); 
        digitalWrite (relay, HIGH); // "NO" is now connected through
        delay (3000);
        digitalWrite (relay, LOW); // "NC" is now connected through
        delay (3000);

    }
    delay(100);

}
