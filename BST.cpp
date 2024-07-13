#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

//*************(b)*******************


bool BST::deepestNodes() {
	if (empty())  return false; //Special Case: Check if the Tree is empty	
	cout << "\nThe deepest nodes with student ID : \n";
	printNodes(root, heightOfTree(root));
	cout << endl << endl;
	return true;
}

void BST::printNodes(BTNode* cur, int height)
{
	if (cur == NULL) return;
	if (height == 1) cout << cur->item.id << " ";
	else if (height > 1)
	{
		printNodes(cur->left, height - 1);;
		printNodes(cur->right, height - 1);
	}
} 

int BST::heightOfTree(BTNode* cur) {
	if (empty()) return 0; //Special case : Check if the Tree is empty
	// declare left side Height as lHeight and right side Height to rHeight
	int lHeight = 0, rHeight = 0;
	//Normal case
	if (cur->left != NULL) {
		lHeight = heightOfTree(cur->left);
	}
	if (cur->right != NULL) {
		rHeight = heightOfTree(cur->right);
	}
	return max(lHeight, rHeight) + 1;
}

int BST::max(int right, int left) { //Compare both side of the tree
	int height = 0;
	if (right < left) {
		height = left;
	}
	else if (right > left) {
		height = right;
	}
	else {
		height = right = left;
	}
	return height;
}
//  **********(c)**************


//For printing ascending in file or screen
void BST::AscOrderPrint(BTNode* cur, ostream& file) {
	if (cur == NULL) return;
	AscOrderPrint(cur->left, file);
	file << "\nStudent " << ++i;
	cur->item.print(file);
	AscOrderPrint(cur->right, file);
}

//For printing descending in file or screen
void BST::DesOrderPrint(BTNode* cur, ostream& file) {
	if (cur == NULL) return;
	DesOrderPrint(cur->right, file);
	file << "\nStudent " << ++i;
	cur->item.print(file);
	DesOrderPrint(cur->left, file);
}

bool BST::display(int order, int source) {
	ofstream write;
	write.open("student-info.txt");

	//Error handling
	if (root == NULL)
	{
		cout << "---------------------------------------\n";
		cout << "| Unable to Print. The tree is empty! |\n";
		cout << "---------------------------------------";
		write.close();
		return false;
	}

	//Print in ascending order in screen
	if ((order == 1) && (source == 1))
	{
		i = 0;
		cout << "-----------------------\n";
		cout << "| Student Information |\n";
		cout << "-----------------------\n";
		AscOrderPrint(root,cout);
		write.close();
		return true;
	}
	//Print in descending order in screen
	else if ((order == 2) && (source == 1))
	{
		i = 0;
		cout << "-----------------------\n";
		cout << "| Student Information |\n";
		cout << "-----------------------\n";
		DesOrderPrint(root, cout);
		write.close();
		return true;
	}
	//Print in ascending order in file
	else if ((order == 1) && (source == 2))
	{
		i = 0;
		cout << "---------------------------------\n";
		cout << "| Display successfully in File! |\n";
		cout << "---------------------------------\n\n\n";
		write << "-----------------------\n";
		write << "| Student Information | \n";
		write << "-----------------------\n";
		AscOrderPrint(root, write);//pass root and file
		write.close();
		return true;
	}
	//Print in descending order in file
	else if ((order == 2) && (source == 2))
	{
		i = 0;
		cout << "---------------------------------\n";
		cout << "| Display successfully in File! |\n";
		cout << "---------------------------------\n\n\n";
		write << "-----------------------\n";
		write << "| Student Information | \n";
		write << "-----------------------\n";
		DesOrderPrint(root, write);//pass root and file
		write.close();
		return true;
	}
	write.close();
	return false;
}

//*************(d)*******************
bool BST::CloneSubtree(BST t1, type item)
{
	if (t1.empty() || t1.root == NULL) 
	{
		cout << "\nTree is empty. Please insert the node first!!" << endl;
		return false;
	}
	
	return CloneSubtree2(t1.root, item); //normal case and return the value from CloneSubtree2
}

bool BST::CloneSubtree2(BTNode* cur, type item)
{
	if (cur == NULL) return false;
	if (cur->item.compare2(item))
	{
		CloneSubtree3(cur);
		return true;
	}
	
	bool check = CloneSubtree2(cur->left, item);
	bool check2 = CloneSubtree2(cur->right, item);
	return check || check2;
}

void BST::CloneSubtree3(BTNode* cur)
{
	if (cur == NULL) return ;
	insert(cur->item);
	if (cur->left != NULL) CloneSubtree3(cur->left);
	if (cur->right != NULL) CloneSubtree3(cur->right);
}

void BST::delete_t2(BTNode* cur)//delete the node in t2
{
	if (cur == NULL) return;

	delete_t2(cur->left);
	delete_t2(cur->right);

	free(cur);

}

//***********(e)*****************

bool BST::printLevelNodes()
{

	if (empty()) return false;
	else
	{
		cout <<endl;
		for (int i = 1; i <= heightOfTree(root); i++)
		{
			cout << "Level " << i << " nodes: ";
			printNodes(root, i);
			cout << endl;
		}
		cout << endl;
	}
	return true;
}


// *********(f)**********
bool BST::printPath() {
	// Special case 1
	if (root == NULL) {
		cout << "\n\nUnable to print external path for an empty binary search tree.\n\n";
		return false;
	}

	// Special case 2
	if (count == 1) {
		cout << "\n\nUnable to print external path since the binary search tree has only a root.\n";
		return false;
	}



	// Normal case
	BTNode* cur = root;
	BTNode* tmp;
	Queue leaf;
	int n = 1;

	// Find and store the leaf node(s)
	findLeaf(root, leaf);

	cout << "\n\nBelow are all the external paths for the tree:\n\n";

	// Print out all external path(s)
	while (!leaf.empty()) {
		cout << "External Path " << n << ":\t";
		leaf.dequeue(tmp);
		printPath2(cur, tmp);
		cout << endl;
		n++;
	}

	return true;
}

// Traverse the tree to search for leaf node(s) in the queue and print them in preorder manner
void BST::printPath2(BTNode* cur, BTNode* leafNode) {
	if (cur == NULL) return;
	cout << cur->item.id << "\t";
	if (cur->item.id > leafNode->item.id)
		printPath2(cur->left, leafNode);
	else
		printPath2(cur->right, leafNode);
}


void BST::findLeaf(BTNode* cur, Queue& leaf) {
	if (cur == NULL) return;

	if (cur->left == NULL && cur->right == NULL) {
		leaf.enqueue(cur); // store the address value of leaf node(s) in a queue
	}

	findLeaf(cur->left, leaf);
	findLeaf(cur->right, leaf);
}







