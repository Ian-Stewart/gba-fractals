# GBA Fractals Demo
A homebrew gameboy game which renders Newton's Fractal, as inspired by [this 3Blue1Brown video](https://www.youtube.com/watch?v=-RdOwhmqP5s). Makefile, big chunks of this readme, and other project infrastrucutre lovingly copied from [Jamie Stewart's VSCode Sample Project](https://github.com/JamieDStewart/GBA_VSCode_Basic), which you should probably at least skim if you're actually going to try to build this locally :)

Also this readme isn't fully updated yet, which you can probably gather from *waves hands* all of this

The neat stuff is in [main.c](https://github.com/Ian-Stewart/fractals/blob/master/source/main.c), [newton.c](https://github.com/Ian-Stewart/fractals/blob/master/source/newton.c), and [fractals.c](https://github.com/Ian-Stewart/fractals/blob/master/source/polynomials.c)

## Dependencies

To get this project to compile there are some dependancies that need to be taken into consideration.
Obviously you will need a GBA emulator set up on your sytem, I tend to flip flop between using NO$GBA or lately mGBA. At the minute I use mGBA as it hooks up nicely with gdb debugging. Which I've configured this VS Code set up to make use of, so get a copy of [mGBA](https://mgba.io/downloads.html) (I'm using Version 0.9.2 - GDB seems to work fine, but if you have issues 0.6.2 was mentioned as working).

### devkitPro

You will need to have devkitPro with devkitARM installed, this can easily be carried out by heading over to the [devkitPro Installer page](https://github.com/devkitPro/installer/releases) and getting the most current version for your development platform.
Try to avoid installing devkitPro to a directory or sub directory with long path names. I installed them to the root of my C drive, because I'm an idiot. 

After installing it, you need to **add "%DEVKITPRO%\tools\bin" to the Path**. The installation seems to no make this and is necessary for the debugger to work correctly.
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
Line 35 may need to change, or you can remove the whole **run** label if you choose to. I sometimes use No$GBA as the source debugger is pretty great.

## Debugging the Game
Once all of the above changes have been squared away you should be able to make this project (ctrl+shift+p -> make debug) then press F5 to begin debugging, if all your paths are set up you should be good to go. There was an issue with *"The specified task cannot be tracked"* but pressing the button for "debug anyway" keeps the process going with no ill effects, this issue I've managedd to work around by having the launch task run as non-background and have set a simple sleep value in the shell command as a way to delay the process enough for mGBA to get up and running before attempting to connect with gdb, these didn't seem to be anyother way to do this as mGBA doesn't provide any hooks to inform when it has successfully started and I couldn't find any in the process history.
You should then be presented with a debug view, where you can navigate through the code line by line and track individual values and memory addresses.

Click on the video to view a youtube video going through this GitHub repo. 

[![alt text](https://github.com/JamieDStewart/GBA_VSCode_Basic/blob/master/images/running.PNG "Proof it works!")](https://youtu.be/Rj0lf46iljc "Video Guide")