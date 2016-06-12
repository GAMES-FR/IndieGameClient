#include "Player.hpp"
#include <vector>
#include <iostream>

#define MOVE_SCALE 10

Player::Player(std::string const & meshPath, iscene::ISceneManager *smgr) : entity(meshPath, "Player", smgr)
{
	this->smgr = smgr;

	this->_vehicle.setConfig(Vehicle::getDefaultConfig());

	// Ce que charpe � rajouter
	this->has_missile = false;
	this->stopped_fire = false;
}

Player::~Player()
{
}

Entity const & Player::getEntity() const {
	return this->entity;
}

void Player::update(irr::f32 dt)
{
	iscene::IAnimatedMeshSceneNode *node = this->entity.getNode();
	icore::vector3df pos = node->getPosition();
	icore::vector3df rot = node->getRotation();

	Vector::Vec2 p(pos.X / MOVE_SCALE, pos.Z / MOVE_SCALE);
	Vector::Vec2 kek = this->_vehicle.getPosition();
	if (abs(p.x - kek.x) > 0.1 || abs(p.y - kek.y) > 0.001) {
		std::cout << "Calmez vous !" << std::endl;
		this->_vehicle.calmezVous(M_PI, 10.f);
	}

	this->_vehicle.setPosition(p);

	this->_vehicle.update((double)dt);

	Vector::Vec2 vehiclePos = this->_vehicle.getPosition();
	pos.X = vehiclePos.x * MOVE_SCALE;
	pos.Z = vehiclePos.y * MOVE_SCALE;
	rot.Y = (-this->_vehicle.getHeading() / M_PI * 180.f);
	node->setPosition(pos);
	node->setRotation(rot);

	// Ce que charpe � rajouter
	if ((core::Receiver::inputs & core::GAME_FIRE) && this->stopped_fire)
		fire_blipblipblipblipblip();

	// Check si le missile collisionne : appliquez des calmez-vous aux entit�s avec des PV ;)
	/*bool omg = false;
	for (std::vector<Missile *>::const_iterator it = this->_missiles.begin(); it != this->_missiles.end();)
	{
		std::cout << "it1" << std::endl;
		const std::vector<iscene::ISceneNodeAnimatorCollisionResponse *> worldCollision = (*it)->getEntity().getWorldCollision();
		for (std::vector<iscene::ISceneNodeAnimatorCollisionResponse *>::const_iterator it2 = worldCollision.begin();
		it2 != worldCollision.end(); ++it2)
		{
			std::cout << "noooooooooooooooo" << std::endl;
			if ((*it2)->collisionOccurred())
			{
				delete (*it);
				this->_missiles.erase(it);
				omg = true;
				break;
			}
		}
		if (!omg)
		{
			++it;
			omg = false;
		}
	}*/

	unsigned int	i = 0;
	while (i < this->_missiles.size())
	{
		std::cout << "Checking " << this->_missiles[i]->getEntity().getNode()->getName() << " n" << i <<
			"\n - Missile address : << " << &this->_missiles[i] << " - Mesh address : << " << this->_missiles[i]->getEntity().getMesh() <<
			"\n - Missile queue = " << this->_missiles.size() << std::endl;
		unsigned int j = 0;
		while (j < this->_missiles[i]->getEntity().getWorldCollision().size())
		{
			if (this->_missiles[i]->getEntity().getWorldCollision()[j]->collisionOccurred())
			{
				std::cout << "Deleting missile n" << i << "." << std::endl;
				delete this->_missiles[i];
				std::cout << "Erasing missile n" << i << " from the vector." << std::endl;
				this->_missiles.erase(this->_missiles.begin() + i);
				std::cout << "missile erased." << std::endl;
				break;
			}
			j++;
		}
		i++;
	}
}

void					Player::setCollisions(iscene::ISceneManager* &smgr)
{
	//Ce que jeune poney a chang�
	icore::array<irr::scene::ISceneNode*>	nodes;

	smgr->getSceneNodesFromType(irr::scene::ESNT_ANY, nodes); // Find all nodes

	for (irr::u32 i = 0; i < nodes.size(); ++i)
	{
		iscene::ISceneNode*								node = nodes[i];
		iscene::ITriangleSelector*						selector = 0;
		iscene::ISceneNodeAnimatorCollisionResponse*	anim = 0;

		if (node != this->entity.getNode())
		{
			switch (node->getType())
			{
			case irr::scene::ESNT_OCTREE:
				selector = smgr->createOctreeTriangleSelector(((irr::scene::IMeshSceneNode*)node)->getMesh(), node);
				this->entity.getNode()->setTriangleSelector(selector);

				anim = smgr->createCollisionResponseAnimator(selector,
					this->entity.getNode(), this->entity.getNode()->getTransformedBoundingBox().getExtent(),
					irr::core::vector3df(0, -5.f, 0));

				selector->drop();
				this->entity.getNode()->addAnimator(anim);
				this->entity.addWorldCollision(anim);
				anim->drop();
				break;

			case irr::scene::ESNT_ANIMATED_MESH:
				selector = smgr->createTriangleSelectorFromBoundingBox(node);
				this->entity.getNode()->setTriangleSelector(selector);

				anim = smgr->createCollisionResponseAnimator(selector,
					this->entity.getNode(), this->entity.getNode()->getTransformedBoundingBox().getExtent(),
					irr::core::vector3df(0, 0, 0));

				selector->drop();
				this->entity.getNode()->addAnimator(anim);
				this->entity.addWorldCollision(anim);
				anim->drop();
				break;

			default:
				break;
			}
		}
	}
}

// Ce que charpe � rajouter
void Player::fire_blipblipblipblipblip()
{
	this->_missiles.push_back(new Missile(this->entity.getNode(), this->smgr));
	this->stopped_fire = false;
	//MenuLoop::entities.push_back(this->_bonus);
}
