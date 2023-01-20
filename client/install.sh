#!/bin/bash

# Update package list
apt-get update

# Install ncurses library
apt-get install libncurses5-dev libncursesw5-dev -y

# Install sqlite3 library
apt-get install sqlite3 libsqlite3-dev -y

# Install openssl library
apt-get install openssl libssl-dev -y

# Install crypto library
apt-get install libcrypto++-dev -y
