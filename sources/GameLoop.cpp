#include "Loop.hpp"
#include "Constants.hpp"
#include "Camera.hpp"
#include "Vehicle.hpp"

core::GameLoop::GameLoop(device_t *device)
  : Loop(device, L"Suck My Wheels")
{
}

bool	core::GameLoop::_init(void)
{
  this->_device->smgr->addCameraSceneNode(0,
				    icore::vector3df(0,0,0),
				    icore::vector3df(0,0,0));
  return (OK_CODE);
}

int	core::GameLoop::_loop(void)
{
	// Nodes and meshes to print 
	iscene::IAnimatedMesh			*map = this->_device->smgr->getMesh(ASSETS_DIR"/map/awp_india.obj");
	iscene::IMeshSceneNode			*map_node = 0;
	iscene::IAnimatedMesh			*ennemy_mesh = this->_device->smgr->getMesh(ASSETS_DIR"/truck/bulldozer.obj");
	iscene::IAnimatedMeshSceneNode	*ennemy_node = 0;

	if (map)
	{
		map_node = this->_device->smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);
		if (map_node)
		{
			map_node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
			map_node->setPosition(icore::vector3df(0, 0, 0));
		}
	}

	Player		player(std::string(ASSETS_DIR"/car/Avent.obj"), this->_device->smgr);

	iscene::ISceneNode *playerNode = player.getEntity().getNode();
	playerNode->setScale(icore::vector3df(3.0f, 3.0f, 3.0f));
	playerNode->setPosition(icore::vector3df(100, 100, 100));
	playerNode->setMaterialFlag(ivideo::EMF_LIGHTING, false);

	if (ennemy_mesh)
	{
		ennemy_node = this->_device->smgr->addAnimatedMeshSceneNode(ennemy_mesh);
		ennemy_node->setPosition(icore::vector3df(0, 500, 100));
		ennemy_node->setRotation(icore::vector3df(-90, 0, 0));
		ennemy_node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
	}

	Camera		camera(this->_device->ptr);

	player.setCollisions(this->_device->smgr);

	

	irr::u32	before = camera.getDevice()->getTimer()->getTime();

  while (this->_device->ptr->run())
    {
		const irr::u32 now = camera.getDevice()->getTimer()->getTime();
		const irr::f32 dt = (irr::f32)(now - before) / 1000.f; // Time in seconds
		before = now;

		if (this->_device->receiver.isKeyDown(irr::KEY_ESCAPE))
			return (OK_CODE);
		int inputs = 0;
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_Z))
			inputs |= I_THROTTLE;
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_Q))
			inputs |= I_LEFT;
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_S))
			inputs |= I_BRAKE;
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_D))
			inputs |= I_RIGHT;
		if (this->_device->receiver.isKeyDown(irr::KEY_SPACE))
			inputs |= I_EBRAKE;
		if (this->_device->receiver.isKeyDown(irr::KEY_LCONTROL))
			inputs |= I_REVERSE;

		// Ce que charpe à rajouter
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_F))
		{
			if (!player.fire)
				player.stopped_fire = true;
			player.fire = true;
		}
		else
			player.fire = false;

		player.setInputs(inputs);
			if (this->_device->receiver.getMouseWheel() != 0)
		{
			camera.addDistance(5 * this->_device->receiver.getMouseWheel());
			this->_device->receiver.setMouseWheel(0);
		}

		player.update(dt);
		camera.updateCamera(&player);
		this->_device->driver->beginScene(true, true, ivideo::SColor(255,200,200,200));
		this->_device->smgr->drawAll();
		this->_device->driver->endScene();
    }
  return (OK_CODE);
}
