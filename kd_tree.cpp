#include "kd_node.hpp"
#include "kd_tree.hpp"

#include <iostream>

void kd_tree::input(const char * filename)
{
    std::ifstream input_file(filename);

    double temp[N] = {0};

    int index_vec = -1;

    while (input_file >> temp[0]) {
        for (std::size_t j = 1; j < N; j++) {
            input_file >> temp[j];
        }
        push(temp, index_vec, -1, -1);
    }

    input_file.close();
}

void kd_tree::push(double * temp, int & index_vec, int index_dev, int index_par)
{
    /** next split axis */
    index_dev = (index_dev + 1) % N;

    if (index_vec == -1) {
        index_vec = nodes.size();
        nodes.insert(nodes.end(), kd_node(temp, index_dev));

        if (index_par != -1 && index_dev != 0) {
            kd_node & n = nodes[index_par];

            double value = nodes[index_vec].value[--index_dev];

            int & child = (value >= n.value[n.split_index])
                ? n.right
                : n.left;

            child = index_vec;
        }
    } else {
        kd_node & n = nodes[index_vec];

        double value = temp[index_dev];

        int & next = (value >= n.value[n.split_index])
            ? n.right
            : n.left;

        push(temp, next, index_dev, index_vec);
    }
}

static
std::string get_info(const kd_node & n)
{
    std::string info;
    for (size_t i = 0 ; i < N ; i++) {
        info += ((i > 0) ? " " : "") + std::to_string((int)n.value[i]);
    }
    return info;
}

static
void save_link(std::ostream &output_file, const std::string & color, int parent_index, int child_index)
{
    if (child_index == -1 || parent_index == -1)
    {
        return;
    }

    output_file << "\tN" << parent_index << " -> ";
    output_file  << "N" << child_index << "[color=" << color << ",penwidth=3.0]" << ";" << std::endl;
}

void kd_tree::save(std::ostream &output_file)
{
    /* save node IDs */
    output_file << "digraph {" << std::endl;
    output_file << "# Nodes:" << std::endl;

    std::size_t sz = nodes.size();
    for (std::size_t i = 0 ; i < sz ; i++)
    {
        output_file << "\tN" << i << " [label=\"" << get_info(nodes[i]) << "\"];"<< std::endl;
    }

    output_file << "# Links:" << std::endl;

    /* save links between nodes */
    for (std::size_t i = 0 ; i < sz ; i++)
    {
        save_link(output_file, "blue", i, nodes[i].left);
        save_link(output_file, "red",  i, nodes[i].right);
    }

    output_file << "}" << std::endl;
}

double kd_tree::get_distance(int index, kd_node * other_node)
{
    double dist = 0, tmp;
    for (size_t i = 0; i < N; i++) {
        tmp = nodes[index].value[i] - other_node -> value[i];
        dist += tmp * tmp;
    }
    return dist;
}

void kd_tree::seek_nearest(int index_root, kd_node * other_node,
                    int index_dev, int & best_index, double & best_distance)
{
    if (index_root == -1) return;

    double distance = get_distance(index_root, other_node);
    double temp_div = nodes[index_root].value[nodes[index_root].split_index]
                    - other_node -> value[index_dev];
    double distance_dev = temp_div * temp_div;

    if (best_index == -1 || distance < best_distance) {
        best_distance = distance;
        best_index = index_root;
        if (!best_distance) return;
    }

    index_dev = (index_dev + 1) % N;

    seek_nearest(temp_div > 0 ? nodes[index_root].left : nodes[index_root].right,
            other_node, index_dev, best_index, best_distance);
    if (distance_dev >= best_distance) return;
    seek_nearest(temp_div > 0 ? nodes[index_root].right : nodes[index_root].left,
            other_node, index_dev, best_index, best_distance);
}

void kd_tree::get_node(int index)
{
    std::cout << "(";
    for (size_t i = 0; i < N; i++) {
        if (i == N - 1) {
            std::cout << nodes[index].value[i];
            break;
        }
        std::cout << nodes[index].value[i] << ", ";
    }
    std::cout << ")" << std::endl;
}
