#include "kd_node.hpp"
#include "kd_tree.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    kd_tree tree;
    tree.input("test_for_2d.txt");

    return 0;
}

/*
7 2
5 4
9 6
2 3
4 7
8 1
*/
/*
30 40
5 25
10 12
70 70
50 30
35 45
*/
/*
51 75
25 40
70 70
10 30
35 90
55 1
60 80
1 10
50 50
*/

/*
40 45
15 70
70 10
69 50
66 85
85 90
*/
