#ifndef MISSILE_HPP_
# define MISSILE_HPP_

# define _USE_MATH_DEFINES
# include "Entity.hpp"
# include "Constants.hpp"
# include "GMath.hpp"

class Missile
{
private:
	Entity	entity;

public:
	Missile(irr::scene::ISceneNode *, irr::scene::ISceneManager *);
	~Missile();
};

#endif /* !MISSILE_HPP_ */