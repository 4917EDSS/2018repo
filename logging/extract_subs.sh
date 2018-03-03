#!/bin/sh
echo
echo Extracting subsystem logs from $1...
echo ... global
grep LP:Global $1 > global.csv
echo ... drivetrain
grep LP:Drivetrain $1 > drivetrain.csv
echo ... elevator
grep LP:Elevator $1 > elevator.csv
echo ... intake
grep LP:Intake $1 > intake.csv
echo Done.
