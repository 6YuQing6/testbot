#include "vex.h"

// PID Tuning variables
struct PIDTuneValues {
  double drive_kP = 1.5;
  double drive_kI = 0;
  double drive_kD = 10;
  double turn_kP = 0.4;
  double turn_kI = 0.03;
  double turn_kD = 3;
};

PIDTuneValues pidTune;
int tuneIndex = 0; // 0=drive_kP, 1=drive_kI, 2=drive_kD, 3=turn_kP, 4=turn_kI, 5=turn_kD
double tuneIncrement = 0.1;

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants() {
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){

  // FirstStage.spin(fwd);
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    // task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

/**
 * PID Tuning Function
 * Use controller buttons:
 * - Button UP: Increase current PID value
 * - Button DOWN: Decrease current PID value
 * - Button RIGHT: Next PID parameter
 * - Button LEFT: Previous PID parameter
 * - Button B: Increase increment step
 * - Button A: Decrease increment step
 * - Button X: Apply changes to chassis
 * - Button Y: Print current values to console
 */

void pid_tune_task() {
  bool upPressed = false;
  bool downPressed = false;
  bool leftPressed = false;
  bool rightPressed = false;
  bool aPressed = false;
  bool bPressed = false;
  bool xPressed = false;
  bool yPressed = false;
  
  const char* paramName[] = {"Drive kP", "Drive kI", "Drive kD", "Turn kP", "Turn kI", "Turn kD"};
  
  while(true) {
    Brain.Screen.clearScreen();
    
    // Display title
    Brain.Screen.printAt(5, 10, "=== PID TUNING ===");
    Brain.Screen.printAt(5, 30, "Parameter: %s", (int)paramName[tuneIndex]);
    Brain.Screen.printAt(5, 50, "Increment: %.3f", tuneIncrement);
    
    // Display current values
    Brain.Screen.printAt(5, 80, "Drive PID: kP=%.3f kI=%.3f kD=%.3f", 
                        pidTune.drive_kP, pidTune.drive_kI, pidTune.drive_kD);
    Brain.Screen.printAt(5, 100, "Turn PID:  kP=%.3f kI=%.3f kD=%.3f", 
                        pidTune.turn_kP, pidTune.turn_kI, pidTune.turn_kD);
    
    // Display instructions
    Brain.Screen.printAt(5, 130, "UP/DOWN: Adjust | L/R: Switch Param");
    Brain.Screen.printAt(5, 150, "A/B: Change Step | X: Apply | Y: Print");
    
    // Button UP - Increase value
    if(Controller1.ButtonUp.pressing() && !upPressed) {
      upPressed = true;
      switch(tuneIndex) {
        case 0: pidTune.drive_kP += tuneIncrement; break;
        case 1: pidTune.drive_kI += tuneIncrement; break;
        case 2: pidTune.drive_kD += tuneIncrement; break;
        case 3: pidTune.turn_kP += tuneIncrement; break;
        case 4: pidTune.turn_kI += tuneIncrement; break;
        case 5: pidTune.turn_kD += tuneIncrement; break;
      }
    } else if(!Controller1.ButtonUp.pressing()) {
      upPressed = false;
    }
    
    // Button DOWN - Decrease value
    if(Controller1.ButtonDown.pressing() && !downPressed) {
      downPressed = true;
      switch(tuneIndex) {
        case 0: pidTune.drive_kP -= tuneIncrement; break;
        case 1: pidTune.drive_kI -= tuneIncrement; break;
        case 2: pidTune.drive_kD -= tuneIncrement; break;
        case 3: pidTune.turn_kP -= tuneIncrement; break;
        case 4: pidTune.turn_kI -= tuneIncrement; break;
        case 5: pidTune.turn_kD -= tuneIncrement; break;
      }
    } else if(!Controller1.ButtonDown.pressing()) {
      downPressed = false;
    }
    
    // Button RIGHT - Next parameter
    if(Controller1.ButtonRight.pressing() && !rightPressed) {
      rightPressed = true;
      tuneIndex = (tuneIndex + 1) % 6;
    } else if(!Controller1.ButtonRight.pressing()) {
      rightPressed = false;
    }
    
    // Button LEFT - Previous parameter
    if(Controller1.ButtonLeft.pressing() && !leftPressed) {
      leftPressed = true;
      tuneIndex = (tuneIndex - 1 + 6) % 6;
    } else if(!Controller1.ButtonLeft.pressing()) {
      leftPressed = false;
    }
    
    // Button B - Increase increment
    if(Controller1.ButtonB.pressing() && !bPressed) {
      bPressed = true;
      tuneIncrement *= 2;
      if(tuneIncrement > 10) tuneIncrement = 10;
    } else if(!Controller1.ButtonB.pressing()) {
      bPressed = false;
    }
    
    // Button A - Decrease increment
    if(Controller1.ButtonA.pressing() && !aPressed) {
      aPressed = true;
      tuneIncrement /= 2;
      if(tuneIncrement < 0.001) tuneIncrement = 0.001;
    } else if(!Controller1.ButtonA.pressing()) {
      aPressed = false;
    }
    
    // Button X - Apply changes to chassis
    if(Controller1.ButtonX.pressing() && !xPressed) {
      xPressed = true;
      chassis.set_drive_constants(10, pidTune.drive_kP, pidTune.drive_kI, pidTune.drive_kD, 0);
      chassis.set_turn_constants(12, pidTune.turn_kP, pidTune.turn_kI, pidTune.turn_kD, 15);
      Brain.Screen.printAt(5, 170, ">> Changes Applied! <<");
    } else if(!Controller1.ButtonX.pressing()) {
      xPressed = false;
    }
    
    // Button Y - Print values
    if(Controller1.ButtonY.pressing() && !yPressed) {
      yPressed = true;
      Brain.Screen.printAt(5, 170, "Values printed to console");
      printf("Current PID Values:\n");
      printf("Drive: kP=%.3f, kI=%.3f, kD=%.3f\n", pidTune.drive_kP, pidTune.drive_kI, pidTune.drive_kD);
      printf("Turn:  kP=%.3f, kI=%.3f, kD=%.3f\n", pidTune.turn_kP, pidTune.turn_kI, pidTune.turn_kD);
    } else if(!Controller1.ButtonY.pressing()) {
      yPressed = false;
    }
    
    wait(20, msec);
  }
}

/**
 * Simple PID drive test for tuning
 * Drive forward 24 inches and measure overshoot/settling time
 */
void pid_drive_test() {
  chassis.drive_distance(24);
}

/**
 * Simple PID turn test for tuning
 * Turn 90 degrees and measure accuracy
 */
void pid_turn_test() {
  chassis.turn_to_angle(90);
}