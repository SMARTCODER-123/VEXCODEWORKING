#include "main.h"


const int DRIVE_SPEED = 110;
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;


// Ports for functions below
pros::Motor right_intake(20);
pros::Motor left_intake(14);
pros::ADIDigitalOut horiz_left('G', false);
pros::ADIDigitalOut horiz_right('F', false);
pros::Motor kicker(3);

// pros::Rotation rotationSensor(8);

pros::Motor left1(-12);
pros::Motor left2(-18);
pros::Motor left3(-19);

pros::Motor right1(13);
pros::Motor right2(17);
pros::Motor right3(1);



// Intake
void runIntake() {
    right_intake.move_velocity(-600);
    left_intake.move_velocity(600);
}

void stopIntake() {
    right_intake.move_velocity(0);
    left_intake.move_velocity(0);
}

void runOuttake() {
  right_intake.move_velocity(600);
  left_intake.move_velocity(-600);
}



// Wings
void wingsDown() {
  wings.set_value(true);
}

void wingsUp() {
  wings.set_value(false);
}



// Horizontal Wings
void horiz_wingsDown() {
  horiz_left.set_value(true);
  horiz_right.set_value(true);
}

void horiz_wingsUp() {
  horiz_left.set_value(false);
  horiz_right.set_value(false);
}

void horiz_leftDown() {
  horiz_left.set_value(true);
}

void horiz_leftUp() {
  horiz_left.set_value(false);
}

void horiz_rightDown() {
  horiz_right.set_value(true);
}

void horiz_rightUp() {
  horiz_right.set_value(false);
}


// Kicker
void runKicker() {
  // Max Speed
  kicker.move_velocity(105);
}

void stopKicker() {
  kicker.move_velocity(0);
}



// Braking
void chassisBrake(pros::motor_brake_mode_e_t M) {
  left1.set_brake_mode(M);
  left2.set_brake_mode(M);
  left3.set_brake_mode(M);

  right1.set_brake_mode(M);
  right2.set_brake_mode(M);
  right3.set_brake_mode(M);
}

// void initialize() {
//   pros::Rotation rotationSensor(8);
// }





//AUTONS:





void auton_close_wp(){
  //Retracts the lift piston to raise it(so it doesnt get in the way of corner rings.)
  horiz_leftDown();
  pros::delay(10);
  wingsDown();
  //We swing turn onto our alliance stake.
  //Drives backwards to move initial rings out of the way.
  chassis.set_drive_pid(-14.66,127,true);
  chassis.wait_drive();
  //Goes to prefered position for swing turn.
  chassis.set_drive_pid(12.57 ,127,true);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 97 , 87);
  chassis.wait_drive();
  //We drive back into the wall to make sure our intake is alligned with the stake.
  chassis.set_drive_pid(-4.55, 107, true);
  //Initializing 
  chassis.wait_drive();
  //We run the "Intake" and set a delay so the robot stays in place while scoring. 
  runOuttake();
  pros::delay(500);
  chassis.wait_drive();
  //Goes a little bit forward to put the robot in a posisiton to turn to mogo(avoids rings in field)
  chassis.set_drive_pid(12.5, 127, true);
  chassis.wait_drive();
  //Turns to sweep the extra rings.
  chassis.set_turn_pid(330, 90);
  chassis.wait_drive();
  //Turns to the direction of the Mogo.
  chassis.set_turn_pid(313, 90);
  chassis.wait_drive();
  //drives backwards towards the right side mogo.
  chassis.set_drive_pid(-24.85, 60, true);
  chassis.wait_drive();
  //clamps onto the mogo.
  wingsUp();
  chassis.wait_drive();
  //Goes a little bit backward for clear positioning.
  chassis.set_drive_pid(-4,127,true);
  chassis.wait_drive();
  //Turns towards the ring stack.
  chassis.set_turn_pid(185, 90);
  chassis.wait_drive();
  //Drives towards the ring stack.
  chassis.set_drive_pid(18,127,true);
  //Runs intake to get rings from ring stack. 
  runOuttake();
  //Wait command to allow time to intake rings. 
  chassis.wait_drive();
  //Drives back to have a clear positioning for corner stack. 
  pros::delay(500);
  chassis.set_drive_pid(-18,127,true);
  chassis.wait_drive();
  //Turns to corner stack.
  chassis.set_turn_pid(228, 90);
  chassis.wait_drive();
  kicker.move_velocity(-127); 
  chassis.wait_drive();
  //Driving to the corner stack
  chassis.set_drive_pid(47, 90, true);
  chassis.wait_drive();
  chassis.set_drive_pid(-7,127, true);
  chassis.wait_drive();
  chassis.set_drive_pid(7,127,true);
  //running the intake for it.
  runOuttake();
  pros::delay(800);
  chassis.set_drive_pid(-49, 127, true);
  chassis.wait_drive();
  stopKicker(); 
  chassis.wait_drive();
  //Turns towards the ladder.
  chassis.set_swing_pid(ez::LEFT_SWING, 200, 90); 
  chassis.wait_drive();
  chassis.set_drive_pid(-6,127,true);
  stopIntake();
  

 
  

  


  
  
}



void auton_close_wp_safe(){
  //SKILLS AUTON AS OF NOW 
  /*chassis.set_drive_pid(-0.5, 5, true);
  kicker.move_velocity(-127);
  pros::delay(500);
  chassis.set_drive_pid(5,10,true);
  chassis.wait_drive();
  kicker.move_velocity(127);
  chassis.set_drive_pid(-5,10,true)
  chassis.wait_drive();
  chassis.set_turn_pid(90,90);
  chassis.wait_drive();
  chassis.set_drive_pid()
*/
//Puts the mogule up
wingsDown();
pros::delay(200);
//Moving backward to align with the stake to put the ring in
chassis.set_drive_pid(-4, 6, true);
chassis.wait_drive();
//Outtaking the ring onto the stake
runOuttake();
pros::delay(500);
//stops the intake
stopIntake();
//Moving forward from the stake to go to the first ring
chassis.set_drive_pid(4,10,true);
chassis.wait_drive();
chassis.set_turn_pid(90, TURN_SPEED);
//turning 90 degrees to face the mogo clamp
chassis.wait_drive();
chassis.set_drive_pid(-15, 30, true);
chassis.wait_drive();
//Clamps on to the mogule
wingsUp();

pros::delay(100);
chassis.set_drive_pid(4,40,true);
chassis.wait_drive();
//turn the robot and proceeds to run the outtake and and take in the rings
chassis.set_turn_pid(0, TURN_SPEED);  
chassis.wait_drive();
runOuttake();
chassis.set_drive_pid(13,60,true);
pros::delay(500);
chassis.wait_drive();
chassis.set_turn_pid(90, TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(15,60,true);
pros::delay(500);
chassis.wait_drive();
chassis.set_turn_pid(180, TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(20,30,true);
chassis.wait_drive();
pros::delay(100);
chassis.set_drive_pid(-10,100,true);
chassis.wait_drive();
chassis.set_turn_pid(160,TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(10,70, true);
chassis.wait_drive();
pros::delay(50);
stopIntake();
chassis.set_turn_pid(-30,TURN_SPEED);
runOuttake();
pros::delay(100);
stopIntake();
chassis.set_drive_pid(-5,70, true);
chassis.wait_drive();
//releases the mogo into the postive side
wingsDown();
pros::delay(70);
//Moves forward after placing the mogul and turn to the left to go get the next mogul
chassis.set_drive_pid(5,70, true);
chassis.wait_drive();
//Turning before it goes to the other mogo goal
chassis.set_turn_pid(90,TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(-50, 127, true);
chassis.wait_drive();
chassis.set_drive_pid(-5,30,true);
chassis.wait_drive();
// Clamps on to the mogo goal
wingsUp();
pros::delay(100);
chassis.set_drive_pid(5, 30, true);
chassis.wait_drive();
chassis.set_turn_pid(0,TURN_SPEED);
chassis.wait_drive();
runOuttake();
chassis.set_drive_pid(14, 80, true);
pros::delay(600);
chassis.wait_drive();
chassis.set_turn_pid(-90, 127);
chassis.wait_drive();
chassis.set_drive_pid(10, 80, true);
chassis.wait_drive();
pros::delay(400);
chassis.set_turn_pid(180, TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(8, 40, true);
chassis.wait_drive();
runOuttake();
chassis.wait_drive();













  }



void auton_far_qual(){ 
  wingsDown();
  pros::delay(100);
  chassis.set_drive_pid(-26, 35, true);
  chassis.wait_drive();
  wingsUp();
  pros::delay(400);
  runIntake();
  chassis.set_turn_pid(110, 60);
  pros::delay(100);
  chassis.wait_drive();
  chassis.set_drive_pid(25, 80, true);
   chassis.wait_drive();
   runIntake();
  chassis.set_drive_pid(-5,60,true);
  chassis.wait_drive();
  pros::delay(100);
  chassis.set_turn_pid(180,40);
  chassis.wait_drive();
  chassis.set_drive_pid(10,60,true);
  chassis.wait_drive();
  chassis.set_drive_pid(3,60,true);
  chassis.wait_drive();
  chassis.set_drive_pid(-6,60,true);
  chassis.set_turn_pid(140,40); 
  chassis.wait_drive();
  chassis.set_drive_pid(9,60,true);
  chassis.wait_drive();
  chassis.set_drive_pid(-7,60,true);




  //Blue left side Auton 
  //Sets down our lift piston as we no longer have to fit in size contraint. 
  /*horiz_leftUp();
  pros::delay(400);
  //Raises our lift
  kicker.move_velocity(-600);
  //Gives an ample amount of time for the lift to raise
  pros::delay(500);
  //
  horiz_leftDown();
  //Drives slighlty back to allow lift to go fully up. 
  chassis.set_drive_pid(-0.5,10,true);
  chassis.wait_drive();
  //Turns towards the alliance stake
  chassis.set_turn_pid(-42.87, TURN_SPEED);
  pros::delay(400);
  chassis.wait_drive();
  //Drives forward towards the alliance stake.
  chassis.set_drive_pid(4.1,10,true);
  chassis.wait_drive();
  horiz_leftUp();
  //The lift moves fully down at max speed
  kicker.move_velocity(600);
  //This allows time for 
  pros::delay(400);
  stopKicker();
  chassis.wait_drive();
  chassis.set_drive_pid(-9,10,true);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, -97, SWING_SPEED);
  chassis.wait_drive();
  kicker.move_velocity(-600);
  horiz_rightDown();
  pros::delay(500);
  chassis.set_drive_pid(8.4,5,true);
  chassis.wait_drive();
  horiz_rightUp();
  pros::delay(200);
  runOuttake();
  pros::delay(300);
  stopIntake();
  //Turns backwards towards mogo 
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  wingsDown();
  pros::delay(100);
  chassis.set_drive_pid(-34,90,true);
  chassis.wait_drive();
  pros::delay(200);
  wingsUp();
  chassis.set_drive_pid(-4, 60, true);
  runOuttake();
  pros::delay(300);
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(90, 110);
  chassis.wait_drive();
  runOuttake();
  pros::delay(300);
  chassis.set_drive_pid(17, 110, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-2, 110);
  chassis.wait_drive();
  chassis.set_drive_pid(-5, 110, true);
  chassis.wait_drive();
  chassis.set_drive_pid(20, 110, true);
  chassis.wait_drive();
  stopIntake();
*/



   
}



void auton_far_elim(){
  horiz_leftDown();
  chassis.set_drive_pid(-26, 40, true);
   //Raises lift in beginning  
  chassis.wait_drive();
  //Raises the mogo clamp
  wingsDown();
  //Drives backwards onto first mogo(directly in front of starting position )
  chassis.set_drive_pid(-19, 40, true);
  chassis.wait_drive();
  //Mogo mech clamps down onto Mogo.
  wingsUp();
  pros::delay(500); // Better version of chassis.wait_drive; custom amount of wait
  runOuttake();
  pros::delay(500);
  chassis.set_drive_pid(-3, 40, true);
  chassis.wait_drive();
  //Turns towards stack of rings on line.
  chassis.set_turn_pid(145, TURN_SPEED);
  chassis.wait_drive();
  //drives towards the front stack of rings(outer edge).
  chassis.set_drive_pid(13.4, 120, true);
  chassis.wait_drive();
  //Swings onto the line of rings
  chassis.set_swing_pid(ez::RIGHT_SWING, 82, SWING_SPEED);
  //Runs the intake
  //Outtake = intake because hooks spin in opposite direction
  chassis.wait_drive();
  //Drives forward into the stack and near the wall stake
  chassis.set_drive_pid(12, 15, true);
  runOuttake();
  pros::delay(1000);
  stopIntake(); 
  chassis.set_drive_pid(13, 15, true);
  runOuttake();
  pros::delay(500);
  chassis.wait_drive();
  chassis.set_turn_pid(78.5, TURN_SPEED);
  //We allow it ample time for it to do down and be stable.
  chassis.set_turn_pid(-17.5, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(32, 100, true);
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(20);
  kicker.move_velocity(-127);
  pros::delay(500);
  chassis.set_drive_pid(31, 127, true);
  runOuttake();
  pros::delay(500);
  stopKicker();




  /*chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(4, 100, true);
  chassis.wait_drive();
  pros::delay(200);
  stopIntake();
  chassis.set_turn_pid(-45, TURN_SPEED);
  runOuttake();
  chassis.wait_drive();
  chassis.set_drive_pid(35, 100, true);
  pros::delay(50);
  stopIntake();
  chassis.wait_drive();
  chassis.set_turn_pid(-60, TURN_SPEED);*/
  
    
}



void auton_close_elim(){
  chassis.set_drive_pid(8.4, 30, true);
  runKicker();
  pros::delay(1750);
  kicker.move_velocity(-127);
  pros::delay(560);
  chassis.set_turn_pid(20,40);
  chassis.wait_drive();
  stopKicker();
  wings.set_value(true);
  chassis.set_drive_pid(-43, 65, true);
  chassis.wait_drive();
  pros::delay(50);
  wings.set_value(false);
  pros::delay(50);
  chassis.wait_drive();
  chassis.set_drive_pid(8, 80, true);
  chassis.wait_drive();
  chassis.set_turn_pid(138,100);
  runIntake();
  pros::delay(100);
  chassis.wait_drive();
  chassis.set_drive_pid(25, 80, true);
  chassis.wait_drive();
  pros::delay(100);
  chassis.set_drive_pid(-15, 80, true);
  pros::delay(300);
  stopIntake; 
  chassis.wait_drive();
  chassis.set_turn_pid(201, 110);
  runIntake();
  chassis.wait_drive();
  chassis.set_drive_pid(21.85, 50, true);
  chassis.wait_drive();
  pros::delay(300);
  chassis.set_drive_pid(-15.75,70, true);
  chassis.wait_drive();
  chassis.set_turn_pid(177, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(19.79, 50, true);
  chassis.wait_drive();
  pros::delay(300);
  chassis.set_drive_pid(-23, 50, true);
  chassis.wait_drive();
  chassis.set_turn_pid(300,110);
  chassis.wait_drive();
  chassis.set_drive_pid(28, 70, true);
  chassis.wait_drive();



  


  
  /*wingsDown();
  chassis.set_swing_pid(ez::LEFT_SWING, 90, 60);
  chassis.wait_drive();
  runKicker();
  chassis.set_drive_pid(3, 30, true);
  pros::delay(1000);
  chassis.set_drive_pid(-5, 30, true);
  kicker.move_velocity(-127);
  pros::delay(1000);
  stopKicker();
  pros::delay(100);
  chassis.set_drive_pid(-24, 25, true);
  chassis.wait_drive();
  pros::delay(100);
  wingsUp();
  chassis.wait_drive();
  runIntake();
  pros::delay(50);
  chassis.set_drive_pid(-3, 40, true);
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(90,40);
  chassis.wait_drive();
  runIntake();
  pros::delay(1000);
  chassis.set_drive_pid(18, 40, true);
   chassis.wait_drive();
  chassis.set_drive_pid(-5,60,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180,40);
  chassis.set_drive_pid(10,60,true);
  chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
*/




  




 /* //Sets down our lift piston as we no longer have to fit in size contraint. 
  horiz_leftUp();
  pros::delay(400);
  //Raises our lift
  kicker.move_velocity(-600);
  //Gives an ample amount of time for the lift to raise
  pros::delay(500);
  //
  horiz_leftDown();
  //Drives slighlty back to allow lift to go fully up. 
  chassis.set_drive_pid(-0.5,10,true);
  chassis.wait_drive();
  //Turns towards the alliance stake
  chassis.set_turn_pid(42.87, TURN_SPEED);
  pros::delay(400);
  chassis.wait_drive();
  //Drives forward towards the alliance stake.
  chassis.set_drive_pid(4.1,10,true);
  chassis.wait_drive();
  horiz_leftUp();
  //The lift moves fully down at max speed
  kicker.move_velocity(600);
  //This allows time for 
  pros::delay(400);
  stopKicker();
  chassis.wait_drive();
  chassis.set_drive_pid(-9,10,true);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 97, SWING_SPEED);
  chassis.wait_drive();
  kicker.move_velocity(-600);
  horiz_rightDown();
  pros::delay(500);
  chassis.set_drive_pid(8.4,5,true);
  chassis.wait_drive();
  horiz_rightUp();
  pros::delay(200);
  runOuttake();
  pros::delay(300);
  stopIntake();
  //Turns backwards towards mogo 
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  wingsDown();
  pros::delay(100);
  chassis.set_drive_pid(-34,90,true);
  chassis.wait_drive();
  pros::delay(200);
  wingsUp();
  chassis.set_drive_pid(-4, 60, true);
  runOuttake();
  pros::delay(300);
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(-90, 110);
  chassis.wait_drive();
  runOuttake();
  pros::delay(300);
  chassis.set_drive_pid(17, 110, true);
  chassis.wait_drive();
  chassis.set_turn_pid(2, 110);
  chassis.wait_drive();
  chassis.set_drive_pid(-5, 110, true);
  chassis.wait_drive();
  chassis.set_drive_pid(20, 110, true);
  chassis.wait_drive();
  stopIntake();

*/
  
}



void skills_auton(){
  /*/ horiz_leftDown();
   //Raises lift in beginning  
  chassis.wait_drive();
  //Raises the mogo clamp
  wingsDown();
  //Drives backwards onto first mogo(directly in front of starting position )
  chassis.set_drive_pid(-19, 40, true);
  chassis.wait_drive();
  //Mogo mech clamps down onto Mogo.
  wingsUp();
  pros::delay(500); // Better version of chassis.wait_drive; custom amount of wait
  runOuttake();
  pros::delay(500);
  chassis.set_drive_pid(-3, 40, true);
  chassis.wait_drive();
  //Turns towards stack of rings on line.
  chassis.set_turn_pid(-145, TURN_SPEED);
  chassis.wait_drive();
  //drives towards the front stack of rings(outer edge).
  chassis.set_drive_pid(13.45, 120, true);
  chassis.wait_drive();
  //Swings onto the line of rings
  chassis.set_swing_pid(ez::LEFT_SWING, -90, SWING_SPEED);
  //Runs the intake
  //Outtake = intake because hooks spin in opposite direction
  chassis.wait_drive();
  //Drives forward into the stack and near the wall stake
  chassis.set_drive_pid(12, 15, true);
  runOuttake();
  pros::delay(1000);
  stopIntake(); 
  chassis.set_drive_pid(15, 15, true);
  runOuttake();
  pros::delay(500);
  chassis.wait_drive();
  chassis.set_turn_pid(-78.5, TURN_SPEED);
  //We allow it ample time for it to do down and be stable.
  chassis.set_turn_pid(17.5, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(32, 100, true);
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(130, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(20);
  kicker.move_velocity(-127);
  pros::delay(500);
  chassis.set_drive_pid(31, 127, true);
  runOuttake();
  pros::delay(500);
  stopKicker();
*/
}










//heyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy











// Constants

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  //default: chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, .75, 0.0, 6, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, .75, 0.0, 6, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}

// Interference example
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}