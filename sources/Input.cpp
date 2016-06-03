#include "IncludeIrrlicht.hpp"
#include <iostream>

core::InputHandler::InputHandler()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_keyIsDown[i] = false;
	this->_mouseWheel = 0;
}

bool		core::InputHandler::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		if (event.MouseInput.Wheel)
			this->_mouseWheel = event.MouseInput.Wheel;

	return false;
}

bool		core::InputHandler::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return _keyIsDown[keyCode];
}

void		core::InputHandler::setMouseWheel(irr::f32 value)
{
	this->_mouseWheel = value;
}

irr::f32	core::InputHandler::getMouseWheel() const
{
	return (this->_mouseWheel);
}
