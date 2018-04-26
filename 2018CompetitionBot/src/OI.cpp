#include <Commands/FoldArmsDownHeldCmd.h>
#include <Commands/FoldArmsUpHeldCmd.h>
#include <Commands/ZeroAndIntakeGrp.h>
#include <Commands/SetHighGearHeldCmd.h>
#include "OI.h"
#include <WPILib.h>
#include "Commands/ReverseIntakeCmd.h"
#include "Commands/DropBoxCmd.h"
#include "Commands/HoldBoxCmd.h"
#include <Commands/MoveElevatorToHeightCmd.h>
#include "Commands/KillEverythingCmd.h"
#include "Subsystems/ElevatorSub.h"
#include "Commands/IntakeUntilLimitCmd.h"
#include "Commands/ElevatorFullPowerDownCmd.h"
#include "Commands/PrepareToClimbGrp.h"
#include "Commands/ClimbGrp.h"
#include "Commands/ResetElevatorCmd.h"


OI::OI() {
	// Process operator interface input here.
	driverController.reset(new frc::Joystick(DRIVER_CONTROLLER_PORT));
	driverController->SetXChannel(0);
	driverController->SetYChannel(1);
	driverController->SetZChannel(2);
	driverController->SetThrottleChannel(3);

	highGearBtn.reset(new JoystickButton(driverController.get(), HIGH_GEAR_BTN));
	highGearBtn->WhileHeld(new SetHighGearHeldCmd());
	killEverythingD1.reset(new frc::JoystickButton(driverController.get(), KILL_EVERYTHING_BTN_1));
	killEverythingD1->WhenPressed(new KillEverythingCmd());
	killEverythingD2.reset(new frc::JoystickButton(driverController.get(), KILL_EVERYTHING_BTN_2));
	killEverythingD2->WhenPressed(new KillEverythingCmd());
	prepareToClimbBtn.reset(new JoystickButton( driverController.get(),PREPARE_TO_CLIMB_BTN));
	prepareToClimbBtn->WhenPressed(new PrepareToClimbGrp());
	climbBarBtn.reset(new JoystickButton(driverController.get(), CLIMB_BAR_BTN));
	climbBarBtn->WhenPressed(new ClimbGrp());
	resetElevatorBtn.reset(new JoystickButton(driverController.get(), RESET_ELEVATOR_BTN));
	resetElevatorBtn->WhenPressed(new ResetElevatorCmd());

	operatorController.reset(new frc::Joystick(OPERATOR_CONTROLLER_PORT));
	operatorController->SetXChannel(0);
	operatorController->SetYChannel(1);
	operatorController->SetZChannel(2);
	operatorController->SetThrottleChannel(3);

	groundIntakeBtn.reset(new frc::JoystickButton(operatorController.get(), GROUND_INTAKE_BTN));
	groundIntakeBtn->WhenPressed(new ZeroAndIntakeGrp());
	placeBoxHighScale.reset(new frc::JoystickButton(operatorController.get(),PLACE_BOX_HIGH_SCALE_BTN));
	placeBoxHighScale ->WhenPressed(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_HIGH_HEIGHT));
	placeBoxMediumScale.reset(new frc::JoystickButton(operatorController.get(),PLACE_BOX_MEDIUM_SCALE_BTN));
	placeBoxMediumScale ->WhenPressed(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_MEDIUM_HEIGHT));
	placeBoxLowScale.reset(new frc::JoystickButton(operatorController.get(),PLACE_BOX_LOW_SCALE_BTN));
	placeBoxLowScale ->WhenPressed(new MoveElevatorToHeightCmd(ElevatorSub::SCALE_BOX_LOW_HEIGHT));
	placeBoxSwitchBtn.reset(new frc::JoystickButton(operatorController.get(),PLACE_BOX_SWITCH_BTN));
	placeBoxSwitchBtn ->WhenPressed(new MoveElevatorToHeightCmd(ElevatorSub::SWITCH_BOX_HEIGHT));
	intakeBtn.reset(new frc::JoystickButton(operatorController.get(), INTAKE_BTN));
	intakeBtn->WhenPressed(new IntakeUntilLimitCmd());
	dropBox.reset(new frc::JoystickButton(operatorController.get(), DROP_BOX_BTN));
	dropBox->WhileHeld(new DropBoxCmd());
	killEverythingO1.reset(new frc::JoystickButton(operatorController.get(), KILL_EVERYTHING_BTN_1));
	killEverythingO1->WhenPressed(new KillEverythingCmd());
	killEverythingO2.reset(new frc::JoystickButton(operatorController.get(), KILL_EVERYTHING_BTN_2));
	killEverythingO2->WhenPressed(new KillEverythingCmd());
	climbBtn.reset(new frc::JoystickButton(operatorController.get(), CLIMB_BTN));
	climbBtn->WhileHeld(new ElevatorFullPowerDownCmd());
	foldUpBtn.reset(new frc::JoystickButton(operatorController.get(), FOLD_UP_BTN));
	foldUpBtn->WhileHeld(new FoldArmsUpHeldCmd());
	foldDownBtn.reset(new frc::JoystickButton(operatorController.get(), FOLD_DOWN_BTN));
	foldDownBtn->WhileHeld(new FoldArmsDownHeldCmd());

}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}
std::shared_ptr<frc::Joystick> OI::getOperatorController() {
	return operatorController;
}

