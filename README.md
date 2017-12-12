# FAT EFI
### FAT EFI loader plugin for Hopper Disassembler

This project is a **FAT EFI** loader plugin for [Hopper Disassembler](http://www.hopperapp.com/)

Apple uses an extension to the standard PE format for EFI binaries to allow FAT EFI binaries that contain both 32 and 64 bits executables. It is very similar to the FAT format, except for a different magic number and for little endianness.

This plugin allows to read these FAT EFI binaries with Hopper Disassembler.

Clone or download the sources, then open the XCode project and build the plugin. Once built, the plugin must be moved to the `~/Library/Application Support/Hopper/PlugIns/v4/Loaders` folder (that must be created, if it doesn't yet exist).

This plugin was developed on OS X, it has not been tested on Linux. I don’t even know if plugins are supported on the Linux version of Hopper. If you manage to use it on Linux, please let me know.

This plugin is based on information found [here](http://refit.sourceforge.net/info/fat_binary.html).

Pascal Werz (a.k.a. xvi);

**PS**: A few days after developing this plugin, I discovered one was already available [here](https://github.com/0xc010d/EFIFatBinary.hopperLoader). I prefer mine because it does not use C++ ;-)