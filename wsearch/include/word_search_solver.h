/*!
 * \file word_search_solver.h
 * \brief Declare the WordSearchSolver class.
 */

#pragma once

#include <tuple>
#include <vector>
#include <string>
#include <fstream>

namespace supersearch
{

/*!
 * \class WordSearchSolver
 * \brief Declare the interface for a class whose purpose is to solve word puzzles.
 * \details WordSearchSolver exposes an interface which allows the user to
 *          (1) Load word puzzle data from a text file.
 *          (2) Solve the word puzzle in either a wrapped or no wrap mode.
 *          (3) Print the word puzzle solution to stdout.
 *          (4) Perform (1)-(3) for each subsequent puzzle in the input text file.
 */
class WordSearchSolver
{
public:
    /*!
     * \brief Construct a WordSearchSolver object purposed to read from \p puzzle_file.
     * \param puzzle_file An absolute or relative path to the text file containing puzzle data.
     */
    WordSearchSolver(const std::string& puzzle_file=DEFAULT_PUZZLE_FILE);

    /*!
     * \brief WordSearchSolver objects are not copy constructable.
     */
    WordSearchSolver(const WordSearchSolver& wss) = delete;

    /*!
     * \brief WordSearchSolver objects do not implement move semantics.
     */
    WordSearchSolver(WordSearchSolver&& wss) = delete;

    /*!
     * \brief WordSearchSolver objects do not support assignment.
     */
    WordSearchSolver& operator=(const WordSearchSolver& wss) = delete;

    /*!
     * \brief Default destructor.
     * \details All members of a WordSearchSolver will be automatically destroyed.
     *          The fstream file handle will be closed on our behalf by the object's
     *          destructor.
     */
    ~WordSearchSolver() = default;

    /*!
     * \brief Load a puzzle from the input puzzle data file.
     * \details load_puzzle() is responsible for fetching all state data associated with a puzzle
     *          from the input file. Puzzle state data includes
     *          (1) The word search grid.
     *          (2) The search mode.
     *          (3) The list of search terms.
     *          If any of (1)-(3) fails, load_puzzle() returns false and prints an error message to stderr.
     * \return True if all puzzle state data is loaded into memory.
     */
    bool load_puzzle();

    /*!
     * \brief Search for all input search terms in the word grid.
     * \details solve() attempts find search terms in the word grid by iterating over the grid
     *          and launching a directional search at each cell. This directional search
     *          goes down all 8 possible paths. If found, the search term's starting and ending
     *          indices are stored.
     * \return True if a search for each search term is performed successfully. Note, a return value
     *         of true does NOT indicate all search terms were found!
     */
    bool solve();

    const auto& get_soln() const { return search_results_; }
    auto get_soln() { return search_results_; }

    /*!
     * \brief Print the solution to the current word search puzzle to stdout.
     */
    void print_results() const;

    /*!
     * \brief Reset the state of the current word search puzzle.
     * \details clear_puzzle() updates the internal state of WordSearchSolver instance such that
     *          the current loaded puzzle (if any) is discarded. Note, memory allocated
     *          during a previous call to load_puzzle() or solve() is not necessarily freed.
     */
    void clear_puzzle();

private:
    /*!
     * \brief Load the word search grid into memory.
     * \details get_grid() attempts to read the puzzle's dimension data from the input file and
     *          then proceeds to read NxM-length strings. The strings are decomposed into chars and
     *          the end result is an NxM matrix of chars representing the word search grid. The
     *          representation is stored in #word_grid_.
     * \return True if the word search grid is loaded into memory.
     */
    bool get_grid();

    /*!
     * \brief Load the search mode data from file.
     * \details During get_mode(), if the read string is WRAP, #wrap_enabled_ is set to true,
     *          otherwise #wrap_enabled_ is set to false.
     * \return True if search mode data is loaded successfully.
     */
    bool get_mode();

    /*!
     * \brief Load all search terms into memory.
     * \details get_search_words() reads in the count of search terms, nwords, and then proceeds
     *          to read nwords strings into memory storing the strings in #search_words_.
     * \return True if all search terms are loaded.
     */
    bool get_search_words();

    /*!
     * \brief Wrap \pos around \p limit.
     * \details wrap_move() is a helper method of directional_search() that takes a position \pos and
     *          wraps it around a boundary, \p limit. There are three cases:
     *          (1) pos >= limit -> pos = 0
     *          (2) pos < 0 -> pos = limit - 1
     *          (3) pos does not satisfy (1)-(2) and thus remains unchanged
     * \return An integer representing the wrap of \p pos around \p limit. If no wrapping was performed,
     *         \p pos is returned.
     */
    int wrap_move(int limit, int pos) const;

    /*!
     * \brief Search for \p word in #word_grid_ starting from the index (\p row,\p col).
     * \details directional_search() tries to construct \p word starting from index (\p row, \p col).
     *          The search goes down all 8 possible paths. If wrapping is enabled, the search will
     *          automatically wrap around the bounds of the word grid.
     * \param row Row index from which to begin the search.
     * \param col Column index from which to begin the search.
     * \param word Word to search for.
     */
    void directional_search(int row, int col, const std::string& word);

    const static std::string WRAP_MODE; /*!< Token indicating wrapping should be enabled during search. */
    const static std::string DEFAULT_PUZZLE_FILE; /*!< Default path to the puzzle data text file. */

    bool has_load_; /*!< Flag indicating whether this instance has already loaded a puzzle. */
    bool wrap_enabled_; /*!< Flag indicating whether the wrapping search mode is enabled. */
    std::ifstream puzzle_file_handle_; /*!< Handle to the puzzle file ifstream. */
    std::vector<std::string> search_words_; /*!< Vector of search terms to search for in this puzzle. */
    std::vector<std::vector<char>> word_grid_; /*!< Character matrix representing the word grid. */
    std::vector<std::vector<std::tuple<int,int>>> search_results_; /*!< x,y coordinate pairs representing the start/end point of a search term in word grid. */
}; // end WordSearchSolver

} // end supersearch
