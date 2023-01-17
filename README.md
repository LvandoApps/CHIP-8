# CHIP-8
### Overview:
Essentially the "hello world" of emulation and a project I did to learn more about bitwise operations, assembly, as well as hone some general C++ skills. Some of the code I used to complete this project is heavily inspired by Austin Morlan's tutorial on building the CHIP-8 (the specifics are outlined at the bottom of this file), so be sure to check it out, as well as his other projects on emulation, if you are interested in this area in general (link below).

https://austinmorlan.com/posts/chip8_emulator/

Below are the other main references I used to complete the project. I would highly recommend checking these out as well for general learning, as well as completing the instructions, as they helped me out a lot and are in my opinion essential for learning about how each instruction functions in the CHIP-8, which you can then convert into your own code quite easily as the descriptions are highly detailed.

http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

### Inspired Code:
The process in which keys presses are stored within the SDL sequence was a very intelligent and easy way of recording what keypresses are done by the user playing the ROM, and then translating these to the CHIP-8 keypad. As such I used this same method for myself (named 'Process') within my drawscreen.cpp file without much modification. I also liked making use of the instructor and destructor to initialise and destroy required functions rather than just using seperate methods to do so, and while this is obvious in foresight, I did end up getting this idea from the tutorial code.

On top of this I liked the idea of having parameters to decide the screen scale, as well as the game speed, and also liked how the main loop was setup via a while loop that depends on the result of the aforementioned 'Process' method, as such all the code involving these ideas within my main.cpp file was gained from the tutorial.

Aside from this, all other code was written myself and invoked my own creativity, or was written due to information gained from one of the other two links I presented. 

The CHIP-8 is quite a static project such that most of it's architecture is already predefined such that there is generally only one correct way of doing most operations and defining variables, however I have outlined to the best of my ability the areas within my project that were heavily inspired by MIT licensed code so as to stay consistent with the guidelines of MIT license.
