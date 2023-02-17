# Explanation of files
* ee+simulation.cpp is the full program with tons of comments explaining everything, all my thoughts and logic throughout the program
* main.cpp is the same program with the comments removed, only a few important comments remain
* analysis.cpp is the program to be passed a data.txt file and interpret the results. Currently unfinished
* program is the compiled main.cpp file, it can be run directly through terminal with ./program

## How to configure collision energy and number of experiments
Default value for collision energy (Ce) is 500 Gev. 
Default value for number of experiments (Nexp) is 10.
The main.cpp file includes two variables configurable through the command line, one for selecting the collision energy and one for number of experiments (thought of as dice rolls, a random number is generated and an outcome is selected based on it). To pick the collision energy use the input -Ce followed by the double (in units of GeV) you want to use.

You can use the already compiled main.cpp file, "program", just run:
`./program` in your command line. Make sure you are in the directory where "program" is stored. 

If you want to use different collision energy and/or number of experiment, lets say Ce = 200 and Nexp = 1000, do this:

`./program -Ce 200 -Nexp 1000`

