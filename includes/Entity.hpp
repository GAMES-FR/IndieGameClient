#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <irrlicht.h>
# include <string>

class Entity {
private:
	irr::scene::ISceneManager						*smgr;
	irr::scene::IAnimatedMesh						*mesh;
	irr::scene::IAnimatedMeshSceneNode				*node;
	irr::scene::ISceneNodeAnimatorCollisionResponse	*worldCollision;
		
public:
	Entity(std::string const & meshPath, std::string const & name, irr::scene::ISceneManager *smgr);

	irr::scene::IAnimatedMesh						*getMesh() const;
	irr::scene::IAnimatedMeshSceneNode				*getNode() const;

	void											setWorldCollision(irr::scene::ISceneNodeAnimatorCollisionResponse *worldCollision);
	irr::scene::ISceneNodeAnimatorCollisionResponse	*getWorldCollision();
};

#endif