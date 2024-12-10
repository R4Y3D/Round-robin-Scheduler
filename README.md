 # Final Project: Round-Robin Scheduler Simulation
 **CISC 3595 Operating Systems**\
 by Rayed Jawad and Ulises Jaimez

## Overview
This project simulates a Round-Robin scheduling algorithm. It takes a list of processes, each with a specific arrival time and burst time, and simulates how they would be scheduled using a Round-Robin algorithm with a customizable quantum time. The program also handles context switch times between processes and displays a Gantt chart and process execution results.

## Files Included
- `RR.cpp`: The main C++ source file containing the simulation logic.
- `README.md`: This README file with instructions on how to build and run the project.

**Compiler**: GNU C++ compiler (`g++`)

## Installation Instructions
1. **Clone or Download the Project**:
   Download the ZIP file with the project contents. Extract it into a directory.

2. **Install g++ (if not already installed)**:
   If you do not have `g++` installed, you can install it using the following commands:
   ```bash
   sudo apt update
   sudo apt install g++

3. **Navigate to the project directory**:		 
   Use the cd command in the terminal to navigate to the directory where the project files are located.

## Building the Project
**Compile the source code**:
To compile the C++ file into an executable, use the following command:\

    g++ -o round_robin_scheduler RR.cpp
    
This will create an executable named `round_robin_scheduler.`

## Running the Program:
Once the program has been compiled successfully, you can run it using the following command
    
    ./round_robin_scheduler

## Using the Program
**Expected User Input**: Enter a positive numerical value for each input.

1. <u>Number of Processes</u>: The number of processes in the simulation.
2. <u>Quantum Time</u>: The quantum time for the Round-Robin scheduling.
3. <u>Context Switch Duration</u>: The duration of the context switch between processes.
4. <u>Process Detail</u>s: For each process, the arrival time and burst time must be entered.