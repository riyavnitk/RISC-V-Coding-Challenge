#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <duration>"
    exit 1
fi

duration=$1

# Compile C application
gcc -o solution solution.c -pthread

# Start application in background
./solution &

# Capture PID of the application
app_pid=$!

# Sleep for specified duration
sleep $duration

# Send SIGINT signal to the application
kill -SIGINT $app_pid

# Wait for the application to exit
wait $app_pid
