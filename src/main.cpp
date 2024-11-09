#include "main.h"



// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
 // {12, 13, 14}
  {-12, -19, -11}


  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  //,{20, 18, 17}
  ,{13, 17, 4}

  // IMU Port
  // TODO: Mount IMU
  ,5

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.3333

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

//  PROS materials used for the robots movement on the map. 
pros::Motor slapper(3);
pros::Motor blocker(20);
pros::Motor blocker2(14);
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::ADIDigitalOut wings('E', false);
pros::ADIDigitalOut horiz_left_wing('G', false);
pros::ADIDigitalOut horiz_right_wing('F', false);
pros::ADIDigitalOut hang('C', false);
pros::Rotation rotationSensor(8);



bool kicker_toggle = false;
bool slapper_on = false;
bool slapper2_on = false;
bool wings_on = false;
bool horiz_left_wing_on = false;
bool horiz_right_wing_on = false;
bool hang_on = false;




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D

  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0.1); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("Far Qual", auton_far_qual),
    Auton("Far Elim", auton_far_elim),
    Auton("Close WP", auton_close_wp),
    Auton("Close WP Safe", auton_close_wp_safe),
    Auton("Close Elim", auton_close_elim),
    Auton("Skills Auton", skills_auton),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}

void rotateToTarget(double angle)
{
  if (rotationSensor.get_angle() < angle) {
        slapper.move_velocity(100);
        while (rotationSensor.get_angle() < angle) {
            pros::delay(20);
        }
  }
  else 
  {
      slapper.move_velocity(-100);
      while (rotationSensor.get_angle() > angle){
        pros::delay(20);
      }
  }
  slapper.move_velocity(0);
    
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off
 */


void opcontrol(){
  
  // Driving Functions

  slapper_on = false;
  slapper2_on = false;
  kicker_toggle = false;
  wings_on = false;
  horiz_left_wing_on = true;
  horiz_right_wing_on = false;
  hang_on = false;
  bool isRunning = true;
  double angle = 540.0;
  

  wings.set_value(wings_on);
  horiz_left_wing.set_value(horiz_left_wing_on);
  horiz_right_wing.set_value(horiz_right_wing_on);
  hang.set_value(hang_on);
  slapper.move(0);
  blocker.set_brake_mode(MOTOR_BRAKE_HOLD);
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);


  while (true) {
    
    chassis.tank();
    if (slapper_on) {
      slapper.move(-127);
    } else {
      if (!slapper2_on) {
        slapper.move(0);
      }
    }


  // WINGS TOGGLE:
    bool wings_toggle = master.get_digital_new_press(DIGITAL_B) == 1;
    if (wings_toggle) {
      wings_on = !wings_on;
      wings.set_value(wings_on);
    }

 //

  // HORIZONTAL LEFT WING TOGGLE
  bool horiz_left_wing_toggle = master.get_digital_new_press(DIGITAL_LEFT) == 1;
    if (horiz_left_wing_toggle) {
      horiz_left_wing_on = !horiz_left_wing_on;
      horiz_left_wing.set_value(horiz_left_wing_on);
    }
  
  // HORIZONTAL RIGHT WING TOGGLE
  bool horiz_right_wing_toggle = master.get_digital_new_press(DIGITAL_RIGHT) == 1;
    if (horiz_right_wing_toggle) {
      horiz_right_wing_on = !horiz_right_wing_on;
      horiz_right_wing.set_value(horiz_right_wing_on);
    }

 
  // HANG TOGGLE:
  bool hang_toggle = master.get_digital_new_press(DIGITAL_A) == 1;


  if (hang_toggle) {
    hang_on = !hang_on;
    hang.set_value(hang_on);
  }

  // KICKER TOGGLE
  bool kicker_toggle_button = master.get_digital_new_press(DIGITAL_R2) == 1; // Change the button as per your preference
  if (kicker_toggle_button) {
    kicker_toggle = !kicker_toggle;
  }

  if (kicker_toggle) {
    slapper.move_velocity(105); 
  } else {
    slapper.move(0);
  }
  // lift goes up
  if (master.get_digital(DIGITAL_R1)) {
    slapper.move_velocity(-600);
  } else if (master.get_digital(DIGITAL_R2)){
    slapper.move_velocity(600);
  } else {
    slapper.move(0);
  }


  // INTAKE MOTORS TOGGLE:
  if (master.get_digital(DIGITAL_L1)) {
    blocker.move(-127);
    blocker2.move(127); 
  } else if (master.get_digital(DIGITAL_L2)) {
    blocker.move(127);
    blocker2.move(-127);
  } else {
    blocker.move(0);
    blocker2.move(0);
  }
  


    pros::delay(ez::util::DELAY_TIME); 
  }
}