#include "Input.h"
#include <iostream>

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

InputHandler::InputHandler()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_keyIsDown[i] = false;
	this->_mouseWheel = 0;
}

bool		InputHandler::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		if (event.MouseInput.Wheel)
		{
			this->_mouseWheel = event.MouseInput.Wheel;
			std::cout << "Mouse Wheel = " << this->_mouseWheel << std::endl;
		}

	return false;
}

bool		InputHandler::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return _keyIsDown[keyCode];
}

void		InputHandler::moveObject(Camera& camera, Player& player, irr::f32 dt)
{
	const irr::f32			speed = 300.f;
	irr::core::vector3df	nodePos = player.getNode()->getPosition();
	irr::core::vector3df	nodeRot = player.getNode()->getRotation();
	irr::core::vector3df	cameraRot = camera.getDevice()->getSceneManager()->getActiveCamera()->getAbsolutePosition();

	if (this->isKeyDown(irr::KEY_KEY_Z))
	{
		nodePos.X += (float)(cos(nodeRot.Y * M_PI / 180.0f) * speed * dt);
		nodePos.Y += (float)((nodePos.Y - cameraRot.Y + 15.0f) * M_PI / 180.0f) * speed * dt;
		nodePos.Z -= (float)(sin(nodeRot.Y * M_PI / 180.0f) * speed * dt);

	}
	else if (this->isKeyDown(irr::KEY_KEY_S))
	{
		nodePos.X -= (float)(cos(nodeRot.Y * M_PI / 180.0f) * speed * dt);
		nodePos.Z += (float)(sin(nodeRot.Y * M_PI / 180.0f) * speed * dt);
	}

	if (this->isKeyDown(irr::KEY_KEY_Q))
	{
		nodePos.X += (float)(cos(nodeRot.Y * M_PI / 180.0f) * speed * dt) ;
		nodePos.Z -= (float)(sin(nodeRot.Y * M_PI / 180.0f) * speed * dt);
	}

	else if (this->isKeyDown(irr::KEY_KEY_D))
	{
		/*nodePos.X += speed * dt;
		nodePos.Y += (nodePos.Y - cameraRot.Y + 25.0f) * dt;*/
	}

	player.getNode()->setPosition(nodePos);
}

void		InputHandler::setZoom(Camera& camera)
{
	if (this->_mouseWheel < 0 && camera.getZoom() < 196.0f)
		camera.setZoom(camera.getZoom() + 10.0f);
	if (this->_mouseWheel > 0 && camera.getZoom() > 16.0f)
		camera.setZoom(camera.getZoom() - 10.0f);
	this->_mouseWheel = 0;
}