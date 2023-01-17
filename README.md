# CHIP-8
### How to Run:
./emulator Scale Delay ROMFileName
- Scale: Is an int that determines the size of the screen. Have a play around with it and see what you like, I generally use 20.
- Delay: Is an int that determines the speed of the game. Again, have a play around with it for each game and see what you prefer, as each game feels nicer at a different speed.
- ROMFileName: Is a string for the name of the file you want to use as a ROM. I will include a folder of all ROMs I have found to be used, so just pick one and use that (ensure the path to it is correct).

### Overview:
Essentially the "hello world" of emulation and a project I did to develop my skills in reverse engineering, low-level programming, optimisation, and working with unfamiliar libraries/technologies. On top of this I could develop my general skills in C++, documentation. Some of the code I used to complete this project is heavily inspired by Austin Morlan's own CHIP-8 emulator (the specifics are outlined at the bottom of this file), so be sure to check it out, as well as his other projects on emulation, if you are interested in this area in general (link below).

https://code.austinmorlan.com/austin/2019-chip8-emulator

Below are the other main references I used to complete the project. I would highly recommend checking these out as well for general learning, as well as completing the instructions, as they helped me out a lot and are in my opinion essential for learning about how each instruction functions in the CHIP-8, which you can then convert into your own code quite easily as the descriptions are highly detailed.

http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

### Requirements:
- I have included the required files of the SDL library into the project to make the process of using the SDL library much easier for users who would like to demonstrate this code for themselves, however you will have to include the "include" folder of the SDL library into your IDE's include path (this will be src/include). Once this is done, the code should run fine as long as all other requirements are met. If not, then you will have to install SDL for yourself.
- Ensure that you are using a compiler that can compile C++ code.
- This project was built with Windows, as such this is the preferred OS, however it should run just fine on Linux (I had issues however this was I believe only due to WSL conflicts with SDL, it should work fine on a proper Linux machine). I am unsure whether or not this will work on Mac.

### Inspired Code:
The process in which keys presses are stored within the SDL sequence was a very intelligent and easy way of recording what keypresses are done by the user playing the ROM, and then translating these to the CHIP-8 keypad. As such I used this same method for myself (named 'Process') within my drawscreen.cpp file without much modification. I also liked making use of the instructor and destructor to initialise and destroy required functions rather than just using seperate methods to do so, and while this is obvious in foresight, I did end up getting this idea from the tutorial code.

On top of this I liked the idea of having parameters to decide the screen scale, as well as the game speed, and also liked how the main loop was setup via a while loop that depends on the result of the aforementioned 'Process' method, as such all the code involving these ideas within my main.cpp file (more or less any piece of code that connected the main loop with my SDL methods) was gained from the tutorial.

Aside from this, all other code was entirely written myself and invoked only my own creativity and understanding, or was written due to information gained from one of the other two links I presented.

The CHIP-8 is quite a static project in which most of its architecture is already predefined such that there is generally only one accepted way of writing most operations and defining variables when it comes to the actual CHIP-8 itself, however I have outlined to the best of my ability the areas within my project that were heavily inspired by MIT licensed code so as to stay consistent with the guidelines of the MIT license (included in the repository).
