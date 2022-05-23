# GhostInTheFirmware

Born out of the desire to demo LED effects on the keyboard without having to
touch it by hand (which would obstruct the video), the `GhostInTheFirmware`
plugin allows one to inject events at various delays, by telling it which keys
to press. Unlike macros, these press keys at given positions, as if they were
pressed by someone typing on it - the firmware will not see the difference.

Given a sequence (with press- and delay times), the plugin will walk through it
once activated, and hold the key for the specified amount, release it, and move
on to the next after the delay time.

## Using the plugin

To use the plugin, one needs to include the header, and configure it with a list
of key coordinates, a press time, and a delay time quartett. One also needs a
way to trigger starting the sequence, and a macro is the most convenient way for
that.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-GhostInTheFirmware.h>
#include <Kaleidoscope-Macros.h>

const macro_t *macroAction(uint8_t macro_index, uint8_t key_state) {
  if (macro_index == 0 && keyToggledOn(key_state))
    GhostInTheFirmware.activate();

  return MACRO_NONE;
}

static const kaleidoscope::plugin::GhostInTheFirmware::GhostKey ghost_keys[] PROGMEM = {
  {0, 0, 200, 50},
  {0, 0, 0}
};

KALEIDOSCOPE_INIT_PLUGINS(GhostInTheFirmware,
                          Macros);

void setup() {
  Kaleidoscope.setup ();

  GhostInTheFirmware.ghost_keys = ghost_keys;
}
```

The plugin won't be doing anything until its `activate()` method is called -
hence the macro.

## Plugin methods

The plugin provides the `GhostInTheFirmware` object, which has the following
methods and properties:

### `.activate()`

> Start playing back the sequence. Best called from a macro.

### `.ghost_keys`

> Set this property to the sequence of keys to press, by assigning a sequence to
> this variable. Each element is a quartett of `row`, `column`, a `pressTime`,
> and a `delay`. Each of these will be pressed in different cycles, unlike
> macros which play back within a single cycle.
>
> The key at `row`, `column` will be held for `pressTime` milliseconds, and
> after an additional `delay` milliseconds, the plugin will move on to the next
> entry in the sequence.
>
> The sequence *MUST* reside in `PROGMEM`.

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: /examples/Features/GhostInTheFirmware/GhostInTheFirmware.ino
