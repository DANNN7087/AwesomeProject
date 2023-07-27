/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       dlyubchik                                                 */
/*    Created:      7/25/2023, 2:50:29 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// VEXcode device constructors
motor motorLeft = motor(PORT1, ratio18_1, true);
motor motorRight = motor(PORT10, ratio18_1, false);
motor motorArm = motor(PORT8, ratio18_1, false);
sonar ultrasoundBack = sonar(Brain.ThreeWirePort.E);

const float PI = 3.1415;
const float TRACK_WIDTH = 11.515;
const float WHEEL_DIAMETER = 4;
const float MOTOR_TO_DRIVE_WHEEL_RATIO = 1;

void resetValues() {
  motorLeft.stop();
  motorRight.stop();
  motorArm.stop();
}

void moveForwardsDistance(float inches, bool wait) {
  float wheelRevolutions = MOTOR_TO_DRIVE_WHEEL_RATIO*inches/(WHEEL_DIAMETER*PI);
  motorLeft.spinFor(forward, wheelRevolutions, rev, 100, velocityUnits::pct,false);
  motorRight.spinFor(forward, wheelRevolutions, rev, 100, velocityUnits::pct,wait);
}

void moveForwardsRate(float speed) {
  motorLeft.spin(forward, speed, percent);
  motorRight.spin(forward, speed, percent);
}

void turnDegrees(float degrees, bool spinOnCenter, bool wait) {
  //TRACK_WIDTH is in inches
  //one full rotation wheel-travel: TRACK_WIDTH*pi
  float rotations = degrees/360;
  float inchesTravel = rotations*TRACK_WIDTH*PI;
  float wheelRevolutions = MOTOR_TO_DRIVE_WHEEL_RATIO*inchesTravel/(WHEEL_DIAMETER*PI);
  if(spinOnCenter) {
    motorLeft.spinFor(forward, wheelRevolutions, rev, 100, velocityUnits::pct,false);
    motorRight.spinFor(reverse, wheelRevolutions, rev, 100, velocityUnits::pct,wait);
  } else {
    if (degrees > 0) {
      motorLeft.spinFor(forward, wheelRevolutions*2, rev, 100, velocityUnits::pct,false);
    } else {
      motorRight.spinFor(reverse, wheelRevolutions*2, rev, 100, velocityUnits::pct,wait);
    }
  }
}

void drivePolygon(int sides) {
  for (int i = 0; i < sides; i++) {
    moveForwardsDistance(60/sides, true);
    turnDegrees(360/sides, true, true);
  }
}

void moveBackwardUntilCertainDistanceFromObjectInFrontOfRobot(float inches) {
  float Kp = 1; //proportional gain
  float maxP = Kp * 5;
  while (true) {
    float error = ultrasoundBack.distance(vex::distanceUnits::in) - inches;
    float driveP = error * Kp;
    if (driveP > maxP)  {driveP =  maxP;}
    if (driveP < -maxP) {driveP = -maxP;}
    motorLeft.spin(reverse, driveP, pct);
    motorRight.spin(reverse, driveP, pct);
    
  }
}

int main() {
  //float distance = ultrasoundBack.distance(vex::distanceUnits::in);
  // Initializing Robot Configuration. DO NOT REMOVE!
  //vexcodeInit();
  /*motorLeft.setVelocity(100,percent);
  motorRight.setVelocity(100,percent);*/
  //motorLeft.spinFor(forward, 5*15/(4*3.14), rev, 100, velocityUnits::pct,false);
  //motorRight.spinFor(forward, 5*15/(4*3.14), rev, 100, velocityUnits::pct,false);
  /*motorLeft.spin(forward,100,percent);
  motorRight.spin(forward,100,percent);*/
  //turnDegrees(-45, false);
  //drivePolygon(50);
  /*for (int i = 0; i < 4; i++) {
    moveForwards(10);
    turnDegrees(90,true);
  }*/
  /*while (true) {
    char f[] = "ffsdfds";
    float distance = ultrasoundBack.distance(vex::distanceUnits::in);
    printf("Distance: %2.2f in\n", distance);
    if(distance > 3.00){
      moveForwardsRate(-10);
    } else {
      moveForwardsRate(0);
  }*/
  
  /*while (true) {
    distance = ultrasoundBack.distance(vex::distanceUnits::in);
    while (distance > 5) {
      distance = ultrasoundBack.distance(vex::distanceUnits::in);
      moveForwardsRate(-100);
    }
    moveForwardsRate(0);
    turnDegrees(135, true, true);
  }*/
  moveBackwardUntilCertainDistanceFromObjectInFrontOfRobot(12);
  

    /*float distance = ultrasoundBack.distance(vex::distanceUnits::in);
    printf("%2.2f\n", distance);
    wait(1,seconds);*/
    /*motorArm.spinTo(30+sin(tick/57)*30, deg);
    vexDelay(10);
    Brain.Screen.printAt( 10, 50, "Hello V5" );
    Brain.Screen.print(tick);*/
    //Brain.Screen.printAt( 10, 30, "\-  \-   \-     \-   \-   \-\-   \-    \-     \- \-   \-  \_  \-    \-  \-      \-  \- \-  \-  \-  \-\n=-   - =- = - =  -  =- =   _.----~~~~~~-----..__ =   =-   -=-  - = =  -=--  = -\n=#-=  =-# - == ##= -__..------~~~~-     .._     ~~-. #== -#- = =-  ##=-= =#- -\n#===#==___.--.--~~~~     --~~~~---~ __  ~~----.__   ~~~~~~~---...._____#== =##=\n##(~~~~_..----~       ~~--=< O >- .----. -< O >=--~~             ..   .)#=#=##=\n###~-..__..--         ..  ___-----_...__-----___        _.  ~-=___..-~#########\n##==#===#==`   _    ..   (     \" :_.}{._; \" \"   )      _-     '==#=##=====#=#==\n=#-==-== =# \   ~~-      `   " " __###__  ""    '    -~     .'==-=#===#- -=- #=\n-= == -=  -= `-._  ~-.    _`--~~~VvvvvVV~~---'_     ~..    _. #= =  =  ==# - ==\n = -==  - = - == -.     `~##\(            )/###~' .     _.~    -=- = -= -=- -\n= -  -= -   - -    -    `.###\#    {     #/####.'    _-~  - =  - - -  -    = -\n -    -       -  -  -_    -####    !     #####-  ..    -    -       -   -   - -\n                      -._  ~.###   }     ###-~ ___.-~\n                         ~-  \##  / \"   ##.~ /~                      \n                           \ |###  \"   ###' /   \n                            \`/\#######/\' ;                               \n                             ~-.^^^^^^^ .-~                                    \n                                ~~~~~~~~");

}