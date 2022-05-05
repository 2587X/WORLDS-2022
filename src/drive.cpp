#include "main.h"

void set_drive(double left_voltage, double right_voltage){

  left1.move_voltage(left_voltage);
  left2.move_voltage(left_voltage);
  left3.move_voltage(left_voltage);

  right4.move_voltage(right_voltage);
  right5.move_voltage(right_voltage);
  right6.move_voltage(right_voltage);

}

void engage_brake(){
  left1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  left2.set_brake_mode(MOTOR_BRAKE_BRAKE);
  left3.set_brake_mode(MOTOR_BRAKE_BRAKE);

  right4.set_brake_mode(MOTOR_BRAKE_BRAKE);
  right5.set_brake_mode(MOTOR_BRAKE_BRAKE);
  right6.set_brake_mode(MOTOR_BRAKE_BRAKE);

}

void drive_control(){

  // initializes two integers for each joystick and passes them their values
  double leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  double rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  // creates a deadzone for each joystick
  if(abs(leftJoystick) < 10){
    leftJoystick = 0;
  }

  if(abs(rightJoystick) < 10){
    rightJoystick = 0;
  }

  // passes joystick values to the drivetrain
  set_drive(leftJoystick / 127 * 12000, rightJoystick / 127 * 12000);
}
