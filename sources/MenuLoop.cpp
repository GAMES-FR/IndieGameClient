#include "Loop.hpp"
#include "Constants.hpp"
#include "Camera.hpp"

MenuLoop::MenuLoop(device_t *d)
  : _device(d), _title(L"Hello World! - Irrlicht Engine Demo")
{
  d->ptr->setWindowCaption(this->_title);
  d->guienv->addStaticText(L"Suck My Wheels",
			   irr::core::rect<irr::s32>(10,10,260,22), true);
}

bool	MenuLoop::init()
{
  this->_device->smgr->addCameraSceneNode(0,
				    irr::core::vector3df(0,0,0),
				    irr::core::vector3df(0,0,0));
  return (OK_CODE);
}

bool	MenuLoop::loop()
{
	// Nodes and meshes to print 
	irr::scene::IAnimatedMesh			*map = this->_device->smgr->getMesh(ASSETS_DIR"/map/awp_india.obj");
	irr::scene::IMeshSceneNode			*map_node = 0;
	irr::scene::IAnimatedMesh			*player_mesh = this->_device->smgr->getMesh(ASSETS_DIR"/car/Avent.obj");
	irr::scene::IAnimatedMeshSceneNode	*player_node = 0;
	irr::scene::IAnimatedMesh			*ennemy_mesh = this->_device->smgr->getMesh(ASSETS_DIR"/truck/bulldozer.obj");
	irr::scene::IAnimatedMeshSceneNode	*ennemy_node = 0;

	if (map)
	{
		map_node = this->_device->smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);
		if (map_node)
		{
			map_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			map_node->setPosition(irr::core::vector3df(0, 0, 0));
		}
	}

	if (player_mesh)
	{
		player_node = this->_device->smgr->addAnimatedMeshSceneNode(player_mesh);
		player_node->setScale(irr::core::vector3df(9.0f, 9.0f, 9.0f));
		player_node->setPosition(irr::core::vector3df(100, 100, 100));
		player_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	if (ennemy_mesh)
	{
		ennemy_node = this->_device->smgr->addAnimatedMeshSceneNode(ennemy_mesh);
		ennemy_node->setPosition(irr::core::vector3df(0, 500, 100));
		ennemy_node->setRotation(irr::core::vector3df(-90, 0, 0));
		ennemy_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	Player		player(player_node);
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
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_Z))
			player.up = true;
		else
			player.up = false;
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_Q))
			player.left = true;
		else
			player.left = false;
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_S))
			player.down = true;
		else
			player.down = false;
		if (this->_device->receiver.isKeyDown(irr::KEY_KEY_D))
			player.right = true;
		else
			player.right = false;
		if (this->_device->receiver.getMouseWheel() != 0)
		{
			printf("%f\n", this->_device->receiver.getMouseWheel());
			camera.addDistance(5 * this->_device->receiver.getMouseWheel());
			this->_device->receiver.setMouseWheel(0);
		}

		player.update(dt);
		camera.updateCamera(&player);
		this->_device->driver->beginScene(true, true, irr::video::SColor(255,200,200,200));
		this->_device->smgr->drawAll();
		this->_device->driver->endScene();
    }
  return (OK_CODE);
}

MenuLoop::~MenuLoop()
{
}
