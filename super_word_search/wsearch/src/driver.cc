/*!
 * \file driver.cc
 * \brief Execute the Super Word Search puzzle solver on a user specified puzzle file.
 * \details This driver prompts the user for a word search puzzle data file and then
 *          uses an object of the WordSearchSolver to solve all puzzles contained
 *          within the data file. All output is sent to stdout. Error messages
 *          if any are sent to stderr.
 */

#include <iostream>
#include "word_search_solver.h"

int main(int argc, char** argv)
{
    std::cout << "Please enter the path (abs or rel) to your puzzle file: ";
    std::string puzzle_file;
    std::cin >> puzzle_file;

    supersearch::WordSearchSolver solver(puzzle_file);
    while (solver.load_puzzle()) {
        solver.solve();
        solver.print_results();
    }

    return 0;
}
