/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  // These are from the 2019 Robot.cpp
  elevator.ConfigFactoryDefault();
  elevator.ConfigOpenloopRamp(0.05);
  // elevator.ConfigClosedloopRamp(0.02); // Shouldn't need that
  elevator.ConfigContinuousCurrentLimit(39, 10);
  elevator.ConfigPeakCurrentLimit(0, 10);    
  elevator.SetNeutralMode(NeutralMode::Brake);
  elevator.SetInverted(false);    // Would be good to check these two
  elevator.SetSensorPhase(false); 
  // elevator.ConfigPeakOutputReverse(-1.0); // Shouldn't need these two
  // elevator.ConfigPeakOutputForward(1.0);

  // So are these
  elevator.Set(ControlMode::PercentOutput, 0.0);
  elevator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
  elevator.SetSelectedSensorPosition(0, 0, 10);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  absPos2 = elevator.GetSelectedSensorPosition();
  elevatorAtZero = (absPos2 < 3); // copied. not sure why it's 3, and not 0
  elevatorNearZero = (abs(absPos2) < 100);

  frc::SmartDashboard::PutNumber("absPos2", absPos2);
  frc::SmartDashboard::PutBoolean("elevatorAtZero", elevatorAtZero);
  frc::SmartDashboard::PutBoolean("elevatorNearZero", elevatorNearZero);
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  elevator.Set(ControlMode::PercentOutput, -gamerJoystick.GetRawAxis(5));
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
