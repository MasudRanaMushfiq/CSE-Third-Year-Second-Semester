#include <iostream>
#include <vector>
using namespace std;

int main() {
    int numberOfProcesses;

    cout << "Enter number of processes: ";
    cin >> numberOfProcesses;

    vector<int> burstTime(numberOfProcesses);
    vector<int> remainingTime(numberOfProcesses);
    vector<int> waitingTime(numberOfProcesses, 0);
    vector<int> turnaroundTime(numberOfProcesses, 0);
    vector<int> completionTime(numberOfProcesses, 0);
    vector<bool> completed(numberOfProcesses, false);

    // Input burst times
    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "Enter burst time for P" << i + 1 << ": ";
        cin >> burstTime[i];
        remainingTime[i] = burstTime[i];
    }

    int currentTime = 0;
    int finished = 0;

    cout << "\nGantt Chart:\n|";

    while (finished < numberOfProcesses) {

        int shortestProcess = -1;
        int minimumRemaining = 1e9;

        // Find process with shortest remaining time
        for (int i = 0; i < numberOfProcesses; i++) {
            if (!completed[i] && remainingTime[i] < minimumRemaining && remainingTime[i] > 0) {
                minimumRemaining = remainingTime[i];
                shortestProcess = i;
            }
        }

        // Run process for 1 unit time
        remainingTime[shortestProcess]--;
        currentTime++;

        cout << " P" << shortestProcess + 1 << " |";

        // If process finishes
        if (remainingTime[shortestProcess] == 0) {
            completed[shortestProcess] = true;
            finished++;

            completionTime[shortestProcess] = currentTime;
            turnaroundTime[shortestProcess] = completionTime[shortestProcess];
            waitingTime[shortestProcess] = turnaroundTime[shortestProcess] - burstTime[shortestProcess];
        }
    }

    // Output
    cout << "\n\nProcess\tBT\tCT\tWT\tTAT\n";

    double totalWT = 0, totalTAT = 0;

    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "P" << i + 1 << "\t"
             << burstTime[i] << "\t"
             << completionTime[i] << "\t"
             << waitingTime[i] << "\t"
             << turnaroundTime[i] << endl;

        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    cout << "\nAverage Waiting Time: " << totalWT / numberOfProcesses << endl;
    cout << "Average Turnaround Time: " << totalTAT / numberOfProcesses << endl;

    return 0;
}

