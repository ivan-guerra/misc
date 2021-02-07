"""Solve linear programming problems using the Simplex Method."""

import sys
import numpy as np
from io import TextIOWrapper, BytesIO
from scipy.optimize import linprog

__author__ = 'ieg'


class SimplexSolver():
    """Linear function optimization using the Simplex Method.

    Public Variables
    ----------
    c : list[int]
      Coefficients of the objective function.
    A_ub : list[list[int]]
      Secondary constraint coeffecients for constraints of the form A_kx <= b_k
      or A_kx >= b_k.
    A_eq : list[list[int]]
      Secondary constraint coeffecients for constraints of the form A_kx == b_k.
    b_ub : list[int]
      RHS of secondary constraints of the form A_kx <= b_k.
    b_eq : list[int]
      RHS of secondary constraints of the form A_kx = b_k.
    signs : list[str]
      Inequality or equality symbols corresponding to the LP secondary constraints.
    is_max : bool
      Flag indicating to maximize the objective rather than minimize.
    verbose : bool
      Flag toggling verbose output (i.e., print intermediate tableauxs to sys.stdout).
    """

    def __init__(self, obj_coeffs, constraint_coeffs, rhs, signs, is_max=False, verbose=False):
        self.c = [val for val in obj_coeffs]
        self.A_ub = [[val for val in c]
                     for i, c in enumerate(constraint_coeffs) if signs[i] != '=']
        self.A_eq = [[val for val in c]
                     for i, c in enumerate(constraint_coeffs) if signs[i] == '=']
        self.b_ub = [b for i, b in enumerate(rhs) if signs[i] != '=']
        self.b_eq = [b for i, b in enumerate(rhs) if signs[i] == '=']
        self.signs = signs
        self.is_max = is_max
        self.verbose = verbose
        self.soln_text = ''

    def simplex(self):
        """Solve the LP using the Simplex Method.

        Returns
        ----------
        A scipy.optimize.OptimizeResult consisting of the following fields::
        x : ndarray
            The independent variable vector which optimizes the linear
            programming problem.
        fun : float
            Value of the objective function.
        slack : ndarray
            The values of the slack variables.  Each slack variable corresponds
            to an inequality constraint.  If the slack is zero, then the
            corresponding constraint is active.
        success : bool
            Returns True if the algorithm succeeded in finding an optimal
            solution.
        status : int
            An integer representing the exit status of the optimization::
             0 : Optimization terminated successfully
             1 : Iteration limit reached
             2 : Problem appears to be infeasible
             3 : Problem appears to be unbounded
        nit : int
            The number of iterations performed.
        message : str
            A string descriptor of the exit status of the optimization.
        """
        self._standard_form()

        if self.A_eq:
            if self.A_ub:
                result = self._linprog_wrapper(
                    self.c, self.A_ub, self.b_ub, self.A_eq, self.b_eq)
            else:
                result = self._linprog_wrapper(self.c, self.A_eq, self.b_eq)
        else:
            result = self._linprog_wrapper(self.c, self.A_ub, self.b_ub)

        if self.is_max:
            result['fun'] *= -1

        return result

    def verbose_mode(self, toggle=False):
        """Toggle verbose mode to print intermediate tableauxs to sys.stdout."""
        self.verbose = toggle

    def _standard_form(self):
        """Transform the given LP to standard form."""
        if self.is_max:
            self.c = [-c for c in self.c]

        for i, s in enumerate(self.signs):
            if s == '>=':
                self.A_ub[i] = [-a for a in A_ub[i]]
                self.b_ub[i] *= -1

    def _setup_output_stream(self, stream):
        """Redirect sys.stdout to stream.

        Parameters
        ----------
        stream : streamObj
          The stream to be assigned to sys.stdout.

        Returns
        ----------
        old_stream : streamObj
          The old sys.stdout.
        """
        old_stream = sys.stdout
        sys.stdout = stream
        return old_stream

    def _redirect_output_stream(self, stream):
        """Redirect sys.stdout to the parameter 'stream'."""
        sys.stdout.close()
        sys.stdout = stream

    def _linprog_wrapper(self, c, A_u=None, b_u=None, A_e=None, b_e=None):
        """Apply the verbose flag to the scipy.optimize.linprog call.

        Returns
        ----------
        A scipy.optimize.OptimizeResult consisting of the following fields::
        x : ndarray
            The independent variable vector which optimizes the linear
            programming problem.
        fun : float
            Value of the objective function.
        slack : ndarray
            The values of the slack variables.  Each slack variable corresponds
            to an inequality constraint.  If the slack is zero, then the
            corresponding constraint is active.
        success : bool
            Returns True if the algorithm succeeded in finding an optimal
            solution.
        status : int
            An integer representing the exit status of the optimization::
             0 : Optimization terminated successfully
             1 : Iteration limit reached
             2 : Problem appears to be infeasible
             3 : Problem appears to be unbounded
        nit : int
            The number of iterations performed.
        message : str
            A string descriptor of the exit status of the optimization.
        """
        if self.verbose:
            result = linprog(c, A_ub=A_u, b_ub=b_u, A_eq=A_e,
                             b_eq=b_e, callback=self._linprog_verbose_callback)
        else:
            old_stream = self._setup_output_stream(
                TextIOWrapper(BytesIO(), sys.stdout.encoding))

            result = linprog(c, A_ub=A_u, b_ub=b_u, A_eq=A_e,
                             b_eq=b_e, callback=self._linprog_verbose_callback)
            sys.stdout.seek(0)
            self.soln_text = sys.stdout.read()

            self._redirect_output_stream(old_stream)
        return result

    def _linprog_verbose_callback(self, xk, **kwargs):
        """
        A sample callback function demonstrating the linprog callback interface.
        This callback produces detailed output to sys.stdout before each iteration
        and after the final iteration of the simplex algorithm.
        Parameters
        ----------
        xk : array_like
        The current solution vector.
        **kwargs : dict
        A dictionary containing the following parameters:
        tableau : array_like
            The current tableau of the simplex algorithm.
            Its structure is defined in _solve_simplex.
        phase : int
            The current Phase of the simplex algorithm (1 or 2)
        nit : int
            The current iteration number.
        pivot : tuple(int, int)
            The index of the tableau selected as the next pivot,
            or nan if no pivot exists
        basis : array(int)
            A list of the current basic variables.
            Each element contains the name of a basic variable and its value.
        complete : bool
            True if the simplex algorithm has completed
            (and this is the final call to callback), otherwise False.
        """
        tableau = kwargs["tableau"]
        nit = kwargs["nit"]
        pivrow, pivcol = kwargs["pivot"]
        phase = kwargs["phase"]
        basis = kwargs["basis"]
        complete = kwargs["complete"]

        saved_printoptions = np.get_printoptions()
        np.set_printoptions(linewidth=500,
                            formatter={'float': lambda x: "{0: 12.4f}".format(x)})
        if complete:
            print(
                "--------- Iteration Complete - Phase {0:d} -------\n".format(phase))
            print("Tableau:")
        elif nit == 0:
            print(
                "--------- Initial Tableau - Phase {0:d} ----------\n".format(phase))

        else:
            print(
                "--------- Iteration {0:d}  - Phase {1:d} --------\n".format(nit, phase))
            print("Tableau:")

        if nit >= 0:
            print("" + str(tableau) + "\n")
            if not complete:
                print("Pivot Element: T[{0:.0f}, {1:.0f}]\n".format(
                    pivrow, pivcol))
            print("Basic Variables:", basis)
            print()
            print("Current Solution:")
            print("x = ", xk)
            print()
            print("Current Objective Value:")
            if self.is_max:
                print("f = ", tableau[-1, -1])
            else:
                print("f = ", -tableau[-1, -1])
            print()
        np.set_printoptions(**saved_printoptions)
