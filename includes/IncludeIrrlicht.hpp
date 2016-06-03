#ifndef INCLUDE_IRRLICHT_HPP_
# define INCLUDE_IRRLICHT_HPP_

# include <irrlicht.h>
# define iscene irr::scene
# define icore irr::core
# define ivideo irr::video
# define igui irr::gui

namespace core
{
  enum input_type
    {
      MOVE_FOWARD = 1,
      MOVE_BACK = 1 << 1,
      MOVE_LEFT = 1 << 2,
      MOVE_RIGHT = 1 << 3,
      MOVE_REVERSE = 1 << 4,
      MOVE_STAP = 1 << 5,
      GUI_MENU = 1 << 6,
      GUI_SCREEN = 1 << 7
    };
  enum { KEYS_COUNT = 8 };

  class InputHandler : public irr::IEventReceiver
  {
  private:
    // Handler des touches actuellement pressées ou non
    bool					_keyIsDown[irr::KEY_KEY_CODES_COUNT];
    irr::f32				_mouseWheel;

  public:
    InputHandler();
    // Override de la méthode OnEvent de Irrlicht
    virtual bool			OnEvent(const irr::SEvent& event);
    virtual bool			isKeyDown(irr::EKEY_CODE keyCode) const;
    virtual void			setMouseWheel(irr::f32 value);
    virtual irr::f32		getMouseWheel() const;
  };

  struct device_t
  {
    InputHandler receiver;
    irr::IrrlichtDevice *ptr;
    ivideo::IVideoDriver *driver;
    iscene::ISceneManager *smgr;
    igui::IGUIEnvironment *guienv;
  };
}

#endif /* INCLUDE_IRRLICHT_HPP_ */
