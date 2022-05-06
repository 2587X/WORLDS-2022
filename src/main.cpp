#include "main.h"

auto Chassis = okapi::ChassisControllerBuilder()
    .withMotors({12, 13, 14}, {18, 17, 16})
    .withDimensions({AbstractMotor::gearset::blue, (8 / 2)}, {{3.25_in, 12.4_in}, imev5BlueTPR})
    .withMaxVelocity(600)
    .build();

  std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(Chassis->getModel());

    std::shared_ptr<okapi::AsyncMotionProfileController> drive = AsyncMotionProfileControllerBuilder()
      .withLimits({
        2.7, //max linear velocity of Chassis in m/s
        9, //max linear acceleration in m/s^2
        18.0 //max linear jerk in m/s^3
      })
      .withOutput(Chassis)
      .buildMotionProfileController();

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {

	pros::lcd::initialize();

	pros::lcd::set_text(0, "2587X DISCOBOTS XENON");

	engage_brake();

  drive->generatePath({
  {0_ft, 0_ft, 0_deg},
  {1.5_ft, 0_ft, 0_deg}},
  "Left Rush"
  );

  drive->generatePath({
  {0_ft, 0_ft, 0_deg},
  {0.5_ft, 0_ft, 0_deg}},
  "Goal Pickup"
  );
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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

void central_rush(){


	drive->setTarget("Central Rush");

  cover.set_value(true);

	drive->waitUntilSettled();

  drive->setTarget("Central Rush", true);

  drive->waitUntilSettled();
}

void left_rush(){

  drive->setTarget("Left Rush");

  cover.set_value(true);

  drive->waitUntilSettled();

  drive->setTarget("Left Rush", true);

  drive->waitUntilSettled();

  drive->setTarget("Goal Pickup");

  drive->waitUntilSettled();

}

void autonomous() {

	central_rush();
  //
  left_rush();

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
 * task, not resume it from where it left off.
 */



void opcontrol() {

	engage_brake();

	while (true) {



		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){

			if(clampIsOpen == false){

					clampIsOpen = true;

					clamp.set_value(true);

			} else if (clampIsOpen == true) {

					clamp.set_value(false);

					clampIsOpen = false;

			}
		}



		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
			if (coverIsDown == true){

				coverIsDown = false;
			  cover.set_value(false);

			} else if (coverIsDown == false){

				coverIsDown = true;
				cover.set_value(true);

			}
		}



		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){

			intake.move_voltage(12000);

		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){

			intake.move_voltage(-6000);

		} else {

			intake.move_voltage(0);

		}

    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
      central_rush();
    }


		drive_control();
		pros::delay(20);
	}
}
