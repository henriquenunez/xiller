//

#include <cmath>
#include <stdlib.h>

struct Point3d
{
    float x, y, z;
    static constexpr const float epsilon = 0.001; 

    bool operator == (const Point3d &comp)
    {
	if (std::abs(comp.x - x) < epsilon && 
	    std::abs(comp.y - y) < epsilon &&
	    std::abs(comp.z - z) < epsilon)
	   return true; 

	return false;	
    }
};

struct KDTreeNode
{
    enum {
	X,
	Y,
	Z,
    } cutDirection;
    Point3d location;
    KDTreeNode *leftChild, *rightChild;

};

struct KDTree
{
    KDTreeNode* root;
};

KDTree* initKDTree()
{
    return (KDTree*) calloc(1, sizeof(KDTree));
}

/* Will return the node corresponding to the closest postition for the
 * point, so if the point exists will be the point node, and if the point does
 * not exists its parent will be returned.
 * */
KDTreeNode* __searchKDTree(KDTreeNode* root, Point3d location)
{
    KDTreeNode* next_node = NULL;
    bool keep_searching = false;

    // Return this node if it's the correct location.
    if(location == root->location)
	return root;

    if (root->cutDirection == KDTreeNode::X)
    {
	if (root->location.x < location.x)
	{
	    next_node = root->rightChild ? root->rightChild : NULL;	
	}
	else
	{
	    next_node = root->leftChild ? root->leftChild : NULL;
	}
    }
    else if (root->cutDirection == KDTreeNode::Y)
    {
	if (root->location.y < location.y)
	{
	    next_node = root->rightChild ? root->rightChild : NULL;	
	}
	else
	{
	    next_node = root->leftChild ? root->leftChild : NULL;
	}
    }
    else // Z
    {
	if (root->location.z < location.z)
	{
	    next_node = root->rightChild ? root->rightChild : NULL;	
	}
	else
	{
	    next_node = root->leftChild ? root->leftChild : NULL;
	}
    }

    if (next_node)
	keep_searching = true;
    else
	next_node = root;

    if (keep_searching)
        return __searchKDTree(next_node, location);
    else return next_node;
}

KDTreeNode* searchKDTree(KDTree* tree, Point3d location)
{
    return __searchKDTree(tree->root, location);
}

/* Tree traversal, left-node-first order
 * does the operation first
 * */
void __traverse_tree(KDTreeNode* root, void (*callback)(KDTreeNode*))
{
    // Run the function
    if (!root) return;

    callback(root);
    __traverse_tree(root->leftChild, callback);
    __traverse_tree(root->rightChild, callback);
}

/* Tree traversal, left-node-first order
 * does the operation after 
 * */
void __traverse_tree_operation_after(KDTreeNode* root, void (*callback)(KDTreeNode*))
{
    // Run the function
    if (!root) return;

    __traverse_tree_operation_after(root->leftChild, callback);
    __traverse_tree_operation_after(root->rightChild, callback);
    callback(root);
}

void inline __nodeFree(KDTreeNode* node)
{
    free(node);
}

void cleanUpKDTree(KDTree *tree)
{
    __traverse_tree_operation_after(tree->root, __nodeFree);
}

#define CALLOC_ONE(t) ((t*) calloc(1, sizeof(t)));

void addPointKDTree(KDTree* tree, Point3d addedPoint)
{
    // Create tree root in case we don't have one
    if (!tree->root)
    {
	tree->root = CALLOC_ONE(KDTreeNode);
	tree->root->location = addedPoint;
	tree->root->cutDirection = KDTreeNode::X;

	return;
    }

    KDTreeNode* parent_node = __searchKDTree(tree->root,
					     addedPoint);

    if (parent_node->location == addedPoint) // Point was already here
	return;

    KDTreeNode* added_node = CALLOC_ONE(KDTreeNode);
    added_node->location = addedPoint;

    float one_dimensional_location_par;
    float one_dimensional_location_child;
    
    if (parent_node->cutDirection == KDTreeNode::X)
    {
	added_node->cutDirection = KDTreeNode::Y;
	one_dimensional_location_child = addedPoint.x;
	one_dimensional_location_par = parent_node->location.x;
    }
    else if (parent_node->cutDirection == KDTreeNode::Y)
    {
	added_node->cutDirection = KDTreeNode::Z;
	one_dimensional_location_child = addedPoint.y;
	one_dimensional_location_par = parent_node->location.y;
    }
    else // Z
    {
	added_node->cutDirection = KDTreeNode::X;
	one_dimensional_location_child = addedPoint.z;
	one_dimensional_location_par = parent_node->location.z;
    }

    if (one_dimensional_location_child < one_dimensional_location_par)
    {
	parent_node->leftChild = added_node;
    }
    else 
    {
	parent_node->rightChild = added_node;
    }
}

