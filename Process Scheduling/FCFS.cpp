#include <iostream>

using namespace std;

struct Process
{
    int pid;
    int burst;
    int arrival;
    int waiting;
    int turnaround;
};

void find_waiting(Process procs[], int n_proc, int service[]);
void find_turnaround(Process procs[], int n_proc);

int main()
{
    int i;
    int n_proc;
    cout << "Enter no. of processes : ";
    cin >> n_proc;

    Process procs[n_proc];
    for (i = 0; i < n_proc; i++)
    {
        procs[i].pid = i + 1;
        cout << "Enter burst time of process " << i << ": ";
        cin >> procs[i].burst;
        cout << "Enter arrival time of process " << i << ": ";
        cin >> procs[i].arrival;
    }

    int service[n_proc], total_waiting = 0, total_turnaround = 0;

    find_waiting(procs, n_proc, service);
    find_turnaround(procs, n_proc);

    for (i = 0; i < n_proc; i++)
    {
        total_turnaround += procs[i].turnaround;
        total_waiting += procs[i].waiting;
    }

    for (i = 0; i < n_proc - 1; i++)
    {
        cout << service[i] << "-" << service[i + 1] << ": " << procs[i].pid << ", ";
    }
    cout << endl;

    cout << "Avg turnaround time :" << total_turnaround / n_proc << endl;
    cout << "Avg waiting time :" << total_waiting / n_proc << endl;

    return 0;
}

void find_waiting(Process procs[], int n_proc, int service[])
{
    service[0] = 0;
    procs[0].waiting = 0;
    for (int i = 1; i < n_proc; i++)
    {
        service[i] = service[i - 1] + procs[i-1].burst;
        procs[i].waiting = service[i] - procs[i].arrival;

        if (procs[i].waiting < 0)
            procs[i].waiting = 0;
    }

    int wait[n];
    for (int i = 0; i < n; i++)
        wait[i] = 0;
    for (int i = 1; i < n; i++)
    {
        int x = wait[i - 1] + arrival[i - 1] + burst[i - 1];
        if (x > arrival[i])
        {
            wait[i] = x - arrival[i];
        }
    }
}

void find_turnaround(Process procs[], int n_proc)
{
    for (int i = 0; i < n_proc; i++)
    {
        procs[i].turnaround = procs[i].waiting + procs[i].burst;
    }
}