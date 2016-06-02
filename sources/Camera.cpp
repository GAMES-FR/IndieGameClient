#include "Camera.hpp"
#include "Input.hpp"
#include "GMath.hpp"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Camera::Camera(irr::IrrlichtDevice *device)
{
	this->_device = device;
	this->_distance = 40;
	this->_angle = 20.f;
	this->_angleOffset = 90.f;
	this->_curX = 0;
	this->_curY = 0;
	this->_curZ = 0;
}

void					Camera::updateCamera(Player *player)
{
	irr::scene::ICameraSceneNode	*camera = this->_device->getSceneManager()->getActiveCamera();
	irr::scene::ISceneNode			*node = player->getEntity().getNode();

	float yf = node->getAbsolutePosition().Y + this->_distance * sin(this->_angle / 180.f * M_PI);
	float d = this->_distance * cos(this->_angle / 180.f * M_PI);

	float a = (node->getRotation().Y - this->_angleOffset) / 180.0f * M_PI;

	float xf = node->getAbsolutePosition().X + sin(a) * d;
	float zf = node->getAbsolutePosition().Z + cos(a) * d;

	this->_curX = (this->_curX + xf) / 2;
	this->_curY = (this->_curY * 4 + yf) / 5;
	this->_curZ = (this->_curZ + zf) / 2;
	camera->setPosition(irr::core::vector3df(this->_curX, this->_curY, this->_curZ));
	camera->setTarget(node->getPosition());
}

void					Camera::setDevice(irr::IrrlichtDevice *device)
{
	this->_device = device;
}

irr::IrrlichtDevice*	Camera::getDevice() const
{
	return (this->_device);
}

void					Camera::addDistance(float d) {
	float sd = this->_distance - d;
	
	this->_distance = GMath::clamp(sd, MIN_DIST, MAX_DIST);
}

float					Camera::getDistance() const {
	return this->_distance;
}