#ifndef LOOP_HPP_
# define LOOP_HPP_

#  include <iostream>

# include <string>
# include "IncludeIrrlicht.hpp"
# include "Constants.hpp"

namespace core
{
  class ILoop // loop interface
  {
  public:
    virtual ~ILoop() {}
    virtual bool init(void) = 0;
    virtual int loop(void) = 0;
  };

  template<class T>
  class Loop: public ILoop // generic loop declarations
  {
  protected: // protected attributes
    core::device_t *_device;
    std::wstring const _title;
  protected: // protected constructors and operators
    Loop(core::device_t *device)
      : _device(device), _title(MENU_TITLE)
    {
      device->ptr->setWindowCaption(this->_title.c_str());
      device->guienv->
	addStaticText(MENU_TITLE,
		      icore::rect<irr::s32>(10,10,260,22), true);
    }

  public: // public methods
    bool init(void)
    {
      return (static_cast<T *>(this)->_init());
    }
    int loop(void)
    {
      return (static_cast<T *>(this)->_loop());
    }
  };

  class MenuLoop: public Loop<MenuLoop> // loop derivate for menu
  {
    friend class Loop<MenuLoop>; // Loop class must access private derived methods
  public:
    MenuLoop(core::device_t *device)
      : Loop(device) {}
  private:
    bool _init(void);
    int _loop(void);
  };

  class GameLoop: public Loop<GameLoop> // loop derivate for games
  {
    friend class Loop<GameLoop>;  // Loop class must access private derived methods
  public:
    GameLoop(core::device_t *device)
      : Loop(device) {}
  private:
    bool _init(void);
    int _loop(void);
  };

  // you can stop read from here, this code will not be used
  template <class T>
  class LoopAllocator // vector allocator to stock every Loop derivated class
  {
    class Padding: public ILoop // sizeof(ILoop) is too small so..
    {
      char padding[sizeof(device_t *) +
		   sizeof(std::wstring const)];
    };
    bool round;
  public: // vetor use value type to call the constructors
    typedef Padding value_type;
  public:
    Padding *allocate(std::size_t const) const
    {
      return (reinterpret_cast<Padding *>
	      (::operator new
	       (sizeof(MenuLoop) + sizeof(GameLoop))));
    }

    template <class _Obj, class ..._Args>
    void construct(_Obj * const ptr, _Args &&... args)
    {
      this->round =! this->round;
      if (this->round)
	::new (reinterpret_cast<void *>(ptr))
	    MenuLoop(std::forward<_Args>(args)...);
      else
	::new (reinterpret_cast<void *>(ptr))
	    GameLoop(std::forward<_Args>(args)...);
    }

    template <class _Obj>
    void destroy(_Obj * const ptr) const
    {
      ptr->~_Obj();
    }

    void deallocate(Padding * const ptr, std::size_t) const
    {
      ::operator delete(ptr);
    }

  private:
    constexpr std::size_t max_size(void) const
    {
      return (((std::size_t)(-1)) / sizeof(Padding));
    }
  };
}

#endif /* LOOP_HPP_ */
