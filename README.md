# satellite-Imagery
A simple program that accesses the NASA's Astronomy Picture of the Day (APOD), Earth and Mars Rover Photos APIs using C and the CURL and cJSON libraries.

# Getting started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

# Prerequisites
A C compiler (such as GCC)
The CURL and cJSON libraries

# Installing
Clone the repository to your local machine:
git clone https://github.com/Itssubhraneelbruv/satellite-Imagery.git
  
Install the CURL and cJSON libraries(only on MacOS):
brew install curl
brew install cjson

  
Compile the code using a C compiler, such as GCC(only on MacOS):
gcc -o satellite-Imagery satellite-Imagery.c -I/path/to/libcurl/ -L/path/to/libcjson/ -lcjson -lcurl -lm -std=c99 -include stdlib.h -include string.h
  
# Usage
run this on your terminal:
./satellite-Imagery
