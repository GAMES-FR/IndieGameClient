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
		float	gravity;
		float	mass;
		float	inertiaScale;
		float	halfWidth;
		float	cgToFront;
		float	cgToRear;
		float	cgToFrontAxle;
		float	cgToRearAxle;
		float	cgHeight;
		float	wheelRadius;
		float	wheelWidth;
		float	tireGrip;
		float	lockGrip;
		float	engineForce;
		float	brakeForce;
		float	eBrakeForce;
		float	weightTransfer;
		float	maxSteer;
		float	cornerStiffnessFront;
		float	cornerStiffnessRear;
		float	airResist;
		float	rollResist;
	};

	Config *getDefaultConfig();

	class Car {
	private:
		Config			*cfg;
		int				inputs;

		float 			heading;
		Vector::Vec2 	position;
		Vector::Vec2	velocity;
		Vector::Vec2	velocity_c;
		Vector::Vec2	accel;
		Vector::Vec2	accel_c;
		float			absVel;
		float 			yawRate;
		float			steer;
		float 			steerAngle;

		float			inertia;
		float			wheelBase;
		float			axleWeightRatioFront;
		float			axleWeightRatioRear;

		int				throttle;
		int				brake;

		void			doPhysics(float dt);
		float			applySmoothSteer(float steerInput, float dt);
		float			applySafeSteer(float steerInput);
	public:
		bool			smoothSteer;
		bool			safeSteer;

		Car(float x = 0.f, float y = 0.f, float heading = 0.f);
		~Car();
		void			update(float dtms);
		void			setConfig(Config *cfg);
		Config			*getConfig() const;
		void			setInputs(int inputs);
		void			setPosition(const Vector::Vec2 & pos);
		void			setHeading(float heading);
		Vector::Vec2	getPosition() const;
		float			getHeading() const;
	};
}

#endif