/*!
 * \file nearest_neighbors_test.cc
 * \brief Unit test the 3-D tree's radial search functionality.
 */

#include "3d_tree.h"
#include "gtest/gtest.h"

using namespace nnalgo;

TEST(NNSearch, OutOfRadiusSearch)
{
    std::vector<ThreeDPoint> points;
    points.emplace_back(ThreeDPoint(0,0,0,0));
    points.emplace_back(ThreeDPoint(1,0,0,1));
    points.emplace_back(ThreeDPoint(2,0.5,0.5,0.5));

    ThreeDTree search_tree(points);

    ThreeDPoint missing_key(3,10,10,10);
    std::vector<ThreeDPoint> neighbors;
    search_tree.radial_search(missing_key, 1.0, neighbors);

    ASSERT_TRUE(neighbors.empty());
}

TEST(NNSearch, InRadiusSearchValidPoint)
{
    std::vector<ThreeDPoint> points;
    points.emplace_back(ThreeDPoint(0,0,0,0));
    points.emplace_back(ThreeDPoint(1,0,0,1));
    points.emplace_back(ThreeDPoint(2,0.5,0.5,0.5));

    ThreeDTree search_tree(points);

    ThreeDPoint ref_point(2,0.5,0.5,0.5);
    std::vector<ThreeDPoint> neighbors;
    search_tree.radial_search(ref_point, 1.0, neighbors);

    ASSERT_EQ(neighbors.size(), 2);
    std::vector<ThreeDPoint> expected_result;
    expected_result.emplace_back(ThreeDPoint(1,0,0,1));
    expected_result.emplace_back(ThreeDPoint(0,0,0,0));
    ASSERT_EQ(neighbors[0].id_, expected_result[0].id_);
    ASSERT_EQ(neighbors[1].id_, expected_result[1].id_);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
