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

int main() {

    Brain.Screen.printAt( 10, 50, "Hello V5" );
   
    while(1) {
        
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
