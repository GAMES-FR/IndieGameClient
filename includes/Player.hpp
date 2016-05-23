#include <irrlicht.h>
#define _USE_MATH_DEFINES
#include <cmath>

#include "Vehicle.hpp"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef PLAYER_H
# define PLAYER_H

class Player
{
private:
	irr::core::vector3df _pos;
	irr::core::vector3df _rot;
	irr::scene::ISceneNode *_node;
	Vehicle::Car _vehicle;

public:
	Player(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Player();

	void update(irr::f32 dt);

	void setNode(irr::scene::ISceneNode *node);

	void setPosition(irr::core::vector3df newPos);
	void setPosition(float newX, float newY, float newZ);
	irr::core::vector3df getPosition() const;
	void setRotation(irr::core::vector3df newRot);
	void setRotation(float newX, float newY, float newZ);
	irr::core::vector3df getRotation() const;

	bool left;
	bool up;
	bool right;
	bool down;
	int input;
};

#endif