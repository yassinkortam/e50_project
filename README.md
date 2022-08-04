# E50 Project

## Introduction
The objective of this project is to create a C++ program to approximate the solution to the following initial value problem **using differencing**:

V" + 2V' + 5V = 50, V(0) = V"(0) = 0

In addition to this, the program must conduct a simple error analysis given the exact analytic solution and exports relevant data into csv files for investigation. 

To be extra industriuous, I decided to give this program the ability to solve any linear ODE with a constant forcing function. Although there are probably better ways to do this (e.g. via laplace transforms, etc.) it was an assignment requirement to use differencing. It was also a requirement to use C++ (I would have loved to use python).

This project was completed in ~3 days.


## linode_input.h
Contains methods that abstract user input for analysis.

## linode.h
Contains methods that solve linear ODEs and abstract their attributes.

## project_case.h
Contains methods that satisfy original assignment requirements.

## main.cpp
Driver program. Takes user inputs and executes functions from the above header files.
