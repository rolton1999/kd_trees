#include <string>

#include "kd_node.hpp"

kd_node::kd_node(double * values, int index)
{
    if (values != 0) {
        for (size_t i = 0; i < N; i++) {
            value[i] = values[i];
        }
    } else {
        for (size_t i = 0; i < N; i++) {
            value[i] = 0;
        }
    }

    info += std::to_string((int)value[0]);
    for (size_t i = 1; i < N; i++) {
        info += " " + std::to_string((int)value[i]);
    }
    info += "\"";

    left = -1;
    right = -1;
    split_index = index;
}
