/*!
 * \file driver.cc
 * \brief Execute a nearest neighbors search on a set of 3D points.
 * \details This driver prompts the user to enter the path to a text file containing
 *          a list of 3D coordinates. The user is also prompted for a search radius
 *          value. A 3-d tree is then constructed using the input points. For each point 
 *          in the input, the point's neighbor(s) who are within the given radius are recorded. 
 *          The result of the nearest neighbors search for each point is output to stdout.
 */

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "3d_tree.h"

using namespace nnalgo;

/*!
 * \brief Load the 3D points in \p point_file into \p points.
 * \param point_file Path to the 3D point data file.
 * \param points Vector of ingested 3D points.
 * \return True if all points are loaded from the input file.
 */
bool load_points(const std::string& point_file, std::vector<ThreeDPoint>& points)
{
    std::ifstream point_file_handle(point_file);
    if (!point_file_handle.is_open()) {
        std::cerr << "Unable to open file: " << point_file << std::endl;
        std::cerr << "Check that you provided a valid path." << std::endl;
        return false;
    }

    int npoints = 0;
    point_file_handle >> npoints;
    if (npoints <= 0) {
        std::cerr << "Invalid number of points: " << npoints << std::endl;
        std::cerr << "The number of points must be positive." << std::endl;
        return false;
    }

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    int i = 0;
    while (point_file_handle && i < npoints) {
        point_file_handle >> x >> y >> z;
        points.emplace_back(ThreeDPoint(i+1, x, y, z));
        i++;
    }

    if (npoints != i) {
        std::cerr << "Unable to read " << npoints << ". Loaded only " << i << " points." << std::endl;
        return false;
    }

    return true;
}

/*!
 * \brief Print the contents of the \p results matrix to stdout.
 * \details For each point, we print in the format
 *          point_id:[num_neighbors | neighbor_ids]
 */
void print_results(const std::vector<std::vector<int>>& results)
{
    int n = results.size();
    int m = results.front().size();
    std::cout << "------------- Start Search Results -------------" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << i+1 << ":[ ";
        std::cout << results[i][0] << " | ";
        for (int j = 1; j < m; j++) {
            if (0 == results[i][j])
                break;
            std::cout << results[i][j] << ' ';
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "------------- End Search Results --------------" << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "Enter the path (rel or abs) to the file containing your 3D points: ";

    std::string point_file;
    std::vector<ThreeDPoint> points;
    std::cin >> point_file;
    std::cout << "Loading points into memory..." << std::endl;
    if (!load_points(point_file, points))
        return 1;
    std::cout << "Points loaded successfully!" << std::endl;

    std::cout << "Enter the search radius (double precision values accepted): ";
    double rad = 0.0;
    std::cin >> rad;
    if (rad <= 0) {
        std::cerr << "Invalid search radius value: " << rad << std::endl;
        std::cerr << "Radius value must be positive." << std::endl;
        return 1;
    }

    ThreeDTree search_tree(points);
    search_tree.print_tree();
    std::vector<std::vector<int>> search_results(points.size(), std::vector<int>(points.size()+1, 0));
    for (const auto& p : points) {
        std::vector<ThreeDPoint> neighbors;
        search_tree.radial_search(p, rad, neighbors);

        search_results[p.id_-1][0] = neighbors.size();
        int i = 1;
        for (const auto& n : neighbors)
            search_results[p.id_-1][i++] = n.id_;
    }
    print_results(search_results);

    return 0;
}
