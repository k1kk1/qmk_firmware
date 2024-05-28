# key1a

![key1a](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [k1kk1](https://github.com/k1kk1)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make key1a:default

Flashing example for this keyboard:

    make key1a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## install

```shell
git clone git@github.com:qmk/qmk_firmware.git
cd qmk_firmware
make git-submodule # lufa等をinstall
brew install avr-gcc 
# 
brew uninstall --ignore-dependencies avrdude
brew install avrdude
```

以下のエラーが出た時はavrdudeを再インストールした
```shell
avrdude warning: System wide configuration file version ()
        does not match Avrdude build version (7.3)
avrdude error: no programmer has been specified on the command line or in the
        config file(s); specify one using the -c option and try again

```

```
qmk new-keyboard
...
```


https://github.com/qmk/qmk_firmware/blob/master/docs/isp_flashing_guide.md


```
❯ arm-none-eabi-gcc --version

arm-none-eabi-gcc (Homebrew ARM GCC 9.5.0_2) 9.5.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
