

#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

// ai::jetson  jetson_comms;

Drive chassis(
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(Left1,Left2,Left3),

//Right Motors:
motor_group(Right1,Right2,Right3),


//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT8,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
356.4,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);


/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

 void pre_auton() {
  // // Initializing Robot Configuration. DO NOT REMOVE!
  // OpticalBottom.setLightPower(100, percent);
  // OpticalTop.setLightPower(100, percent);
  // OpticalBottom.setLight(ledState::on);
  // OpticalTop.setLight(ledState::on);
  // ZeroStage.setVelocity(100, percent);
  // SecondStage.setVelocity(100, percent);
  // ThirdStage.setVelocity(100, percent);
  // FirstStage.setVelocity(100, percent);
  // Expansion.set(true);
  // Matchloader.set(false);
  // // while (InertialSensor.isCalibrating()) {
  // InertialSensor.calibrate();
  // OpticalBottom1.integrationTime(5);
  // OpticalBottom.integrationTime(5);
  //   // Brain.Screen.printAt(10, 10, "Calibrating");
  // // }
  // Brain.Screen.printAt(10,10, "Done Calibrating");
  // // vexcodeInit();
  default_constants();
}



void auto_Isolation(void) {
  // chassis.set_drive_exit_conditions(1.5, 300, 2000);

  // // start with bot backwards, top left park zone black aligns with bottom right of bot
  // // OpticalBottom.objectDetected(onBottomDetected);
  // chassis.set_heading(0);
  // chassis.drive_distance(-36.5);
  // chassis.turn_to_angle(45);
  // // chassis.drive_distance(-5);
  // // ThirdStage.spin(reverse, 50, percent);
  // // SecondStage.spin(forward, 50, percent);
  // // wait(1000, msec);
  // // chassis.drive_distance(6);
  // // wait(500, msec);
  // // chassis.turn_to_angle(-45);
  // // chassis.drive_distance(10);

  // // knocks tower of balls down and grabs at least one ball
  // chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  // chassis.drive_distance(10);
  // // matchloader down to anchor ball
  // // Matchloader.set(true);
  // FirstStage.spin(forward, 100, percent);
  // // SecondStage.spin(forward, 100, percent);
  // wait(500, msec);
  // chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  // // drives back to middle goal scores two balls
  // chassis.drive_distance(-13);
  // SecondStage.spin(forward, 100, percent);
  // ThirdStage.spin(reverse,100,percent);
  // wait(1000, msec);
  // // FirstStage.stop();
  // SecondStage.stop();
  // ThirdStage.stop();
  // // drives to long goal
  // chassis.drive_distance(52);
  // Matchloader.set(true);
  // chassis.turn_to_angle(0);
  // chassis.set_drive_constants(10, 1.5, 0, 10, 0);

  // chassis.drive_distance(14);
  // wait(1000, msec);
  // // chassis.drive_distance(-24);
  // // loads long goal
  // // OpticalTop.objectDetected(onTopDetected);
  // FirstStage.spin(forward, 100, percent);
  // SecondStage.spin(forward, 100, percent);
  // ThirdStage.spin(forward, 100, percent);
  
}





/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        Auto_Interaction Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous interaction*/
/*  phase of a VEX AI Competition.                                           */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void auto_Interaction(void) {

  // // OpticalBottom.setLightPower(100, percent);
  // // OpticalTop.setLightPower(100, percent);
  // Expansion.set(true);
  // Matchloader.set(false);


  // chassis.drive_max_voltage = 8;
  // chassis.drive_distance(22);// Va
  // chassis.turn_to_angle(225);  // se alinea con el middle goal
  // chassis.drive_distance(20);// Va adelante
  // FirstStage.spin(fwd,0,voltageUnits::mV);
  // SecondStage.spin(fwd,6000,voltageUnits::mV);
  // ThirdStage.stop(hold);
  // chassis.drive_distance(48);// Va adelante
  // FirstStage.spin(reverse,12000,voltageUnits::mV);
  // SecondStage.spin(reverse,12000,voltageUnits::mV);
  // ThirdStage.spin(reverse,12000,voltageUnits::mV);
  // chassis.drive_distance(-5);// va atras hacia el long goal
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          AutonomousMain Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void intakeBalls() {
  //   // responsible for intaking balls correctly
  // FirstStage.spin(forward, 100, percent);
  // SecondStage.spin(forward, 100, percent);
  // ThirdStage.spin(thirdStageDefaultDir, 100, percent);
  // while (true) {
  //   if (OpticalBottom1.isNearObject() || OpticalBottom.isNearObject()) {
  //     ZeroStage.spin(forward, 10, percent);
  //   } else {
  //     ZeroStage.spin(forward, 100, percent);
  //   }
  // }
}

distance DistanceTopLeft = distance(PORT15);
distance DistanceTopRight = distance(PORT4);
distance DistanceBottomLeft = distance(PORT13);
distance DistanceBottomRight = distance(PORT9);

distance* distanceArr[4] = {
  &DistanceTopLeft,
  &DistanceTopRight,
  &DistanceBottomLeft,
  &DistanceBottomRight
};
void distanceTest() {
  float distanceThreshold = 8.0;
  while (true) {
    // Clear the screen and set the cursor to the top left corner on each loop
    Brain.Screen.setCursor(1, 1);


    bool bottomNear =
      DistanceBottomLeft.isObjectDetected() &&
      DistanceBottomRight.isObjectDetected() &&
      DistanceBottomLeft.objectDistance(inches) < distanceThreshold &&
      DistanceBottomRight.objectDistance(inches) < distanceThreshold;

    bool topNear =
      (DistanceTopLeft.isObjectDetected() &&
       DistanceTopLeft.objectDistance(inches) < distanceThreshold) ||
      (DistanceTopRight.isObjectDetected() &&
       DistanceTopRight.objectDistance(inches) < distanceThreshold);

    if (bottomNear && topNear) {
      printf("near wall");
      Brain.Screen.print("Near Wall");
      Brain.Screen.newLine();
      chassis.drive_stop(hold);
      chassis.set_heading(0);
      chassis.drive_distance(-10);
      chassis.turn_to_angle(180);
      // callback here
    } else {
      chassis.drive_with_voltage(4,4);
    }

    for (int i = 0; i < 4; i ++) {
      distance* Dist = distanceArr[i];
          
      Brain.Screen.print("%d Found Object?: ", i);
      Brain.Screen.print("%s", Dist->isObjectDetected() ? "TRUE" : "FALSE");
      Brain.Screen.newLine();

      Brain.Screen.newLine();
      Brain.Screen.print("Distance in Inches: ");
      Brain.Screen.print("%.2f", Dist->objectDistance(inches));
    }
    // A brief delay to allow text to be printed without distortion or tearing
    wait(0.2, seconds);
  }  
}



bool firstAutoFlag = true;
void autonomousMain(void) {
  // ..........................................................................
  // The first time we enter this function we will launch our Isolation routine
  // When the field goes disabled after the isolation period this task will die
  // When the field goes enabled for the second time this task will start again
  // and we will enter the interaction period. 
  // ..........................................................................
  // thread colorTop = thread(onTopDetectedThread);
  // thread colorBottom = thread(onBottomDetectedThread); // responsible for opening / closing piston
  // colorBottom.setPriority(15);
  // colorTop.setPriority(14);
  
  distanceTest();

}

bool mbool = false;
bool cbool = false;
// bool dbool = false;
void usercontrol(void) {
  // thread colorTop = thread(onTopDetectedThread);
  // thread colorBottom = thread(onBottomDetectedThread);
  // colorBottom.setPriority(15);
  // colorTop.setPriority(14);
  // User control code here, inside the loop
  // while (1) {
  //   if (Controller1.ButtonR1.pressing()) {
  //     ZeroStage.spin(forward);
  //     FirstStage.spin(forward);
  //     // if (OpticalBottom1.isNearObject() || OpticalBottom.isNearObject()) {
  //     //   SecondStage.stop(brake);
  //     // } else {
  //     //   SecondStage.spin(forward);
  //     // }
  //   } else if (Controller1.ButtonR2.pressing()) {
  //     ZeroStage.spin(reverse);
  //     FirstStage.spin(reverse);
  //     SecondStage.spin(reverse);
  //   } else {
  //     FirstStage.stop(hold);
  //   }
  //   if (!thirdStageOverrideActive) {
  //     if (Controller1.ButtonUp.pressing()) {
  //       ThirdStage.spin(forward, 100, percent);
  //     } else if (Controller1.ButtonDown.pressing()) {
  //       ThirdStage.spin(reverse, 100, percent);
  //     } else if (Controller1.ButtonLeft.pressing()) {
  //       ThirdStage.stop(hold);
  //     }
  //   }

  //   if (Controller1.ButtonA.pressing()) {
  //     mbool = !mbool;
  //     waitUntil(!Controller1.ButtonA.pressing());
  //   }
  //   Matchloader.set(mbool);

  //   if (Controller1.ButtonB.pressing()) {
  //     cbool = !cbool;
  //     waitUntil(!Controller1.ButtonB.pressing());
  //   }
  //   ColorSort.set(cbool);

  //   // OpticalBottom.objectDetected(onBottomDetected);
  //   // OpticalTop.objectDetected(onTopDetected);
  //   // ........................................................................
  //   // Insert user code here. This is where you use the joystick values to
  //   // update your motors, etc.
  //   // ........................................................................
  //   //Replace this line with chassis.control_tank(); for tank drive 
  //   //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  // }
}


void pid_tuning_mode(void) {
  pid_drive_test();
  pid_tune_task();
}

// // Task to periodically send test messages to worker robot
// int sendTask() {
//   // wait for link
//   while( !serialManager.isLinked()) {
//     this_thread::sleep_for(50);
//   }
//   uint8_t buffer[] = {0,1,2,3,4,5,6,7};
//   // send demo message
//   while(1) {
//     serialManager.send(buffer, sizeof(buffer));
//     buffer[0]++;
//     this_thread::sleep_for(500);
//   }
//   return 0;
// }

// void serialManagerAutonTest() {
//   // start demo task
//   thread t1( sendTask );
//   // show link status
//   while(1) {
//     Brain.Screen.printAt( 10, 50, true, "Link: %s", serialManager.isLinked() ? "ok" : "--" );
//     // Allow other tasks to run
//     this_thread::sleep_for(50);
//   }
// }

// // callbacks only print to terminal
// void receive_message( uint8_t *buffer, int32_t length ) {
//   printf("receive_message: %ld bytes were recieved\n", length );
//   for(int i=0;i<length;i++) {
//     printf("%02X ", buffer[i] );
//     printf("\n");
//   }
// }

// void serialWorkerAutonTest() {
//   // register callback
//   serialWorker.received( receive_message );
//   // show link status
//   while(1) {
//     Brain.Screen.printAt( 10, 50, true, "Link: %s", serialWorker.isLinked() ? "ok" : "--" );
//     // Allow other tasks to run
//     this_thread::sleep_for(50);
//   }
// }



//
// Main will set up the competition functions and callbacks.
//
bool isManager = false;

int main() {
  // Run the pre-autonomous function.
  pre_auton();
  // printf("Distance Test");
  // distanceTest();

  // printf("Running program");
  // if (isManager) serialManagerAutonTest();
  // else serialWorkerAutonTest();

  // Set up callbacks for autonomous and driver control periods.
  // Competition.autonomous(autonomousMain);
  distanceTest();
  // Competition.autonomous(autonomousMain);
  // Competition.drivercontrol(usercontrol);


  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
