#include "Entity.hpp"

Entity::Entity(std::string const & meshPath, std::string const & name, irr::scene::ISceneManager *smgr) {
	this->mesh = smgr->getMesh(meshPath.c_str());
	this->node = smgr->addAnimatedMeshSceneNode(this->mesh);
	this->smgr = smgr;
}

irr::scene::IAnimatedMesh						*Entity::getMesh() const {
	return (this->mesh);
}

irr::scene::IAnimatedMeshSceneNode				*Entity::getNode() const {
	return (this->node);
}

void											Entity::setWorldCollision(irr::scene::ISceneNodeAnimatorCollisionResponse * worldCollision) {
	this->worldCollision = worldCollision;
}

irr::scene::ISceneNodeAnimatorCollisionResponse	*Entity::getWorldCollision() {
	return (this->worldCollision);
}