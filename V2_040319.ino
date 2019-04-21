
#include <Servo.h>
const int BLUE  = 3; //blue goes to pin 3
const int RED = 4; // red goes to pin 4
const int GREEN  = 5; // green goes to pin 5
const int YELLOW = 6; // yellow goes to pin 6


int time = 1000; //this sets the delay to 1 sec, used as variable incase global scope maniuplation is needed. 

int blueButton = 22; // button corresponding to the blue input button on pin 7
int redButton = 24; // button for red light input on pin 8
int greenButton = 26; // button for green button input on pin 9
int yellowButton = 28; // yellow input button on pin 10
int blackButton = 30; // black button
int whiteButton = 32; // white button
int resetButton = 34; // reset button

// if i cannot get the reset button wired up (due to cable restrictions) i will code it so black and white together will reset the program.

int BB = 0;
int RB = 0;
int GB = 0;
int YB = 0;
int BkB = 0;
int WB = 0;
int RST = 0;

/* Since we are using an Arduino MEGA 2560 board there is about 3x the number of avaible features compared to the standard board. 9 and 10 on arduino regular are for the servo motor
this might still be the case on the MEGA. If so the button for either green or yuellow will be moved to a new digital pin.*/
int user[4]= {}; //  user array input
int seq[4]= {}; // generated array
int rng = 0; //random number genreator holding variable
int test = 0; // used to track the size of the array math and make sure size is correct

int pos = 0;



boolean valid = false; // this is used at the end when comparing the user inpiut array to the generated one and complete the end of the game
boolean flag = false; // used to pause Loop();
boolean turnCounter = false;

int buttonState = 1; // 1 is unoccupied 0 is used in RandomSeed so didnt want potential conflict

//(sizeof(seq) / sizeof(seq[4])) storeage

Servo myservo;


void setup() {

Serial.begin(9600);

myservo.attach(9);

if(myservo.attached())
{
  Serial.println("Servo attached");
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
  /* Set all the LEDs as output devices */
pinMode(RED, OUTPUT); 
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
pinMode(YELLOW, OUTPUT);

/* Set the digital buttons as input devices */
pinMode(blueButton , INPUT_PULLUP);
pinMode(redButton , INPUT_PULLUP);
pinMode(greenButton , INPUT_PULLUP);
pinMode(yellowButton , INPUT_PULLUP);
pinMode(blackButton , INPUT_PULLUP);
pinMode(whiteButton , INPUT_PULLUP);
pinMode(resetButton ,  INPUT_PULLUP);


randomSeed(analogRead(0)); // this randomizes everytime the program is ran

delay(2000);
/* This block below tests all the LEDs on start up to make sure the wiring is correct. It holds the on position for 1 sec */
digitalWrite(BLUE, HIGH);
delay(time);
digitalWrite(BLUE, LOW);
Serial.println("BLUE is working");

digitalWrite(RED, HIGH);
delay(time);
digitalWrite(RED, LOW);
Serial.println("RED is working");



digitalWrite(GREEN, HIGH);
delay(time);
digitalWrite(GREEN, LOW);
Serial.println("GREEN is working");

digitalWrite(YELLOW, HIGH);
delay(time);
digitalWrite(YELLOW, LOW);
Serial.println("YELLOW is working");




delay(2000); // wait 2 seconds before going into the loop to make sure light are in the correct order.

}


/* ----------------------------------------  */
/* ----------------------------------------  */
/* ----------------------------------------  */



void loop() 
{
 



rngLv1();

while(flag == false)
{


 
}


} // end of Loop()


/* ----------------------------------------  */
/* ----------------------------------------  */
/* ----------------------------------------  */



void rngLv1()
{
    for( int i = 0; i < 4; i++)
  {

     rng = random(0,6);
     seq[i] = rng;
  }

checkSize(seq);
  
} //end of rng function


void checkSize(int seq[])
{

for(int i = 0; i < 4; i++)
{
Serial.println(seq[i]);
}
  playColors(seq);
} // end of checkSize



/* ----------------------------------------  */
/* ----------------------------------------  */
/* ----------------------------------------  */


void playColors(int seq[])
{
  
   for( int x = 0; x < 4; x++)
  {
    if(seq[x] == 0)
    {
      BlueLight();
      
    }

    else if(seq[x] == 1)
    {
      RedLight();
      
    }

    else if(seq[x] == 2)
    {
      GreenLight();
      
    }

     else if(seq[x] == 3)
    {
      YellowLight();
      
    }

       else if(seq[x] == 4)
    {
      dot();
      
    }

     else if(seq[x] == 5)
    {
      line();
      
    }
    else{
      Serial.println("Something is busted, FeelsBadMan");
    }
  }

  userIn();
}



/* ----------------------------------------  */
/* ----------------------------------------  */
/* ----------------------------------------  */


void userIn() // this area is broken
{

  
  Serial.println("User in function");
  
int i = 0;
while( turnCounter == false)
{
     BB = digitalRead(blueButton);
   RB = digitalRead(redButton);
   GB = digitalRead(greenButton);
  YB = digitalRead(yellowButton);
  BkB = digitalRead(blackButton);
  WB = digitalRead(whiteButton);
  RST = digitalRead(resetButton);

  
  if(BB == LOW)
{
  BlueLight();
  user[i] = 0;
  i++;
}

if(RB == LOW)
{
  RedLight();
  user[i] = 1;
  i++;
}
if(GB == LOW)
{
  GreenLight();
    user[i] = 2;
  i++;
}

if(YB == LOW)
{
  YellowLight();
    user[i] = 3;
  i++;
}

if(BkB == LOW)
{
  dot();
  user[i] = 4;
  i++;
}

if(WB == LOW)
{
  line();
  user[i] = 5;
  i++;
}

if(RST == LOW || (BkB == LOW && WB == LOW))
{
  Serial.println("Game being reset");
  reset();
}

if(i == 4)
  {
 
    Serial.println("Success user input complete");
    for (int i = 0; i < 4; i++)
    {
      Serial.println( user[i]);
    }
    i++;
   
    compareUser(seq , user);
     turnCounter = true;
  };
}


} // end of user input function


/* ----------------------------------------  */
/* ----------------------------------------  */
/* ----------------------------------------  */



boolean compareUser(int seq[] , int user[])
{

  Serial.println("Entering the compare function");
  int i = 0;
for (int y = 0;  y < 4; y++)
{
  if(seq[y] == user[y])
  {

   i++;
          Serial.println("Entering the compare function 2");
  }

  if(i == (y+1))
  {
    success();
     valid = true;
     return valid;
  }


  if(seq[y] != user[y])
  {
    fail();
    valid = false;
    return valid;  
 }
}

}; // end of comparing function



/* ----------------------------------------  */

/* ----------------------------------------  */

/* ----------------------------------------  */


void fail()
{
  Serial.println("Sequence is not matching, better luck next time");
  reset2();
}


void success()
{
  Serial.println("Match good job");
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

    delay((time * 5));
  reset();
}

void reset()
{
valid = false;
flag = false; 
turnCounter = false;

buttonState = 1; 
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  loop();
}


void reset2()
{
valid = false;
flag = false; 
turnCounter = false;

buttonState = 1; 

  loop();
}

/* ----------------------------------------  */

/* ----------------------------------------  */

/* ----------------------------------------  */



void BlueLight()
{
  
  digitalWrite(BLUE, HIGH);
   delay((time*.65));
  digitalWrite(BLUE, LOW);
 delay((time*.65));
};

void RedLight()
{
  digitalWrite(RED, HIGH);
 delay((time*.65));
  digitalWrite(RED, LOW);
 delay((time*.65));
}

void GreenLight()
{
  digitalWrite(GREEN, HIGH);
  delay((time*.65));
  digitalWrite(GREEN, LOW);
  delay((time*.65));
}

void YellowLight()
{
  digitalWrite(YELLOW, HIGH);
 delay((time*.65));
  digitalWrite(YELLOW, LOW);
   delay((time*.65));
  
}

void dot()
{
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
 delay((time*.65));
   digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
  delay((time*.65));
}

void line()
{
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(YELLOW, HIGH);
 delay((time*.65));
   digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
 delay((time*.65));
}
