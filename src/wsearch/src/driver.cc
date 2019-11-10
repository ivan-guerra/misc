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
