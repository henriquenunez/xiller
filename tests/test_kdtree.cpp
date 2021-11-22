#include "../src/structures.h"

#include <stdio.h>
#include <vector>

void print_debug(KDTreeNode* node)
{
    printf("Node (%f, %f, %f) %d\n", node->location.x, node->location.y, node->location.z, node->cutDirection);
}

void test_add_points(KDTree& tree)
{
    // Generate some points
    std::vector<Point3d> points_to_add;

    points_to_add.push_back({1, 1, 1});
    points_to_add.push_back({2, 2, 2});
    points_to_add.push_back({3, 3, 3});
    points_to_add.push_back({4, 4, 4});

    for (auto& a : points_to_add)
    {
	addPointKDTree(&tree, a);
    }

    __traverse_tree(tree.root, print_debug);

    for (auto& a : points_to_add)
    {
	KDTreeNode* temp = searchKDTree(&tree, a);

	printf("found node (%f, %f, %f): (%f, %f, %f) %d\n", a.x, a.y, a.z, temp->location.x, temp->location.y, temp->location.z, temp->cutDirection);
    }
}

int main()
{
    KDTree test_tree;
    test_tree.root = NULL;
    test_add_points(test_tree);
    cleanUpKDTree(&test_tree);
}

