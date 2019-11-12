/*!
 * \file 3d_tree.h
 * \brief Declare the ThreeDTree container class.
 */

#pragma once

#include <vector>

namespace nnalgo
{

/*!
 * \struct ThreeDPoint
 * \brief Declare a type for storing 3D coordinate data.
 */
struct ThreeDPoint
{
    unsigned int id_; /*!< Unique integral ID identifying this point. */
    double x_; /*!< X axis location. */
    double y_; /*!< Y axis location. */
    double z_; /*!< Z axis location. */

    /*!
     * \brief Default constructed ThreeDPoint.
     * \details No non-default constructed ThreeDPoint should have ID of 0.
     */
    ThreeDPoint() : id_(0), x_(0.0), y_(0.0), z_(0.0) { }

    /*!
     * \brief Construct a ThreeDPoint with a set ID and location.
     */
    ThreeDPoint(unsigned id, double x, double y, double z) : id_(id), x_(x), y_(y), z_(z) { }

    /*!
     * \brief Determine whether \p a is further left on the x-axis than \p b.
     * \return True if \p a is less than \p b with respect to x.
     */
    static bool compare_x(const ThreeDPoint& a, const ThreeDPoint& b) { return (a.x_ < b.x_); }

    /*!
     * \brief Determine whether \p a is further left on the y-axis than \p b.
     * \return True if \p a is less than \p b with respect to y.
     */
    static bool compare_y(const ThreeDPoint& a, const ThreeDPoint& b) { return (a.y_ < b.y_); }

    /*!
     * \brief Determine whether \p a is further left on the z-axis than \p b.
     * \return True if \p a is less than \p b with respect to z.
     */
    static bool compare_z(const ThreeDPoint& a, const ThreeDPoint& b) { return (a.z_ < b.z_); }

    /*!
     * \brief Overload [] to return the x, y, or z coordinate.
     * \param i Integral index into the coordinate triplet.
     * \return The coordinate mapped to \p i. Zero is returned if i is not in [0,2].
     */
    double operator[](int i) const
    {
        if (0 == i) return x_;
        if (1 == i) return y_;
        if (2 == i) return z_;
        return 0;
    }
};

/*!
 * \class ThreeDTree
 * \brief Declare the interface for a simplified k-d tree where k equals 3.
 * \details ThreeDTree exposes an interface which allows the user to:
 *          (1) Construct a balanced, static 3-d tree from of a set points in 3D space.
 *          (2) Perform radial queries (i.e., find all points within a specific radius of a reference point).
 *          (3) Print the inorder traversal of the tree.
 *          The tree itself is recursively defined. Operations such as tree construction and radial searches
 *          are performed recursively and therefore make heavy use of the call stack. However, the tree
 *          is guaranteed to be balanced and therefore have a depth of no more than O(logn).
 */
class ThreeDTree
{
public:

    /*!
     * \brief ThreeDTrees cannot be default constructed.
     * \details ThreeDTrees can only be constructed from a set of ThreeDPoints.
     */
    ThreeDTree() = delete;

    /*!
     * \brief Construct a balanced ThreeDTree containing the points in \p coords.
     * \details ThreeDTree does not guarantee the order of the elements in \p coords will
     *          be the same after a call to the ThreeDTree constructor.
     * \param coords A vector of unique ThreeDPoint objects.
     */
    ThreeDTree(std::vector<ThreeDPoint>& coords);

    /*!
     * \brief ThreeDTree is not copy constructable.
     */
    ThreeDTree(const ThreeDTree& tree) = delete;

    /*!
     * \brief ThreeDTree does not support move semantics.
     */
    ThreeDTree(ThreeDTree&& tree) = delete;

    /*!
     * \brief Recursively delete the ThreeDNode objects that form this tree.
     */
    ~ThreeDTree() { destruct_tree(root_); }

    /*!
     * \brief ThreeDTree does not support assignment.
     */
    ThreeDTree& operator=(const ThreeDTree& tree) = delete;

    /*!
     * \brief Print the coordinates stored in this tree using an inorder traversal pattern.
     */
    void print_tree() const;

    /*!
     * \brief Find all the neighbors of \p ref within a search radius of size \p rad.
     * \param ref A 3D reference point.
     * \param rad A nonnegative radius value.
     * \param neighbors Vector used to store \p ref neighbors.
     */
    void radial_search(const ThreeDPoint& ref, double rad, std::vector<ThreeDPoint>& neighbors) const;

private:
    /*!
     * \struct ThreeDNode
     * \brief Representation of a node within the 3-d tree.
     */
    struct ThreeDNode
    {
        ThreeDPoint location_; /*!< Location of this node in 3D space. */
        ThreeDNode* left_; /*!< Pointer to the left subtree of this node. */
        ThreeDNode* right_; /*!< Pointer to the right subtree of this node. */

        /*!
         * \brief Default constructor.
         */
        ThreeDNode() : location_(0, 0, 0, 0), left_(nullptr), right_(nullptr) { }

        /*!
         * \brief Construct a ThreeDNode with a set location.
         * \param location A non-default constructed ThreeDPoint object.
         * \param left Pointer to this ThreeDNode's left subtree.
         * \param right Pointer to this ThreeDNode's right subtree.
         */
        ThreeDNode(const ThreeDPoint& location, ThreeDNode* left=nullptr, ThreeDNode* right=nullptr) :
            location_(location), left_(left), right_(right) { }
    };

    /*!
     * \brief Find the index in \p coords of the median element on the current search axis.
     * \details find_median_on_axis() computes the median point by axis in the range [\p l, \p r]. The
     *          implementation has the side effect of sorting \p coords from index \p l to index \p r. The
     *          sort is performed with respect to the current axis (x, y, or z) which is calculated as
     *          axis = depth % 3.
     * \param l Left bound of \p coords.
     * \param r Right bound of \p coords.
     * \param depth Level of the median within the tree.
     * \param coords Vector of 3D point objects.
     * \return The index of the median by axis in \p coords within the bounds [\p l, \p r].
     */
    int find_median_on_axis(int l, int r, int depth, std::vector<ThreeDPoint>& coords);

    /*!
     * \brief Recursively construct a 3-d tree containing all points in \p coords.
     * \param l Left bound of \p coords.
     * \param r Right bound of \p coords.
     * \param depth Current depth within the nascent tree.
     * \return The root node of the newly constructed tree.
     */
    ThreeDNode* construct_tree(int l, int r, int depth, std::vector<ThreeDPoint>& coords);

    /*!
     * \brief Recursively destruct the 3-d tree.
     * \param root The root of the 3-d tree.
     */
    void destruct_tree(ThreeDNode* root);

    /*!
     * \brief Helper method used by the public print_tree() to recrusively print the inorder traversal.
     * \param root The root of the 3-d tree.
     */
    void print_tree(ThreeDNode* root) const;

    /*!
     * \brief Compute the square of the distance between two points in 3D space.
     * \param a A 3D point.
     * \param b A 3D point.
     * \return The square of the distance between point a and b in 3D space.
     */
    double distance_squared(const ThreeDPoint& a, const ThreeDPoint& b) const;

    /*!
     * \brief Helper method used by the public radial_search() to find all neighbors of \p ref within \p rad.
     * \param ref A 3D reference point.
     * \param rad A nonnegative radius value.
     * \param neighbors Vector used to store \p ref neighbors.
     */
    void radial_search_(ThreeDNode* root, const ThreeDPoint& ref, double rad,
            std::vector<ThreeDPoint>& neighbors, int depth) const;

    ThreeDNode* root_; /*!< The root of this 3-d tree. */
}; // end ThreeDTree

} // end nnalgo
