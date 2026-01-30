#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

BallCounter counter(6);
vex::timer ColorSortTimer;

int detectBallFromHue(int hue) {
  if ((hue >= 300 && hue <= 359) || (hue >= 0 && hue <= 50)) {
    return BallRed;
  }
  if (hue >= 160 && hue <= 250) {
    return BallBlue;
  }
  return BallUndefined;
}

void onCountBall() {
  if (counter.countBall()) {
    Brain.Screen.printAt(10, 50, "Ball added! Count: %d", counter.balls());
  } else {
    Brain.Screen.printAt(10, 50, "Count full (%d)", counter.balls());
  }
}

enum ColorState {
  COLOR_IDLE = 0,
  COLOR_EJECTING,
  COLOR_RESET
};

int colorState = COLOR_IDLE;
int colorTimer = 0;

int onBottomDetectedThread() {
  // Optical setup (run once)
  OpticalBottom.setLightPower(100, percent);
  OpticalBottom1.setLightPower(100, percent);
  OpticalBottom.setLight(ledState::on);
  OpticalBottom1.setLight(ledState::on);

  // OpticalBottom.objectDetectThreshold(255);
  // OpticalBottom1.objectDetectThreshold(255);
  OpticalBottom1.objectLost(onCountBall);

  while (true) {
    if (OpticalBottom.isNearObject() || OpticalBottom1.isNearObject()) {
      int hue0 = OpticalBottom.hue();
      int hue1 = OpticalBottom1.hue();
      int avgHue = (hue0 + hue1) / 2;
      Brain.Screen.printAt(10, 20, "Hue1: %d, Hue2: %d", hue0, hue1);
      Brain.Screen.printAt(10, 30, "Average Hue: %d", avgHue);

      int detected = BallUndefined;

      // Classify independently
      int d0 = OpticalBottom.isNearObject() ? detectBallFromHue(hue0) : BallUndefined;
      int d1 = OpticalBottom1.isNearObject() ? detectBallFromHue(hue1) : BallUndefined;

      if (d0 == d1) {
        detected = d0;
      } else if (d0 != BallUndefined) {
        detected = d0;
      } else if (d1 != BallUndefined) {
        detected = d1;
      } else {
        detected = detectBallFromHue(avgHue);
      }
      Brain.Screen.printAt(10, 40, "Detected Color: %d", detected);
      
      // Wrong color → eject
      if (detected != TEAMCOLOR) {
        colorState = COLOR_EJECTING;
      }
    }    
    switch (colorState) {

      case COLOR_IDLE: {
        Brain.Screen.printAt(10, 70, "State: Color Idle");
        break;
      }

      // ───────────────────────────────
      case COLOR_EJECTING: {
          Brain.Screen.printAt(10, 70, "State: Color Eject");
          ColorSort.set(true);
          counter.removeBall();
          colorTimer = ColorSortTimer.time();
          colorState = COLOR_RESET;
          break;
      }

      // ───────────────────────────────
      case COLOR_RESET: {
        Brain.Screen.printAt(10, 70, "State: Color Reset");

        int currentTime = ColorSortTimer.time();
        // after 200 msec set false
        if (currentTime > colorTimer + 500) {
          Brain.Screen.printAt(10, 90, "Closing Color Sort");
          ColorSort.set(false);
          colorTimer = 0;
          colorState = COLOR_IDLE;
        }
        break;
      }
    }

    // Let auton & other tasks run
    this_thread::sleep_for(20);
  }

  return 0;
}


// called when bottom optical *detects* a new object
void onBottomDetected() {
  // attempt to add a ball
  Brain.Screen.print("Bottom detected");
  int hue = OpticalBottom.hue();
  int detected = BallUndefined;

    // RED: 350–359 and 0–10
  if ((hue >= 300 && hue <= 359) ||
      (hue >= 0   && hue <= 50)) {
    detected = BallRed;
  }

  // BLUE: 210–240
  if (hue >= 160 && hue <= 250) {
    detected = BallBlue;
  }
  Brain.Screen.printAt(10, 90, "Detected hue: %d Color: %d", hue, detected);


  if (TEAMCOLOR != detected) {
    ColorSort.set(true);
    wait(500, msec);
  } else {
    if (counter.countBall()) {
      Brain.Screen.printAt(10, 50, "Ball added! Count: %d", counter.balls());
    } else {
      Brain.Screen.printAt(10, 50, "Count full (%d)", counter.balls());
    }
  }

  ColorSort.set(false);
}

// called when top optical *detects* a new object being sorted out
void onTopDetected() {
    // Brain.Screen.print("Top detected");

  int hue = OpticalTop.hue();
  // bool shouldSort = false;
  int detected = BallUndefined;

  if ((hue >= 300 && hue <= 359) ||
      (hue >= 0   && hue <= 50)) {
    // shouldSort = true;
    detected = BallRed;
  }
  // BLUE: 210–240
  if (hue >= 160 && hue <= 260) {
    detected = BallBlue;
  }
  
  Brain.Screen.printAt(10, 90, "Detected hue: %d Color: %d", hue, detected);


  // Only eject if it's the wrong color and we're not already ejecting
  if (TEAMCOLOR != detected ) {
    ColorSortTimer.event([]() {
      // eject
      ThirdStage.spin(reverse, 12000, voltageUnits::mV);
      wait(500, msec);

      // restore normal behavior
      ThirdStage.spin(thirdStageDefaultDir, 12000, voltageUnits::mV);
    }, 100);
  } else {
    ThirdStage.spin(thirdStageDefaultDir, 12000, voltageUnits::mV);
  }
}

