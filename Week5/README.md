## Instructions for use:

This directory contains code to integrate the function y = x^5 + 8. It has two methods, the default is trapezoidal integration with default 100 intervals and default limits from 0 to 2. 
It also contains a function to do Guassian quadrature integration with default quadrature n = 2.

I will explain how to change parameters by examples: Running the compiled code, ./integration, you can change the type of integrations by passing "-t" followed by 0, for trapezoidal integration or 1 for Gaussian quadrature. If you pick Gaussian the program will then prompt you for an input of what quadrature you would like, enter either 2, 3, or 4 into the terminal and press enter to make your selection.
For changing the limits, doing "-a 4" will change the lower limit to 4 and "-b 10" will change the upper limit to 10. 
For changing the intervals for the trapezoidal, do "-intv 10000" to change the number of intervals to 10,000.

This should be everything, the code will tell you what the result of the numerical integration is followed by the analytic result for comparison.
