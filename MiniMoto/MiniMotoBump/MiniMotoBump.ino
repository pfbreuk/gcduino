/************************************************************************************************
**                         MiniMoto & GCDuino Code Example                                     **
**     To set Direction: digitalWrite(M1_Dir or M2_Dir, HIGH = Reverse, LOW = Fowards);        **
**     To set Speed: analogWrite(M1_Speed or M2_Speed, 0-250);                                 **
**           NOTE: When going Forwards 0 = Slow, 250 = Fast                                    **
**                            Reverse 0 = Fast, 250 = Slow                                     **
**                                                                                             **
**    Written by Rod Christian                                                    03/12/2013   **
************************************************************************************************/

const int M1_Speed = 6;  //Speed
const int M1_Dir = 7;    //Direction
const int M2_Speed = 5;   //Speed
const int M2_Dir = 4;     //Direction

const int BUMP_INTERUPT = 0;

const int BUMP = 2;  // Actual Bump sensor pin
const int LED = 9;   // GCDuino Built-in LED
const int PIEZO = 10;   // Piezo Buzzer

int Max_Speed = 250;  // 0 = Stopped, 250 = Fast 

boolean bumped = false;

void setup()
{
  pinMode(M1_Speed, OUTPUT);  //Set All pin's as Outputs
  pinMode(M1_Dir, OUTPUT);
  pinMode(M2_Speed, OUTPUT);
  pinMode(M2_Dir, OUTPUT); 
  pinMode(LED, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  
  digitalWrite(BUMP, HIGH); // turn on pull up resistor for flow sensor on pin 2
  attachInterrupt(BUMP_INTERUPT, interuptHandler, CHANGE);
  
  LEDon();
}

void loop()
{
  if(bumped) {
    turn();
    beep(50);
  }
  M_Fwd();
}

void interuptHandler()
{
  bumped = true;
}

void turn() { 
  M_Rev();
  delay(100);
  M1_Fwd();
  M2_Rev();
  delay(400);  
  bumped = false;
}


void LEDon()
{
  digitalWrite(LED, HIGH);
}

void LEDoff()
{
  digitalWrite(LED, LOW);
}
//M1 Control (Right Motor)
void M1_Rev()
{
  analogWrite(M1_Speed, 0);
  digitalWrite(M1_Dir, HIGH);
}

void M1_Fwd()
{
  analogWrite(M1_Speed, 250);
  digitalWrite(M1_Dir, LOW);
}

void M1_Stop()
{
  digitalWrite(M1_Speed, LOW);
  digitalWrite(M1_Dir, LOW);
}

//M2 Control (Left Motor)
void M2_Rev()
{
  analogWrite(M2_Speed, 0);
  digitalWrite(M2_Dir, HIGH);
}

void M2_Fwd()
{
  analogWrite(M2_Speed, 250);
  digitalWrite(M2_Dir, LOW);
}

void M2_Stop()
{
  digitalWrite(M2_Speed, LOW);
  digitalWrite(M2_Dir, LOW);
}

//Control Both Motors
void M_Rev()
{
  M1_Rev();
  M2_Rev();
}

void M_Fwd()
{
  M1_Fwd();
  M2_Fwd();
}

void M_Stop()
{
  M1_Stop();
  M2_Stop();
}

void beep(int delayms){
  analogWrite(PIEZO, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(PIEZO, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  

