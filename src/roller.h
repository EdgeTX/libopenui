/*
 * Copyright (C) OpenTX
 *
 * Source:
 *  https://github.com/opentx/libopenui
 *
 * This file is a part of libopenui library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#ifndef _ROLLER_H_
#define _ROLLER_H_

#include <touch.h>
#include <choice.h>
#include <font.h>
#include <static.h>
#include "libopenui_globals.h"
#include "libopenui_config.h"

constexpr WindowFlags ROLLER_SEPARATION_LINES = (FORM_FLAGS_LAST << 1u);

class Roller: public Choice {
  public:
    Roller(FormGroup * parent, const rect_t & rect, const char * label, const char ** values, int16_t vmin, int16_t vmax, std::function<int16_t()> getValue, std::function<void(int16_t)> setValue = nullptr, WindowFlags windowFlags = ROLLER_SEPARATION_LINES):
      Choice(parent, rect, values, vmin, vmax, std::move(getValue), std::move(setValue), windowFlags | NO_SCROLLBAR)
    {
      if (label) {
        // the label is another window, could be changed, but is it needed?
        new StaticText(parent, {rect.x, rect.y - ROLLER_LINE_HEIGHT, rect.w, ROLLER_LINE_HEIGHT}, label, 0, CENTERED);
      }

      setHeight(ROLLER_LINE_HEIGHT * 3 - 1);
      setPageHeight(ROLLER_LINE_HEIGHT);
      setInnerHeight(INFINITE_HEIGHT);
      setScrollPositionY(ROLLER_LINE_HEIGHT * (this->getValue() - vmin - 1));
      lastScrollPositionY = scrollPositionY;
    }

    void paint(BitmapBuffer * dc) override
    {
      int32_t value = getValue();

      int index = (scrollPositionY - ROLLER_LINE_HEIGHT + 1)  / ROLLER_LINE_HEIGHT;
      coord_t y = index * ROLLER_LINE_HEIGHT;
      coord_t yMax = scrollPositionY + 3 * ROLLER_LINE_HEIGHT;

      while (y < yMax) {
        auto displayedValue = vmin + index % (vmax - vmin + 1);
        if (displayedValue < vmin)
          displayedValue += vmax - vmin + 1;

        auto fgColor = DISABLE_COLOR;

        if (value == displayedValue) {
          fgColor = FOCUS_COLOR | FONT(STD);
        }

        if ((unsigned)displayedValue < values.size()) {
          dc->drawText(width() / 2, y, values[displayedValue].c_str(), fgColor | CENTERED);
        }
        else {
          dc->drawNumber(width() / 2, y, displayedValue, fgColor | CENTERED);
        }

        if (windowFlags & ROLLER_SEPARATION_LINES) {
          dc->drawSolidHorizontalLine(0, y - 10, width(), DISABLE_COLOR);
        }

        index += 1;
        y += ROLLER_LINE_HEIGHT;
      }
    }

    void checkEvents() override
    {
      Window::checkEvents();

#if defined(HARDWARE_TOUCH)
      if (touchState.event != TE_SLIDE) {
        if (scrollPositionY != lastScrollPositionY) {
          updateScrollPosition();
        }
      }
#endif
    }


  protected:
    coord_t lastScrollPositionY = 0;

    void updateScrollPosition()
    {
      lastScrollPositionY = scrollPositionY;

      auto newValue = vmin + ((scrollPositionY / ROLLER_LINE_HEIGHT) + 1) % (vmax - vmin + 1);
      if (newValue < vmin)
        newValue += vmax - vmin + 1;

      setValue(newValue);
      invalidate();
    }
};

#endif // _ROLLER_H_