/*!
 * \file 3d_tree.cc
 * \brief ThreeDTree definition.
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include "3d_tree.h"

namespace nnalgo
{

ThreeDTree::ThreeDTree(std::vector<ThreeDPoint>& coords) : root_(nullptr)
{
    int median_index = find_median_on_axis(0, coords.size(), 0, coords);

    root_ = new ThreeDNode(coords[median_index]);
    root_->left_ = construct_tree(0, median_index-1, 1, coords);
    root_->right_ = construct_tree(median_index+1, coords.size()-1, 1, coords);
}

int ThreeDTree::find_median_on_axis(int l, int r, int depth, std::vector<ThreeDPoint>& coords)
{
    int axis = depth % 3;
    if (0 == axis)
        std::sort(coords.begin()+l, coords.begin()+r, ThreeDPoint::compare_x);
    else if (1 == axis)
        std::sort(coords.begin()+l, coords.begin()+r, ThreeDPoint::compare_y);
    else
        std::sort(coords.begin()+l, coords.begin()+r, ThreeDPoint::compare_z);
    return ((l + r) / 2);
}

void ThreeDTree::print_tree() const
{
    if (!root_)
        return;

    print_tree(root_->left_);
    std::cout << "(" << root_->location_.x_ << ", " << root_->location_.y_
        << ", " << root_->location_.z_ << ")" << std::endl;
    print_tree(root_->right_);
}

void ThreeDTree::radial_search(const ThreeDPoint& ref, double rad, std::vector<ThreeDPoint>& neighbors) const

{
    if (!root_)
        return;

    radial_search_(root_, ref, rad, neighbors, 0);
}

ThreeDTree::ThreeDNode* ThreeDTree::construct_tree(int l, int r,
        int depth, std::vector<ThreeDPoint>& coords)
{
    if (l > r)
        return nullptr;

    int median_index = find_median_on_axis(l, r, depth, coords);
    ThreeDNode* inode = new ThreeDNode(coords[median_index]);
    inode->left_ = construct_tree(l, median_index-1, depth+1, coords);
    inode->right_ = construct_tree(median_index+1, r, depth+1, coords);

    return inode;
}

void ThreeDTree::destruct_tree(ThreeDNode* root)
{
    if (!root)
        return;

    destruct_tree(root->left_);
    destruct_tree(root->right_);
    delete root;
}

void ThreeDTree::print_tree(ThreeDNode* root) const
{
    if (!root)
        return;

    print_tree(root->left_);
    std::cout << "(" << root->location_.x_ << ", " << root->location_.y_
        << ", " << root->location_.z_ << ")" << std::endl;
    print_tree(root->right_);
}

double ThreeDTree::distance_squared(const ThreeDPoint& a, const ThreeDPoint& b) const
{
    double x_term = a.x_ - b.x_;
    double y_term = a.y_ - b.y_;
    double z_term = a.z_ - b.z_;
    double dist_squared = (x_term * x_term) + (y_term * y_term) + (z_term * z_term);

    return dist_squared;
}

void ThreeDTree::radial_search_(ThreeDNode* root, const ThreeDPoint& ref, double rad,
        std::vector<ThreeDPoint>& neighbors, int depth) const
{
    if (!root)
        return;

    double rad_squared = rad * rad;
    double dist_squared = distance_squared(ref, root->location_);
    int axis = depth % 3;
    double axis_dist = root->location_[axis] - ref[axis];
    double axis_dist_squared = axis_dist * axis_dist;

    if ((dist_squared <= rad_squared) && (0 != dist_squared))
        neighbors.emplace_back(root->location_);

    ThreeDNode* section = nullptr;
    ThreeDNode* other = nullptr;
    if (axis_dist > 0) {
        section = root->left_;
        other = root->right_;
    } else {
        section = root->right_;
        other = root->left_;
    }

    radial_search_(section, ref, rad, neighbors, depth+1);
    if (axis_dist_squared <= rad_squared)
        radial_search_(other, ref, rad, neighbors, depth+1);
}

} // end nnalgo
