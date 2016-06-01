#ifndef INCLUDE_IRRLICHT_HPP_
# define INCLUDE_IRRLICHT_HPP_

# include <irrlicht.h>
# define iscene irr::scene
# define icore irr::core
# define ivideo irr::video
# define igui irr::gui

namespace core
{
  struct device_t
  {
    irr::IrrlichtDevice *ptr;

    ivideo::IVideoDriver* driver;
    iscene::ISceneManager* smgr;
    igui::IGUIEnvironment* guienv;
  };

  enum input_type
    {
      MOVE_FOWARD = 1,
      MOVE_BACK = 1 << 1,
      MOVE_LEFT = 1 << 2,
      MOVE_RIGHT = 1 << 3,
      GUI_MENU = 1 << 4,
      GUI_SCREEN = 1 << 5
    };
  enum { KEYS_COUNT = 6 };

  class Receiver: public irr::IEventReceiver
  {
  private: // private attributes
    irr::EKEY_CODE _irr_keys[KEYS_COUNT];
    input_type const _core_keys[KEYS_COUNT];
    input_type match_irr_keys[irr::KEY_KEY_CODES_COUNT];
  public: // public attributes
    static int inputs;
    static int buttons;
  public: // constructors and operators
    Receiver(void);
  private: // private methods
    bool match_input(irr::EKEY_CODE const code) const;
  public: // public methods
    bool OnEvent(irr::SEvent const &event);
  };
}

// class MyEventReceiver : public IEventReceiver
// {
// public:
//   static int movements;

// public:
//   virtual bool OnEvent(const SEvent& event)
//   {
//     // Remember whether each key is down or up
//     if (event.EventType == irr::EET_KEY_INPUT_EVENT)
//       KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
//     return (OK_CODE);
//   }

//   // This is used to check whether a key is being held down
//   virtual bool IsKeyDown(EKEY_CODE keyCode) const
//   {
//     return KeyIsDown[keyCode];
//   }

//   MyEventReceiver()
//   {
//     for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
//       KeyIsDown[i] = false;
//   }

// private:
//   // We use this array to store the current state of each key
//   bool KeyIsDown[KEY_KEY_CODES_COUNT];
// };

// MyEventReceiver::movements = 0;

#endif /* INCLUDE_IRRLICHT_HPP_ */
