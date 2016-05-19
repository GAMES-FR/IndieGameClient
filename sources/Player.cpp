#include "Player.hpp"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Player::Player(float x, float y, float z)
{
	this->_pos.X = x;
	this->_pos.Y = y;
	this->_pos.Z = z;
	this->_rot.X = 0;
	this->_rot.Y = 0;
	this->_rot.Z = 0;
	this->left = false;
	this->up = false;
	this->right = false;
	this->down = false;
}

Player::~Player()
{
}

void Player::update(irr::f32 dt)
{
	const irr::f32 speed = 300.f;

	if (this->left)
		this->_rot.Y -= 1;
	if (this->right)
		this->_rot.Y += 1;
	if (this->_rot.Y < -180)
		this->_rot.Y += 360;
	if (this->_rot.Y >= 180)
		this->_rot.Y -= 360;
	if (this->up)
	{
		this->_pos.X += (float)(cos(this->_rot.Y * M_PI / 180.0f) * speed * dt);
		this->_pos.Z -= (float)(sin(this->_rot.Y * M_PI / 180.0f) * speed * dt);
	}
	if (this->down)
	{
		this->_pos.X -= (float)(cos(this->_rot.Y * M_PI / 180.0f) * speed * dt);
		this->_pos.Z += (float)(sin(this->_rot.Y * M_PI / 180.0f) * speed * dt);
	}
	this->_node->setPosition(this->_pos);
	this->_node->setRotation(this->_rot);
}

void Player::setNode(irr::scene::ISceneNode *node)
{
	this->_node = node;
}

void Player::setPosition(irr::core::vector3df newPos)
{
	this->_pos = newPos;
}

void Player::setPosition(float newX, float newY, float newZ)
{
	this->_pos.X = newX;
	this->_pos.Y = newY;
	this->_pos.Z = newZ;
}

irr::core::vector3df Player::getPosition() const
{
	return (this->_pos);
}

void Player::setRotation(irr::core::vector3df newRot)
{
	this->_rot = newRot;
}

void Player::setRotation(float newX, float newY, float newZ)
{
	this->_rot.X = newX;
	this->_rot.Y = newY;
	this->_rot.Z = newZ;
}

irr::core::vector3df Player::getRotation() const
{
	return (this->_rot);
}