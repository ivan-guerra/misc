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

} // end nnalgo
