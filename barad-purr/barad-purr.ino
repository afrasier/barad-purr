#include <Servo.h> 

int const ACTION_ENABLE_LASER = 0;
int const ACTION_DISABLE_LASER = 1;
int const ACTION_MOVE = 2;

int verticalPin = 11;
int horizontalPin = 10;
int buttonPin = 2;
int laserPin = 5;

int vOffset = 0;
int hOffset = 0;

bool processing = false;

int MEDIUM = 20;
int SLOW = 30;
int FAST = 10;
int INSTANT = 0;
 
Servo vServo;
Servo hServo;

// Pattern definitions

// ACTION, VERT, HORZ, SPEED }
int catplay1[24][4] = {
  {ACTION_MOVE, 60, 45, SLOW},
  {ACTION_MOVE, 50, 55, MEDIUM},
  {ACTION_MOVE, 40, 65, SLOW},
  {ACTION_MOVE, 35, 70, MEDIUM},
  {ACTION_MOVE, 20, 75, SLOW},
  {ACTION_MOVE, 40, 80, SLOW},
  {ACTION_MOVE, 10, 85, MEDIUM},
  {ACTION_MOVE, 25, 90, FAST},
  {ACTION_MOVE, 35, 95, MEDIUM},
  {ACTION_MOVE, 30, 100, SLOW},
  {ACTION_MOVE, 20, 105, SLOW},
  {ACTION_MOVE, 15, 110, SLOW},
  {ACTION_MOVE, 35, 115, MEDIUM},
  {ACTION_MOVE, 15, 110, MEDIUM},
  {ACTION_MOVE, 20, 105, SLOW},
  {ACTION_MOVE, 30, 100, MEDIUM},
  {ACTION_MOVE, 35, 95, SLOW},
  {ACTION_MOVE, 30, 85, FAST},
  {ACTION_MOVE, 40, 80, SLOW},
  {ACTION_MOVE, 20, 75, MEDIUM},
  {ACTION_MOVE, 35, 70, SLOW},
  {ACTION_MOVE, 40, 65, SLOW},
  {ACTION_MOVE, 50, 55, MEDIUM},
  {ACTION_MOVE, 60, 45, SLOW}
};

int catplay2[10][4] = {
  {ACTION_MOVE, 20, 30, FAST},
  {ACTION_MOVE, 25, 120, FAST},
  {ACTION_MOVE, 30, 30, FAST},
  {ACTION_MOVE, 35, 120, FAST},
  {ACTION_MOVE, 40, 30, FAST},
  {ACTION_MOVE, 45, 120, FAST},
  {ACTION_MOVE, 50, 30, FAST},
  {ACTION_MOVE, 55, 120, FAST},
  {ACTION_MOVE, 60, 30, FAST},
  {ACTION_MOVE, 65, 120, FAST}
};

int catplay3[10][4] = {
  {ACTION_MOVE, 35, 45, MEDIUM},
  {ACTION_MOVE, 10, 90, MEDIUM},
  {ACTION_MOVE, 35, 135, FAST},
  {ACTION_MOVE, 50, 90, MEDIUM},
  {ACTION_MOVE, 35, 45, SLOW},
  {ACTION_MOVE, 5, 45, FAST},
  {ACTION_MOVE, 10, 90, SLOW},
  {ACTION_MOVE, 35, 135, MEDIUM},
  {ACTION_MOVE, 50, 90, SLOW},
  {ACTION_MOVE, 35, 45, FAST}
};

int catplay4[26][4] = {
  {ACTION_MOVE, 65, 10, MEDIUM},
  {ACTION_MOVE, 15, 10, MEDIUM},
  {ACTION_MOVE, 15, 20, MEDIUM},
  {ACTION_MOVE, 65, 20, MEDIUM},
  {ACTION_MOVE, 65, 30, MEDIUM},
  {ACTION_MOVE, 15, 30, MEDIUM},
  {ACTION_MOVE, 15, 40, MEDIUM},
  {ACTION_MOVE, 65, 40, MEDIUM},
  {ACTION_MOVE, 65, 50, MEDIUM},
  {ACTION_MOVE, 15, 50, MEDIUM},
  {ACTION_MOVE, 15, 60, MEDIUM},
  {ACTION_MOVE, 65, 60, MEDIUM},
  {ACTION_MOVE, 65, 70, MEDIUM},
  {ACTION_MOVE, 15, 70, MEDIUM},
  {ACTION_MOVE, 15, 80, MEDIUM},
  {ACTION_MOVE, 65, 80, MEDIUM},
  {ACTION_MOVE, 65, 90, MEDIUM},
  {ACTION_MOVE, 15, 90, MEDIUM},
  {ACTION_MOVE, 15, 100, MEDIUM},
  {ACTION_MOVE, 65, 100, MEDIUM},
  {ACTION_MOVE, 65, 110, MEDIUM},
  {ACTION_MOVE, 15, 110, MEDIUM},
  {ACTION_MOVE, 15, 120, MEDIUM},
  {ACTION_MOVE, 65, 120, MEDIUM},
  {ACTION_MOVE, 65, 130, MEDIUM},
  {ACTION_MOVE, 15, 130, MEDIUM}
};

int numPatterns = 4;

void setup() 
{ 
  Serial.begin(9600);
  Serial.write("hello");
  pinMode(laserPin, OUTPUT);
  
  vServo.attach(verticalPin); 
  hServo.attach(horizontalPin);
    
  moveVertical(90);
  moveHorizontal(90);
  
  delay(500);
  randomSeed(analogRead(0));
  bootSequence();
  delay(500);
} 
 
 
void loop() 
{ 
  int ptr = random(1, numPatterns+1);
  int rev = random(0,2);
  bool reverse = (rev == 1);
  Serial.print(ptr);
  Serial.write(" ");
  Serial.println(rev);
  
  enableLaser();
  switch(ptr) {
    case 1:
      runPattern(catplay1, 24, reverse);
      break;
    case 2:
      runPattern(catplay2, 10, reverse);
      break;
    case 3:
      runPattern(catplay3, 10, reverse);
      break;
    case 4:
      runPattern(catplay4, 26, reverse);
      break;
  }
  disableLaser();  
}

void runPattern(int pattern[][4], int instructions, bool reverse) {
  int j = 0;
  for (int i = 0; i < instructions; i++) {
    if(reverse) {
      j = instructions - 1 - i;
    } else {
      j = i;
    }
    switch(pattern[j][0]) {
      case ACTION_ENABLE_LASER:
        enableLaser();
        break;
      case ACTION_DISABLE_LASER:
        disableLaser();
        break;
      case ACTION_MOVE:
        moveTo(pattern[j][1], pattern[j][2], pattern[j][3]);
        break;
    }
  }
}

void bootSequence() {
  moveTo(90,90, FAST);
  delay(500);
  enableLaser();
  delay(500);
  disableLaser();
  delay(500);
  enableLaser();
  delay(500);
  disableLaser();
  delay(500);
  enableLaser();
  delay(500); 
  disableLaser();
}

void enableLaser() {
  digitalWrite(laserPin, HIGH);
}

void disableLaser() {
 digitalWrite(laserPin, LOW); 
}

void moveToFast(int vert, int horz) {
  moveVertical(vert);
  moveHorizontal(horz);
}

void moveTo(int vert, int horz, int delayTime) {
  int startV = vServo.read();
  int startH = hServo.read();
  
  int vdir = 1;
  int hdir = 1;
  if ((vert - startV) < 0) {
    vdir = -1;
  }
  if ((horz - startH) < 0) {
    hdir = -1;
  }

  while(startV != vert || startH != horz) {
    if(startV != vert) {
      moveVertical(startV+vdir);
    }
    
    if(startH != horz) {
      moveHorizontal(startH+hdir);
    }
    
    startV = vServo.read();
    startH = hServo.read();
    delay(delayTime);
  }
}

void moveVertical(int angle)
{
  vServo.write(angle);
}

void moveHorizontal(int angle)
{
  hServo.write(angle);
}
