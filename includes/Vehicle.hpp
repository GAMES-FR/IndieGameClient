#ifndef CAR_HPP_
# define CAR_HPP_

# include <cmath>
# include "Vector.hpp"
# include "GMath.hpp"

# define I_THROTTLE 0b1
# define I_BRAKE	0b10
# define I_EBRAKE	0b100
# define I_LEFT		0b1000
# define I_RIGHT	0b10000

namespace Vehicle {
	struct Config
	{
		double	gravity;
		double	mass;
		double	inertiaScale;
		double	halfWidth;
		double	cgToFront;
		double	cgToRear;
		double	cgToFrontAxle;
		double	cgToRearAxle;
		double	cgHeight;
		double	wheelRadius;
		double	wheelWidth;
		double	tireGrip;
		double	lockGrip;
		double	engineForce;
		double	brakeForce;
		double	eBrakeForce;
		double	weightTransfer;
		double	maxSteer;
		double	cornerStiffnessFront;
		double	cornerStiffnessRear;
		double	airResist;
		double	rollResist;
	};

	Config *getDefaultConfig();

	class Car {
	private:
		Config			*cfg;
		int				inputs;

		double 			heading;
		Vector::Vec2 	position;
		Vector::Vec2	velocity;
		Vector::Vec2	velocity_c;
		Vector::Vec2	accel;
		Vector::Vec2	accel_c;
		double			absVel;
		double 			yawRate;
		double			steer;
		double 			steerAngle;

		bool			smoothSteer;
		bool			safeSteer;

		double			inertia;
		double			wheelBase;
		double			axleWeightRatioFront;
		double			axleWeightRatioRear;

		int				throttle;
		int				brake;

		void			doPhysics(double dt);
		double			applySmoothSteer(double steerInput, double dt);
		double			applySafeSteer(double steerInput);
	public:
		Car(double x = 0.0, double y = 0.0, double heading = 0.0);
		~Car();
		void			update(double dtms);
		void			setConfig(Config *cfg);
		Config			*getConfig() const;
		void			setInputs(int inputs);
	};
}

#endif