#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

struct SAppContext
{
	IrrlichtDevice *device;
	s32 counter;
	IGUIListBox* listbox;
};

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR
};

void setSkinTransparency(s32 alpha, irr::gui::IGUISkin *skin)
{
	for (s32 i = 0; i < irr::gui::EGDC_COUNT; ++i)
	{
		video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(alpha);
		skin->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
}

class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver(SAppContext & context) : Context(context) {}

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch (event.GUIEvent.EventType)
			{
			case EGET_SCROLL_BAR_CHANGED:
				if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					setSkinTransparency(pos, env->getSkin());
				}
				break;
			case EGET_BUTTON_CLICKED:
				switch (id)
				{
				case GUI_ID_QUIT_BUTTON:
					Context.device->closeDevice();
					return true;

				case GUI_ID_NEW_WINDOW_BUTTON:
				{
					Context.listbox->addItem(L"Window created");
					Context.counter += 30;
					if (Context.counter > 200)
						Context.counter = 0;

					IGUIWindow* window = env->addWindow(
						rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter), false, L"Test window");

					env->addStaticText(L"Welcome in this new window", rect<s32>(35, 35, 140, 50), true, false, window);
				}
				return true;

				default:
					return false;
				}
				break;

			case EGET_FILE_SELECTED:
			{
				IGUIFileOpenDialog* dialog = (IGUIFileOpenDialog*)event.GUIEvent.Caller;
				Context.listbox->addItem(dialog->getFileName());
			}
			break;

			default:
				break;
			}
		}
		return false;
	}
private:
	SAppContext & Context;
};

int main()
{
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	IrrlichtDevice * device = createDevice(driverType, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1;

	device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
	device->setResizable(true);

	video::IVideoDriver* driver = device->getVideoDriver();
	IGUIEnvironment* env = device->getGUIEnvironment();

	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("../..*/media/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

	env->addButton(rect<s32>(10, 240, 110, 240 + 32), 0, GUI_ID_QUIT_BUTTON, L"Quit", L"Exits Program");
	env->addButton(rect<s32>(10, 280, 110, 280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON, L"New Window", L"Launches a new Window");
	env->addButton(rect<s32>(10, 320, 110, 320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON, L"File Open", L"Opens a file");

	env->addStaticText(L"Transparent Control:", rect<s32>(150, 20, 350, 40), true);
	IGUIScrollBar* scrollbar = env->addScrollBar(true, rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
	scrollbar->setMax(255);
	scrollbar->setPos(255);
	setSkinTransparency(scrollbar->getPos(), env->getSkin());

	scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

	env->addStaticText(L"Logging ListBox:", rect<s32>(50, 110, 250, 130), true);
	IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
	env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

	SAppContext context;
	context.device = device;
	context.counter = 0;
	context.listbox = listbox;

	MyEventReceiver receiver(context);

	device->setEventReceiver(&receiver);

	env->addImage(driver->getTexture("../../media/irrlichtlogo2.png"), position2d<int>(10, 10));

	while (device->run() && driver)
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, SColor(0, 200, 200, 200));
			env->drawAll();
			driver->endScene();
		}
	device->drop();
	return 0;
}