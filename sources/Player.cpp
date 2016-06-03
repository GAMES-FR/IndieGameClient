#include "Player.hpp"
#include <iostream>

#define MOVE_SCALE 10

Player::Player(std::string const & meshPath, iscene::ISceneManager *smgr) : entity(meshPath, "Player", smgr)
{
	this->smgr = smgr;
	
	this->input = 0;
	this->_vehicle.setConfig(Vehicle::getDefaultConfig());

	// Ce que charpe à rajouter
	this->fire = false;
	this->has_missile = false;
	this->stopped_fire = false;
}

Player::~Player()
{
}

void Player::setInputs(int inputs) {
	this->input = inputs;
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
	this->_vehicle.setPosition(p);

	this->_vehicle.setInputs(this->input);
	this->_vehicle.update((double)dt);
	
	Vector::Vec2 vehiclePos = this->_vehicle.getPosition();
	pos.X = vehiclePos.x * MOVE_SCALE;
	pos.Z = vehiclePos.y * MOVE_SCALE;
	rot.Y = (-this->_vehicle.getHeading() / M_PI * 180.f);
	node->setPosition(pos);
	node->setRotation(rot);

	// Ce que charpe à rajouter
	if (this->fire && this->stopped_fire)
		fire_blipblipblipblipblip();
}

void					Player::setCollisions(iscene::ISceneManager* &smgr)
{
	iscene::IMetaTriangleSelector*			meta = smgr->createMetaTriangleSelector(); // Hold several triangles at a time
	icore::array<iscene::ISceneNode*>	nodes;
	iscene::ISceneNode *playerNode = this->entity.getNode();

	smgr->getSceneNodesFromType(iscene::ESNT_ANY, nodes); // Find all nodes

	for (irr::u32 i = 0; i < nodes.size(); ++i)
	{
		iscene::ISceneNode*			node = nodes[i];
		iscene::ITriangleSelector*	selector = 0;

		if (node != playerNode)
		{
			switch (node->getType())
			{
			case iscene::ESNT_ANIMATED_MESH:
				selector = smgr->createTriangleSelectorFromBoundingBox(node);
				break;

			case iscene::ESNT_OCTREE:
				selector = smgr->createOctreeTriangleSelector(((iscene::IMeshSceneNode*)node)->getMesh(), node);
				break;

			default:
				break;
			}

			if (selector)
			{
				// Add selector to the meta then drop it *DUBSTEP INTENSIFIES*
				meta->addTriangleSelector(selector);
				selector->drop();
			}
		}
	}

	if (meta)
	{
		iscene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			meta, playerNode, playerNode->getTransformedBoundingBox().getExtent(),
			icore::vector3df(0, -5.f, 0));
		meta->drop();

		playerNode->addAnimator(anim);
		anim->drop();
	}
}

// Ce que charpe à rajouter
void Player::fire_blipblipblipblipblip()
{
	this->_missiles.push_back(new Missile(this->entity.getNode(), this->smgr));
	this->stopped_fire = false;
	//MenuLoop::entities.push_back(this->_bonus);
}
