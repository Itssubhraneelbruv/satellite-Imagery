# satellite-Imagery
A simple program that accesses the NASA's Astronomy Picture of the Day (APOD), Earth and Mars Rover Photos APIs using C and the CURL and cJSON libraries.

# Getting started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

# Prerequisites
A C compiler (such as GCC)
The CURL and cJSON libraries

# Installing
Clone the repository to your local machine:
git clone https://github.com/<username>/nasa-apis.git
  
Install the CURL and cJSON libraries. On Ubuntu, you can do this by running:
sudo apt-get install libcurl4-openssl-dev libcjson-dev
  
Compile the code using a C compiler, such as GCC:
gcc -o nasa-apis main.c -lcurl -lcjson
  
