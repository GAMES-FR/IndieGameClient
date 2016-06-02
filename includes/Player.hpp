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

# include "Entity.hpp"

class Player
{
private:
	Entity					entity;
	Vehicle::Car			_vehicle;
	irr::scene::ISceneManager *smgr;

public:
	Player(std::string const &, irr::scene::ISceneManager *);
	~Player();

	void					update(irr::f32 dt);

	void					setInputs(int);
	void					setCollisions(irr::scene::ISceneManager* &smgr);

	Entity const &			getEntity() const;

	int		input;
};

#endif