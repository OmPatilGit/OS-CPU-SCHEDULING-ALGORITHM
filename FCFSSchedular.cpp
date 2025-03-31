#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Processes {
    int PID;
    int ArrivalTime;
    int BurstTime;
    int CompletionTime;
    int TAT;
    int WT;
};


vector<Processes> ProcessRecord;

bool SortByAT(const Processes &pr1, const Processes &pr2) {
    return pr1.ArrivalTime < pr2.ArrivalTime;
}

void Load_Processes() {
    int ProcessNum;
    cout << "Enter the number of processes: ";
    cin >> ProcessNum;

    if (ProcessNum <= 0) 
        return;

    for (int i = 0; i < ProcessNum; i++) {
        Processes pr;
        pr.PID = i + 1; 
        cout << "Enter Burst Time for P" << pr.PID << ": ";
        cin >> pr.BurstTime;
        cout << "Enter Arrival Time for P" << pr.PID << ": ";
        cin >> pr.ArrivalTime;
        ProcessRecord.push_back(pr);
    }
}

void Execute_Process() {
    sort(ProcessRecord.begin(), ProcessRecord.end(), SortByAT);

    int Timer = 0;
    int total_TAT = 0, total_WT = 0;

    for (auto &p : ProcessRecord) {
        
        if (Timer < p.ArrivalTime) {
            Timer = p.ArrivalTime;
        }

        p.CompletionTime = Timer + p.BurstTime;
        p.TAT = p.CompletionTime - p.ArrivalTime;  
        p.WT = p.TAT - p.BurstTime;  
        Timer = p.CompletionTime;
        total_TAT += p.TAT;
        total_WT += p.WT;
    }

    cout << "\nProcess Execution Order (FCFS):\n";
    for (auto &p : ProcessRecord) {
        cout << "| P" << p.PID << " | ";
    }
    cout << "\n\nProcess Info:\n";
    cout << "--------------------------------------------------\n";
    cout << "PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    cout << "--------------------------------------------------\n";
    for (auto &p : ProcessRecord) {
        cout << "P" << p.PID << "\t" << p.ArrivalTime << "\t" << p.BurstTime
             << "\t" << p.CompletionTime << "\t\t" << p.WT
             << "\t" << p.TAT << "\n";
    }


    cout << "\nAverage Waiting Time: " << (float)total_WT / ProcessRecord.size() << " ms";
    cout << "\nAverage Turnaround Time: " << (float)total_TAT / ProcessRecord.size() << " ms\n";
}

int main() {
    Load_Processes();
    Execute_Process();
    return 0;
}
