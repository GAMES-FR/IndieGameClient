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

	smgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	device->getFileSystem()->addFileArchive(ASSETS_DIR"/map-20kdm2.pk3");

	// Nodes and meshes to print 
	irr::scene::IAnimatedMesh			*map = smgr->getMesh("20kdm2.bsp");
	irr::scene::ISceneNode				*map_node = 0;
	irr::scene::ISceneNode				*sphere = smgr->addSphereSceneNode();
	irr::scene::ISceneNode				*sphere2 = smgr->addSphereSceneNode();
	irr::scene::IMesh					*bear = smgr->getMesh(ASSETS_DIR"/bear.obj");
	irr::scene::ISceneNode				*bear_node = 0;

	// Collision detection
	irr::scene::ITriangleSelector*		selector = 0;

	if (bear)
	{
		bear_node = smgr->addMeshSceneNode(bear, 0, -1, irr::core::vector3df(90, -80, 90),
			irr::core::vector3df(0, 0, 0),
			irr::core::vector3df(2.0f, 2.0f, 2.0f));
		sphere->setMaterialTexture(0, driver->getTexture(ASSETS_DIR"/bear.tga"));
		bear->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	if (map)
		map_node = smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);

	if (map_node)
	{
		map_node->setPosition(irr::core::vector3df(-1300, -144, -1249));
		selector = smgr->createOctreeTriangleSelector(map->getMesh(0), map_node, 128);
		map_node->setTriangleSelector(selector);
	}

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

	/*if (selector)
	{
		irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			selector, smgr->getActiveCamera(), irr::core::vector3df(30, 50, 30),
			irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
		selector->drop(); // As soon as we're done with the selector, drop it.
		smgr->getActiveCamera()->addAnimator(anim);
		anim->drop();  // And likewise, drop the animator when we're done referring to it.
	}*/

	/*selector = smgr->createTriangleSelector(bear, bear_node);
	bear_node->setTriangleSelector(selector);
	selector->drop();*/

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