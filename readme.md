<h1>Overview</h1>
This C program is a work-in-progress of a translated C code from MATLAB. It contains a header file that provides the functions for matrix calculations. It also contains functions that convert degrees to radians and radians to degrees. The code is able to create a 3-2-1 Euler rotation matrix that can be used to express a position vector expressed in body frame coordinates to the position vector expressed in inertial frame coordinates. The code recreates only some of the outputs from the MATLAB program, as it is unfinished, but is able to read off the same statements using printf(). 

<h1>Libraries/Header File</h1>
The code uses a header file called MatLib. This header file contains several functions in which recreates functions from MATLAB that can do matrix calculations similarly to MATLAB. This header file must be included in the same folder as the project folder. There is no need to add any additional libraries. 

<h1>Softwares</h1>
The MATLAB code that was recreated was using the MATLAB (Ideally R2020b or later) and MATLAB Aerospace Toolbox. The C Program software that was used to recreate the program but in C was Codeblocks. 

<h1>References</h1>
[1] Abolpour, Roozbeh. Matrix Library in C. https://www.codeproject.com/Articles/5283245/Matrix-Library-in-C
[2] Christhuraj, Edwin. CubeSat Detumbling Simulator. https://github.com/echristhuraj/CubeSatDetumblingSimulator
