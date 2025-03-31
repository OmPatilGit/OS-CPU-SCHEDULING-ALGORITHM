#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct ProcessData
{
    int ProcessID;
    int ArrivalTime; 
    int BurstTime; 
    int RemainingTime; 
    int CompletionTime;
};

struct ProcessInfo
{
    int PID; 
    int AT; 
    int TAT;
    int WT;
};

vector<ProcessData> ProcessList;
vector<ProcessInfo> Operations;
queue<ProcessData> ReadyQueue;
int Quantum;

void Load_Processes()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> Quantum;
    
    for (int i = 0; i < n; i++)
    {
        ProcessData p;
        p.ProcessID = i + 1;
        cout << "Enter Arrival Time P" << i + 1 << ": ";
        cin >> p.ArrivalTime;
        cout << "Enter Burst Time P" << i + 1 << ": ";
        cin >> p.BurstTime;
        p.RemainingTime = p.BurstTime;
        ProcessList.push_back(p);
    }
}

bool SortByAT(ProcessData& a, ProcessData& b){
    return a.ArrivalTime < b.ArrivalTime;
}

void Execute_Processes()
{
    int Time = 0;
    sort(ProcessList.begin(), ProcessList.end(), SortByAT);

    for (auto &p : ProcessList){
        ReadyQueue.push(p);
    }

    while (!ReadyQueue.empty())
    {
        ProcessData p = ReadyQueue.front();
        ReadyQueue.pop();

        if (p.RemainingTime > Quantum)
        {
            Time += Quantum;
            p.RemainingTime -= Quantum;
            ReadyQueue.push(p);
        }
        else
        {
            Time += p.RemainingTime;
            p.RemainingTime = 0;
            p.CompletionTime = Time;
            ProcessInfo pi;
            pi.PID = p.ProcessID;
            pi.AT = p.ArrivalTime;
            pi.TAT = p.CompletionTime - pi.AT;
            pi.WT = pi.TAT - p.BurstTime;
            Operations.push_back(pi);
        }
    }
}

void Print_Processes()
{
    cout << "\nProcess Table:\n";
    cout << "--------------------------------------\n";
    cout << "| PID | AT  | TAT | WT  |\n";
    cout << "--------------------------------------\n";
    
    for (auto &itr : Operations)
    {
        cout << "| " << itr.PID << "   | " << itr.AT << "   | " << itr.TAT << "   | " << itr.WT << "   |\n";
    }
    
    cout << "--------------------------------------\n";
}

int main()
{
    Load_Processes();
    Execute_Processes();
    Print_Processes();
    return 0;
}
