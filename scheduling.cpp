#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

void printmessage() {

    int option;
    cout<<"\t\t\t"<<"CPU Scheduler Similator"<<endl;
    cout<<"1) Scheduling Method"<<endl;
    cout<<"2) Preemptive Mode"<<endl;
    cout<<"3) Non-preemptive Mode"<<endl;
    cout<<"4) Show Result"<<endl;
    cout<<"5) End Program"<<endl;
    cout<<"Option"<<endl;
    cin>>option;

}

int main (){
    int process_number;
    int burst_time;
    int arrival_time;
    int priority;
    struct node* start = NULL;

    ifstream fin("input.txt");
    if(!fin) exit(1);

    while(fin >> process_number >> arrival_time>> burst_time >> priority)
    {
        start = take_back(start, process_number, arrival_time, burst_time, priority);
    }
    fin.close();

    printmessage();

    return 0;
}


