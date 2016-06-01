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

class Camera
{
private:
	irr::IrrlichtDevice*			_device;
	irr::core::vector3df			_offset;

public:
	Camera(irr::IrrlichtDevice *device);
	void					updateCamera(Player *player);

	void					setDevice(irr::IrrlichtDevice *device);
	irr::IrrlichtDevice*	getDevice() const;
	void					addZoom(float zoom);
	irr::core::vector3df	getZoom() const;
};

#endif