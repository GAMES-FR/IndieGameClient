#include <irrlicht.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.h"
#include "Player.h"

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
	virtual void			moveObject(Camera& camera, Player& player, irr::f32 dt);
	virtual void			setZoom(Camera& camera);
};

#endif