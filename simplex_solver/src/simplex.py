#!/usr/bin/env python

"""Provide a GUI application for solving linear programming problems.

This module provides a basic interface by which the user
maximizes or minimizes an objective function subject to
a number of secondary constraints.

For more information, see the README at
https://github.com/ivan-guerra/simplex_solver/
"""

import simplex_solver as ss
import tkinter as tk
from tkinter import ttk

__author__ = 'ieg'
__version__ = '1.0'


class SimplexCalculator(tk.Frame):
    """Display a GUI through which the user spawns an entry form for a particular LPP.

      Public Variables
      ----------
      master : tk.Frame
        Frame object containing all slave widgets.
      num_vars : tk.IntVar
        Number of variables in the objective function.
      num_contraints : tk.IntVar
        Number of secondary constraints placed on the objective.
    """

    def __init__(self, master):
        tk.Frame.__init__(self, master)
        self.master = master
        self.master.title('Simplex Solver')
        self.num_vars = tk.IntVar()
        self.num_contraints = tk.IntVar()
        self._init_widgets()

    def _init_widgets(self):
        """Initialize all slave widgets of the master frame."""
        self.master.rowconfigure(0, pad=15)
        self.master.rowconfigure(1, pad=10)
        self.master.rowconfigure(2, pad=10)

        ttk.Label(self.master, text='Enter the number of variables and A for this optimization problem below then hit the next button.',
                  justify='center').grid(row=0, column=0, padx=5)
        ttk.Label(self.master, text='Number of Variables:', justify='left').grid(
            row=1, column=0, sticky='w', padx=5)
        ttk.Label(self.master, text='Number of Constraints:',
                  justify='left').grid(row=2, column=0, sticky='w', padx=5)

        ttk.Entry(self.master, textvariable=self.num_vars).grid(
            row=1, column=1, sticky='w')
        ttk.Entry(self.master, textvariable=self.num_contraints).grid(
            row=2, column=1, sticky='w')

        ttk.Button(self.master, text='continue', command=self._spawn_tableaux_entry).grid(
            row=3, column=0, pady=2)
        ttk.Button(self.master, text='exit', command=self.master.destroy).grid(
            row=4, column=0, pady=2)

    def _spawn_tableaux_entry(self):
        """Spawn an instance of the TableauxEntry window."""
        self.master.withdraw()
        subframe = TableauxEntry(
            self.master, self.num_vars.get(), self.num_contraints.get())


class TableauxEntry(tk.Toplevel):
    """Display a GUI through which the user supplies the objective function and corresponding constraint values of an LP problem and recieves the solution.

      Public Variables
      ----------
      num_vars : int
        Number of variables in the objective function.
      num_contraints : int
        Number of secondary constraints placed on the objective.
      obj_coeffs : list[tk.IntVar]
        Objects containing the coefficients of the objective function.
      constraint_coeffs : tk.IntVar
        Matrix containing the coefficients of each constraint.
      rhs : list[tk.IntVar]
        The RHS values of each constraint.
      signs : list[tk.Combobox]
        Inequality or equality sign corresponding to each constraint.
    """

    def __init__(self, master, num_vars, num_contraints):
        tk.Toplevel.__init__(self)
        self.title('Simplex Data Entry')

        self.num_vars = num_vars
        self.num_contraints = num_contraints
        self.obj_coeffs = [tk.IntVar() for _ in range(self.num_vars)]
        self.constraint_coeffs = [[tk.IntVar() for _ in range(
            self.num_vars)] for _ in range(self.num_contraints)]
        self.rhs = [tk.IntVar() for _ in range(self.num_contraints)]
        self.signs = []
        self.output_text = tk.Text(self, height=15, width=60, wrap=tk.NONE)
        self.is_max = ttk.Combobox(self, values=(
            'min', 'max'), state='readonly', width=4)

        self._init_widgets()

    def _init_widgets(self):
        """Initialize all slave widgets of this frame."""
        ttk.Label(self, text='Objective Coefficients:',
                  pad=5).grid(row=0, column=0)
        self._init_obj_coeffs()

        ttk.Label(self, text='Constraints:', pad=10).grid(
            row=3, column=0, sticky='w')
        self._init_constraint_coeffs()
        self._init_signs()
        self._init_rhs()

        self._init_bound_label()
        self._init_output_text_area()
        self._init_button_controls()

    def _init_obj_coeffs(self):
        """Draw entry fields and labels for the coefficients of the objective function."""
        for i in range(self.num_vars):
            ttk.Label(self, text='x' + str(i)).grid(row=1,
                                                    column=i + 1, sticky='w', padx=5)

        for i in range(self.num_vars):
            ttk.Entry(self, textvariable=self.obj_coeffs[i], width=3).grid(
                row=2, column=i + 1, padx=5, sticky='w')

        ttk.Label(self, text='max/min').grid(row=1,
                                             column=self.num_vars + 1, padx=5, sticky='w')
        self.is_max.grid(row=2, column=self.num_vars + 1, sticky='w', padx=5)
        self.is_max.current(0)

    def _init_constraint_coeffs(self):
        """Draw entry fields and labels for the coefficients of each secondary constraint."""
        for i in range(self.num_vars):
            ttk.Label(self, text='x' + str(i)).grid(row=4,
                                                    column=i + 1, padx=5, sticky='w')

        for i in range(self.num_contraints):
            ttk.Label(self, text='Constraint ' + str(i + 1) + ':',
                      pad=2).grid(row=5 + i, column=0, padx=5, sticky='e')
            for j in range(self.num_vars):
                ttk.Entry(self, textvariable=self.constraint_coeffs[i][j], width=3).grid(
                    row=5 + i, column=j + 1, padx=5, sticky='w')

    def _init_rhs(self):
        """Draw entry fields and labels for the right hand side of each objective constraint."""
        ttk.Label(self, text='b').grid(
            row=4, column=self.num_vars + 2, padx=5, sticky='w')

        for i in range(self.num_contraints):
            ttk.Entry(self, textvariable=self.rhs[i], width=3).grid(
                row=5 + i, column=self.num_vars + 2, padx=5, sticky='w')

    def _init_bound_label(self):
        """Draw a label indicating all LPP variables are zero or positive."""
        ttk.Label(self, text='x_i >= 0', pad=10).grid(
            row=5 + self.num_contraints + 1, column=self.num_vars + 2, stick='w')

    def _init_output_text_area(self):
        """Draw the text box and scrollbars used to write the LP results."""
        xscroll_bar = tk.Scrollbar(
            self, orient=tk.HORIZONTAL, command=self.output_text.xview)
        yscroll_bar = tk.Scrollbar(self, command=self.output_text.yview)
        xscroll_bar.grid(row=5 + self.num_contraints + 4,
                         column=1, columnspan=10, sticky='ew')
        yscroll_bar.grid(row=5 + self.num_contraints + 3,
                         column=10, columnspan=4, sticky='nes')

        self.output_text.config(
            xscrollcommand=xscroll_bar.set, yscrollcommand=yscroll_bar.set)
        self.output_text.grid(row=5 + self.num_contraints + 3,
                              column=1, columnspan=10, padx=3, pady=10, stick='nsew')

    def _init_signs(self):
        """Draw comboboxes for each constraint providing the user with the option of <=, >=, or =."""
        for i in range(self.num_contraints):
            cb = ttk.Combobox(self, values=('<=', '>=', '='),
                              state='readonly', width=3)
            cb.grid(row=5 + i, column=self.num_vars + 1, padx=5, sticky='w')
            self.signs.append(cb)

    def _init_button_controls(self):
        """Construct and place all interface buttons."""
        ttk.Button(self, text='solve', command=self._solve_action).grid(
            row=5 + self.num_contraints + 2, column=1, columnspan=2, pady=10)
        ttk.Button(self, text='back', command=self._back_action).grid(
            row=5 + self.num_contraints + 2, column=3, columnspan=2, padx=3, pady=10)
        ttk.Button(self, text='quit', command=self._quit_action).grid(
            row=5 + self.num_contraints + 2, column=5, columnspan=2, padx=3, pady=10)

    def _solve_action(self):
        """Construct a SimplexSolver object based on widget field values and update the displayed solution."""
        # Extract variable values from widgets prior to constructing the
        # SimplexSolver object.
        c = [val.get() for val in self.obj_coeffs]
        A = [[val.get() for val in coeffs]
             for coeffs in self.constraint_coeffs]
        b = [val.get() for val in self.rhs]
        signs = [val.get() for val in self.signs]

        if self.is_max.get() == 'max':
            solver = ss.SimplexSolver(c, A, b, signs, is_max=True)
        else:
            solver = ss.SimplexSolver(c, A, b, signs, is_max=False)

        self._update_solution(solver)

    def _update_solution(self, solver):
        """Run the parameter object's simplex method and display the output in self.output_text.

        Parameters
        ----------
        solver : SimplexSolver
          Object used to execute the simplex method and retrieve the corresponding results.
        """
        result = solver.simplex()

        # A status of 0 indicates a successful optimization. Other status values indicate
        # the problem is either infeasible, unbounded, or malformed.
        if 0 == result['status']:
            self.output_text.insert(tk.END, solver.soln_text)
        else:
            self.output_text.insert(tk.END, result['message'])

    def _back_action(self):
        """Destroy the current tableaux entry form and respawn the master window."""
        self.destroy()
        self.master.update()
        self.master.deiconify()

    def _quit_action(self):
        """Destroy all application windows and exit the program."""
        self.destroy()
        self.master.destroy()

if '__main__' == __name__:
    root = tk.Tk()
    app = SimplexCalculator(root)
    root.mainloop()
