#include <tuple>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include "word_search_solver.h"

namespace supersearch
{

const std::string WordSearchSolver::WRAP_MODE("WRAP");
const std::string WordSearchSolver::DEFAULT_PUZZLE_FILE("sample_input.txt");

WordSearchSolver::WordSearchSolver(const std::string& puzzle_file) :
    has_load_(false), wrap_enabled_(false), puzzle_file_handle_(puzzle_file)
{

}

bool WordSearchSolver::load_puzzle()
{
    if (has_load_)
        clear_puzzle();

    if (!puzzle_file_handle_.is_open()) {
        std::cerr << "Unable to open puzzle file. Verify you provided a valid path." << std::endl;
        return false;
    }

    if (!get_grid()) {
        if (!puzzle_file_handle_.eof())
            std::cerr << "Unable to load grid. Verify you provided valid row/col numbers and data." << std::endl;
        return false;
    }

    if (!get_mode()) {
        std::cerr << "Unable to parse solver mode. Verify you provided 'WRAP' or 'NO WRAP' in the input."
            << std::endl;
        return false;
    }

    if (!get_search_words()) {
        std::cerr << "Unable to retrieve search terms. Verify you provided a valid term count and "
            << "list of terms" << std::endl;
        return false;
    }

    has_load_ = true;

    return true;
}

bool WordSearchSolver::solve()
{
    if (!has_load_)
        return false;

    for (const auto& word : search_words_) {
        for (std::size_t i = 0; i < word_grid_.size(); ++i) {
            for (std::size_t j = 0; j < word_grid_[i].size(); ++j) {
                directional_search(i, j, word);
            }
        }
    }
    return true;
}

void WordSearchSolver::print_results() const
{
    if (!has_load_)
        return;

    std::cout << "--------------------------------" << std::endl;
    for (const auto& v : search_results_) {
        if (v.empty()) {
            std::cout << "NOT FOUND" << std::endl;
        } else {
            std::cout << "(" << std::get<0>(v[0]) << "," << std::get<1>(v[0]) << ") ";
            std::cout << "(" << std::get<0>(v[1]) << "," << std::get<1>(v[1]) << ")" << std::endl;
        }
    }
    std::cout << "--------------------------------" << std::endl;
}

bool WordSearchSolver::get_grid()
{
    int rowlen = 0;
    int collen = 0;
    puzzle_file_handle_ >> rowlen >> collen;
    if (rowlen <= 0 || collen <= 0)
        return false;

    std::string curr_row;
    for (int i = 0; i < rowlen; ++i) {
        puzzle_file_handle_ >> curr_row;
        std::istringstream is(curr_row);
        word_grid_.push_back({std::istream_iterator<char>(is), std::istream_iterator<char>()});
    }

    return true;
}

bool WordSearchSolver::get_mode()
{
    std::string mode;
    puzzle_file_handle_ >> mode;
    if (mode == WRAP_MODE) {
        wrap_enabled_ = true;
    } else {
        puzzle_file_handle_ >> mode; // Make sure we extract the 'WRAP' in 'NO WRAP'
        wrap_enabled_ = false;
    }

    return true;
}

bool WordSearchSolver::get_search_words()
{
    std::size_t nwords = 0;
    puzzle_file_handle_ >> nwords;
    if (nwords <= 0)
        return false;

    std::string curr_word;
    for (std::size_t i = 0; i < nwords; ++i) {
        puzzle_file_handle_ >> curr_word;
        search_words_.emplace_back(curr_word);
    }

    if (search_words_.size() != nwords)
        return false;

    return true;
}

void WordSearchSolver::clear_puzzle()
{
    has_load_ = false;
    wrap_enabled_ = false;
    search_words_.clear();
    word_grid_.clear();
    search_results_.clear();
}

int WordSearchSolver::wrap_move(int limit, int pos) const
{
    if (pos < 0)
        return (limit - 1);

    if (pos >= limit)
        return 0;

    return pos;
}

void WordSearchSolver::directional_search(int row, int col, const std::string& word)
{
    const static int XMOVES[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const static int YMOVES[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    if (word.empty() || word_grid_[row][col] != word[0])
        return;

    const int ROWS = word_grid_.size();
    const int COLS = word_grid_[0].size();
    for (int i = 0; i < 8; ++i) {
        std::size_t match_ctr = 1;
        int xmove = row + XMOVES[i];
        int ymove = col + YMOVES[i];
        for (; match_ctr < word.size(); ++match_ctr) {
            if (xmove < 0 || xmove >= ROWS || ymove < 0 || ymove >= COLS) {
                if (wrap_enabled_) {
                    xmove = wrap_move(ROWS, xmove);
                    ymove = wrap_move(COLS, ymove);
                } else {
                    break;
                }
            }

            if ((word_grid_[xmove][ymove] != word[match_ctr]) || (xmove == row && ymove == col))
                break;

            xmove += XMOVES[i];
            ymove += YMOVES[i];
        }

        if (match_ctr == word.size()) {
            search_results_.push_back({
                    std::make_tuple(row, col),
                    std::make_tuple(xmove - XMOVES[i], ymove - YMOVES[i])});
            return;
        }
    }
    search_results_.push_back({});
}

}
