#include "Loop.hpp"
#include "Constants.hpp"
#include "Input.hpp"

#if defined (_IRR_WINDOWS_) && ! defined (MSYS)
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

/* 
 * bonjour je suis le main
 * pour l'instant je contient l'init de la lib et la boucle de jeu
 */
int main()
{
  device_t	device;
  bool		ret;

  /* lib and device init */
  device.ptr = irr::createDevice(irr::video::EDT_OPENGL,
	  irr::core::dimension2d<irr::u32>(1280, 720), 16,
				 false, true, false, &device.receiver);
  if (!device.ptr)
    return (ERROR_CODE);
  device.driver = device.ptr->getVideoDriver();
  device.smgr = device.ptr->getSceneManager();
  device.guienv = device.ptr->getGUIEnvironment();

  /* gui and objects init */
  MenuLoop menu(&device);
  if (menu.init())
    return (ERROR_CODE);

  /* omg la loop */
  ret = menu.loop();
  device.ptr->drop();
  return (ret);
}
