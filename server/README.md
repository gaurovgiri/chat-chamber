# Running the Server Application

This guide will explain how to run the ./bin/server binary, which is created after running the make command. The application also includes a install.sh script and a Dockerfile for running the application in a container.
## Prerequisites

    - A Unix-based operating system (Windows users can use the Windows Subsystem for Linux (WSL))
    GCC, the GNU Compiler Collection
    - Make
    - Docker (if you want to run the application in a container)

## Running the Application
### Using Make

    Run the install.sh script to install the required libraries and dependencies.

`./install.sh`

    Run the make command to build the binary.

`make`

    Run the binary with the port as command-line argument.

`./bin/server <port>`

### Using Docker

    Build the image using the provided Dockerfile.

`docker build -t myserver .`

    Run the container and pass the port as command-line argument.

`docker run --name myservercontainer -p <port>:<port> myserver <port>`

### Notes

    Make sure that the install.sh script and Dockerfile are in the same directory as the Makefile.
    Make sure that the make command in your makefile is building the server binary and it is located at ./bin/server and the installation script is located at ./install.sh and it is executable.
    Make sure that the port you specify is available on your system.

### Troubleshooting

    If you encounter any issues while building the binary, check that all the dependencies are installed and that the install.sh script is executable.
    If you encounter any issues while running the container, check that the port is correct and available on your system.
    If you encounter any other issues, please check the logs or contact the developer for assistance.

Please note that this is just a basic example and the actual steps may vary depending on the specific requirements of your application. Also, make sure to read and understand the source code and any additional documentation provided with the application before running it.