const double maxSpeed = 1203.00; //this is the max value the potentiometer can produce with 250 kOhm resistance scaled such that its lowest value is 0
double pMeter,speed;


bool S1,S2,S3,S4,S5;

void setup(){
  
	//MOTOR  
	pinMode(2,OUTPUT);
  	pinMode(3,OUTPUT);
  	pinMode(4,OUTPUT);
  	pinMode(5,OUTPUT);
  
  	//Potentiometer
  	pinMode(A0,INPUT);
  
  	//DipSwitch
  	pinMode(8,INPUT);
  	pinMode(9,INPUT);
  	pinMode(10,INPUT);
  	pinMode(11,INPUT);
  	pinMode(12,INPUT);
  
  	Serial.begin(9600);
}

void loop()
{
 	//gather inputs from tools
  	switchInput();
  	potInput();
  
  	//modify speed
  	//speed = maxSpeed - pMeter;
  	speed = 100;
  	
  	//used for debugging
  	debugSwitches();
  	debugPot();
  	debugSpeed();
  	Serial.println();
  
  	/*
    COMMAND DESCIPTIONS
    Switch 1 = Move Forward
    Switch 2 = Move Backwards
    Switch 3 = Move Right
    Switch 4 = Move Left
    Switch 5 = Reset
    */
  
  	//commands
  	commands();
}

void switchInput(){
 	S1 = digitalRead(8);
  	S2 = digitalRead(9);
  	S3 = digitalRead(10);
  	S4 = digitalRead(11);
 	S5 = digitalRead(12);
}

void potInput(){
	pMeter = analogRead(A0);
}

void debugSwitches(){
  	//debugging 
  	Serial.print("Switch State: ");
  	Serial.print(S1);
  	Serial.print(S2);
  	Serial.print(S3);
  	Serial.print(S4);
  	Serial.print(S5);
  	Serial.println();
}

void debugPot(){
	//debugging
  	Serial.print("pMeter: ");
  	Serial.println(pMeter);
} 

void debugSpeed(){
	//debugging
  	Serial.print("Speed: ");
  	Serial.println(speed);
}

void commands(){
	/*
    Note: The first entered command will be the ONLY command 
    running until its corresponding switch has been turned off 
    or the reset function has been pressed. If a command 1-4 is 
    active and the reset is inactive, that command will remain 
    active and no other command will be allowed to execute until 
    one of the two termination conditions have been achieved
 	*/	
  
  if (S5){
  	kill();
  }
  
  else if (S1){
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }
  
  else if (S2){
  	digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
  }
  
  else if (S3){
  	digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
  }
  
   else if (S4){
  	digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }
  
  //if no switch is active
  else {
  	kill();
  }
}

void kill(){
  	//resets every switch
    analogWrite(2,LOW);
    analogWrite(3,LOW);
    analogWrite(4,LOW);
    analogWrite(5,LOW);
}