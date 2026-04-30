#include <bits/stdc++.h>
using namespace std;

int main(){

    int n;
    cout << "Enter Process Number: ";
    cin>>n;

    vector<int> burst_time (n);
    vector<int> waiting_time (n, 0);
    vector<int> turne_around_time (n, 0);

    for(int i=0; i < n; i++){
        cout<<"Enter Burst Time For Process " << i+1<<": ";
        cin>>burst_time[i];
    }

    waiting_time[0] = 0;
    turne_around_time[0] = 0;

    for(int i=1; i<n; i++){
        waiting_time[i] = waiting_time[i-1] + burst_time[i-1];
        turne_around_time[i] = waiting_time[i] + burst_time[i];
    }

    double totall_waiting_time = 0, totall_turn_around_time = 0;

        cout<<"\nProcess\tBurst_time\tWaiting_Time\tTurn_Around_Time"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"p"<< i+1 << "\t" << burst_time[i] << "\t\t"  <<  waiting_time[i] << "\t\t"  << turne_around_time[i] << endl;
        totall_waiting_time += waiting_time[i];
        totall_turn_around_time += turne_around_time[i];
    }

    cout<< "\nAvarage Waiting Time: " << totall_waiting_time / n <<endl;
    cout<< "\nAvarage Turnaround Time: " << totall_turn_around_time / n <<endl;
}

