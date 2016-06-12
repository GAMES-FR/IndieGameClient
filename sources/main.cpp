#include "Loop.hpp"
#include "Constants.hpp"
#include "irrKlang.h"
#include "irrKlangSceneNode.h"

#if defined (_IRR_WINDOWS_) && ! defined (MSYS)
# pragma comment(lib, "Irrlicht.lib")
# pragma comment(lib, "irrKlang.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

/* 
 * bonjour je suis le main
 * pour l'instant je contient l'init de la lib et la boucle de jeu
 */
int main()
{
  ::core::device_t	device;
  ::core::ILoop		*loop[2];
  int ret;

  irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();

  // .. other code here

  /* lib and device init */
  device.ptr = irr::createDevice(ivideo::EDT_OPENGL,
	  icore::dimension2d<irr::u32>(1280, 720), 16,
				 false, true, false, &device.receiver);
  if (!device.ptr)
    return (ERROR_CODE);
  device.driver = device.ptr->getVideoDriver();
  device.smgr = device.ptr->getSceneManager();
  device.guienv = device.ptr->getGUIEnvironment();

  CIrrKlangSceneNode* soundNode =
	  new CIrrKlangSceneNode(soundEngine, device.smgr->getRootSceneNode(), device.smgr, 666);

  soundNode->setSoundFileName(ASSETS_DIR"/salty.flac");
  soundNode->setMinMaxSoundDistance(300.0f); // influences the distance where the sound can be heard
  //soundNode->setRandomMode(1000, 5000); // plays sound multiple times with random interval

										// other modes would be:
  soundNode->setLoopingStreamMode();
										// or
										// soundNode->setPlayOnceMode();
  //soundNode->drop();


  loop[0] = new ::core::GameLoop(&device);
  // loop[1] = new ::core::MenuLoop(&device);
  if (loop[0]->init())
    return (ERROR_CODE);
  // if (loop[1]->init())
  //   return (ERROR_CODE);

  ret = 0;
  while (device.ptr->run())
    ret = loop[ret]->loop();
  device.ptr->drop();
  // delete loop[1];
  delete loop[0];
  return (OK_CODE);
}
