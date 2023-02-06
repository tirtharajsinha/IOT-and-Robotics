#include <AFMotor.h>

AF_DCMotor motor(4);

void setup() 
{
	//Set initial speed of the motor & stop
	motor.setSpeed(255);
	motor.run(RELEASE);
  Serial.begin(9600);
  Serial.write("Starting motor\n");
}

void loop() 
{
	uint8_t i;

	// Turn on motor
	motor.run(FORWARD);
  motor.setSpeed(200);
  delay(1000);
  // motor.run(FORWARD);
  // motor.setSpeed(200);
  // delay(1000);
  // motor.run(BACKWARD);
  // motor.setSpeed(255);
  // delay(1000);

	
	// // Accelerate from zero to maximum speed
	// for (i=200; i<255; i++) 
	// {
  //   Serial.println(i);
	// 	motor.setSpeed(i);  
	// 	delay(10);
	// }
	
	// // Decelerate from maximum speed to zero
	// for (i=255; i!=200; i--) 
	// {
  //   Serial.println(i);
	// 	motor.setSpeed(i);  
	// 	delay(10);
	// }

	// // Now change motor direction
	// motor.run(BACKWARD);
	
	// Accelerate from zero to maximum speed
	// for (i=200; i<255; i++) 
	// {
  //   Serial.println(i);
	// 	motor.setSpeed(i);  
	// 	delay(10);
	// }

	// // Decelera200te from maximum speed to zero
	// for (i=255; i!=200; i--) 
	// {
  //   Serial.println(i);
	// 	motor.setSpeed(i);  
	// 	delay(10);
	// }

	// Now turn off motor
	// motor.run(RELEASE);
	// delay(1000);
}