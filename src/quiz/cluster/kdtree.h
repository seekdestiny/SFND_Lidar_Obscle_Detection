/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
    if (root == NULL) {
      root = new Node(point, id);
      return;
    }

    int depth = 0;
    Node* cur = root;
    while (cur->id != id) {
      if (cur->point[depth % 2] <= point[depth % 2]) {
        if (cur->right == NULL) {
          cur->right = new Node(point, id);
        }
        cur = cur->right;
        depth++;
      } else {
        if (cur->left == NULL) {
          cur->left = new Node(point, id);
        }
        cur = cur->left;
        depth++;
      } 
    }
	}

  void searchHelper(std::vector<int>& ids, std::vector<float> target, float distanceTol, int depth, Node* node) {
    if (node == NULL) return;
      
    if (node->point[0] >= target[0] - distanceTol &&
        node->point[0] <= target[0] + distanceTol &&
        node->point[1] >= target[1] - distanceTol &&
        node->point[1] <= target[1] + distanceTol) {
        float distance = sqrt((node->point[0] - target[0]) * (node->point[0] - target[0]) + (node->point[1] - target[1]) * (node->point[1] - target[1]));
        if (distance <= distanceTol) {
          ids.push_back(node->id);
        }
    }

    if (target[depth % 2] - distanceTol < node->point[depth % 2]) {
      searchHelper(ids, target, distanceTol, depth + 1, node->left);
    }
    if (target[depth % 2] + distanceTol > node->point[depth % 2])  {
      searchHelper(ids, target, distanceTol, depth + 1, node->right);
    }
  }

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
    searchHelper(ids, target, distanceTol, 0, root);
		return ids;
	}
	

};




