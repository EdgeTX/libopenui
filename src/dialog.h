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

#pragma once

#include "modal_window.h"
#include "form.h"

class Dialog;

class DialogWindowContent : public ModalWindowContent
{
  friend class Dialog;

 public:
  DialogWindowContent(Dialog* parent, const rect_t& rect);

  void setTitle(const std::string& text) override;

  void deleteLater(bool detach = true, bool trash = true) override;
  void updateSize() override;

#if defined(DEBUG_WINDOWS)
  std::string getName() const override;
#endif

 public:
  FormGroup form;
};

class Dialog : public ModalWindow
{
 public:
  Dialog(Window* parent, std::string title, const rect_t& rect);

 protected:
  DialogWindowContent* content;

  void onCancel() override;
  void onEvent(event_t event) override;
};
