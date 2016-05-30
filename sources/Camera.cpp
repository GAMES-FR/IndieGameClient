#include "Camera.hpp"
#include "Input.hpp"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Camera::Camera(irr::IrrlichtDevice *device)
{
	this->_device = device;
	this->_offset.X = 60;
	this->_offset.Y = 60;
	this->_offset.Z = 60;
}

void					Camera::updateCamera(Player *player)
{
	irr::scene::ICameraSceneNode	*camera = this->_device->getSceneManager()->getActiveCamera();
	irr::scene::ISceneNode			*node = player->getNode();

	float xf = node->getAbsolutePosition().X - cos(node->getRotation().Y * M_PI / 180.0f) * (this->_offset.X + this->_offset.Y);
	float yf = node->getAbsolutePosition().Y + this->_offset.Y;
	float zf = node->getAbsolutePosition().Z + sin(node->getRotation().Y * M_PI / 180.0f) * (this->_offset.Z + this->_offset.Y);

	camera->setPosition(irr::core::vector3df(xf, yf, zf));
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

void					Camera::addZoom(float new_offset)
{
	this->_offset -= new_offset;
	if (this->_offset < irr::core::vector3df(20, 20, 20) ||
		this->_offset > irr::core::vector3df(120, 120, 120))
		this->_offset += new_offset;
}

irr::core::vector3df	Camera::getZoom() const
{
	return (this->_offset);
}