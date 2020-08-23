# Fuzzy Boat Control System #
Implementation of a fuzzy control system for a boat simulation.

## Requirements ##
Any C++ compiler which supports the C++17 standard.

## Input ##
The application accepts input from standard input(command line) in the form of five 
space-seperated integers which represent the following in order:
- Distance of the boat from shore to the left of where the boat is facing at a 90 degree angle
- Distance of the boat from shore to the right of where the boat is facing at a 90 degree angle
- Distance of the boat from shore to the left from where the boat is facing at a 45 degree angle
- Distance of the boat from shore to the right from where the boat is facing at a 45 degree angle
- The velocity of the boat
- Is the roughly facing the right way

The inputs are represented in the *[inputs](fuzzy_system/inputs.h)* class.

## Output ##
Analogous to the input, the app outputs to stanard output in the form of space-seperated integers after passing the inputs through the fuzzy control system.

The two space-seperated integer outputs in order are:
- The acceleration of the boat
- The angle K at which to turn the helm at, where **K** is in [-90, 90]. The negative angles denote a steer to the right(clockwise) while positive denote a steer to the left(counter-clockwise).




