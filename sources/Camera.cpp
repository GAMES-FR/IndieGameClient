#include "Camera.hpp"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Camera::Camera(irr::IrrlichtDevice *device,	float zoom)
{
	this->_device = device;
	this->_zoom = zoom;
}

void					Camera::updateCamera(Player *player)
{
	irr::scene::ICameraSceneNode *camera = this->_device->getSceneManager()->getActiveCamera();

	float xf = player->getPosition().X - cos(player->getRotation().Y * M_PI / 180.0f) * this->_zoom;
	float yf = player->getPosition().Y;// - sin(player->getRotation() * M_PI / 180.0f) * this->_zoom;
	float zf = player->getPosition().Z + sin(player->getRotation().Y * M_PI / 180.0f) * this->_zoom;

	camera->setPosition(irr::core::vector3df(xf, yf + 45.0f, zf));
	camera->setTarget(player->getPosition());
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