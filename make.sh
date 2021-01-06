#!/bin/sh

c++ -std=c++17 -I./libraries/ -I./include/ src/Parser.cpp src/FPage.cpp -o fpage

# Create directory
sudo mkdir /usr/local/fpages/

# Copy all pages to /usr/local/pages/
sudo rsync -a fpages/. /usr/local/fpages/
