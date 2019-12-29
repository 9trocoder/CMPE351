#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

struct Processing_data{
    int burst_time, arrival_time, priority;
};

int main (){
    Processing_data processing_datas[100];
    ifstream fin("input.txt");
    if(!fin) exit(1);

    Processing_data pd;
    int number_of_pd = 0;
    fin >> pd.burst_time;
    while(!(pd.burst_time == -1)){
        fin >> pd.arrival_time >> pd.priority;
        processing_datas[number_of_pd] = pd;
        number_of_pd++;
    }
    fin.close();



    return 0;
}
