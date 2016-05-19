#include "Car.hpp"

Vehicle::Car::Car(double x, double y, double heading) {
	this->position = Vector::Vec2(x, y);
	this->heading = heading;
	this->absVel = 0.0;
	this->yawRate = 0.0;
	this->steer = 0.0;
	this->steerAngle = 0.0;

	this->inputs = 0;
	this->smoothSteer = true;
	this->safeSteer = true;

	this->inertia = 0.0;
	this->wheelBase = 0.0;
	this->axleWeightRatioFront = 0.0;
	this->axleWeightRatioRear = 0.0;

	this->cfg = NULL;
}

Vehicle::Car::~Car() {}

void Vehicle::Car::doPhysics(double dt) {
	double sn = sin(this->heading);
	double cs = cos(this->heading);

		// Get velocity in local car coordinates
	this->velocity_c.x = cs * this->velocity.x + sn * this->velocity.y;
	this->velocity_c.y = cs * this->velocity.y - sn * this->velocity.x;

	// Weight on axles based on centre of gravity and weight shift due to forward/reverse acceleration
	double axleWeightFront = cfg->mass * (this->axleWeightRatioFront * cfg->gravity - cfg->weightTransfer * this->accel_c.x * cfg->cgHeight / this->wheelBase);
	double axleWeightRear = cfg->mass * (this->axleWeightRatioRear * cfg->gravity + cfg->weightTransfer * this->accel_c.x * cfg->cgHeight / this->wheelBase);

	// Resulting velocity of the wheels as result of the yaw rate of the car body.
	// v = yawrate * r where r is distance from axle to CG and yawRate (angular velocity) in rad/s.
	double yawSpeedFront = cfg->cgToFrontAxle * this->yawRate;
	double yawSpeedRear = -cfg->cgToRearAxle * this->yawRate;

	// Calculate slip angles for front and rear wheels (a.k.a. alpha)
	double slipAngleFront = atan2(this->velocity_c.y + yawSpeedFront, abs(this->velocity_c.x)) - GMath::sign(this->velocity_c.x) * this->steerAngle;
	double slipAngleRear  = atan2(this->velocity_c.y + yawSpeedRear,  abs(this->velocity_c.x));

	double tireGripFront = cfg->tireGrip;
	double tireGripRear = cfg->tireGrip * (1.0 - (this->inputs & I_EBRAKE) * (1.0 - cfg->lockGrip)); // reduce rear grip when ebrake is on

	double frictionForceFront_cy = GMath::clamp(-cfg->cornerStiffnessFront * slipAngleFront, -tireGripFront, tireGripFront) * axleWeightFront;
	double frictionForceRear_cy = GMath::clamp(-cfg->cornerStiffnessRear * slipAngleRear, -tireGripRear, tireGripRear) * axleWeightRear;

	//  Get amount of brake/throttle from our inputs
	double brake = GMath::min((this->inputs & I_BRAKE) * cfg->brakeForce + (this->inputs & I_EBRAKE) * cfg->eBrakeForce, cfg->brakeForce);
	double throttle = (this->inputs & I_THROTTLE) * cfg->engineForce;

	//  Resulting force in local car coordinates.
	//  This is implemented as a RWD car only.
	double tractionForce_cx = throttle - brake * GMath::sign(this->velocity_c.x);
	double tractionForce_cy = 0;

	double dragForce_cx = -cfg->rollResist * this->velocity_c.x - cfg->airResist * this->velocity_c.x * abs(this->velocity_c.x);
	double dragForce_cy = -cfg->rollResist * this->velocity_c.y - cfg->airResist * this->velocity_c.y * abs(this->velocity_c.y);

	// total force in car coordinates
	double totalForce_cx = dragForce_cx + tractionForce_cx;
	double totalForce_cy = dragForce_cy + tractionForce_cy + cos(this->steerAngle) * frictionForceFront_cy + frictionForceRear_cy;

	// acceleration along car axes
	this->accel_c.x = totalForce_cx / cfg->mass;  // forward/reverse accel
	this->accel_c.y = totalForce_cy / cfg->mass;  // sideways accel

	// acceleration in world coordinates
	this->accel.x = cs * this->accel_c.x - sn * this->accel_c.y;
	this->accel.y = sn * this->accel_c.x + cs * this->accel_c.y;

	// update velocity
	this->velocity.x += this->accel.x * dt;
	this->velocity.y += this->accel.y * dt;

	this->absVel = this->velocity.len();

	// calculate rotational forces
	double angularTorque = (frictionForceFront_cy + tractionForce_cy) * cfg->cgToFrontAxle - frictionForceRear_cy * cfg->cgToRearAxle;

	//  Sim gets unstable at very slow speeds, so just stop the car
	if( abs(this->absVel) < 0.5 && !throttle )
	{
		this->velocity.x = this->velocity.y = this->absVel = 0;
		angularTorque = this->yawRate = 0;
	}

	double angularAccel = angularTorque / this->inertia;

	this->yawRate += angularAccel * dt;
	this->heading += this->yawRate * dt;

	//  finally we can update position
	this->position.x += this->velocity.x * dt;
	this->position.y += this->velocity.y * dt;
}

void Vehicle::Car::update(double dtms) {
	double dt = dtms / 1000.0;

	this->throttle = this->inputs & I_THROTTLE;
	this->brake = this->inputs & I_BRAKE;

	int steerInput = (this->inputs & I_LEFT) - (this->inputs & I_RIGHT);

	if (this->smoothSteer)
		this->steer = this->applySmoothSteer(steerInput, dt);
	else
		this->steer = steerInput;

	if (this->safeSteer)
		this->steer = this->applySafeSteer(this->steer);

	this->steerAngle = this->steer * this->cfg->maxSteer;

	this->doPhysics(dt);
}

double Vehicle::Car::applySmoothSteer(double steerInput, double dt) {
	double steer = 0.0;

	if (abs(steerInput) > 0.001)
		steer = GMath::clamp(this->steer - dt * 2.0, -1.0, 1.0);
	else
	{
		if (this->steer > 0)
			steer = GMath::max(this->steer - dt, 0.0);
		else if (this->steer < 0)
			steer = GMath::max(this->steer + dt, 0.0);
	}
	return (steer);
}

double Vehicle::Car::applySafeSteer(double steerInput) {
	double avel = GMath::min(this->absVel, 250.0);
	double steer = steerInput * (1.0 - (avel / 280.0));
	return (steer);
}

Vehicle::Config *Vehicle::Car::getConfig() const {
	return (this->cfg);
}

void Vehicle::Car::setConfig(Vehicle::Config *cfg) {
	this->cfg = cfg;
	this->inertia = this->cfg->mass * this->cfg->inertiaScale;
	this->wheelBase = this->cfg->cgToFrontAxle + this->cfg->cgToRearAxle;
	this->axleWeightRatioFront = this->cfg->cgToRearAxle / this->wheelBase; // % car weight on the front axle
	this->axleWeightRatioRear = this->cfg->cgToFrontAxle / this->wheelBase; // % car weight on the rear axle
}

void Vehicle::Car::setInputs(int inputs) {
	this->inputs = inputs;
}