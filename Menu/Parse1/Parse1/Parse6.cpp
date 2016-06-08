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

const std::string tab[3] = { "PANEL_BACK", "STAT_GAMES", "STAT_VICTORIES" };

enum Button_Type
{
	PANEL_BACK,
	STAT_GAMES,
	STATE_VICTORIES
};

Button_Type get_Index(std::string id)
{
	int i = 0;

	while (i < 3)
	{
		if (id == tab[3])
			return (Button_Type)i;
		i++;
	}
}

int main()
{
	IrrXMLReader* xml = createIrrXMLReader("../../XML/point xml/panel6.xml");

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
	std::string value;
	std::string cursor;
	std::string checked;

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

			if (!strcmp("scroll", xml->getNodeName()))
			{
				scrollW = xml->getAttributeValue("w");
				scrollH = xml->getAttributeValue("h");
				scrollX = xml->getAttributeValue("x");
				scrollY = xml->getAttributeValue("y");
			}

			if (!strcmp("label", xml->getNodeName()))
			{
				label = xml->getAttributeValue("text");
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

			if (!strcmp("data", xml->getNodeName()))
			{
				id = xml->getAttributeValue("id");
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

			if (!strcmp("label", xml->getNodeName()))
			{
				label = xml->getAttributeValue("text");
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

			if (!strcmp("data", xml->getNodeName()))
			{
				id = xml->getAttributeValue("id");
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

			if (!strcmp("data", xml->getNodeName()))
			{
				id = xml->getAttributeValue("id");
				value = xml->getAttributeValue("value");
			}

			if (!strcmp("position", xml->getNodeName()))
			{
				positionX = xml->getAttributeValue("x");
				positionY = xml->getAttributeValue("y");
			}

			if (!strcmp("size", xml->getNodeName()))
			{
				sizeH = xml->getAttributeValue("h");
				sizeW = xml->getAttributeValue("w");
			}

			break;
		}
	}
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::PANEL_BACK, L"Back", L"Go Back");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::STAT_GAMES, L"Stat games", L"Stat Games");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::STATE_VICTORIES, L"Stat Victories", L"Stat Victories");
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