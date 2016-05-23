#include "Loop.hpp"
#include "Constants.hpp"
#include "Camera.hpp"

MenuLoop::MenuLoop(device_t *d)
  : _device(d), _title(L"Hello World! - Irrlicht Engine Demo")
{
  d->ptr->setWindowCaption(this->_title);
  d->guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
			   irr::core::rect<irr::s32>(10,10,260,22), true);
}

bool MenuLoop::init()
{
  /*irr::scene::IAnimatedMesh* mesh =
    this->_device->smgr->getMesh(ASSETS_DIR"/sydney.md2");
  if (!mesh)
    {
      this->_device->ptr->drop();
      return (ERROR_CODE);
    }
  irr::scene::IAnimatedMeshSceneNode* node =
    this->_device->smgr->addAnimatedMeshSceneNode(mesh);
  if (node)
    {
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMD2Animation(irr::scene::EMAT_STAND);
		node->setMaterialTexture(0, this->_device->driver->getTexture(ASSETS_DIR"/sydney.bmp"));
    }*/
  this->_device->smgr->addCameraSceneNode(0,
				    irr::core::vector3df(0,0,0),
				    irr::core::vector3df(0,0,0));
  return (OK_CODE);
}

bool MenuLoop::loop()
{
	this->_device->ptr->getFileSystem()->addFileArchive(ASSETS_DIR"/map-20kdm2.pk3");

	// Nodes and meshes to print 
	irr::scene::IAnimatedMesh			*map = this->_device->smgr->getMesh("20kdm2.bsp");
	irr::scene::ISceneNode				*map_node = 0;
	irr::scene::IMesh					*bear = this->_device->smgr->getMesh(ASSETS_DIR"/bear.obj");
	irr::scene::ISceneNode				*bear_node = 0;

	// Collision detection
	irr::scene::ITriangleSelector*		selector = 0;

	if (bear)
	{
		bear_node = this->_device->smgr->addMeshSceneNode(bear, 0, -1, irr::core::vector3df(90, -80, 90),
			irr::core::vector3df(0, 0, 0),
			irr::core::vector3df(2.0f, 2.0f, 2.0f));
		bear_node->setMaterialTexture(0, this->_device->driver->getTexture(ASSETS_DIR"/bear.tga"));
		bear->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	if (map)
		map_node = this->_device->smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);

	if (map_node)
	{
		map_node->setPosition(irr::core::vector3df(-1300, -144, -1249));
		selector = this->_device->smgr->createOctreeTriangleSelector(map->getMesh(0), map_node, 128);
		map_node->setTriangleSelector(selector);
	}

	Player		player(bear_node);
	Camera		camera(this->_device->ptr);
	irr::u32	before = camera.getDevice()->getTimer()->getTime();

  while (this->_device->ptr->run())
    {
		const irr::u32 now = camera.getDevice()->getTimer()->getTime();
		const irr::f32 dt = (irr::f32)(now - before) / 1000.f; // Time in seconds
		before = now;

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
