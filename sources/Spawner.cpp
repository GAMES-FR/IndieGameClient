#include "Spawner.hpp"

Spawner::Spawner(struct device_t *&device) : Entity(0)
{
	this->_type = (Bonus::Type)(rand() % NB_BONUS);
	this->generateBonus();
	
	irr::scene::IAnimatedMesh					*mesh = device->smgr->getMesh(ASSETS_DIR"/bear.obj");
	this->_node = 0;

	// Collision detection

	if (mesh)
	{
		this->_node = device->smgr->addAnimatedMeshSceneNode(mesh);
		//player_node->setScale(irr::core::vector3df(15.0f, 15.0f, 15.0f));
		this->_node->setPosition(irr::core::vector3df(50, 100, 100));
		this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}
	this->_pos.pos.X = this->_node->getPosition().X;
	this->_pos.pos.Y = this->_node->getPosition().Y;
	this->_pos.pos.Z = this->_node->getPosition().Z;

	irr::scene::IMetaTriangleSelector*			meta = device->smgr->createMetaTriangleSelector();
}

Spawner::~Spawner()
{

}

void Spawner::generateBonus()
{
	this->_bonus = new Bonus(this->_type);
}

void Spawner::giveBonusToPlayer(Player &player)
{
	player.setBonus(this->_bonus);
	this->_bonus = NULL;
}

void					Spawner::setCollisions(irr::scene::ISceneManager* &smgr)
{
	irr::scene::IMetaTriangleSelector*			meta = smgr->createMetaTriangleSelector(); // Hold several triangles at a time
	irr::core::array<irr::scene::ISceneNode*>	nodes;

	smgr->getSceneNodesFromType(irr::scene::ESNT_ANY, nodes); // Find all nodes

	for (irr::u32 i = 0; i < nodes.size(); ++i)
	{
		irr::scene::ISceneNode*			node = nodes[i];
		irr::scene::ITriangleSelector*	selector = 0;

		if (node != this->_node)
		{
			switch (node->getType())
			{
			case irr::scene::ESNT_ANIMATED_MESH:
				selector = smgr->createTriangleSelectorFromBoundingBox(node);
				break;

			case irr::scene::ESNT_OCTREE:
				selector = smgr->createOctreeTriangleSelector(((irr::scene::IMeshSceneNode*)node)->getMesh(), node);
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
		irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			meta, this->_node, this->_node->getTransformedBoundingBox().getExtent(),
			irr::core::vector3df(0, -5.f, 0));
		meta->drop();

		this->_node->addAnimator(anim);
		anim->drop();
	}
}
