#pragma once

#include <vector>

namespace nnalgo
{

struct ThreeDPoint
{
    int id_;
    double x_;
    double y_;
    double z_;
    ThreeDPoint() : id_(0), x_(0.0), y_(0.0), z_(0.0) { }
    ThreeDPoint(int id, double x, double y, double z) : id_(id), x_(x), y_(y), z_(z) { }

    static bool compare_x(const ThreeDPoint& a, const ThreeDPoint& b) { return (a.x_ < b.x_); }
    static bool compare_y(const ThreeDPoint& a, const ThreeDPoint& b) { return (a.y_ < b.y_); }
    static bool compare_z(const ThreeDPoint& a, const ThreeDPoint& b) { return (a.z_ < b.z_); }
};

class ThreeDTree
{
public:
    ThreeDTree() : root_(nullptr) { }
    ThreeDTree(std::vector<ThreeDPoint>& coords);
    ThreeDTree(const ThreeDTree& tree) = delete;
    ThreeDTree(ThreeDTree&& tree) = delete;
    ~ThreeDTree() { destruct_tree(root_); }

    ThreeDTree& operator=(const ThreeDTree& tree) = delete;
    void print_tree() const;

private:
    struct ThreeDNode
    {
        ThreeDPoint location_;
        ThreeDNode* left_;
        ThreeDNode* right_;
        ThreeDNode() : location_(0, 0, 0, 0), left_(nullptr), right_(nullptr) { }
        ThreeDNode(const ThreeDPoint& location, ThreeDNode* left=nullptr, ThreeDNode* right=nullptr) :
            location_(location), left_(left), right_(right) { }
    };

    int find_median_on_axis(int l, int r, int depth, std::vector<ThreeDPoint>& coords);
    ThreeDNode* construct_tree(int l, int r, int depth, std::vector<ThreeDPoint>& coords);
    void destruct_tree(ThreeDNode* root);
    void print_tree(ThreeDNode* root) const;

    ThreeDNode* root_;
}; // end ThreeDTree

} // end nnalgo
