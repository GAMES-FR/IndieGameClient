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

bool MenuLoop::init()
{
  this->_device->smgr->addCameraSceneNode(0,
				    irr::core::vector3df(0,0,0),
				    irr::core::vector3df(0,0,0));
  return (OK_CODE);
}

bool MenuLoop::loop()
{
	//this->_device->ptr->getFileSystem()->addFileArchive(ASSETS_DIR"/map-20kdm2.pk3");

	// Nodes and meshes to print 
	irr::scene::IAnimatedMesh			*map = this->_device->smgr->getMesh(ASSETS_DIR"/map/awp_india.obj");
	irr::scene::IMeshSceneNode			*map_node = 0;
	irr::scene::IAnimatedMesh			*player_mesh = this->_device->smgr->getMesh(ASSETS_DIR"/car/Avent.obj");
	irr::scene::IAnimatedMeshSceneNode	*player_node = 0;

	// Collision detection
	irr::scene::ITriangleSelector*		selector = 0;

	if (map)
	{
		map_node = this->_device->smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);
		if (map_node)
		{
			map_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			map_node->setPosition(irr::core::vector3df(0, 0, 0));
			selector = this->_device->smgr->createOctreeTriangleSelector(map->getMesh(0), map_node, 128);
			map_node->setTriangleSelector(selector);
		}
	}

	if (player_mesh)
	{
		player_node = this->_device->smgr->addAnimatedMeshSceneNode(player_mesh);
		player_node->setScale(irr::core::vector3df(15.0f, 15.0f, 15.0f));
		player_node->setPosition(irr::core::vector3df(100, 84, 100));
		player_node->setRotation(irr::core::vector3df(0, 90, 0));
		player_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	Player		player(player_node);

	if (selector)
	{
		irr::scene::ISceneNodeAnimator* anim = this->_device->smgr->createCollisionResponseAnimator(
			selector, player_node, player_node->getTransformedBoundingBox().getExtent(), irr::core::vector3df(0, -10.0f, 0));
		player_node->addAnimator(anim);
		anim->drop();  // And likewise, drop the animator when we're done referring to it.
		selector->drop(); // As soon as we're done with the selector, drop it.
	}

	Camera		camera(this->_device->ptr);
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
			camera.addZoom(5 * this->_device->receiver.getMouseWheel());
			this->_device->receiver.setMouseWheel(0);
		}

		player.update(dt);
		camera.updateCamera(&player);
		this->_device->driver->beginScene(true, true, irr::video::SColor(255,200,200,200));
		this->_device->smgr->drawAll();
		//this->_device->guienv->drawAll();
		this->_device->driver->endScene();
    }
  return (OK_CODE);
}

MenuLoop::~MenuLoop()
{
}
