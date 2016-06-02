#include <irrlicht.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Player.hpp"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef CAMERA_H
# define CAMERA_H

# define MAX_DIST 200.f
# define MIN_DIST 10.f
# define STEP_DIST 5.f

class Camera
{
private:
	irr::IrrlichtDevice*			_device;

	float							_distance;
	float							_angle;
	float							_angleOffset;

	float							_curX;
	float							_curY;
	float							_curZ;

public:
	Camera(irr::IrrlichtDevice *device);
	void					updateCamera(Player *player);

	void					setDevice(irr::IrrlichtDevice *device);
	irr::IrrlichtDevice*	getDevice() const;

	void					addDistance(float);
	float					getDistance() const;
};

#endif