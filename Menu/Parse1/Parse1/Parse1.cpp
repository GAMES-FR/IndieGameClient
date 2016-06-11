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

const std::string tab[33] = { "PANEL_BACK", "CONTROL_FORWARD", "CONTROL_LEFT", "PANEL_LOGIN", "PANEL_FIND", "PANEL_ENTER", "PANEL_CONTROLS", "PANEL_VIDEO_AND_SOUND", "PANEL_STATS", "SETTINGS_FULLSCREEN", "SETTING_CURSOR", "STAT_GAMES", "STAT_VICTORIES", "TAB_PLAYER1_PSEUDO", "TAB_PLAYER1_PASTILLE", "TAB_PLAYER1_LIFE", "TAB_PLAYER1_BOOST", "TAB_PLAYER1_BONUS", "TAB_PLAYER1_STATS", "GAME_TRUCK_LIFE", "GAME_TRUCK_BOOST", "GAME_TRUCK_BONUS", "GAME_PLAYER_LIFE", "GAME_PLAYER_BOOST", "GAME_PLAYER_BONUS", "GAME_PLAYER2_PSEUDO", "GAME_PLAYER2_LIFE", "GAME_PLAYER2_BOOST", "GAME_PLAYER2_BONUS", "GAME_PLAYER3_PSEUDO", "GAME_PLAYER3_LIFE", "GAME_PLAYER3_BOOST", "GAME_PLAYER3_BONUS" };

enum Button_Type
{
	PANEL_JOIN,
	PANEL_SETTINGS,
	PANEL_QUIT,
	PANEL_LOGIN,
	PANEL_FIND,
	PANEL_ENTER,
	PANEL_CONTROLS,
	PANEL_VIDEO_AND_SOUND,
	PANEL_STATS,
	SETTINGS_FULLSCREEN,
	SETTING_CURSOR,
	STAT_GAMES,
	STAT_VICTORIES,
	TAB_PLAYER1_PSEUDO,
	TAB_PLAYER1_PASTILLE,
	TAB_PLAYER1_LIFE,
	TAB_PLAYER1_BOOST,
	TAB_PLAYER1_BONUS,
	TAB_PLAYER1_STATS,
	GAME_TRUCK_LIFE,
	GAME_TRUCK_BOOST,
	GAME_TRUCK_BONUS,
	GAME_PLAYER_LIFE,
	GAME_PLAYER_BOOST,
	GAME_PLAYER_BONUS,
	GAME_PLAYER2_PSEUDO,
	GAME_PLAYER2_LIFE,
	GAME_PLAYER2_BOOST,
	GAME_PLAYER2_BONUS,
	GAME_PLAYER3_PSEUDO,
	GAME_PLAYER3_LIFE,
	GAME_PLAYER3_BOOST,
	GAME_PLAYER3_BONUS
};

Button_Type get_Index(std::string id)
{
	int i = 0;

	while (i < 33)
	{
		if (id == tab[33])
			return (Button_Type)i;
		i++;
	}
}

int parser()
{
	IrrXMLReader* xml = createIrrXMLReader("../../XML/point xml/");

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
	std::string data;
	std::string type;
	std::string checked;
	std::string value;

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

			if (!strcmp("data", xml->getNodeName()))
			{
				id = xml->getAttributeValue("id");
				type = xml->getAttributeValue("type");
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

			if (!strcmp("checkbox", xml->getNodeName()))
			{
				id = xml->getAttributeValue("id");
				checked = xml->getAttributeValue("checked");
			}

			if (!strcmp("cursor", xml->getNodeName()))
			{
				id = xml->getAttributeValue("id");
				value = xml->getAttributeValue("value");
			}

			if (!strcmp("input", xml->getNodeName()))
			{
				input = xml->getAttributeValue("id");
				text = xml->getAttributeValue("text");
			}

			break;
		}
	}
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::PANEL_JOIN, L"Join", L"Join Game");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_SETTINGS, L"Settings", L"Edit Settings");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_QUIT, L"Quit", L"Quit");
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::PANEL_LOGIN, L"Login", L"Login");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_FIND, L"Find", L"Find");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_ENTER, L"Enter", L"Enter");
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::PANEL_CONTROLS, L"Control", L"Control");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_VIDEO_AND_SOUND, L"Video and Sound", L"Video and Sound");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::PANEL_STATS, L"Stat", L"Stat");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::SETTINGS_FULLSCREEN, L"Fullscreen", L"Fullscreen");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::SETTING_CURSOR, L"Cursor", L"Cursor");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::STAT_GAMES, L"Stat games", L"Stat games");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::STAT_VICTORIES, L"Stat victories", L"Stat victories");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::TAB_PLAYER1_PSEUDO, L"PseudoP1", L"PseudoP1");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::TAB_PLAYER1_PASTILLE, L"PastilleP1", L"PastilleP1");
	env->addButton(rect<s32>(atof(positionX.c_str()), atof(positionY.c_str()), atof(sizeW.c_str()), atof(sizeH.c_str())), 0, Button_Type::TAB_PLAYER1_LIFE, L"LifeP1", L"LifeP1");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::TAB_PLAYER1_BOOST, L"BoostP1", L"BoostP1");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::TAB_PLAYER1_BONUS, L"BonusP1", L"BonusP1");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::TAB_PLAYER1_STATS, L"StatP1", L"StatP1");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_LIFE, L"LifeTruck", L"LifeTruck");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_BOOST, L"TruckBoost", L"TruckBoost");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_TRUCK_BONUS, L"TruckBonus", L"TruckBonus");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER_LIFE, L"LifeP", L"LifeP");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER_BOOST, L"PlayerBoost", L"PlayerBoost");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER_BONUS, L"PlayerBonus", L"PlayerBonus");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER2_PSEUDO, L"PseudoP2", L"PseudoP2");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER2_LIFE, L"LifeP2", L"LifeP2");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER2_BOOST, L"BoostP2", L"BoostP2");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER2_BONUS, L"BonusP2", L"BonusP2");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER3_PSEUDO, L"PseudoP3", L"PseudoP3");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER3_LIFE, L"LifeP3", L"LifeP3");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 50, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER3_BOOST, L"BoostP3", L"BoostP3");
	env->addButton(rect<s32>(atoi(positionX.c_str()), atoi(positionY.c_str()) + 150, atoi(sizeW.c_str()), atoi(sizeH.c_str())), 0, Button_Type::GAME_PLAYER3_BONUS, L"BonusP3", L"BonusP3");
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

int main()
{
	parser();
}