#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;


// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//Controller
controller Controller1;

//Motors for the drivetrain

motor Right1 = motor(PORT20, ratio6_1, false);
motor Right2 = motor(PORT19, ratio6_1, false);
motor Right3 = motor(PORT18, ratio6_1, false);

motor Left1 = motor(PORT16, ratio6_1, true);
motor Left2 = motor(PORT15, ratio6_1, true);
motor Left3 = motor(PORT14, ratio6_1, true);

//The motor constructor takes motors as (port, ratio, reversed), so for example
motor FirstStage = motor(PORT8, ratio6_1, false); // forward intake
motor SecondStage = motor(PORT11, ratio6_1, false); // forward outake / up
motor ThirdStage = motor(PORT12, ratio6_1, false); // forward outake / up
motor ZeroStage = motor(PORT2, ratio6_1, false); // forward up

//Pneumatics
digital_out Matchloader = digital_out(Brain.ThreeWirePort.A);
digital_out ColorSort = digital_out(Brain.ThreeWirePort.B);
digital_out Expansion = digital_out(Brain.ThreeWirePort.C);

//Sensors
optical OpticalTop = optical(PORT4);
optical OpticalBottom = optical(PORT1);
optical OpticalBottom1 = optical(PORT6);

// // AI 
// gps GPSLeft = gps(PORT9, 0, -165, distanceUnits::mm, 180);
// gps GPSRight = gps(PORT12, 0, 165, distanceUnits::mm, 180);
serial_link seriallink = serial_link(PORT1, "Link", linkType::manager);


inertial InertialSensor = inertial(PORT17);


directionType thirdStageDefaultDir = forward;
bool thirdStageOverrideActive = false;

//Add your devices below, and don't forget to do the same in robot-config.h:


void vexcodeInit( void ) {
  // nothing to initialize
}