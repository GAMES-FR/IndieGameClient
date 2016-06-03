#include "Missile.hpp"

Missile::Missile(irr::scene::ISceneNode *player, irr::scene::ISceneManager *smgr) : entity(std::string(MISSILE_MESH_PATH), std::string("missile"), smgr)
{
	this->entity.getNode()->setPosition(irr::core::vector3df(player->getPosition().X, player->getPosition().Y + 20.f, player->getPosition().Z));
	this->entity.getNode()->setRotation(player->getRotation());

	irr::scene::IMetaTriangleSelector*			meta = smgr->createMetaTriangleSelector(); // Hold several triangles at a time
	irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		meta, this->entity.getNode(), this->entity.getNode()->getTransformedBoundingBox().getExtent(),
		irr::core::vector3df(sin(player->getRotation().Y / 180.f * M_PI + M_PI_2) * 10.f, 0, cos(player->getRotation().Y / 180.f * M_PI + M_PI_2) * 10.f));

	meta->drop();
	this->entity.getNode()->addAnimator(anim);
	anim->drop();
}

Missile::~Missile()
{

}