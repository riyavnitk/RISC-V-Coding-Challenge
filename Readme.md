# RISC-V Coding Challenge

## Problem Statement
[Problem Description](https://docs.google.com/document/d/11qdeJnV9h3SniG9cui0SUGmK9j5vmd_NoNxHzBUEpQg/edit?usp=sharing)

## Assumptions
- The shared counter is initialized to 0.
- The counter is shared between two threads and is incremented by 1 and decremented by 1.
- The counter is accessed by two threads concurrently.

## Requirements
- The application is developed using C programming language.
- The application is developed and tested on a Linux environment.
- The application uses pthreads for thread management.

## Running the Application
To build the application, run the following command:
```
make run DURATION=<duration>
```
where ```<duration>``` is the time in seconds for which the application should run.

## Clean the Application
To clean the application, run the following command:
```
make clean
```

## Solution
The simple application implements a threaded approach using pthreads to demonstrate concurrent execution of two threads incrementing and decrementing a shared counter. A mutex lock is used to ensure thread-safe access to the shared counter, preventing any possible race conditions. A signal handler is implemented in ```solution.c``` to gracefully exit the program upon receiving a SIGINT signal. 