#include "Entity.hpp"

Entity::Entity(int id)
{
	this->_id = id;
	this->_pos.pos.X = 0.0f;
	this->_pos.pos.Y = 0.0f;
	this->_pos.pos.Z = 0.0f;
	this->_pos.rot.X = 0.0f;
	this->_pos.rot.Y = 0.0f;
	this->_pos.rot.Z = 0.0f;
	this->_acc.pos.X = 0.0f;
	this->_acc.pos.Y = 0.0f;
	this->_acc.pos.Z = 0.0f;
	this->_acc.rot.X = 0.0f;
	this->_acc.rot.Y = 0.0f;
	this->_acc.rot.Z = 0.0f;
}

Entity::Entity(int id, pos_t pos, pos_t acc)
{
	this->_id = id;
	this->_pos = pos;
	this->_acc = acc;
}

Entity::Entity(int id, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df acc_pos, irr::core::vector3df acc_rot)
{
	this->_id = id;
	this->_pos.pos = pos;
	this->_pos.rot = rot;
	this->_acc.pos = acc_pos;
	this->_acc.rot = acc_rot;
}

Entity::~Entity()
{
	
}

void Entity::update(irr::f32 dt)
{
	printf("%f\n", this->_pos.pos.X);
	this->_pos = this->_pos + this->_acc * dt;
	printf("%f\n", this->_acc.pos.X * dt * 1000.0f);
	this->_node->setPosition(this->_pos.pos);
	this->_node->setRotation(this->_pos.rot);
}