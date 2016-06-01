#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <irrlicht.h>

typedef struct pos_s
{
	irr::core::vector3df pos;
	irr::core::vector3df rot;
	struct pos_s operator*(irr::f32 f) { struct pos_s tmp; tmp.pos = pos * f; tmp.rot = rot * f; return tmp; }
	struct pos_s operator+(struct pos_s p) { struct pos_s tmp; tmp.pos = pos + p.pos; tmp.rot = rot + p.rot; return tmp; }
} pos_t;

class Entity
{
protected:
	int _id;
	pos_t _pos;
	pos_t _acc;
	irr::scene::IAnimatedMeshSceneNode *_node;

public:
	Entity(int id);
	Entity(int id, pos_t pos, pos_t acc);
	Entity(int id, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df acc_pos, irr::core::vector3df acc_rot);
	~Entity();

	virtual void update(irr::f32 dt);
};

#endif /* !ENTITY_HPP_ */