# R-TYPE

R-TYPE is a 3rd year project at Epitech.

## Installation

### Requirements

* You must have **conan** and **cmake** installed.
* You must have a compiler installed (windows: **Visual Studio 15 2017**, unix: **g++**)

Of course you should have git and have cloned this repository.

### Windows

First add the conan remote that have all the dependencies required:

    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
    conan remote add epitech https://api.bintray.com/conan/epitech/public-conan
    
Then make build folder and go into it:
    
    mkdir build
    cd build
    
Run conan to install all dependencies to your computer:

    conan install .. --build=missing
    
Run CMake for 64bit processor:

    cmake .. -G "Visual Studio 15 2017 Win64"
    
for 32bit processor:
    
    cmake .. -G "Visual Studio 15 2017 Win32"
    
At this point the .sln will be generated and you can freely change the code by opening it.

Finally if nothing went wrong you just need to build the exe file:

    cmake --build . --config Release
    
If you want to change the config to debug simply use Debug instead of Release.

### Unix Systems (Linux, MacOS)

Add the conan remote that have all the dependencies required:

    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
    conan remote add epitech https://api.bintray.com/conan/epitech/public-conan
    
then create your build folder:
    
    mkdir build/
    cd build/
    
install the dependencies of the project:

    conan install .. --build=missing
    
compile the project:
    
    make
    
then execute the server or the client

    cd bin/
    ./r-type-server
    ./r-type-client    


## Documentation

To see the documentation, please execute this commands at the root of the project:

    doxygen Doxyfile


## Important information

The server uses the _6969_ port to receive information. And use by default the port _8080_ to send information to the client.
You can change this port inside the Network System.

Don't forget to open your ports

On Linux:

    sudo systemctl disable firewalld

On Mac OSX:
    
    Disable your firewall
    
On Windows:

    Go in your firewall settings

## How to play

You can move your spaceship by using the arrows of your keyboard, and shoot with the space bar.

## Author

Jules **BULTEAU**

Charlie **JEANNEAU**

Antoine **CARLIER**

Romain **FOUYER**