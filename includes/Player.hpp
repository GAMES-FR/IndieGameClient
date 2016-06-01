#ifndef PLAYER_H
# define PLAYER_H

# include <irrlicht.h>
# define _USE_MATH_DEFINES
# include <cmath>

# include "Vehicle.hpp"
# include "Bonus.hpp"
# include "Constants.hpp"

class Player
{
private:
	irr::core::vector3df	_pos;
	irr::core::vector3df	_rot;
	irr::scene::ISceneNode*	_node;
	Vehicle::Car			_vehicle;

	int _life;
	Bonus *_bonus;

public:
	Player(irr::scene::ISceneNode *node);
	~Player();

	void					update(irr::f32 dt);

	void					setNode(irr::scene::ISceneNode *node);

	void					setPosition(irr::core::vector3df newPos);
	void					setPosition(float newX, float newY, float newZ);
	irr::core::vector3df	getPosition() const;
	void					setRotation(irr::core::vector3df newRot);
	void					setRotation(float newX, float newY, float newZ);
	irr::core::vector3df	getRotation() const;
	irr::scene::ISceneNode*	getNode() const;
	void					setCollisions(irr::scene::ISceneManager* &smgr);

	void takeDamage(int nb_damage);
	void heal(int amount);
	int getLife() const;
	void setBonus(Bonus *);
	void useBonus();
	void fire_blipblipblipblipblip();

	bool	left;
	bool	up;
	bool	right;
	bool	down;
	int		input;
};

#endif