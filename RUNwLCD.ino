// inlude libs
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>

// start display class
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

// define motorpins
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

// set some values
int RefreshRate = 500; // set time in milis how often we will check for inputs and refresh display

// calcuclate refreshrates
unsigned long lastRefresh = millis();
unsigned long nextRefresh = RefreshRate + lastRefresh;

//go to points
long GoTo[6] = {10000,50000,500,30000,90000,100};
int i = 0;

void setup() {
  pinMode(A3, INPUT);
  
  //init lcd, display welcome screen
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("Stepper Controller");
  delay(1000);
  lcd.clear();

  // set default motor values
  stepper.setMaxSpeed(16000);
  stepper.setSpeed(16000);
  stepper.setAcceleration(100000);
  stepper.setCurrentPosition(0);
  //stepper.setPinsInverted(false, false, false);
}

void loop()
{
  if(millis() > nextRefresh)
  {
    lcd.clear();
    lcd.home();
    lcd.print("Running");
    lcd.setCursor(0,1);
    lcd.print("        ");
    lcd.setCursor(0,1);
    lcd.print(stepper.currentPosition());

    nextRefresh = millis()+RefreshRate; // update refresh interval
  }

  if(stepper.distanceToGo() == 0)
  {
    stepper.moveTo(GoTo[i]);
    i++;
  }
  
  stepper.run();
}
