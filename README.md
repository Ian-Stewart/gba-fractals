# GBA Fractals Demo
A homebrew gameboy game which renders Newton's Fractal, as inspired by [this 3Blue1Brown video](https://www.youtube.com/watch?v=-RdOwhmqP5s). Makefile, big chunks of this readme, and other project infrastrucutre lovingly copied from [Jamie Stewart's VSCode Sample Project](https://github.com/JamieDStewart/GBA_VSCode_Basic), which you should probably at least skim if you're actually going to try to build this locally :)

Also this readme isn't fully updated yet, which you can probably gather from *waves hands* all of this

The neat stuff is in [main.c](https://github.com/Ian-Stewart/fractals/blob/master/source/main.c), [newton.c](https://github.com/Ian-Stewart/fractals/blob/master/source/newton.c), and [fractals.c](https://github.com/Ian-Stewart/fractals/blob/master/source/polynomials.c)

![alt text](https://github.com/Ian-Stewart/fractals/blob/master/images/demo.png "Hey would ya look at that, math")

## Dependencies

To get this project to compile there are some dependancies that need to be taken into consideration.
Obviously you will need a GBA emulator set up on your sytem, mGBA works well and supports gdb debugging, it's configured for this project. Grab it [here](https://mgba.io/downloads.html) (I'm using Version 0.9.2 - GDB seems to work fine, but if you have issues 0.6.2 was mentioned as working).

### devkitPro

You will need to have devkitPro with devkitARM installed, this can easily be carried out by heading over to the [devkitPro Installer page](https://github.com/devkitPro/installer/releases) and getting the most current version for your development platform.
Try to avoid installing devkitPro to a directory or sub directory with long path names. I installed them to the root of my C drive, because I'm lazy.

After installing it, you need to **add "%DEVKITPRO%\tools\bin" to the Path**. The installation seems to not make this and is necessary for the debugger to work correctly.
Once devKitPro has done it's thing you can move on to getting VS Code set up.

### VS Code Extensions

 To make life easier install the following extensions 
  [ARM Extension](https://github.com/dan-c-underwood/vscode-arm)
  [C/C++](https://github.com/Microsoft/vscode-cpptools)
  [C++ Intellisense](https://github.com/austin-----/code-gnu-global)
  
### .vscode file modifications

**c_cpp_properties.json** - line 54 of this file may need to be modified. You can modify this line of code to point to the *arm-none-eabi/include folder* within devkitPro/devkitARM/

**launch.json** - There are a few modifications to be made here, again surrounding where you have installed devkitPro to on your machine. 
  - Line 19 the location that *miDebuggerPath* points to will need to change to reflect your devkitPro installation folder path.
  
**tasks.json** - line 29 will need to change to reflect where you have installed mGBA. Only the first part of this line needs to change up to the call to the exe. The latter half of the line need not change. 
Line 35 may need to change, or you can remove the whole **run** label if you choose to.

## Debugging the Game
IDK man once I installed mGBA and opened the project in VSCode the run and debug stuff just worked. Breakpoints and whatnot work, though if you set it to evaluate an expression on a breakpoint it definitely slows things down. If the debugger fails for whatever reason, make sure your paths are correct in the json files. If that fails, there's a lot more detail in the original repository I cloned this from. 