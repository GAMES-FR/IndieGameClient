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

const std::string tab[6] = { "GAME_TRUCK_LIFE", "GAME_TRUCK_BOOST", "GAME_TRUCK_BONUS", "GAME_PLAYER_LIFE", "GAME_PLAYER_BOOST", "GAME_PLAYER_BONUS" };

enum Button_Type
{
	GAME_TRUCK_LIFE,
	GAME_TRUCK_BOOST,
	GAME_TRUCK_BONUS,
	GAME_PLAYER_LIFE,
	GAME_PLAYER_BOOST,
	GAME_PLAYER_BONUS
};

Button_Type get_Index(std::string id)
{
	int i = 0;

	while (i < 6)
	{
		if (id == tab[6])
			return (Button_Type)i;
		i++;
	}
}

int main()
{
	IrrXMLReader* xml = createIrrXMLReader("../../XML/point xml/gameplay2.xml");

	std::string id;
	std::string type;
	std::string sizeW;
	std::string sizeH;
	std::string positionX;
	std::string positionY;
	std::string data;

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
			data = xml->getNodeData();
			break;
		case EXN_ELEMENT:
			if (!strcmp("data", xml->getNodeName()))
			{
				id = xml->getAttributeValue("id");
				type = xml->getAttributeValue("type");
			}

			if (!strcmp("size", xml->getNodeName()))
			{
				sizeW = xml->getAttributeValue("w");
				sizeH = xml->getAttributeValue("h");
			}

			if (!strcmp("position", xml->getNodeName()))
			{
				positionX = xml->getAttributeValue("x");
				positionY = xml->getAttributeValue("y");
			}

			break;
		}
	}
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_LIFE, L"TruckLife", L"TruckLife");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_BOOST, L"TruckBoost", L"TruckBoost");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_BONUS, L"PlayerBonus", L"PlayerBonus");
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::GAME_PLAYER_LIFE, L"PlayerLife", L"PlayerLife");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER_BOOST, L"PlayerBoost", L"PlayerBoost");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER_BONUS, L"PlayerBonus", L"PlayerBonus");
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