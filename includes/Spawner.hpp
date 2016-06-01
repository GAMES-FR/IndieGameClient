#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#ifndef SPAWNER_HPP_
# define SPAWNER_HPP_

# include <irrlicht.h>

# include "Bonus.hpp"
# include "Player.hpp"
# include "Loop.hpp"
# include "Constants.hpp"
# include "Entity.hpp"

class Spawner : public Entity
{
private:
	Bonus *_bonus;
	Bonus::Type _type;

	void generateBonus();

public:
	Spawner(struct device_t *&);
	~Spawner();

	void giveBonusToPlayer(Player &);
	void setCollisions(irr::scene::ISceneManager* &smgr);
};

#endif /* !SPAWNER_HPP */