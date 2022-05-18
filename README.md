A small program for visualizing a huge ammount of points and separating them based on their location relative to the given planes

1. Build the program using CMake


2. Place your .txt files into inputs folder, one containing points coorditates and one containing coordinates for 3 poins per plane (example files are there by default)
 

3. Run the program (./build/checkPoints) and specify filenames for points and planes


4. When program will complete processing the given points, it will write all the "good" and "wrong" points into the outputs dirrectory. It will also give you an option of running a visualization script. You can run this script yourself by running the python file:
   
   >python 3 pointsVisualizer.py --{output file path for good points} --{output file path for bad points}


Example of program running:

![alt text](https://i.imgur.com/5VUNeCL.png)
