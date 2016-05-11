#include "Loop.hpp"
#include "Constants.hpp"

MenuLoop::MenuLoop(device_t *d)
  : _d(d), _title(L"Hello World! - Irrlicht Engine Demo")
{
  d->ptr->setWindowCaption(this->_title);
  d->guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
			   irr::core::rect<irr::s32>(10,10,260,22), true);
}

bool MenuLoop::init()
{
  irr::scene::IAnimatedMesh* mesh =
    this->_d->smgr->getMesh(ASSETS_DIR"/sydney.md2");
  if (!mesh)
    {
      this->_d->ptr->drop();
      return (ERROR_CODE);
    }
  irr::scene::IAnimatedMeshSceneNode* node =
    this->_d->smgr->addAnimatedMeshSceneNode(mesh);
  if (node)
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMD2Animation(irr::scene::EMAT_STAND);
      node->setMaterialTexture(0, this->_d->driver->getTexture(ASSETS_DIR"/sydney.bmp"));
    }
  this->_d->smgr->addCameraSceneNode(0,
				    irr::core::vector3df(0,30,-40),
				    irr::core::vector3df(0,5,0));
  return (OK_CODE);
}

bool MenuLoop::loop()
{
  while (this->_d->ptr->run())
    {
      this->_d->driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
      this->_d->smgr->drawAll();
      this->_d->guienv->drawAll();
      this->_d->driver->endScene();
    }
  return (OK_CODE);
}

MenuLoop::~MenuLoop()
{
}
