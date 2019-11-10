#pragma once

#include <tuple>
#include <vector>
#include <string>
#include <fstream>

namespace supersearch
{

class WordSearchSolver
{
public:
    WordSearchSolver(const std::string& puzzle_file=DEFAULT_PUZZLE_FILE);
    WordSearchSolver(const WordSearchSolver& gl) = delete;
    WordSearchSolver(WordSearchSolver&& gl) = delete;
    ~WordSearchSolver() = default;

    bool load_puzzle();
    bool solve();
    void print_results() const;
    void clear_puzzle();

private:
    bool get_grid();
    bool get_mode();
    bool get_search_words();
    int wrap_move(int limit, int pos) const;
    void directional_search(int row, int col, const std::string& word);

    const static std::string WRAP_MODE;
    const static std::string DEFAULT_PUZZLE_FILE;

    bool has_load_;
    bool wrap_enabled_;
    std::ifstream puzzle_file_handle_;
    std::vector<std::string> search_words_;
    std::vector<std::vector<char>> word_grid_;
    std::vector<std::vector<std::tuple<int,int>>> search_results_;
};

}
