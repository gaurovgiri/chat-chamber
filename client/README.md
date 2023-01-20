#Running the Client Application

This guide will explain how to run the ./bin/client binary, which is created after running the make command. The application also includes a install.sh script and a Dockerfile for running the application in a container.
Prerequisites

    A Unix-based operating system (Windows users can use the Windows Subsystem for Linux (WSL))
    GCC, the GNU Compiler Collection
    Make
    Docker (if you want to run the application in a container)

# Running the Application
## Using Make

    Run the install.sh script to install the required libraries and dependencies.

    ./install.sh

    Run the make command to build the binary.

    `make`

    Run the binary with the server IP and port as command-line arguments.

    `./bin/client <server_ip> <server_port>`

## Using Docker

    Build the image using the provided Dockerfile.

    `docker build -t myclient .`

    Run the container and pass the server IP and port as command-line arguments.

    `docker run --name myclientcontainer myclient <server_ip> <server_port>`

## Without server IP and port

    If you don't have the server IP and port, you can run the binary without arguments, it will prompt you to enter the IP and port.

    `./bin/client`

## Notes

    Make sure that the install.sh script and Dockerfile are in the same directory as the Makefile.
    Make sure that the make command in your makefile is building the client binary and it is located at ./bin/client and the installation script is located at ./install.sh and it is executable.
    Make sure that the server is running before running the client application.

## Troubleshooting

     If you encounter any issues while building the binary, check that all the dependencies are installed and that the install.sh script is executable.
     If you encounter any issues while running the container, check that the server IP and port are correct and that the server is running.
     If you encounter any other issues, please check the logs or contact the developer for assistance.

Please note that this is just a basic example and the actual steps may vary depending on the specific requirements of your application. Also, make sure to read and understand the source code and any additional documentation provided with the application before running it.