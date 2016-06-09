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

const std::string tab[15] = { "GAME_PLAYER1_PSEUDO", "GAME_PLAYER1_LIFE", "GAME_PLAYER1_BOOST", "GAME_PLAYER1_BONUS", "GAME_PLAYER2_PSEUDO", "GAME_PLAYER2_LIFE", "GAME_PLAYER2_BOOST", "GAME_PLAYER2_BONUS", "GAME_PLAYER3_PSEUDO", "GAME_PLAYER3_LIFE", "GAME_PLAYER3_BOOST", "GAME_PLAYER3_BONUS", "GAME_TRUCK_LIFE", "GAME_TRUCK_BOOST", "GAME_TRUCK_BONUS" };

enum Button_Type
{
	GAME_PLAYER1_PSEUDO,
	GAME_PLAYER1_LIFE,
	GAME_PLAYER1_BOOST,
	GAME_PLAYER1_BONUS,
	GAME_PLAYER2_PSEUDO,
	GAME_PLAYER2_LIFE,
	GAME_PLAYER2_BOOST,
	GAME_PLAYER2_BONUS,
	GAME_PLAYER3_PSEUDO,
	GAME_PLAYER3_LIFE,
	GAME_PLAYER3_BOOST,
	GAME_PLAYER3_BONUS,
	GAME_TRUCK_LIFE,
	GAME_TRUCK_BOOST,
	GAME_TRUCK_BONUS
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
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::GAME_PLAYER1_PSEUDO, L"PseudoP1", L"PseudoP1");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER1_LIFE, L"LifeP1", L"LifeP1");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER1_BOOST, L"BoostP1", L"BoostP1");
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::GAME_PLAYER1_BONUS, L"BonusP1", L"BonusP1");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER2_PSEUDO, L"PseudoP2", L"PseudoP2");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER2_LIFE, L"LifeP2", L"LifeP2");
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::GAME_PLAYER2_BOOST, L"BoostP2", L"BoostP2");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER2_BONUS, L"BonusP2", L"BonusP2");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER3_PSEUDO, L"PseudoP3", L"PseudoP3");
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::GAME_PLAYER3_LIFE, L"LifeP3", L"lifeP3");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER3_BOOST, L"BoostP3", L"BoostP3");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER3_BONUS, L"BonusP3", L"BonusP3");
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_LIFE, L"LifeTruck", L"LifeTruck");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_BOOST, L"TruckBoost", L"TruckBoost");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_BONUS, L"TruckBonus", L"TruckBonus");
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