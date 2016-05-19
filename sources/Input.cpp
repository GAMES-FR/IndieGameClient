#include "Input.hpp"
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