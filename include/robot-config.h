using namespace vex;

enum OBJECT {
  BallBlue,
  BallRed,
  BallUndefined
};

#define TEAMCOLOR BallRed

extern brain Brain;

//Controller
extern controller Controller1;

//Motors
extern motor FirstStage;
extern motor SecondStage;
extern motor ThirdStage;

extern motor Right1;
extern motor Right2;
extern motor Right3;

extern motor Left1;
extern motor Left2;
extern motor Left3;

//Sensors

extern optical OpticalTop;
extern optical OpticalBottom;
extern optical OpticalBottom1;

//Pistons
extern digital_out Matchloader;
extern digital_out ColorSort;
extern digital_out Expansion;

// // AI
// extern gps GPSLeft;
// extern gps GPSRight;

extern inertial InertialSensor;


extern directionType thirdStageDefaultDir;
extern bool thirdStageOverrideActive;
//Drivetrain Motors



//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:



void  vexcodeInit( void );