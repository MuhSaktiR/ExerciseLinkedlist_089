#include <iostream>
#include <string>
using namespace std;
class Node {
public:
	int rollNumber;
	string name;
	Node* next;
};
class CircularLinkedList {
private:
	Node* LAST;
public:
	CircularLinkedList() {
		LAST = NULL;
	}
	void addNode();
	bool search(int rollno, Node** ramadhan, Node** sakti);
	bool listEmpty();
	bool delNode();
	void traverse();
};
void CircularLinkedList::addNode() {
	int rollno;
	string nm;
	cout << "\nMasukkan Nomor: ";
	cin >> rollno;
	cout << "\nMasukkan Nama: ";
	cin >> nm;

	//insert a node in the beginning of the list
	Node* newNode = new Node;//step 1
	newNode->rollNumber = rollno;//step 2
	newNode->name = nm;//step 2

	if (LAST == NULL || rollno <= LAST->rollNumber)
	{
		if ((LAST != NULL) && (rollno == LAST->rollNumber))
		{
			cout << "\nDuplikasi nomor tidak diinjinkan\n";
			return;
		}
		newNode->next = LAST;//step 3
		LAST = newNode;//step 4
		return;
	}

	//Between two nodes in the list
	Node* sakti = LAST->next; //step 1
	Node* ramadhan = NULL; //step 2
	while (sakti->next != NULL && sakti->next->rollNumber < rollno) //Step 3
	{
		ramadhan = sakti; //step 4
		sakti = sakti->next; //step 5
	}
	if (sakti->next != NULL && rollno == sakti->next->rollNumber) {
		cout << "\nDuplicate roll numbers not allowed" << endl;
		return;
	}
}

bool CircularLinkedList::search(int rollno, Node** ramadhan, Node** sakti) {
	*ramadhan = LAST->next;
	*sakti = LAST->next;
	while (*sakti != LAST) {
		if (rollno == (*sakti)->rollNumber) {
			return true;
		}
		*ramadhan = *sakti;
		*sakti = (*sakti)->next;
	}
	if (rollno == LAST->rollNumber) {
		return true;
	}
	else {
		return false;
	}
}
bool CircularLinkedList::listEmpty() {
	return LAST == NULL;
}

bool CircularLinkedList::delNode() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
		return false;
	}
	
	int rollno;
	cout << endl << "\nMasukkan nomor yang akan dihapus : ";
	cin >> rollno;

	Node* sakti, * ramadhan;
	if (search(rollno, &ramadhan, &sakti) == false)
		return false;
	
	if (sakti == LAST->next) {
		LAST->next = sakti->next;
	}

	ramadhan->next = sakti->next;
	if (sakti == LAST)
		LAST = LAST->next;
	LAST->next = sakti->next;
	delete sakti;
	return true;
}

void CircularLinkedList::traverse() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
	}
	else {
		cout << "\nRecords in the list are:\n";
		Node* currentNode = LAST->next;
		while (currentNode != LAST) {
			cout << currentNode->rollNumber << " " << currentNode->name << endl;
			currentNode = currentNode->next;
		}
		cout << LAST->rollNumber << " " << LAST->name << endl;
	}
}
int main() {
	CircularLinkedList obj;
	int rollno;

	while (true) {
		try {
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the records in the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your choice (1-4): ";
			char ch;
			cin >> ch;
			switch (ch) {
			case '1': {
				obj.addNode();
				break;
			}
			case '2': {
				if (obj.delNode() == false)
					cout << endl << "Data tidak ditemukan" << endl;
				else
					cout << endl << "Data dengan nomor mahasiswa " << rollno << " berhasil dihapus " << endl;
				break;
			}
			case '3': {
				obj.traverse();
				break;
			}
			case '4': {
				return 0;
			}
			default: {
				cout << "Invalid option" << endl;
				break;
			}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}