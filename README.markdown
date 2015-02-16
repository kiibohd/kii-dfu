kii-dfu - Kiibohd dfu-util GUI Frontend
=======================================

Simple GUI frontend to dfu-util

Requires that the dfu-util binary/symlink be in the same directory as `./kii-dfu`

dfu-util can be found here: [dfu-util](http://dfu-util.gnumonks.org/)
Please use 0.8 or higher if possible.


Building
--------

### Linux

Requires: qt5, cmake 2.8.9+

```bash
mkdir build
cd build
make
```


### Mac

Requires: qt5, cmake 2.8.9+
(Works with Macports)

```bash
mkdir build
cd build
make
```


### Windows

Requires: [Qt5](http://qt-project.org/qt5 with mingw32), [cmake 3.0+](http://www.cmake.org/download/)

The easiest way is to use QtCreator.
Open up the CMakeLists.txt file with QtCreator (make sure to select a build directory different from the source directory)
Run build



Installation
------------

Linux/Mac just copy/symlink `dfu-util` to the same directory


### Windows

**Driver Installation, only do once**

Download and run [Zadig](http://zadig.akeo.ie/)
Plug in the controller/keyboard and set into 're-flash mode'.
(Just press the button on the back of keyboard, an led should turn on)

'Kiibohd DFU Bootloader' should show up.
In Driver, press the Up/Down arrows until you find 'libusbK'
Click 'Install Driver'

**Driver installation finished**


Then copy `dfu-util.exe` to the same directory as `kii-dfu.exe`



Usage
-----

Run `./kii-dfu` or `kii-dfu.exe`

Browse to the *.dfu.bin* file to flash.
Click Flash


List Devices can be used to see if dfu-util can see your device.
You may need to run the utility as root.


Linux
-----

For Linux it is also possible to a udev rules file to `/etc/udev/rules.d`
[98-kiibohd.rules](https://github.com/kiibohd/controller/blob/master/98-kiibohd.rules)

Then run:
```bash
udevadm control --reload-rules
```

And reconnect the USB device.
You should no longer require root to flash the keyboard



New Patches/Features/Backends
-----------------------------

Completely welcome :D


Spec Additions/Fixes
--------------------

Contact HaaTa via IRC (#geekhack@irc.freenode.net or #deskthority).
Or by email -> haata@kiibohd.com

