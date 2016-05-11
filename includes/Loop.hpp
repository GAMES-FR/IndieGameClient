#ifndef LOOP_HPP_
# define LOOP_HPP_

# include <irrlicht.h>

struct device_t
{
  irr::IrrlichtDevice *ptr;
  irr::video::IVideoDriver* driver;
  irr::scene::ISceneManager* smgr;
  irr::gui::IGUIEnvironment* guienv;
};

class MenuLoop
{
private:
  device_t *_d;
  const wchar_t *_title;
public:
  MenuLoop(device_t *device);
  ~MenuLoop();
public:
  bool init();
  bool loop();
};

#endif /* LOOP_HPP_ */
