#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <irrlicht.h>
# include <string>

class Entity {
private:
	irr::scene::IAnimatedMesh						*mesh;
	irr::scene::IAnimatedMeshSceneNode				*node;
	irr::scene::ISceneNodeAnimatorCollisionResponse	*collision;

public:
	Entity(std::string const & meshPath, std::string const & name);

	irr::scene::IAnimatedMesh						*getMesh() const;
	irr::scene::IAnimatedMeshSceneNode				*getNode() const;

	void											setCollision();
	irr::scene::ISceneNodeAnimatorCollisionResponse	*getCollision();
};

#endif