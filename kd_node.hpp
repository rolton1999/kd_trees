#pragma once

int const N = 2;

struct kd_node {

    double value[N];
    int split_index;
    int left;
    int right;

    kd_node(double * values = 0, int index = 0);

};
