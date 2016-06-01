#include "Loop.hpp"

bool core::GameLoop::_init(void)
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

int core::GameLoop::_loop()
{
  core::device->driver->beginScene(true, true,
				    ivideo::SColor(255, 100, 101, 140));
  core::device->smgr->drawAll();
  core::device->guienv->drawAll();
  core::device->driver->endScene();
  return (OK_CODE);
}
