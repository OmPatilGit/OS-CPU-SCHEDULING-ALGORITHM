#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"

using namespace std;

struct Processes{
    int PID;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

vector<Processes> JobQueue;
queue<Processes> ReadyQueue;
vector<Processes> CompletedProcesses;

void Get_Processes(){
    int ProcessNum = 0;
    Processes ProcessInfo;
    cout << "Enter the Number of Processes : "; 
    cin >> ProcessNum;

    for (int i = 1; i <= ProcessNum; i++)
    {
        cout << "Enter the Burst Time for P" << i << " : ";
        cin >> ProcessInfo.BT;
        cout << "Enter the Arrival Time for P" << i << " : ";
        cin >> ProcessInfo.AT;
        ProcessInfo.PID = i;
        JobQueue.push_back(ProcessInfo);
    }
}

void Load_Processes(){
    int counter = 0;
    sort(JobQueue.begin(), JobQueue.end(), [](const Processes& a, const Processes& b){ return a.BT < b.BT; });
    
    for(auto& itr : JobQueue){
        ReadyQueue.push(itr);
    }
    
    while (!ReadyQueue.empty()){
        Processes pr = ReadyQueue.front();
        ReadyQueue.pop();
        counter = max(counter, pr.AT) + pr.BT; 
        pr.CT = counter;
        pr.TAT = pr.CT - pr.AT;
        pr.WT = pr.TAT - pr.BT;
        CompletedProcesses.push_back(pr);
    }
}

void CompletedProcess(){
    cout << "\nProcess Schedule Table:\n";
    cout << "-------------------------------------------------------------\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "-------------------------------------------------------------\n";
    
    for(auto& itr : CompletedProcesses){
        cout << itr.PID << "\t" << itr.AT << "\t" << itr.BT << "\t" 
             << itr.CT << "\t" << itr.TAT << "\t" << itr.WT << "\n";
    }
    cout << "-------------------------------------------------------------\n";
}

int main(){
    Get_Processes();
    Load_Processes();
    CompletedProcess();
    return 0;
}
