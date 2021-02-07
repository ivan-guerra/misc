/*!
 * \file word_search_solver_test.cc
 * \brief Unit test the WordSearchSolver class.
 * \details The unit tests below test that WordSearchSolver objects can maintain
 *          the correct state between calls/perform basic error handling. It was a concious
 *          design decision to not expose the internals of the word search algorithm to the user.
 *          Cleaner more concise code came out of hiding the details of the search algorithm.
 */

#include <vector>
#include <tuple>
#include "gtest/gtest.h"
#include "word_search_solver.h"

TEST(WordSearchSolver, BadPathToInputFile)
{
    // Verify puzzle loading halts when we provide a bogus data file path.
    supersearch::WordSearchSolver solver("bogus/path/to/data.txt");
    ASSERT_FALSE(solver.load_puzzle());
}

TEST(WordSearchSolver, InvalidWordGridDim)
{
    // Verify puzzle loading halts when invalid grid dimensions are encountered.
    // An invalid dimension is an N or M value where N or M is <= 0.
    supersearch::WordSearchSolver solver("../test/test_data/invalid_dim.txt");
    ASSERT_FALSE(solver.load_puzzle());
}

TEST(WordSearchSolver, InvalidSearchTermCount)
{
    // Verify puzzle loading halts when an invalid search term count is encountered.
    // An invalid search term count is a search term integer <= 0.
    supersearch::WordSearchSolver solver("../test/test_data/invalid_search_term_count.txt");
    ASSERT_FALSE(solver.load_puzzle());
}

TEST(WordSearchSolver, CallToSolveWithNoPuzzle)
{
    // Verify the solver does not crash when asked to solve when no puzzle data has been loaded.
    supersearch::WordSearchSolver solver("../test/test_data/valid_puzzle.txt");
    ASSERT_FALSE(solver.solve());
}

TEST(WordSearchSolver, SolveSinglePuzzleNoWrapping)
{
    // Verify we can load and solve a single puzzle successfully in NO WRAP mode.
    supersearch::WordSearchSolver solver("../test/test_data/valid_puzzle.txt");
    ASSERT_TRUE(solver.load_puzzle());
    ASSERT_TRUE(solver.solve());

    const std::vector<std::vector<std::tuple<int,int>>> expected_soln = {
        {std::make_pair(1, 2), std::make_pair(1, 0)},
        {},
        {},
        {},
        {}
    };
    ASSERT_EQ(solver.get_soln(), expected_soln);
}

TEST(WordSearchSolver, SolveSinglePuzzleWithWrapping)
{
    // Verify we can load and solve a single puzzle successfully in WRAP mode.
    supersearch::WordSearchSolver solver("../test/test_data/valid_puzzle.txt");
    ASSERT_TRUE(solver.load_puzzle());
    ASSERT_TRUE(solver.load_puzzle());
    ASSERT_TRUE(solver.solve());

    const std::vector<std::vector<std::tuple<int,int>>> expected_soln = {
        {std::make_pair(1, 2), std::make_pair(1, 0)},
        {std::make_pair(0, 2), std::make_pair(0, 1)},
        {std::make_pair(0, 0), std::make_pair(2, 0)},
        {std::make_pair(3, 2), std::make_pair(0, 2)},
        {}
    };
    ASSERT_EQ(solver.get_soln(), expected_soln);
}

TEST(WordSearchSolver, SolveSequenceOfPuzzles)
{
    // Verify we can solve puzzles correctly in sequence.
    supersearch::WordSearchSolver solver("../test/test_data/valid_puzzle.txt");
    ASSERT_TRUE(solver.load_puzzle());
    ASSERT_TRUE(solver.solve());

    const std::vector<std::vector<std::tuple<int,int>>> expected_soln1 = {
        {std::make_pair(1, 2), std::make_pair(1, 0)},
        {},
        {},
        {},
        {}
    };
    ASSERT_EQ(solver.get_soln(), expected_soln1);

    ASSERT_TRUE(solver.load_puzzle());
    ASSERT_TRUE(solver.solve());
    const std::vector<std::vector<std::tuple<int,int>>> expected_soln2 = {
        {std::make_pair(1, 2), std::make_pair(1, 0)},
        {std::make_pair(0, 2), std::make_pair(0, 1)},
        {std::make_pair(0, 0), std::make_pair(2, 0)},
        {std::make_pair(3, 2), std::make_pair(0, 2)},
        {}
    };
    ASSERT_EQ(solver.get_soln(), expected_soln2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
