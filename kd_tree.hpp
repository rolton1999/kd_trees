#pragma once

#include <fstream>
#include <vector>

struct kd_tree {
public:
    void input(const char * filename);
    void push(double * temp, int & index_vec, int & index_dev, int index_par);
    void save(int index, std::ofstream & output_file);

private:
    std::vector <kd_node> nodes;
};
