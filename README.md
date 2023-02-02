# CHIP-8
### How to Run:
./emulator Scale Delay DebugOnOff ROMFileName
- Scale: Is an int that determines the size of the screen. Have a play around with it and see what you like, I generally use 20.
- Delay: Is an int that determines the speed of the game. Again, have a play around with it for each game and see what you prefer, as each game feels nicer at a different speed.
- DebugOnOff: Is an int that determines whether debug mode is on or off. Enter 0 for off, enter 1 for on.
- ROMFileName: Is a string for the name of the file you want to use as a ROM. Check this repository to find examples of ROMs you can use (ensure they are .ch8): https://github.com/dmatlack/chip8/tree/master/roms/games

### Overview:
Essentially the "hello world" of emulation and a project I did to develop my skills in reverse engineering, low-level programming, optimisation, and working with unfamiliar libraries/technologies. Some of the code I used to complete this project is heavily inspired by Austin Morlan's own CHIP-8 emulator (the specifics are outlined at the bottom of this file), so be sure to check it out, as well as his other projects on emulation, if you are interested in this area in general (link below).

https://code.austinmorlan.com/austin/2019-chip8-emulator

Below are the other main references I used to complete the project. I would highly recommend checking these out as well for general learning, as well as completing the instructions, as they helped me out a lot and are in my opinion essential for learning about how each instruction functions in the CHIP-8, which you can then convert into your own code quite easily as the descriptions are highly detailed.

http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

I also heavily made use of the file 'test_opcode.ch8' in order to test the functionality of my implemented instructions, hence was a very important file used for testing purposes and the project would have been much more difficult to complete without it (as tests would have had to have been written by hand in .ch8 format). Hence I have included it in this repository and heavily encourage the reader to check out the original author of this test file via his repository below:

https://github.com/corax89/chip8-test-rom

### Requirements:
- I have included the required files of the SDL library into the project to make the process of using the SDL library much easier for users who would like to use this code for themselves, however you will have to include the "include" folder of the SDL library into your IDE's include path (this will be src/include). Once this is done, the code should run fine as long as all other requirements are met. If not, then you will have to install and setup SDL for yourself, I got my version from this link: https://github.com/libsdl-org/SDL/releases/tag/release-2.26.2.
- Ensure that you are using a compiler that can compile C++ code.
- This project was built with Windows, as such this is the preferred OS, however it should run just fine on Linux (I had issues however this was I believe only due to WSL conflicts with SDL due to the nature of how SDL communicates with hardware, it should work fine on a proper Linux machine). I am unsure whether or not this will work on Mac, however I see no reason as to why it wouldn't.

### Inspired Code:
The process in which keys presses are stored within the SDL sequence was a very intelligent and easy way of recording what keypresses are done by the user playing the ROM, and then translating these to the CHIP-8 keypad. As such I used this same method for myself (named 'Process') within my drawscreen.cpp file without much modification. I also liked making use of the constructor and destructor to initialise and destroy required functions rather than just using seperate methods to do so, and while this is obvious in foresight, I did end up getting this idea from the Austin's repository code.

On top of this I liked the idea of having parameters to decide the screen scale, as well as the game speed, and also liked how the main loop was setup via a while loop that depends on the result of the aforementioned 'Process' method, as such all the code involving these ideas within my main.cpp file (more or less any piece of code that connected the main loop with my SDL methods) was gained from the repository.

Aside from this, all other code was entirely written myself and invoked only my own creativity and understanding, or was written due to theoretical information gained from one of the other two links I presented. I have outlined to the best of my ability the areas within my project that were inspired by MIT licensed code so as to stay consistent with the guidelines of the MIT license (license included in the repository, please read the above for specific details on which code the third-party section of the license applies to and which code my part of the license applies to).
