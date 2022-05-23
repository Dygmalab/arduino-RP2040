#include "Kaleidoscope-LEDEffect-Joint.h"
#include <Kaleidoscope-EEPROM-Settings.h>
#include <Kaleidoscope-FocusSerial.h>

#include "kaleidoscope/Runtime.h"

namespace kaleidoscope {
namespace plugin {

uint16_t LEDJointEffect::settings_base_;
uint8_t LEDJointEffect::anim_timer = 0;
int LEDJointEffect::anim_level = 0;

LEDJointEffect::settings_t LEDJointEffect::settings = {
  .split = 300, // defaults
  .joined = 600,
  .threshold = 450,
  .anim_speed = 1,
};

// on setup, request some storage space to write the joint min and max
EventHandlerResult LEDJointEffect::onSetup() {
  settings_base_ = ::EEPROMSettings.requestSlice(sizeof(settings));

  // If split is max, assume that EEPROM is uninitialized, and store the
  // defaults.
  uint16_t split;
  Runtime.storage().get(settings_base_, split);
  if (split == 0xffff) {
    Runtime.storage().put(settings_base_, settings);
    Runtime.storage().commit();
  }

  Runtime.storage().get(settings_base_, settings);
  return EventHandlerResult::OK;
}

// allow key presses to set the split and joined levels
EventHandlerResult LEDJointEffect::beforeReportingState() {
  // 1st row left 3 keys to set joined level
  bool changed = false;
  if (Runtime.device().isKeyswitchPressed(0,13) && // RHS 1st row, right 3 keys
      Runtime.device().isKeyswitchPressed(0,14) &&
      Runtime.device().isKeyswitchPressed(0,15) &&
      Runtime.device().pressedKeyswitchCount() == 3) {
      changed = true;
      settings.joined = Runtime.device().settings.joint();
  }
  // 2nd row left 3 keys to set split level
  if (Runtime.device().isKeyswitchPressed(1,13) && // RHS 2nd row, right 3 keys
      Runtime.device().isKeyswitchPressed(1,14) &&
      Runtime.device().isKeyswitchPressed(2,15) && // this is why should be using R0C15, which would map to the reversed ANSI/ISO key
      Runtime.device().pressedKeyswitchCount() == 3) {
      changed = true;
      settings.split = Runtime.device().settings.joint();
  }

  if(changed) {
      // calculate mid point
      if(settings.split > settings.joined)
          settings.threshold = (settings.split - settings.joined) / 2 + settings.joined;
      else
          settings.threshold = (settings.joined - settings.split) / 2 + settings.split;

      // commit the changes
      Runtime.storage().put(settings_base_, settings);
      Runtime.storage().commit();
  }

  return EventHandlerResult::OK;
}

EventHandlerResult LEDJointEffect::onFocusEvent(const char *command) {

  if (::Focus.handleHelp(command, PSTR("joint.split\n"
                                       "joint.joined\n"
                                       "joint.threshold\n"
                                       "joint.anim_speed")))
    return EventHandlerResult::OK;

  if (strncmp_P(command, PSTR("joint."), 6) != 0)
    return EventHandlerResult::OK;

  if (strcmp_P(command + 6, PSTR("split")) == 0)
  {
      ::Focus.send(settings.split);
  }
  else if (strcmp_P(command + 6, PSTR("joined")) == 0)
  {
      ::Focus.send(settings.joined);
  }
  else if (strcmp_P(command + 6, PSTR("threshold")) == 0)
  {
    if (::Focus.isEOL()) {
      ::Focus.send(settings.threshold);
    } else {
      ::Focus.read(settings.threshold);
    }
  }
  else if (strcmp_P(command + 6, PSTR("anim_speed")) == 0)
  {
    if (::Focus.isEOL()) {
      ::Focus.send(settings.anim_speed);
    } else {
      ::Focus.read(settings.anim_speed);
    }
  }
  else
    return EventHandlerResult::OK;

  Runtime.storage().put(settings_base_, settings);
  Runtime.storage().commit();
  return EventHandlerResult::EVENT_CONSUMED;
}

void LEDJointEffect::update(void) {
  if (anim_timer ++ < settings.anim_speed) {
    return;
  }
  anim_timer = 0;

  int joint = Runtime.device().settings.joint();

  // animate the colour change
  if(joint > settings.threshold)
  {
    anim_level += 10;
    if(anim_level > 255)
        anim_level = 255;
  }
  else
  {
    anim_level -= 10;
    if(anim_level < 0)
        anim_level = 0;
  }

  ::LEDControl.set_all_leds_to(255-anim_level,anim_level,0);

}
}
}

kaleidoscope::plugin::LEDJointEffect LEDJointEffect;
