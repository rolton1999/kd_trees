#pragma once

#include <fstream>
#include <vector>

#include "kd_node.hpp"

struct kd_tree {
public:
    void input(const char * filename);
    void push(double * temp, int & index_vec, int index_dev, int index_par);
    void save(std::ostream &output_file);
    double get_distance(int index, kd_node * other_node);
    double seek_nearest(int index_root, kd_node * other_node,
                        int index_dim, int best_index, double best_distance);

private:
    std::vector <kd_node> nodes;
};
