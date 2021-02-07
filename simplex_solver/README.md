# Simplex Solver

## By: Ivan Guerra

### Overview
Simplex Solver is an application for solving linear programming problems: 
```
Max or Min z = cx
subject to
Ax <= b
```
Simplex solver can handle nonstandard LP problems (i.e., those with negative elements in **b** and mixed inequality and equality signs in the constraints). Additonally, the application can detect when an LPP is infeasible or unbounded.

Simplex Solver outputs the following information for each iteration of the algorithm:
* Intermediate Tableauxs
* Basis Variables
* Current Solution
* Current Objective Value

### Requirements
This application requires [SciPy](https://www.scipy.org), an open source Python library used for scientific computing and technical computing, as a dependency. See [here](https://www.scipy.org/install.html) for help with installing the package.

### Usage
After ensuring you have SciPy installed, you can run this script directly via the interpreter:
```
[user@host ~]$ python simplex.py
```

### License
This software is licensed under the MIT Open Source license (see LICENSE file).