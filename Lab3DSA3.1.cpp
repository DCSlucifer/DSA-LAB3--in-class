//Full Name: Vo Thanh Danh
//MSSV     : 22520201
//Lab 03
//Notes or Remarks:
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <memory>

const int K = 2; // For 2D points, change this for higher dimensions

struct Point {
    std::vector<double> coords;
    
    Point(std::initializer_list<double> c) : coords(c) {}
    
    double distance(const Point& other) const {
        double dist = 0;
        for (int i = 0; i < K; i++) {
            double diff = coords[i] - other.coords[i];
            dist += diff * diff;
        }
        return std::sqrt(dist);
    }
};

struct KDNode {
    Point point;
    std::unique_ptr<KDNode> left;
    std::unique_ptr<KDNode> right;
    
    KDNode(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    std::unique_ptr<KDNode> root;
    
    void insertRecursive(std::unique_ptr<KDNode>& node, const Point& point, int depth) {
        if (!node) {
            node = std::make_unique<KDNode>(point);
            return;
        }
        
        int cd = depth % K;
        
        if (point.coords[cd] < node->point.coords[cd]) {
            insertRecursive(node->left, point, depth + 1);
        } else {
            insertRecursive(node->right, point, depth + 1);
        }
    }
    
    void nearestNeighborRecursive(const KDNode* node, const Point& target, int depth, const Point*& best, double& bestDist) const {
        if (!node) return;
        
        double d = node->point.distance(target);
        if (d < bestDist) {
            bestDist = d;
            best = &node->point;
        }
        
        int cd = depth % K;
        double diff = target.coords[cd] - node->point.coords[cd];
        
        const KDNode* near = (diff < 0) ? node->left.get() : node->right.get();
        const KDNode* far = (diff < 0) ? node->right.get() : node->left.get();
        
        nearestNeighborRecursive(near, target, depth + 1, best, bestDist);
        
        if (diff * diff < bestDist) {
            nearestNeighborRecursive(far, target, depth + 1, best, bestDist);
        }
    }
    
public:
    KDTree() : root(nullptr) {}
    
    void insert(const Point& point) {
        insertRecursive(root, point, 0);
    }
    
    Point nearestNeighbor(const Point& target) const {
        if (!root) throw std::runtime_error("Tree is empty");
        
        const Point* best = &root->point;
        double bestDist = root->point.distance(target);
        
        nearestNeighborRecursive(root.get(), target, 0, best, bestDist);
        
        return *best;
    }
};

int main() {
    KDTree tree;
    
    // Insert some points
    tree.insert({3, 6});
    tree.insert({17, 15});
    tree.insert({13, 15});
    tree.insert({6, 12});
    tree.insert({9, 1});
    tree.insert({2, 7});
    tree.insert({10, 19});
    
    // Find nearest neighbor
    Point target({10, 10});
    Point nearest = tree.nearestNeighbor(target);
    
    std::cout << "Nearest neighbor to (10, 10): (";
    for (int i = 0; i < K; i++) {
        std::cout << nearest.coords[i];
        if (i < K - 1) std::cout << ", ";
    }
    std::cout << ")" << std::endl;
    
    return 0;
}