#include <irrlicht.h>

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifndef PLAYER_H
# define PLAYER_H

class Player
{
private:
	irr::scene::ISceneNode *_node;

public:
	Player(irr::scene::ISceneNode *node = 0)
	{
		this->_node = node;
	}

	void	setNode(irr::scene::ISceneNode *node)
	{
		this->_node = node;
	}

	irr::scene::ISceneNode*	getNode() const
	{
		return (this->_node);
	}
};

#endif