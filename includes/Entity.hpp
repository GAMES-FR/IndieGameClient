#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include "IncludeIrrlicht.hpp"
# include <string>

class Entity {
private:
	iscene::ISceneManager						*smgr;
	iscene::IAnimatedMesh						*mesh;
	iscene::IAnimatedMeshSceneNode				*node;
	iscene::ISceneNodeAnimatorCollisionResponse	*worldCollision;
		
public:
	Entity(std::string const & meshPath, std::string const & name, iscene::ISceneManager *smgr);

	iscene::IAnimatedMesh						*getMesh() const;
	iscene::IAnimatedMeshSceneNode				*getNode() const;

	void											setWorldCollision(iscene::ISceneNodeAnimatorCollisionResponse *worldCollision);
	iscene::ISceneNodeAnimatorCollisionResponse	*getWorldCollision();
};

#endif
