#include "Missile.hpp"
#include <iostream>

Missile::Missile(iscene::ISceneNode *player, iscene::ISceneManager *smgr) : entity(std::string(MISSILE_MESH_PATH), std::string("missile"), smgr)
{
	std::cout << "CONSTRUCTION" << std::endl;
	irr::core::vector3df playerPos = player->getPosition();
	irr::core::vector3df playerRot = player->getRotation();

	this->entity.getNode()->setPosition(icore::vector3df(playerPos.X, playerPos.Y + 5.f, playerPos.Z));
	this->entity.getNode()->setScale(irr::core::vector3df(MISSILE_SCALE, MISSILE_SCALE, MISSILE_SCALE));
	this->entity.getNode()->setRotation(irr::core::vector3df(playerRot.X, playerRot.Y, playerRot.Z));

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

				anim = smgr->createCollisionResponseAnimator(
					selector, this->entity.getNode(), icore::vector3df(1, 1, 1),
					icore::vector3df(sin(playerRot.Y / 180.f * M_PI + M_PI_2) * 10.f, 0, cos(playerRot.Y / 180.f * M_PI + M_PI_2) * 10.f));

				selector->drop();
				this->entity.getNode()->addAnimator(anim);
				this->entity.addWorldCollision(anim);
				anim->drop();
				break;

			case irr::scene::ESNT_ANIMATED_MESH:
				selector = smgr->createTriangleSelectorFromBoundingBox(node);
				this->entity.getNode()->setTriangleSelector(selector);

				anim = smgr->createCollisionResponseAnimator(selector,
					this->entity.getNode(), icore::vector3df(1, 1, 1),
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

Missile::~Missile()
{
	std::cout << "Missile : " << this->getEntity().getNode()->getName() << std::endl;
}

Entity const &	Missile::getEntity() const
{
	return (this->entity);
}