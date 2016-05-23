#include "Irrlicht.h"
#include "driverChoice.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

const int ResX = 800;
const int ResY = 600;
const bool fullScreen = false;

bool SplitScreen = true;

ICameraSceneNode *camera[4] = { 0, 0, 0, 0 };

class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		//Key S enbale/disable SplitScreen
		if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_KEY_S && event.KeyInput.PressedDown)
		{
			SplitScreen = !SplitScreen;
			return true;
		}
		//Send all other events to camera4
		if (camera[3])
			return camera[3]->OnEvent(event);
		return false;
	}
};

int main()
{
	//ask user for driver
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	//Instance of the EventReceiver
	MyEventReceiver receiver;

	//Initialise the engine
	IrrlichtDevice *device = createDevice(driverType, dimension2du(ResX, ResY), 32, fullScreen, false, false, &receiver);
	if (!device)
		return 1;

	ISceneManager *smgr = device->getSceneManager();
	IVideoDriver *driver = device->getVideoDriver();

	//Load mode1
	IAnimatedMesh *mode1 = smgr->getMesh("../../media/sydney.md2");
	if (!mode1)
		return 1;
	IAnimatedMeshSceneNode *mode1_node = smgr->addAnimatedMeshSceneNode(mode1);
	//Load Texture
	if (mode1_node)
	{
		ITexture *texture = driver->getTexture("../../media/sydney.bmp");
		mode1_node->setMaterialTexture(0, texture);
		mode1_node->setMD2Animation(scene::EMAT_RUN);
		//Disable lighting (we've got not light)
		mode1_node->setMaterialFlag(EMF_LIGHTING, false);
	}

	//Load map
	device->getFileSystem()->addFileArchive("../../media/map-20kdm2.pk3");
	IAnimatedMesh *map = smgr->getMesh("20kdm2.bsp");
	if (map)
	{
		ISceneNode *map_node = smgr->addOctreeSceneNode(map->getMesh(0));
		//Set position
		map_node->setPosition(vector3df(-850, -220, -850));
	}
	//Create 3 fixed and one user-controlled cameras
	//Front
	camera[0] = smgr->addCameraSceneNode(0, vector3df(50, 0, 0), vector3df(0, 0, 0));
	//Top
	camera[1] = smgr->addCameraSceneNode(0, vector3df(0, 50, 0), vector3df(0, 0, 0));
	//Left
	camera[2] = smgr->addCameraSceneNode(0, vector3df(0, 0, 50), vector3df(0, 0, 0));
	//User-controlled
	camera[3] = smgr->addCameraSceneNodeFPS();
	//don't start at sydney's position
	if (camera[3])
		camera[3]->setPosition(core::vector3df(-50, 0, -50));
	//Hide mouse
	device->getCursorControl()->setVisible(false);
	//We want to count the fps
	int lastFPS = -1;

	while (device->run())
	{
		//Set the viewpoint to the whole screen and begin scene
		driver->setViewPort(rect<s32>(0, 0, ResX, ResY));
		driver->beginScene(true, true, SColor(255, 100, 100, 100));
		//If SplitScreen is used
		if (SplitScreen)
		{
			//Activate camera1
			smgr->setActiveCamera(camera[0]);
			//Set viewpoint to the first quarter(left top)
			driver->setViewPort(rect<s32>(0, 0, ResX / 2, ResY / 2));
			//Draw scene
			smgr->drawAll();
			//Activate camera2
			smgr->setActiveCamera(camera[1]);
			//Set viewpoint to the second quarter (right top)
			driver->setViewPort(rect<s32>(ResX / 2, 0, ResX, ResY / 2));
			//Draw scene
			smgr->drawAll();
			//Activate camera3
			smgr->setActiveCamera(camera[2]);
			//Set viewpoint to the third quarter (left bottom)
			driver->setViewPort(rect<s32>(0, ResY / 2, ResX / 2, ResY / 2));
			//Draw scene
			smgr->drawAll();
			//Set viewport the last quarter (right bottom)
			driver->setViewPort(rect<s32>(ResX / 2, ResY / 2, ResX, ResY));
		}
		//Activate camera4
		smgr->setActiveCamera(camera[3]);
		//Draw scene
		smgr->drawAll();
		driver->endScene();
		//Get and show fps
		if (driver->getFPS() != lastFPS)
		{
			lastFPS = driver->getFPS();
			core::stringw tmp = L"Irrlicht SplitScreen-Example (FPS: ";
			tmp += lastFPS;
			tmp += ")";
			device->setWindowCaption(tmp.c_str());
		}
	}
	//Delete device
	device->drop();
	return (0);
}