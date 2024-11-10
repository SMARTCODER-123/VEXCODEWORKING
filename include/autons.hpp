#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;
extern pros::Motor fly_wheel;
extern pros::Motor blocker;
extern pros::Controller master;
extern pros::ADIDigitalOut wings;
extern pros::ADIDigitalOut intake;
extern pros::ADIDigitalOut ratchet;


void auton_far_elim();
void auton_far_qual();
void auton_close_wp();
void auton_close_wp_safe();
void auton_close_elim();
void skills_auton();


void wait_until_change_speed();
void interfered_example();
void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();