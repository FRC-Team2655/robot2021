
#include "AutonomousRoutines.h"

frc2::Command* AutonomousRoutines::PickupFromTrechAndShoot(double gyroStartAngle)
{
    /* This auto routine is designed to pick up two balls from the trench, drive to the goal, and shoot all 5 balls.
    The robot start position is on the start line, centered with the balls. The robot must be facing the balls,
    and the back of the robot must be in line with the start line (back of chassis, not back of bumper) */

    /* Create the base sequential command group */
    frc2::SequentialCommandGroup* routine = new frc2::SequentialCommandGroup();

    /* Put the intake out */
    routine->AddCommands(MoveIntakeOutArmCommand(intakeOutPosition));

    /* Run rollers and drive distance (~6'6" + 3' + 3' + margin - robot length (27"))
    Distance: 78 + 36 + 36 + 12 - 27 = 135 inches (3.43m) */
    cmd1.maxSpeed = 2500;
    routine->AddCommands(frc2::ParallelRaceGroup(RunIntakeRollersCommand(rollersSpeed), cmd1, RunSideBeltsCommand()));

    /* Half second delay for balls to settle */
    routine->AddCommands(DelayMillisecondsCommand(500));
    
    /* Bring intake in */
    routine->AddCommands(frc2::ParallelRaceGroup(MoveIntakeInArmCommand(intakeInPosition), DelayMillisecondsCommand(750)));
    routine->AddCommands(EnableLockPIDCommand());

    /* Rotate to point where robot *should* end up 1.5 meters from goal */
    routine->AddCommands(RotateDegreesCommand(-164.9));

    /* Drive to 1.5m from goal */
    DriveDistanceCommand driveToGoal(DriveDistanceCommand::inchesToMeters(245));
    driveToGoal.maxSpeed = 3000;
    routine->AddCommands(driveToGoal);
    
    /* Re-orient based on gyro start angle to align to goal (180 - start angle) */
    routine->AddCommands(RotateToGyroAngleCommand(gyroStartAngle + 180));

    /* Drive 18" while revving shooter (want to bump wall) */
    routine->AddCommands(frc2::ParallelRaceGroup(DriveDistanceCommand(DriveDistanceCommand::inchesToMeters(18)), RunShooterVelocityCommand(), DelayMillisecondsCommand(2000)));

    /* Run belts while running shooter wheel and rollers */
    routine->AddCommands(frc2::ParallelRaceGroup(RunShooterVelocityCommand(), RunBeltsCommand(beltsSpeed), AllBallsShotCommand(1500, 3500), RunIntakeRollersCommand(rollersSpeed)));

    /* Back up to the start line */
    routine->AddCommands(DriveDistanceCommand(-2.6));

    /* Turn 180 */
    routine->AddCommands(RotateToGyroAngleCommand(gyroStartAngle));

    return routine;
}

frc2::Command* AutonomousRoutines::ShootPreloads(double goalOffsetMeters, double startDelayMs, bool buddyDrive, bool pickupFromTrench, double gyroStartAngle)
{
    /* Create the base sequential command group */
    frc2::SequentialCommandGroup* routine = new frc2::SequentialCommandGroup();

    /* straight distance to drive (meters) */
    double straightDriveDist = 2.36;

    if (buddyDrive) {
        routine->AddCommands(frc2::ParallelRaceGroup(DriveDistanceCommand(-0.6), DelayMillisecondsCommand(2500)));
        straightDriveDist += 0.6;
    }

    /* add start delay */
    if(startDelayMs > 0)
    {
        routine->AddCommands(DelayMillisecondsCommand(startDelayMs));
    }

    /* If we need to do some turns to line up */
    if(goalOffsetMeters != 0)
    {
        /* Perform first turn */

        /* Perform first drive */

        /* Perform second turn */
    }

    /* Drive remainder of distance to goal while ramping shooter wheel */
    routine->AddCommands(frc2::ParallelRaceGroup(DriveDistanceCommand(straightDriveDist), RunShooterVelocityCommand(), DelayMillisecondsCommand(5000)));

    /* Run belts while running shooter wheel */
    routine->AddCommands(frc2::ParallelRaceGroup(RunShooterVelocityCommand(), RunBeltsCommand(beltsSpeed), AllBallsShotCommand(1500, 4000)));

    if(pickupFromTrench)
    {
        /* Back up -2 meters */
        routine->AddCommands(DriveDistanceCommand(-1.5));

        /* Rotate 90 degrees right */
        routine->AddCommands(RotateDegreesCommand(-90));

        /* Drive to the middle of trench line (63 inches) */
        routine->AddCommands(DriveDistanceCommand(1.6));

        /* Re-orient to 180 degrees from starting position */
        routine->AddCommands(RotateToGyroAngleCommand(gyroStartAngle + 180));

        /* Move intake out */
        routine->AddCommands(MoveIntakeOutArmCommand(intakeOutPosition));

        /* Drive while running rollers. Total drive distance: 120 inches + 200 inches (-1.5m (59") initial travel) */
        cmd2.maxSpeed = 2000;
        routine->AddCommands(frc2::ParallelRaceGroup(RunIntakeRollersCommand(rollersSpeed), cmd2));

        /* Half second delay for balls to settle */
        routine->AddCommands(DelayMillisecondsCommand(500));
    
        /* Bring intake in */
        routine->AddCommands(frc2::ParallelRaceGroup(MoveIntakeInArmCommand(intakeInPosition), DelayMillisecondsCommand(1000)));

        /* Rotate to goal*/
        routine->AddCommands(RotateDegreesCommand(-165));
    }
    else
    {
        /* Back up to the start line */
        routine->AddCommands(DriveDistanceCommand(-2.36));

        /*Rotate so were facing the right way*/
        routine->AddCommands(RotateDegreesCommand(180));
    }
    
    return routine;
}

frc2::Command* AutonomousRoutines::TestAuto(double distanceMeters, double turnDegrees)
{
    /* Create the base sequential command group */
    frc2::SequentialCommandGroup* routine = new frc2::SequentialCommandGroup();

    /* Add any sub commands */
    DriveDistanceCommand driveDist(distanceMeters);
    driveDist.P_encoders = driveDistance_P_encoder;
    driveDist.P_gyro = driveDistance_P_gyro;
    routine->AddCommands(driveDist);

    RotateDegreesCommand rot(turnDegrees);
    rot.P_gyro = rotate_P_gyro;
    routine->AddCommands(rot);

    return routine;
}