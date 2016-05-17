#include "Camera.h"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Camera::Camera(irr::IrrlichtDevice *device,
	irr::scene::ISceneNode* node,
	float direction,
	float zdirection,
	float zoom)
{
	this->_device = device;
	this->_direction = direction;
	this->_zdirection = zdirection;
	this->_zoom = zoom;
}

void					Camera::moveCameraControl(irr::scene::ISceneNode *node)
{
	irr::core::position2d<irr::f32> cursorPos = this->_device->getCursorControl()->getRelativePosition();
	irr::scene::ICameraSceneNode* camera = this->_device->getSceneManager()->getActiveCamera();
	irr::core::vector3df cameraPos = camera->getAbsolutePosition();

	float change_x = (cursorPos.X - 0.5) * 256.0f;
	float change_y = (cursorPos.Y - 0.5) * 256.0f;
	this->_direction += change_x;
	this->_zdirection -= change_y;
	if (this->_zdirection < -90)
		this->_zdirection = -90;
	else
		if (this->_zdirection > 90)
			this->_zdirection = 90;
	this->_device->getCursorControl()->setPosition(0.5f, 0.5f);

	irr::core::vector3df playerPos = node->getPosition();

	float xf = playerPos.X - cos(this->_direction * M_PI / 180.0f) * this->_zoom;
	float yf = playerPos.Y - sin(this->_zdirection * M_PI / 180.0f) * this->_zoom;
	float zf = playerPos.Z + sin(this->_direction * M_PI / 180.0f) * this->_zoom;

	camera->setPosition(irr::core::vector3df(xf, yf, zf));
	camera->setTarget(irr::core::vector3df(playerPos.X, playerPos.Y + 25.0f, playerPos.Z));
	node->setRotation(irr::core::vector3df(0, this->_direction, 0));
}

void					Camera::setDevice(irr::IrrlichtDevice *device)
{
	this->_device = device;
}

irr::IrrlichtDevice*	Camera::getDevice() const
{
	return (this->_device);
}

void					Camera::setZoom(float zoom)
{
	this->_zoom = zoom;
	std::cout << "setZoom() = " << this->_zoom << std::endl;
}

float					Camera::getZoom() const
{
	std::cout << "getZoom() = " << this->_zoom << std::endl;
	return (this->_zoom);
}