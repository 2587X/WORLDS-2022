#include "main.h"

void set_drive(int left_voltage, int right_voltage){

  left1.move_voltage(left_voltage);
  left2.move_voltage(left_voltage);
  left1.move_voltage(left_voltage);

  right4.move_voltage(right_voltage);
  right5.move_voltage(right_voltage);
  right6.move_voltage(right_voltage);

}

void drive_control(){

  // initializes two integers for each joystick and passes them their values
  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  // creates a deadzone for each joystick
  if(abs(leftJoystick) < 10){
    leftJoystick = 0;
  }
  
  if(abs(rightJoystick) < 10){
    rightJoystick = 0;
  }

  // passes joystick values to the drivetrain
  set_drive(leftJoystick/127*12000, rightJoystick/127*12000);
}
