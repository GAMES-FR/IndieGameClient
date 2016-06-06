#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include "IncludeIrrlicht.hpp"
# include <string>
# include <vector>

class Entity {
private:
	iscene::ISceneManager										*smgr;
	iscene::IAnimatedMesh										*mesh;
	iscene::IAnimatedMeshSceneNode								*node;
	std::vector<iscene::ISceneNodeAnimatorCollisionResponse*>	worldCollision;
		
public:
	Entity(std::string const & meshPath, std::string const & name, iscene::ISceneManager *smgr);
	~Entity();

	iscene::IAnimatedMesh						*getMesh() const;
	iscene::IAnimatedMeshSceneNode				*getNode() const;

	void														setWorldCollision(std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> worldCollision);
	void														addWorldCollision(iscene::ISceneNodeAnimatorCollisionResponse *anim);
	std::vector<iscene::ISceneNodeAnimatorCollisionResponse*>	const & getWorldCollision() const;
};

#endif
