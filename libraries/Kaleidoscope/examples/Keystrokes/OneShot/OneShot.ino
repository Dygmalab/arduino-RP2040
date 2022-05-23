/* -*- mode: c++ -*-
 * Kaleidoscope-OneShot -- One-shot modifiers and layers
 * Copyright (C) 2016-2018  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <Kaleidoscope.h>
#include <Kaleidoscope-Macros.h>
#include <Kaleidoscope-OneShot.h>

// Macros
enum {
  OSMALTCTRL,
};

// *INDENT-OFF*
KEYMAPS(
  [0] = KEYMAP_STACKED
  (
    Key_NoKey,    Key_1, Key_2, Key_3, Key_4, Key_5, Key_NoKey,
    Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
    Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
    Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,

    OSM(LeftControl), Key_Backspace, OSM(LeftGui), OSM(LeftShift),
    M(OSMALTCTRL),

    Key_skip,  Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_skip,
    Key_Enter, Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
               Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
    Key_skip,  Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

    OSM(RightShift), OSM(RightAlt), Key_Spacebar, OSM(RightControl),
    OSL(1)),

  [1] = KEYMAP_STACKED
  (
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,

    ___, ___, ___, ___,
    ___,

    ___, ___,         ___,         ___,        ___,                ___, ___,
    ___, ___,         ___,         ___,        ___,                ___, ___,
         Key_UpArrow, Key_DownArrow, Key_LeftArrow, Key_RightArrow,___, ___,
    ___, ___,         ___,         ___,        ___,                ___, ___,

    ___, ___, ___, ___,
    ___),
)
// *INDENT-ON*

void macroOneShotAltControl(uint8_t keyState) {
  OneShot.inject(OSM(LeftAlt), keyState);
  OneShot.inject(OSM(LeftControl), keyState);
}

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  if (macroIndex == OSMALTCTRL) {
    macroOneShotAltControl(keyState);
  }

  return MACRO_NONE;
}

KALEIDOSCOPE_INIT_PLUGINS(OneShot, Macros);

void setup() {
  Kaleidoscope.setup();
}

void loop() {
  Kaleidoscope.loop();
}
