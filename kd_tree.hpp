#pragma once

#include <fstream>
#include <vector>

#include "kd_node.hpp"

struct kd_tree {
public:
    void input(const char * filename);
    void push(double * temp, int & index_vec, int index_dev, int index_par);
    void save(std::ostream &output_file);
    double get_distance(double * node_1, double * node_2);
    void seek_nearest(int index_root, double * other_node_coordinates,
                        int index_dim, int & best_index, double & best_distance);
    void get_node(int index);

private:
    std::vector <kd_node> nodes;
};
