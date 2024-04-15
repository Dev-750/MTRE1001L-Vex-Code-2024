#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port2,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           wristServo,    tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           intakeMotor,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rightMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           clawMotor,     tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


// 1)	Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                           
// 2)	Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                            

//+++++++++++++| Functions |++++++\\

// Convert d in Inches to revolutions
int rev(d)
{
	int r = d/c;
	int count = r * 360;
	return count;
}

// Shake to eject sample tubes
void shake_bot()
{
	while(vexRT[Btn8D] == 1)
	{
		motor[leftMotor] = 63;
		motor[rightMotor] = 63;
		wait(1);
		motor[leftMotor] = 63;
		motor[rightMotor] = 63;
		wait(1);
	}
}

// Move bot forward
void forward(count)
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	while(SensorValue[rightEncoder] < count && SensorValue[leftEncoder] < count)
	{
		motor[leftMotor] = 63;
		motor[rightMotor] = 63;
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}
// void moveBot(){

}



//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++\\
task main () {
	// Wheel circumference
	const int c = 15.04;

	//+++++++++| AUTONOMOUS |++++++++++\\
 count = rev(30);
 forward(count);


//++++++++| MANUAL CONTROL |++++++++\\

	while(1 == 1)
	{
	//--Intake--
		if(vexRT[Btn6U] == 1)
		{
			motor[intakeMotor] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[intakeMotor] = -127;
		}
		else
		{
			motor[intakeMotor] = 0;
		}

	//--Wheels--
		motor[leftMotor]  = (vexRT[Ch4] + vexRT[Ch3])/2;  // (y + x)/2
		motor[rightMotor] = (vexRT[Ch4] - vexRT[Ch3])/2;  // (y - x)/2

	//--Arm--
		if(vexRT[Btn5U] == 1)       	//If button 5U is pressed...
		{
			motor[armMotor] = 127;    	//...raise arm.
		}
		else if(vexRT[Btn5D] == 1)  	//Else, if button 5D is pressed...
		{
			motor[armMotor] = -127;   	//...lower arm.
		}
		else                      		//Else (neither button is pressed)...
		{
			motor[armMotor] = 0;      	//...stop arm.
		}

	//--Claw--
		if(vexRT[Btn6U] == 1)
		{
			motor[clawMotor] = 63; // Open claw
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[clawMotor] = -63; // CLose claw
		}
		else
		{
			motor[clawMotor] = 0;
		}

	//--Wrist--
		if(vexRT[Btn8L] == 1)
		{
			motor[wristServo] = 60; // Rotate wrist 60deg left
		}
		else if(vexRT[Btn8R] == 1)
		{
			motor[wristServo] = -60; // Rotate wrist 60deg right
		}
		else
		{
			motor[wristServo] = 0;
		}
	//--Shake Motion--
		if(vexRT[Btn8D] == 1)
		{
			shake_bot();
		}
		else
		{
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
		}
	}
}
