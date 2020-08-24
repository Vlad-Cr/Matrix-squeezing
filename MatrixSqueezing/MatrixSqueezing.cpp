#include <iostream>
#include <ctime>
using namespace std;

struct list {
	int i;
	int j;
	int value;
	list *next;
};

void init(int**, const int&);
void display(int**, const int&, const int&);
void squeezing_mas(int**, list*&, const int&);
void display(list*);
void restoration(int**, list*&, const int&);
void offset_diagonal(list*&, const int&);

int main() {

	int size;
	int counter = 0;

	do {
		cout << "Enter size of mas: ";
		cin >> size;
	} while (size < 1);

	int **mas = new int*[size];

	for (int i = 0; i < size; i++) {
		mas[i] = new int[size];
	}

	init(mas, size);
	cout << "<--MAS-->" << endl;
	display(mas, size, size);

	list *head = NULL;

	squeezing_mas(mas, head, size);

	for (int i = 0; i < size; i++) {
		delete[] mas[i];
	}
	delete[] mas;

	cout << "<--Squeezed MAS-->" << endl;
	display(head);

	offset_diagonal(head, size);

	cout << "<--Offset-->" << endl;
	display(head);

	mas = new int*[size];

	for (int i = 0; i < size; i++) {
		mas[i] = new int[size];
	}

	restoration(mas, head, size);

	cout << "<--Restoration-->" << endl;
	display(mas, size, size);

	for (int i = 0; i < size; i++) {
		delete[] mas[i];
	}
	delete[] mas;

	system("pause");
	return 0;
}

void init(int **mas, const int &size) {
	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mas[i][j] = rand() % 21 - 10 > 5 ? rand() % 10 : 0;
		}
	}
}

void display(list *head) {

	list *p = head;
	cout << "<i>";
	while (p) {
		cout.width(5);
		cout << p->i;
		p = p->next;
	}
	cout << endl;

	p = head;
	cout << "<j>";
	while (p) {
		cout.width(5);
		cout << p->j;
		p = p->next;
	}
	cout << endl;

	p = head;
	cout << "<v>";
	while (p) {
		cout.width(5);
		cout << p->value;
		p = p->next;
	}
	cout << endl;
}

void display(int **mas, const int &n, const int &m) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << mas[i][j] << "\t";
		}
		cout << endl;
	}
}

void squeezing_mas(int **mas, list *&head, const int &size) {
	list *p = head;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (mas[i][j] != 0) {
				if (head == NULL) {
					head = new list;
					head->i = i;
					head->j = j;
					head->value = mas[i][j];
					head->next = NULL;
					p = head;
				}
				else {
					p->next = new list;
					p = p->next;
					p->i = i;
					p->j = j;
					p->value = mas[i][j];
					p->next = NULL;
				}
			}
		}
	}
}

void restoration(int **mas, list *&head, const int &size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			list *p = head;
			bool flag = false;
			while (p) {
				if (i == p->i && j == p->j && flag == false) {
					mas[i][j] = p->value;
					flag = true;
				}
				p = p->next;
			}
			if (!flag) {
				mas[i][j] = 0;
			}
		}
	}
}

void offset_diagonal(list *&head, const int &size) {
	list *p = NULL;

	for (int j = 0; j < size; j++) {
		list *min = NULL;
		p = head;
		bool flag = false;
		while (p != NULL && flag == false) {
			if (p->j == j) {
				min = p;
				flag = true;
			}
			p = p->next;
		}
		if (flag) {
			while (p) {
				if (p->j == j) {
					if (min->value > p->value) {
						min = p;
					}
				}
				p = p->next;
			}

			flag = false;
			p = head;
			while (p->next != NULL && flag == false) {
				if (p->i == j && p->j == j) {
					int temp = p->value;
					p->value = min->value;
					min->value = temp;
					flag = true;
				}
				p = p->next;
			}

			if (!flag) {
				while (p->next) {
					p = p->next;
				}
				p->next = new list;
				p = p->next;
				p->i = j;
				p->j = j;
				p->value = min->value;
				p->next = NULL;

				p = head;
				if (head == min) {
					head = head->next;
					delete p;
				}
				else {
					while (p->next != min) {
						p = p->next;
					}
					p->next = min->next;
					delete min;
				}
			}
		}
	}
}
