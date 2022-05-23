# SpaceCadet

[Space Cadet][space-cadet] is a way to make it more convenient to input
parens - those `(` and `)` things -, symbols that a lot of programming languages
use frequently. If you are working with Lisp, you are using these all the time.

What it does, is that it turns your left and right `Shift` keys into parens if
you tap and release them, without pressing any other key while holding them.
Therefore, to input, say, `(print foo)`, you don't need to press `Shift`, hold
it, and press `9` to get a `(`, you simply press and release `Shift`, and
continue writing. You use it as if you had a dedicated key for parens!

But if you wish to write capital letters, you hold it, as usual, and you will
not see any parens when you release it. You can also hold it for a longer time,
and it still would act as a `Shift`, without the parens inserted on release:
this is useful when you want to augment some mouse action with `Shift`, to
select text, for example.

After getting used to the Space Cadet style of typing, you may wish to enable
this sort of functionality on other keys, as well.  Fortunately, the Space Cadet
plugin is configurable and extensible to support adding symbols to other keys.
Along with `(` on your left `Shift` key and `)` on your right `Shift` key,
you may wish to add other such programming mainstays as `{` to your left-side `cmd` key,
`}` to your right-side `alt` key,  `[` to your left `Control` key, and `]` to your right
`Control` key.  You can map the keys in whatever way you may wish to do, so feel free to
experiment with different combinations and discover what works best for you!

 [space-cadet]: https://en.wikipedia.org/wiki/Space-cadet_keyboard

## Using the plugin

Using the plugin with its defaults is as simple as including the header, and
enabling the plugin:

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-SpaceCadet.h>

KALEIDOSCOPE_INIT_PLUGINS(SpaceCadet);

void setup() {
  Kaleidoscope.setup();
}
```

This assumes a US QWERTY layout on the host computer, though the plugin sends
the correct keymap code for each symbol.  Because the mapping is entirely
configurable, though, you may switch out keys at your leisure.

If you wish to enable additional modifier keys (or disable the default behavior
for the shift and parentheses combinations), configuration is as simple as
passing a new keymap into the SpaceCadet object, as shown below:


```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-SpaceCadet.h>

KALEIDOSCOPE_INIT_PLUGINS(SpaceCadet);

void setup() {
  Kaleidoscope.setup();

  //Set the keymap with a 250ms timeout per-key
  //Setting is {KeyThatWasPressed, AlternativeKeyToSend, TimeoutInMS}
  //Note: must end with the SPACECADET_MAP_END delimiter
  static kaleidoscope::plugin::SpaceCadet::KeyBinding spacecadetmap[] = {
    {Key_LeftShift, Key_LeftParen, 250}
    , {Key_RightShift, Key_RightParen, 250}
    , {Key_LeftGui, Key_LeftCurlyBracket, 250}
    , {Key_RightAlt, Key_RightCurlyBracket, 250}
    , {Key_LeftAlt, Key_RightCurlyBracket, 250}
    , {Key_LeftControl, Key_LeftBracket, 250}
    , {Key_RightControl, Key_RightBracket, 250}
    , SPACECADET_MAP_END
  };
  //Set the map.
  SpaceCadet.map = spacecadetmap;
}
```

##   Plugin methods

The plugin provides the `SpaceCadet` object, with the following methods and
properties:

### `.map`

> Set the key map. This takes an array of
> `kaleidoscope::plugin::SpaceCadet::KeyBinding` objects with the special
> `SPACECADET_MAP_END` sentinal to mark the end of the map. Each KeyBinding
> object takes, in order, the key that was pressed, the key that should be sent
> instead, and an optional per-key timeout override
>
> If not explicitly set, defaults to mapping left `shift` to `(` and right `shift`
> to `)`.

### `kaleidoscope::plugin::SpaceCadet::KeyBinding`

> An object consisting of the key that is pressed, the key that should be sent
> in its place, and the timeout (in milliseconds) until the key press is
> considered to be a "held" key press.  The third parameter, the timeout, is
> optional and may be set per-key or left out entirely (or set to `0`) to use
> the default timeout value.

### `.time_out`

> Set this property to the number of milliseconds to wait before considering a
> held key in isolation as its secondary role. That is, we'd have to hold a
> `Shift` key this long, by itself, to trigger the `Shift` role in itself. This
> timeout setting can be overridden by an individual key in the keymap, but if
> it is omitted or set to `0` in the key map, the global timeout will be used.
>
> Defaults to 1000.

### `.enable()`

> This method enables the SpaceCadet plugin.  This is useful for interfacing
> with other plugins or macros, especially where SpaceCadet functionality isn't
> always desired.
>
> The default behavior is `enabled`.

### `.disable()`

> This method disables the SpaceCadet behavior. This is useful for interfacing
> with other plugins or macros, especially where SpaceCadet functionality isn't
> always desired.

### `.active()`

> This method returns `true` if SpaceCadet is enabled and `false` if SpaceCadet
> is disabled. This is useful for interfacing with other plugins or macros,
> especially where SpaceCadet functionality isn't always desired.

### `Key_SpaceCadetEnable`

> This provides a key for placing on a keymap for enabling the SpaceCadet
> behavior.  This is only triggered on initial downpress, and does not
> trigger again if held down or when the key is released.

### `Key_SpaceCadetDisable`

> This provides a key for placing on a keymap for disabling the SpaceCadet
> behavior. This is only triggered on initial downpress, and does not
> trigger again if held down or when the key is released.

## Dependencies

* [Kaleidoscope-Ranges](Ranges.md)

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: /examples/Keystrokes/SpaceCadet/SpaceCadet.ino
