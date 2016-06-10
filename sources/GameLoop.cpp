#include "Loop.hpp"
#include "Constants.hpp"
#include "Camera.hpp"
#include "Vehicle.hpp"

std::vector<iscene::IAnimatedMeshSceneNode *> core::GameLoop::gosts;

core::GameLoop::GameLoop(device_t *device)
  : Loop(device, L"Suck My Wheels")
{
}

core::GameLoop::~GameLoop(void)
{
  unsigned int ct;

  ct = -1;
  while (++ct < core::GameLoop::gosts.size())
    core::GameLoop::gosts[ct]->drop();
}

bool	core::GameLoop::_init(void)
{
  this->_device->smgr->addCameraSceneNode(0,
				    icore::vector3df(0,0,0),
				    icore::vector3df(0,0,0));	// Nodes and meshes to print 
	iscene::IAnimatedMesh			*map = this->_device->smgr->getMesh(MAP_MESH_PATH);
	iscene::IMeshSceneNode			*map_node = 0;
	iscene::IAnimatedMesh			*ennemy_mesh = this->_device->smgr->getMesh(ENEMY_MESH_PATH);
	iscene::IAnimatedMeshSceneNode	*ennemy_node = 0;
	iscene::ISceneNode* skybox = this->_device->smgr->addSkyBoxSceneNode(
		this->_device->driver->getTexture("../../assets/sky/test_shadowmoon_moon01.png"),
		this->_device->driver->getTexture("../../assets/sky/test_shadowmoon_moon01.png"),
		this->_device->driver->getTexture("../../assets/sky/test_shadowmoon_moon01.png"),
		this->_device->driver->getTexture("../../assets/sky/test_shadowmoon_moon01.png"),
		this->_device->driver->getTexture("../../assets/sky/test_shadowmoon_moon01.png"),
		this->_device->driver->getTexture("../../assets/sky/test_shadowmoon_moon01.png"));
	skybox->setRotation(irr::core::vector3df(0.f, 0.f, 0.f));
	//iscene::ISceneNode* skydome = this->_device->smgr->addSkyDomeSceneNode(this->_device->driver->getTexture("../../assets/sky/ashrand_bright_stormy_front.png"), 16, 8, 1.0f, 2.0f);
	//skydome->setRotation(irr::core::vector3df(5.f, 5.f, 5.f));

	if (map)
	{
		map_node = this->_device->smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);
		if (map_node)
		{
			map_node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
			map_node->setPosition(icore::vector3df(150, 0, 100));
			map_node->setScale(icore::vector3df(10.0f, 10.0f, 10.0f));
			map_node->setName("map");
		}
	}

        this->_player = new Player(std::string(CAR_MESH_PATH), this->_device->smgr);

	iscene::ISceneNode *playerNode = this->_player->getEntity().getNode();
	playerNode->setScale(icore::vector3df(2.0f, 2.0f, 2.0f));
	playerNode->setPosition(icore::vector3df(-600, 0, 100));
	playerNode->setMaterialFlag(ivideo::EMF_LIGHTING, false);
	playerNode->setName("player");

	if (ennemy_mesh)
	{
		ennemy_node = this->_device->smgr->addAnimatedMeshSceneNode(ennemy_mesh);
		ennemy_node->setPosition(icore::vector3df(600, -35, 100));
		ennemy_node->setScale(icore::vector3df(0.5f, 0.5f, 0.5f));
		ennemy_node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
		ennemy_node->setName("enemy");
	}

        this->_camera = new Camera(this->_device->ptr);

	this->_player->setCollisions(this->_device->smgr);

        this->_before = this->_camera->getDevice()->getTimer()->getTime();
  return (OK_CODE);
}

int	core::GameLoop::_loop(void)
{
  const irr::u32 now = this->_camera->getDevice()->getTimer()->getTime();
  const irr::f32 dt = (irr::f32)(now - this->_before) / 1000.f; // Time in seconds
  this->_before = now;

  if (core::Receiver::inputs & core::GUI_MENU)
    return (OK_CODE);

  // Ce que charpe à rajouter
  if (!(core::Receiver::inputs & GAME_FIRE))
    this->_player->stopped_fire = true;

  if (core::Receiver::scroll != 0)
    {
      this->_camera->addDistance(5 * core::Receiver::scroll);
      core::Receiver::scroll = 0;
    }

  this->_player->update(dt);
  this->_camera->updateCamera(this->_player);
  this->_device->driver->beginScene(true, true, ivideo::SColor(255, 200, 200, 200));
  this->_device->smgr->drawAll();
  this->_device->driver->endScene();
  return (OK_CODE);
}
