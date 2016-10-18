#include "kd_node.hpp"

#include <algorithm>
#include <iterator>

kd_node::kd_node(double * values, int index):
    left(-1),
    right(-1),
    split_index(index)
{
    (!values)
        ? (void)std::fill(value, value + N, 0)
        : (void)std::copy(values, values + N, value);
}
