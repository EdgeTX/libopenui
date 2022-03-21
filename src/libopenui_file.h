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

#include "libopenui_compat.h" // for strcasecmp / VC++
#include <string>
#include <cstring>
#include <cinttypes>
#include <memory>

constexpr uint8_t LEN_FILE_EXTENSION_MAX = 5;  // longest used, including the dot, excluding null term.

const char * getFileExtension(const char * filename, uint8_t size = 0, uint8_t extMaxLen = 0, uint8_t * fnlen = nullptr, uint8_t * extlen = nullptr);
bool isFileExtensionMatching(const char * extension, const char * pattern, char * match = nullptr);
//
//const char * OUiGetFileExtension(const char * filename, uint8_t size = 0,
//                                        uint8_t extMaxLen = 0, uint8_t * fnlen = nullptr, uint8_t * extlen = nullptr);
//bool OUiGisFileExtensionMatching(const char * extension, const char * pattern, char * match = nullptr);
