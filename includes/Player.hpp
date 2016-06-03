#ifndef PLAYER_H
# define PLAYER_H

# define _USE_MATH_DEFINES
# include <vector>
# include <irrlicht.h>
# include <cmath>

# include "Vehicle.hpp"
# include "Entity.hpp"
# include "Missile.hpp"

class Player
{
private:
	Entity					entity;
	Vehicle::Car			_vehicle;
	irr::scene::ISceneManager *smgr;

	// Ce que charpe à rajouter
	std::vector<Missile *>	_missiles;


public:
	Player(std::string const &, irr::scene::ISceneManager *);
	~Player();

	void					update(irr::f32 dt);

	void					setInputs(int);
	void					setCollisions(irr::scene::ISceneManager* &smgr);

	Entity const &			getEntity() const;

	int		input;

	// Ce que charpe à rajouter
	void					fire_blipblipblipblipblip();
	bool	fire;
	bool	stopped_fire;
	bool	has_missile;
};

#endif