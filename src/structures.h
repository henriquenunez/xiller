//

#include <stdlib.h>

struct Point3d
{
    float x, y, z;
};

struct TreeNode
{
    enum {
	X,
	Y,
	Z,
    } cutDirection;
    Point3d location;
    TreeNode *leftChild, *rightChild;
};

struct KDTree
{
    TreeNode* root;
};

KDTree* initTree()
{
    return (KDTree*) calloc(1, sizeof(KDTree));
}

TreeNode* searchTree(TreeNode* root, Point3d location)
{
    TreeNode* next_node = NULL;

    // Check if it's the correct location.
    // if(location == root.location)
    // return root;

    if (root->cutDirection == TreeNode::X)
    {
	if (root->location.x < location.x)
	{
	    next_node = root->leftChild ? root->leftChild : NULL;
	}
	else
	{
	    next_node = root->rightChild ? root->rightChild : NULL;	
	}
    }
    else if (root->cutDirection == TreeNode::Y)
    {
	if (root->location.y < location.y)
	{
	    next_node = root->leftChild ? root->leftChild : NULL;
	}
	else
	{
	    next_node = root->rightChild ? root->rightChild : NULL;	
	}
    }
    else // Z
    {
	if (root->location.z < location.z)
	{
	    next_node = root->leftChild ? root->leftChild : NULL;
	}
	else
	{
	    next_node = root->rightChild ? root->rightChild : NULL;	
	}
    }

    if (next_node)
        return searchTree(next_node, location);
    else return NULL;
}

void addPoint(Point3d addedPoint)
{

}

