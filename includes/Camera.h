#include <irrlicht.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

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
	float							_direction;
	float							_zdirection;
	float							_zoom;

public:
	Camera(irr::IrrlichtDevice *device, irr::scene::ISceneNode* node,
		float direction = 0,
		float zdirection = 0,
		float zoom = 64);
	void					moveCameraControl(irr::scene::ISceneNode *node);

	void					setDevice(irr::IrrlichtDevice *device);
	irr::IrrlichtDevice*	getDevice() const;
	void					setZoom(float zoom);
	float					getZoom() const;
};

#endif