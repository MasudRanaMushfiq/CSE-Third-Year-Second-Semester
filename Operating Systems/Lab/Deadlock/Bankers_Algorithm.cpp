#include <iostream>
using namespace std;

int main() {
    int processes, resources;

    cout << "Enter number of processes: ";
    cin >> processes;

    cout << "Enter number of resources: ";
    cin >> resources;

    int allocation[10][10], maximum[10][10], need[10][10];
    int available[10];

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input Maximum Matrix
    cout << "\nEnter Maximum Matrix:\n";
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> maximum[i][j];
        }
    }

    // Input Available Resources
    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < resources; i++) {
        cin >> available[i];
    }

    // Calculate Need Matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    bool finished[10] = {false};
    int safeSequence[10];
    int count = 0;

    int work[10];
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    // Safety Algorithm
    while (count < processes) {
        bool found = false;

        for (int i = 0; i < processes; i++) {

            if (!finished[i]) {
                bool canExecute = true;

                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT in a Safe State.\n";
            return 0;
        }
    }

    // Safe state output
    cout << "\nSystem is in a SAFE state.\nSafe Sequence: ";

    for (int i = 0; i < processes; i++) {
        cout << "P" << safeSequence[i];
        if (i != processes - 1) cout << " -> ";
    }

    cout << endl;

    return 0;
}


/*

Number of processes = 5
Number of resources = 3 (A, B, C)

Allocation Matrix
Process	A	B	C
P0	0	1	0
P1	2	0	0
P2	3	0	2
P3	2	1	1
P4	0	0	2

Maximum Matrix
Process	A	B	C
P0	7	5	3
P1	3	2	2
P2	9	0	2
P3	2	2	2
P4	4	3	3

Available Resources
A = 3, B = 3, C = 2

Need Matrix (Maximum - Allocation)
Process	A	B	C
P0	7	4	3
P1	1	2	2
P2	6	0	0
P3	0	1	1
P4	4	3	1

*/

