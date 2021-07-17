#include "subsystems/ShooterSubsystem.h"
#include "Robot.h"

using IdleMode = rev::CANSparkMax::IdleMode;
using NeutralMode = ctre::phoenix::motorcontrol::NeutralMode;

ShooterSubsystem::ShooterSubsystem() {
    shooter1.SetInverted(true);
    shooter2.Follow(shooter1, true);

    shooter1.SetSmartCurrentLimit(65);
    shooter2.SetSmartCurrentLimit(65);

    shooter1PID.SetP(kP);
    shooter1PID.SetI(kI);
    shooter1PID.SetD(kD);
    shooter1PID.SetFF(kFF);
    shooter1PID.SetIZone(kIz);
    shooter1PID.SetOutputRange(kMin, kMax);

    shooter1.BurnFlash();
    shooter2.BurnFlash();
}

void ShooterSubsystem::Periodic() {
    if ((getRPM() <= ShooterVelocity) && (getRPM() <= 50)) {
        isShooterAtMax = false;
        isShooterRunning = false;
    }else if ((getRPM() <= ShooterVelocity) && (getRPM() > 50)) {
        isShooterAtMax = false;
        isShooterRunning = true;
    }else{
        isShooterAtMax = true;
        isShooterRunning = true;
    }
}

void ShooterSubsystem::runShooterPercentage(double startingSpeed) {
    if (shooterSpeed < startingSpeed) {
        shooterSpeed = startingSpeed;
    }else{
        shooterSpeed += incrementShooterSpeed;
    }

    if (shooterSpeed >= maxShooterSpeed) {
        shooterSpeed = maxShooterSpeed;
    }

    shooter1.Set(shooterSpeed);

    std::cout << "Speed: " << shooterSpeed << std::endl;
}

void ShooterSubsystem::runShooterVelocity() {
    shooter1PID.SetReference(ShooterVelocity, rev::ControlType::kVelocity);
}

void ShooterSubsystem::stopShooter() {
    shooterSpeed = 0.0;
    shooter1.Set(shooterSpeed);
    shooter2.Set(shooterSpeed);
}

void ShooterSubsystem::setCoastMode() {
    shooter1.SetIdleMode(IdleMode::kCoast);
    shooter2.SetIdleMode(IdleMode::kCoast);
}

double ShooterSubsystem::getRPM() {
    return shooterEncoder1.GetVelocity();
}

double ShooterSubsystem::getShooter1Current() {
    return shooter1.GetOutputCurrent();
}

double ShooterSubsystem::getShooter1AccumError() {
    return shooter1PID.GetIAccum();
}

double ShooterSubsystem::getAvgCurrent()
{
    return (shooter1.GetOutputCurrent() + shooter2.GetOutputCurrent()) / 2.0;
}