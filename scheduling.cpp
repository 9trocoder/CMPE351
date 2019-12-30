#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;


void fcfs(struct node* header);
void sjfnp(struct node* header);
void pnp(struct node* header);
void sm(struct node* header);
void pm(struct node* header);
void npm(struct node* header);
void sr(struct node* header);
void gd();

struct node {
	int pn;
	int bt;
	int at;
	int py;
	struct node *next;
};

int is_empty_node(struct node * header);
struct node * sort_list(struct node * header);
struct node * insert_back(struct node * header, int pn, int btm, int atm, int pyn);
struct node * check_completion(struct node * header, int count);
struct node * sort_priority(struct node * header);
struct node * create_node(int pn, int btm, int atm, int pyn);
struct node * delete_front(struct node * header);
int main()
{
	struct node *header = NULL;
	int pn;
	int btm;
	int atm;
	int pyn;
	ifstream fin;
	bool loop = true;
	fin.open("input.txt");


	if (fin.is_open()) {

		while (fin >> pn >> btm >> atm >> pyn) {
			header = insert_back(header, pn, btm, atm, pyn);
		}
	}
	fin.close();
	while (loop) {
		int option;
		cout << endl << "\t\t\tCPU SCHEDULER SIMULATOR" << endl;
		cout << endl << "1) Scheduling Method";
		cout << endl << "2) Preemptive Method";
		cout << endl << "3) Non-preemptive Mode";
		cout << endl << "4) Show Result";
		cout << endl << "5) End Program";
		cout << endl << "Option>";
		cin >> option;

		if (option == 1) {
			sm(header);
		}
		else if (option == 2) {
			pm(header);
		}
		else if (option == 3) {
			npm(header);
		}
		else if (option == 4) {
			sr(header);
		}
		else if (option == 5) {
			return 0;
		}
		else {
			cout << endl << "please enter from 1 - 5" << endl;
		}
	}
	cin.ignore();
	return 0;
}

void sm(struct node* header) {
	bool loop = true;
	int option = 12;
	char menu;
	while (loop) {
		cout<<"1)First Come, First Served Scheduling" << endl;
		cout<<	"2)Shortest - Job - First Scheduling" << endl;
		cout<<	"3)Priority Scheduling" << endl;
		cout<<	"4)Round - Robin Scheduling" << endl;
		cout<<	"Choose scheduling method" << endl;
		cout<<	"Option > ";
		cin >> option;
		if (option == 1) {
			fcfs(header);
			cout <<"\nFCFS scheduling completed, check output.txt file for result";
			loop = false;
		}
		else if (option == 2) {
			int choice;
			cout << "\n1-Shortest job first preemptive method";
			cout << "\n2->Shortest job first non-preemptive method" << endl;
			cin >> choice;
			if (choice == 1) {

				cout<<"i couldnt do it";
				loop = false;
			}
			else if (choice == 2) {
				sjfnp(header);
				loop = false;
			}

			else {
				cout << "invalid choice";
				continue;
			}
		}
		else if (option == 3) {
			int choice;
			cout <<"\n1-Priority scheling preemptive method";
			cout <<"\n2->Priority scheduling non-preemptive method" << endl;
			cin >> choice;
			if (choice == 1) {

				cout<<"i couldnt do it";
				loop = false;
			}
			else if (choice == 2) {
				pnp(header);
				loop = false;
			}
			else {
				cout << "please enter from 1 - 2";
				continue;
			}
		}
		else if (option == 4) {
			cout<<"i couldnt do it";
			loop = false;
		}
		else {
			cout << endl << "please enter from 1 - 4" << endl;
		}
	}
	cout <<"\nhit a key" << endl;
	cin >> menu;
}

void fcfs(struct node* header) {
	int waittime = 0;
	float average = 0;
	int pr;
	struct node *temp = header;
	ofstream fin("output.txt");
	fin <<"Scheuling Method: First Come First Served " << endl;
	fin <<"Process Waiting Times: " << endl;
	while (!(is_empty_node(temp))) {
		fin << "P" << pr << ": " << waittime << endl;
		average += waittime;
		waittime += (int)temp->bt - '0';

		temp = delete_front(temp);

		pr++;
	}
	fin << "Average waiting time " << average / (pr - 1);
}
void sjfnp(struct node* header) {

	struct node *temp = header;

	int wtm = 0, counter = 0;
	int pr = 1;
	float average = 0;
	temp = sort_list(temp);

	ofstream fin("output.txt");

	fin << "Scheuling Method: Shortest Job First(Non-Preemptive)" << endl;
	fin << "Process Waiting Times: " << endl;

	while (!(is_empty_node(temp))) {
		temp = check_completion(temp, counter);

		if (counter < (int)temp->at - '0') {
			counter++;
			continue;
		}
		fin << "P" << temp->pn << ": " << wtm << endl;
		average += wtm;
		wtm += (int)temp->bt - '0';

		counter += (int)temp->bt - '0';

		temp = delete_front(temp);


		pr++;
	}
	fin << "Average waiting time " << average / (pr - 1);

	cout << "Schduling done, check file output.txt for details";

}



void pnp(struct node* header) {

	struct node *temp = header;

	int wtm = 0, counter = 0;
	int pr = 1;
	float average = 0;
	temp = sort_priority(temp);
	ofstream fin("output.txt");

	fin << "Scheuling Method: Priority Scheduling(Non-Preemptive)" << endl;
	fin << "Process Waiting Times: " << endl;

	while (!(is_empty_node(temp))) {


		if (counter < (int)temp->at - '0') {
			counter++;
			continue;
		}


		fin << "P" << temp->pn << ": " << wtm << endl;
		average += wtm;
		wtm += (int)temp->bt - '0';

		counter += (int)temp->bt - '0';

		temp = delete_front(temp);


		pr++;
	}
	fin << "Average waiting time " << average / (pr - 1);

	cout << "Schduling done, check file output.txt for details";

}


int is_empty_node(struct node* header) {
	if (header == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
struct node* sort_list(struct node* header) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = temp->next;

	for (i = temp; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if ((int)(i->at) - '0' > (int)(j->at) - '0') {
				struct node* tempp = create_node(i->pn, i->bt, i->at, i->py);

				i->pn = j->pn;
				i->bt = j->bt;
				i->at = j->at;
				i->py = j->py;

				j->pn = tempp->pn;
				j->bt = tempp->bt;
				j->at = tempp->at;
				j->py = tempp->py;
			}

		}
	}
	struct node* tempp = temp;

	return temp;
}
struct node* insert_back(struct node* header, int pn, int btm, int atm, int pyn) {
	struct node* temp = create_node(pn, btm, atm, pyn);
	struct node* headerTemp;
	if (header == NULL) {
		header = temp;
		return header;
	}
	headerTemp = header;
	while (headerTemp->next != NULL)
		headerTemp = headerTemp->next;
	headerTemp->next = temp;
	return header;
}

struct node* delete_front(struct node* header) {
	struct node* temp;
	if (header == NULL)
		return header;

	temp = header;
	header = header->next;
	free(temp);

	return header;
}


struct node* check_completion(struct node* header, int counter) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = i->next;

	for (i = temp; i != NULL; i = i->next) {

		for (j = i->next; j != NULL; j = j->next) {

			if ((((int)(i->bt) - '0') > ((int)(j->bt) - '0')) &&
				(((int)(j->at) - '0') <= counter)) {
				struct node* tempp = create_node(i->pn, i->bt, i->at, i->py);

				i->pn = j->pn;
				i->bt = j->bt;
				i->at = j->at;
				i->py = j->py;

				j->pn = tempp->pn;
				j->bt = tempp->bt;
				j->at = tempp->at;
				j->py = tempp->py;
			}
		}
	}
	struct node* tempp = temp;
	return temp;
}

struct node* sort_priority(struct node* header) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = temp->next;
	for (i = temp; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if ((int)(i->py) - '0' > (int)(j->py) - '0') {
				struct node* tempp = create_node(i->pn, i->bt, i->at, i->py);
				i->pn = j->pn;
				i->bt = j->bt;
				i->at = j->at;
				i->py = j->py;

				j->pn = tempp->pn;
				j->bt = tempp->bt;
				j->at = tempp->at;
				j->py = tempp->py;

			}
		}
	}
	struct node* tempp = temp;
	return temp;
}



struct node* create_node(int pn, int btm, int atm, int pyn) {
	struct node *header = NULL;
	header = (struct node *) malloc(sizeof(node));
	header->pn = pn;
	header->bt = btm;
	header->at = atm;
	header->py = pyn;
	header->next = NULL;

	return header;
}
void pm(struct node* header) {

}

void npm(struct node* header) {

}

void sr(struct node* header) {

}

void gd() {

}
void pp(struct node* header) {

}
