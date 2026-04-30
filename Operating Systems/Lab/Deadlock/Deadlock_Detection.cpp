#include <iostream>
using namespace std;

int main() {
    int processes, resources;

    cout << "Enter number of processes: ";
    cin >> processes;

    cout << "Enter number of resources: ";
    cin >> resources;

    int allocation[10][10], request[10][10];
    int available[10];

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input Request Matrix
    cout << "\nEnter Request Matrix:\n";
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> request[i][j];
        }
    }

    // Input Available Resources
    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < resources; i++) {
        cin >> available[i];
    }

    bool finished[10] = {false};
    int work[10];

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int completed = 0;

    while (completed < processes) {
        bool found = false;

        for (int i = 0; i < processes; i++) {

            if (!finished[i]) {
                bool canProceed = true;

                for (int j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }

                    finished[i] = true;
                    found = true;
                    completed++;
                }
            }
        }

        if (!found) {
            break; // no progress → possible deadlock
        }
    }

    // Check deadlock
    bool deadlock = false;

    cout << "\nUnfinished Processes: ";

    for (int i = 0; i < processes; i++) {
        if (!finished[i]) {
            cout << "P" << i << " ";
            deadlock = true;
        }
    }

    if (deadlock)
        cout << "\n\nSystem is in DEADLOCK state.\n";
    else
        cout << "\n\nNo Deadlock detected. System is SAFE.\n";

    return 0;
}


/*

Example 1 — SAFE State (NO Deadlock)
Process: 03
Resources: 03


Allocation
Process	A	B	C
P0	0	1	0
P1	2	0	0
P2	3	0	2
Request Matrix

| Process | A | B | C |
|--------|---|---|
| P0 | 0 | 0 | 0 |
| P1 | 1 | 0 | 0 |
| P2 | 0 | 0 | 0 |

Step reasoning


Available
A = (3, 3, 2)

Safe Sequence: P0 → P1 → P2
System is SAFE (NO deadlock)

*/

