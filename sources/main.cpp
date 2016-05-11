#include <irrlicht.h>
#include "Constants.hpp"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

/* 
 * bonjour je suis le main
 * pour l'instant je contient l'init de la lib et la boucle de jeu
 */
int main()
{
  /* lib and device init */
  irr::IrrlichtDevice *device =
    irr::createDevice(irr::video::EDT_SOFTWARE,
		      irr::core::dimension2d<irr::u32>(640, 480), 16,
		      false, false, false, 0);
  if (!device)
    return (ERROR_CODE);
  irr::video::IVideoDriver* driver = device->getVideoDriver();
  irr::scene::ISceneManager* smgr = device->getSceneManager();
  irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

  /* gui and objects init */
  device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
  guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
			irr::core::rect<irr::s32>(10,10,260,22), true);
  irr::scene::IAnimatedMesh* mesh = smgr->getMesh(ASSETS_DIR"/sydney.md2");
  if (!mesh)
    {
      device->drop();
      return (ERROR_CODE);
    }
  irr::scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
  if (node)
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMD2Animation(irr::scene::EMAT_STAND);
      node->setMaterialTexture(0, driver->getTexture(ASSETS_DIR"/sydney.bmp") );
    }
  smgr->addCameraSceneNode(0,
			   irr::core::vector3df(0,30,-40),
			   irr::core::vector3df(0,5,0));

  /* omg la loop */
  while(device->run())
    {
      /* clear screen */
      driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

      /* draw */
      smgr->drawAll();
      guienv->drawAll();

      /* blit */
      driver->endScene();
    }
  device->drop();
  return (OK_CODE);
}
