#pragma once

#include "Kaleidoscope-LEDControl.h"

namespace kaleidoscope {
namespace plugin {
class LEDJointEffect : public LEDMode {
 public:
  LEDJointEffect(void) {}
  EventHandlerResult beforeReportingState();
  EventHandlerResult onSetup();
  EventHandlerResult onFocusEvent(const char *command);

  typedef struct settings_t {
    uint16_t split;
    uint16_t joined;
    uint16_t threshold;
    uint16_t anim_speed;
  } settings_t;

  static settings_t settings;

 protected:
  void update(void) final;

 private:
  static uint8_t anim_timer;
  static int anim_level;
  static uint16_t settings_base_;

};
}
}

extern kaleidoscope::plugin::LEDJointEffect LEDJointEffect;
