#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

		int		count;
		BTNode	*root;
		int i = 0;

		// print operation for BST (same as BT)					
		void preOrderPrint2(BTNode *);	// recursive function for preOrderPrint()
		void inOrderPrint2(BTNode *);	// recursive function for inOrderPrint()
		void postOrderPrint2(BTNode *);	// recursive function for postOrderPrint()

		// sample operation (extra functions) - same as BT
		void countNode2(BTNode *, int &);		// recursive function for countNode()
		bool fGS2(type, BTNode *);					// recursive function for findGrandsons(): to find the grandfather
		void fGS3(BTNode *, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found
		
		// basic functions for BST
		void insert2(BTNode *, BTNode *);		// recursive function for insert() of BST
		void case3(BTNode *);					// recursive function for remove()
		void case2(BTNode *, BTNode *);		// recursive function for remove()
		bool remove2(BTNode *, BTNode *, type);	// recursive function for remove()



		// basic functions for BST
		BST();
		bool empty();
		int size();
		bool insert (type);		// insert an item into a BST
		bool remove(type);			// remove an item from a BST
		
		// print operation for BST (same as BT)
		void preOrderPrint();			// print BST node in pre-order manner
		void inOrderPrint();			// print BST node in in-order manner
		void postOrderPrint();			// print BST node in post-order manner
		void topDownLevelTraversal();	// print BST level-by-level

		// sample operation (extra functions) - same as BT
		int countNode();		// count number of tree nodes
		bool findGrandsons(type);	// find the grandsons of an input father item

		//deepest function		
		bool deepestNodes();
		void printNodes(BTNode*, int);
		int heightOfTree(BTNode* cur);
		int max(int right, int left);

		//display function
		void AscOrderPrint(BTNode* cur, ostream& file);
		void DesOrderPrint(BTNode* cur, ostream& file);
		bool display(int order, int source);

		//clonesubtree function
		bool CloneSubtree(BST, type);
		bool CloneSubtree2(BTNode*, type);
		void CloneSubtree3(BTNode*);
		void delete_t2(BTNode*);

		// print level nodes function
		bool printLevelNodes();

		// printPath function
		bool printPath(); // Print all the external paths of the tree
		void printPath2(BTNode* cur, BTNode* leafNode); // Traverse the tree to search for leaf node(s) in the queue and print them in preorder manner
		void findLeaf(BTNode* cur, Queue& leaf); // Find and store the leaf node(s) in a queue

		
};




#endif