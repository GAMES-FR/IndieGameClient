#include "irrXML.h"
#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;
using namespace io;
using namespace gui;
using namespace core;
using namespace scene;
using namespace video;

#if defined _IRR_WINDOWS_&& ! defined (MSYS)
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <string>

const std::string tab[4] = { "PANEL_CONTROLS", "PANEL_VIDEO_AND_SOUND", "PANEL_STATS", "PANEL_BACK" };

enum Button_Type
{
	PANEL_CONTROLS,
	PANEL_VIDEO_AND_SOUND,
	PANEL_STATS,
	PANEL_BACK
};

Button_Type get_Index(std::string id)
{
	int i = 0;

	while (i < 4)
	{
		if (id == tab[4])
			return (Button_Type)i;
		i++;
	}
}

int main()
{
	IrrXMLReader* xml = createIrrXMLReader("../../XML/point xml/panel4.xml");

	std::string title;
	std::string button;
	std::string scroll;
	std::string input;
	std::string id;
	std::string label;
	std::string text;
	std::string size;
	std::string positionX;
	std::string positionY;
	std::string sizeW;
	std::string sizeH;
	std::string scrollW;
	std::string scrollH;
	std::string scrollX;
	std::string scrollY;

	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;
	IrrlichtDevice * device = createDevice(driverType, core::dimension2d<u32>(640, 480));
	if (device == 0)
		return 1;
	device->setResizable(true);

	video::IVideoDriver* driver = device->getVideoDriver();
	IGUIEnvironment* env = device->getGUIEnvironment();
	while (xml && xml->read())
	{
		switch (xml->getNodeType())
		{
		case EXN_TEXT:
			title = xml->getNodeData();
			break;
		case EXN_ELEMENT:
			if (!strcmp("title", xml->getNodeName()))
			{
				button = xml->getAttributeValue("text");
				/*env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()), atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::CONTROL_FORWARD);
				env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()), atoi(sizeW.c_str()), atoi(sizeH.c_str())),0, Button_Type::CONTROL_LEFT);
				env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()), atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_BACK);
				while (device->run() && driver)
				if (device->isWindowActive())
				{
				driver->beginScene(true, true, SColor(0, 200, 200, 200));
				env->drawAll();
				driver->endScene();
				}
				device->drop();
				printf("%s\n", button.c_str());*/
			}

			if (!strcmp("size", xml->getNodeName()))
			{
				sizeH = xml->getAttributeValue("h");
				sizeW = xml->getAttributeValue("w");
			}

			if (!strcmp("position", xml->getNodeName()))
			{
				positionX = xml->getAttributeValue("x");
				positionY = xml->getAttributeValue("y");
			}

			if (!strcmp("button", xml->getNodeName()))
			{
				id = xml->getAttributeValue("id");
				text = xml->getAttributeValue("text");
			}

			if (!strcmp("size", xml->getNodeName()))
			{
				sizeH = xml->getAttributeValue("h");
				sizeW = xml->getAttributeValue("w");
			}

			if (!strcmp("position", xml->getNodeName()))
			{
				positionX = xml->getAttributeValue("x");
				positionY = xml->getAttributeValue("y");
			}

			break;
		}
	}
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::PANEL_CONTROLS, L"Controls", L"Controls");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_VIDEO_AND_SOUND, L"Video and sound", L"Video and sound");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_STATS, L"Stats", L"Stats");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_BACK, L"Back", L"Go Back");
	printf("%f\n", atof(positionX.c_str()));
	printf("%f\n", atof(positionY.c_str()));
	printf("%f\n", atof(sizeH.c_str()));
	printf("%f\n", atof(sizeW.c_str()));
	while (device->run() && driver)
	{
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, SColor(0, 200, 200, 200));
			env->drawAll();
			driver->endScene();
		}

	}
	device->drop();
	delete xml;
}