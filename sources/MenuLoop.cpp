#include "Loop.hpp"

bool core::MenuLoop::_init(void)
{
  iscene::IAnimatedMesh* mesh =
    core::device->smgr->getMesh(ASSETS_DIR"/sydney.md2");
  if (!mesh)
    {
      core::device->ptr->drop();
      return (ERROR_CODE);
    }
  iscene::IAnimatedMeshSceneNode* node =
    core::device->smgr->addAnimatedMeshSceneNode(mesh);
  if (node)
    {
      node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
      node->setMD2Animation(iscene::EMAT_STAND);
      node->setMaterialTexture(0, core::device->driver->getTexture(ASSETS_DIR"/sydney.bmp"));
    }
  core::device->smgr->addCameraSceneNode(0, icore::vector3df(0, 30, -40),
					  icore::vector3df(0, 5, 0));
  return (OK_CODE);
}

int core::MenuLoop::_loop()
{
  static int omg = 0;

  core::device->driver->beginScene(true, true,
				    ivideo::SColor(255, 100, 101, 140));
  core::device->smgr->drawAll();
  core::device->guienv->drawAll();
  core::device->driver->endScene();
  if (core::Receiver::inputs & core::MOVE_FOWARD)
    std::cout << "omg il avance " << omg << std::endl;
  omg++;
  return (OK_CODE);
}
