#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include	<string>
#include    "Student.h"
#include	<iomanip>

using namespace std;

bool readFile(const char *, BST *);
int menu();
bool duplicateID(BTNode* cur, Student student);

int main() {

	int choice,order,source;
	BST* tree1 = new BST();
	
	do
	{
		choice = menu();

		if (choice == 1)
		{
			cout << "\n*****Read File*****\n";
			(readFile("student.txt", tree1));
			system("pause");
		}
		else if (choice == 2)
		{
			cout << "\n*****Print deepest Node(s)*****\n";
			if (!tree1->deepestNodes()) cout << "The tree is empty!!" << endl;
			system("pause");
		}
		else if (choice == 3)
		{

			cout << "\n*****Display Output*****\n\n";
			cout << "\nChoose order to display the output (1 - Ascending / 2 - Descending): ";
			
			//Error handling for order input
			if (cin >> order && (order == 1 || order == 2)) {
				// Check the validation of  cin
				char c;
				if (cin.get(c) && c != '\n') {//if the cin can get the c and then the c is not the '\n', means has character left in the input buffer, so print invalid message  
					cout << "\n------------------------------------------------------\n";
					cout << "| Invalid Order! Only order 1 and 2 can be selected! |\n";
					cout << "------------------------------------------------------\n\n";
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					system("pause");
					continue;
				}
			}
			else {
				cout << "\n------------------------------------------------------\n";
				cout << "| Invalid Order! Only order 1 and 2 can be selected! |\n";
				cout << "------------------------------------------------------\n\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("pause");
				continue;
			}
			cout << "\nChoose source to display the output (1 - Screen / 2 - File): ";
			//Error handling for source input
			if (cin >> source && (source == 1 || source == 2)) {
				// Check the validation of  cin
				char c;
				if (cin.get(c) && c != '\n') {//if the cin can get the c and then the c is not the '\n', means has character left in the input buffer, so print invalid message  
					cout << "\n--------------------------------------------------------\n";
					cout << "| Invalid Source! Only source 1 and 2 can be selected! |\n";
					cout << "--------------------------------------------------------\n\n";
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					system("pause");
					continue;
				}
			}
			else {
				cout << "\n--------------------------------------------------------\n";
				cout << "| Invalid Source! Only source 1 and 2 can be selected! |\n";
				cout << "--------------------------------------------------------\n\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("pause");
				continue;
			}
			cout << endl;
			tree1->display(order, source);
			cout << endl << endl;
			system("pause");
		}
		else if (choice == 4)
		{
			BST t2;
			Student stud;
			cout << "\n*****Print Clone Subtree*****\n";
			cout << "\nPlease insert the student id that you want to clone: ";

			// Attempt to read an integer
			if (cin >> stud.id) {
				// Check the validation of  cin
				char c;
				if (cin.get(c) && c != '\n') {//if the cin can get the c and then the c is not the '\n', means has character left in the input buffer, so print invalid message 
					cout << "Invalid input. Please make sure the student id is an integer." << endl << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					system("pause");
					continue;
				}
			}
			else {
				cout << "Invalid input. Please make sure the student id is an integer." << endl << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("pause");
				continue;
			}

			if (!t2.CloneSubtree(*tree1, stud)) cout << "\nCannot clone subtree!!!" << endl << endl;
			else
			{
				cout << endl << endl;
				cout << "-------------------------" << endl;
				cout << "||   Pre-order of t1:   ||" << endl;;
				cout << "-------------------------" << endl;;
				tree1->preOrderPrint();
				cout << "----------------------------------------------------\n";
				cout << endl << endl;
				cout << "-------------------------" << endl;
				cout << "||   Pre-order of t2:   ||" << endl;
				cout << "-------------------------" << endl;;
				t2.preOrderPrint();
				t2.delete_t2(t2.root);
			}
			system("pause");

		}
		else if (choice == 5)
		{
			cout << "\n*****Print Level Node(s)*****\n";
			if (!tree1->printLevelNodes()) cout << "\nThe tree is empty!!" << endl;
			system("pause");
		}
		else if (choice == 6) 
		{
			cout << "\n*****Print External Path(s)*****";
			if (!tree1->printPath())
				cout << "Unable to print path.\n\n";
			cout << endl;
			system("pause");
		}

	} while (choice != 7);
	
	delete tree1;
	return 0;
}


bool readFile(const char* filename, BST* t1) {
	Student stu;
	ifstream input;
	//input.open("student.txt");
	input.open("student2.txt");//another version of student information, better to perform functions and features from the program
	// Special case : Unable find the file
	if (!input.is_open()) {
		cout << "\n\n Unable to open file";
		return false;
	}
	string temp;
	int data = 0;
	bool insert = false;
	while (getline(input, temp)) {
		if (temp.substr(0, 13) == "Student Id = ") {
			stu.id = stoi(temp.substr(13, temp.length() - 13));
		}
		else if (temp.substr(0, 7) == "Name = ") {
			strcpy(stu.name, temp.substr(7, temp.length() - 7).c_str());
		}
		else if (temp.substr(0, 10) == "Address = ") {
			strcpy(stu.address, temp.substr(10, temp.length() - 10).c_str());
		}
		else if (temp.substr(0, 6) == "DOB = ") {
			strcpy(stu.DOB, temp.substr(6, temp.length() - 6).c_str());
		}
		else if (temp.substr(0, 15) == "Phone Number = ") {
			strcpy(stu.phone_no, temp.substr(15, temp.length() - 15).c_str());
		}
		else if (temp.substr(0, 9) == "Course = ") {
			strcpy(stu.course, temp.substr(9, temp.length() - 9).c_str());
		}
		else if (temp.substr(0, 7) == "CGPA = ") {
			stu.cgpa = stod(temp.substr(7, temp.length() - 7));
			insert = true;
		}
		if (insert) {
			//Check if the student is empty
			if (t1->empty()) {
				t1->insert(stu);
				data++;
			}
			else {
				if (!duplicateID(t1->root, stu)) { //Check the student ID is duplicated or not
					t1->insert(stu);
					data++;
				}
				else {
					cout << "\n" << stu.name << " with student ID " << stu.id << " is already exists in BST!!\n";
				}
			}
			insert = false;
		}
	}
	if (data == 0) {
		cout << "\n\nPlease check data format and redundancy of student\n";
	}
	else {
		cout << "\nSuccessful read data into BST\n";
	}
	cout << endl;
	cout << "====================================" << endl;
	cout << "|| Total " << data << " records save into BST ||" << endl;
	cout << "====================================" << endl << endl;
	return true;
}

bool duplicateID(BTNode* cur, Student student) {
	if (student.id == cur->item.id) { // Return to true if have the same student ID
		return true;
	}
	else if (student.id > cur->item.id && cur->right != NULL) { // Check right side when student ID smaller than cur->item.id and right side is not equal null
		return duplicateID(cur->right, student);
	}
	else if (student.id < cur->item.id && cur->left != NULL) { // Check left side when student ID greater than cur->item.id and left side is not equal null
		return duplicateID(cur->left, student);
	}
	return false;
}


int menu() {
	int option;
	system("cls");
	cout << endl;
	cout << "==========================" << endl;
	cout << "||         Menu         ||" << endl;
	cout << "==========================" << endl;
	cout << "(1) Read Data to BST\n";
	cout << "(2) Print Deepest Nodes\n";
	cout << "(3) Display Student\n";
	cout << "(4) Clone Subtree\n";
	cout << "(5) Print Level Nodes\n";
	cout << "(6) Print Path\n";
	cout << "(7) Exit\n";
	cout << "\nEnter your choice: ";

	bool a = true;
	while (a) 
	{
		if (cin >> option && (option >= 1 && option <= 7)) {
			// Check the validation of  cin
			char c;
			if (cin.get(c) && c == '\n') {//if the cin remain the '\n' only means true, if cin remain the other character means false 
				a = false; // valid cin and exit the loop
			}
			else {
				cout << "\n\nInvalid input !";
				cout << "\nThe input should be integers from 1 to 7 only.";
				cout << "\nKindly enter your choice again: ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		else {
			cout << "\n\nInvalid input !";
			cout << "\nThe input should be integers from 1 to 7 only.";
			cout << "\nKindly enter your choice again: ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
	}
	cout << endl;
	return option;
}


