#ifndef GUI_HPP_
# define GUI_HPP_

namespace gui
{
  enum button_type
    {
      PANEL_JOIN = 1,
      PANEL_SETTINGS,
      PANEL_FIND,
      PANEL_ENTER,
      PANEL_CONTROLS,
      PANEL_VIDEO_AND_SOUND,
      PANEL_STATS,
      PANEL_BACK,
      PANEL_QUIT
    };
  enum { BUTTONS_COUNT = 9 };
}

#endif /* GUI_HPP_ */
