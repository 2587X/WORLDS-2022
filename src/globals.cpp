#include "main.h"


pros::Motor intake (intake_port, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor lift (lift_port, pros::E_MOTOR_GEARSET_36, pros::E_MOTOR_ENCODER_COUNTS);

//left from lift side
pros::Motor left1 (left1_port, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor left2 (left2_port, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor left3 (left3_port, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_COUNTS);

//right from lift side
pros::Motor right4 (right4_port, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor right5 (right5_port, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor right6 (right6_port, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_COUNTS);

pros::Controller controller(pros::E_CONTROLLER_MASTER);
