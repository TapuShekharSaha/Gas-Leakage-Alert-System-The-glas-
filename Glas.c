
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); 

int temp=0,i,pos ;
String stringVal = "";

const char offMessage[] = "Alarm off";
const char activeMessage[][16] = {"Gas Detected", "Please evacuate"};

const int piezo = 10;
const int gasSensor = A0;
int gas;

void setup(){
    pinMode(piezo, OUTPUT);
    pinMode(A0,INPUT);  
  Serial.begin(9600);
   lcd.begin();
  lcd.backlight();
  lcd.print("Gas Leakage DTctr");
  lcd.setCursor(0,1);
  lcd.print(" with SMS Alert ");
// lcd.scrollDisplayLeft();    //scrolls display left by two positions
   delay(4000);
  gsm_init();
  lcd.clear();  
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(300);
   lcd.print("System Ready");
  temp=0;
}

void loop()
{ 
  int gas_level=readSensors();
  lcd.clear();
       if(gas_level>60)
       {
        setActive();
        init_sms();
        send_sms();
        lcd_status();
       }
       else
       {
        setOff();
       }
}

void gsm_init()
{
  lcd.clear();
  lcd.print("Finding Module..");
  boolean at_flag=1;
  while(at_flag)
  {
    Serial.println("AT");
    delay(1);
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      at_flag=0;
    }
    
    delay(1000);
  }
  lcd.clear();
  lcd.print("Module Connected..");
  delay(1000);
  lcd.clear();
  at_flag=1;
  while(at_flag)
  {
    Serial.println("AT+CMGF=1");
    delay(1);
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      at_flag=0;
    }
    
    delay(1000);
  }
  lcd.clear();
  lcd.print("TEXT MODE..");
  delay(1000);
  lcd.clear();
  lcd.print("Disabling ECHO");
  boolean echo_flag=1;
  while(echo_flag)
  {
    Serial.println("ATE0");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      echo_flag=0;
    }
    delay(1000);
  }
  lcd.clear();
  lcd.print("Echo OFF");
  delay(1000);
  lcd.clear();
  lcd.print("Finding Network..");
  boolean net_flag=1;
  while(net_flag)
  {
    Serial.println("AT+CPIN?");
    while(Serial.available()>0)
    {
      if(Serial.find("+CPIN: READY"))
      net_flag=0;
    }
    delay(1000);
  }
  lcd.clear();
  lcd.print("Network Found..");
  delay(1000);
  lcd.clear();
}
void init_sms()
{
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"mobile number\"");   // use your 10 digit cell no. here
  delay(400);
}
void send_sms()
{
  Serial.println("Gas leakage found");   // use your 10 digit cell no. here
  Serial.print("Leakage level : ");
  Serial.println(gas);
  Serial.write('%');
  Serial.println(activeMessage[1]);

  delay(400);
  Serial.write(26);
}
void lcd_status()
{
  lcd.clear();
  lcd.print("Message Sent");
  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
  return;
}

int readSensors()
{
  int q = analogRead(gasSensor);
 gas = map(q, 10, 1023, 1, 100);
  return gas;
}

void setActive()

 tone(piezo, 750);
 lcd.setCursor(0, 0);
 lcd.print(activeMessage[0]);
 lcd.setCursor(0, 1);
 lcd.print(activeMessage[1]);
 delay(2500);
}

void setOff() {
 noTone(piezo);
 lcd.setCursor(2, 0);
 lcd.print(offMessage); 
 lcd.setCursor(2, 1);
 lcd.print("GAS LVL : ");  
 lcd.print(gas);
 lcd.write('%');
 delay(500);
}
