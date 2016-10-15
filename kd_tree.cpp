#include <fstream>
#include <fstream>
#include <vector>

#include "kd_node.hpp"
#include "kd_tree.hpp"

void kd_tree::input(const char * filename)
{
    std::ifstream input_file(filename);

    double temp[N] = {0};

    int index_dev = 0;
    int index_vec = -1;
    int index_par = -1;

    while (input_file >> temp[0]) {
        for (size_t j = 1; j < N; j++) {
            input_file >> temp[j];
        }
        push(temp, index_vec, index_dev, index_par);
    }

    input_file.close();
    std::ofstream output_file("tree.dot");
    output_file << "digraph {" << std::endl;
    save(0, output_file);
    output_file << "}";

}

void kd_tree::push(double * temp, int & index_vec, int & index_dev, int index_par)
{
    if (index_dev == N) {
        index_dev = 0;
    }

    if (index_vec == -1) {
        index_vec = nodes.size();
        nodes.insert(nodes.end(), kd_node(temp, index_dev));
        if (index_par != -1 && index_dev != 0) {
            if (nodes[index_vec].value[--index_dev]
                >= nodes[index_par].value[nodes[index_par].split_index]) {
                nodes[index_par].right = index_vec;

            } else {
                nodes[index_par].left = index_vec;
            }
        }
        return;
    } else {
        if (temp[index_dev] >= nodes[index_vec].value[nodes[index_vec].split_index]) {
            index_dev++;
            push(temp, nodes[index_vec].right, index_dev, index_vec);
        } else {
            index_dev++;
            push(temp, nodes[index_vec].left, index_dev, index_vec);
        }
    }
}

void kd_tree::save(int index, std::ofstream & output_file)
{
    if (index == -1) {
        return;
    } else {
        if (nodes[index].left != -1) {
            output_file << "\t" << nodes[index].info << " -> ";
            output_file  << nodes[nodes[index].left].info << "[color=blue,penwidth=3.0]" << ";" << std::endl;
            save(nodes[index].left, output_file);
        }
        if (nodes[index].right != -1) {
            output_file << "\t" << nodes[index].info << " -> ";
            output_file  << nodes[nodes[index].right].info << "[color=red,penwidth=3.0]" << ";" << std::endl;
            save(nodes[index].right, output_file);
        }
    }
}
