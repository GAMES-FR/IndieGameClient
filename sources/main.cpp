#include <vector>
#include "Loop.hpp"
#include "Constants.hpp"

#if defined (_IRR_WINDOWS_) && ! defined (MSYS)
# pragma comment(lib, "Irrlicht.lib")
// # pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

namespace core
{
	core::device_t *device = new core::device_t;
}

/* 
 * bonjour je suis le main
 * pour l'instant je contient l'init de la lib et la boucle de jeu
 */
int main()
{
  core::Receiver receiver;
  int ret;

  core::device->ptr = irr::createDevice(ivideo::EDT_SOFTWARE,
				 icore::dimension2d<irr::u32>(640, 480), 16,
				 false, true, false, &receiver);
  if (!core::device->ptr)
    return (ERROR_CODE);
  core::device->driver = core::device->ptr->getVideoDriver();
  core::device->smgr = core::device->ptr->getSceneManager();
  core::device->guienv = core::device->ptr->getGUIEnvironment();

  core::LoopAllocator<core::ILoop> omg;
  std::vector<core::ILoop, core::LoopAllocator<core::ILoop>> 
	loop((std::size_t)2);
  if (loop[0].init())
    return (ERROR_CODE);
  if (loop[1].init())
    return (ERROR_CODE);

  ret = 0;
  while (core::device->ptr->run())
    ret = loop[ret].loop();
  core::device->ptr->drop();
  return (OK_CODE);
}
