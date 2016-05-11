#include <irrlicht.h>
#include <iostream>
#include "Constants.hpp"
#include "Input.h"
#include "Camera.h"
#include "Player.h"

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


/*
* bonjour je suis le main
* pour l'instant je contient l'init de la lib et la boucle de jeu
*/
int main()
{
	InputHandler		receiver;
	Player				player;

	irr::IrrlichtDevice *device =
		irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, false, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();

	device->getFileSystem()->addFileArchive(ASSETS_DIR"/map-20kdm2.pk3");

	irr::scene::IAnimatedMesh			*map = smgr->getMesh("20kdm2.bsp");
	irr::scene::ISceneNode				*map_node = 0;
	irr::scene::ISceneNode				*sphere = smgr->addSphereSceneNode();
	irr::scene::ISceneNode				*sphere2 = smgr->addSphereSceneNode();
	irr::scene::IAnimatedMesh			*bear = smgr->getMesh(ASSETS_DIR"/bear.obj");
	irr::scene::ISceneNode				*bear_node = 0;

	if (bear)
	{
		bear_node = smgr->addOctreeSceneNode(bear->getMesh(0), 0, -1, 1024);
		bear->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	if (map)
		map_node = smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);

	if (map_node)
		map_node->setPosition(irr::core::vector3df(-1300, -144, -1249));

	if (sphere)
	{
		sphere->setPosition(irr::core::vector3df(0, 0, 30));
		sphere->setMaterialTexture(0, driver->getTexture(ASSETS_DIR"/wall.bmp"));
		sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	if (sphere2)
	{
		sphere2->setPosition(irr::core::vector3df(0, 30, 30));
		sphere2->setMaterialTexture(0, driver->getTexture(ASSETS_DIR"/wall.bmp"));
		sphere2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	smgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));

	device->getCursorControl()->setVisible(false);
	player.setNode(bear_node);

	Camera				camera(device, sphere);

	int lastFPS = -1;
	irr::u32 before = camera.getDevice()->getTimer()->getTime();
	
	while (device->run())
	{
		if (device->isWindowActive())
		{
			const irr::u32 now = camera.getDevice()->getTimer()->getTime();
			const irr::f32 dt = (irr::f32)(now - before) / 1000.f; // Time in seconds
			before = now;

			receiver.moveObject(camera, player, dt);
			receiver.setZoom(camera);
			camera.moveCameraControl(player.getNode());

			driver->beginScene(true, true, irr::video::SColor(255, 200, 200, 200));
			smgr->drawAll();
			driver->endScene();

			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				irr::core::stringw str = "Irrlicht Engine - Quake 3 Map example [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		}
		else
			device->yield();
	}

	device->drop();
	return 0;
}