#include <irrlicht.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.hpp"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#ifndef INPUT_H
#define INPUT_H

class InputHandler : public irr::IEventReceiver
{
private:
	// Handler des touches actuellement pressées ou non
	bool					_keyIsDown[irr::KEY_KEY_CODES_COUNT];
	irr::f32				_mouseWheel;

public:
	InputHandler();
	// Override de la méthode OnEvent de Irrlicht
	virtual bool			OnEvent(const irr::SEvent& event);
	virtual bool			isKeyDown(irr::EKEY_CODE keyCode) const;
	virtual void			setMouseWheel(irr::f32 value);
	virtual irr::f32		getMouseWheel() const;
};

#endif