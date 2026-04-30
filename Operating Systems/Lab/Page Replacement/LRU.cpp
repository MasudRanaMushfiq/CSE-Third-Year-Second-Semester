#include <iostream>
#include <vector>
using namespace std;

int main() {
    int numberOfPages, numberOfFrames;

    cout << "Enter number of pages: ";
    cin >> numberOfPages;

    vector<int> pageReference(numberOfPages);

    cout << "Enter page reference string:\n";
    for (int i = 0; i < numberOfPages; i++) {
        cin >> pageReference[i];
    }

    cout << "Enter number of frames: ";
    cin >> numberOfFrames;

    vector<int> frames(numberOfFrames, -1);
    vector<int> lastUsed(numberOfFrames, -1);

    int pageFaults = 0;

    cout << "\nFrame Status:\n";

    for (int i = 0; i < numberOfPages; i++) {
        int currentPage = pageReference[i];
        int found = -1;

        // check if page already exists
        for (int j = 0; j < numberOfFrames; j++) {
            if (frames[j] == currentPage) {
                found = j;
                break;
            }
        }

        if(found != -1) {
            // HIT → update last used time
            lastUsed[found] = i;
        }else{
            // PAGE FAULT
            pageFaults++;

            int lruIndex = -1;
            int minTime = 1e9;

            // find least recently used page
            for (int j = 0; j < numberOfFrames; j++) {
                if (frames[j] == -1) {
                    lruIndex = j;
                    break;
                }
                else if (lastUsed[j] < minTime) {
                    minTime = lastUsed[j];
                    lruIndex = j;
                }
            }

            frames[lruIndex] = currentPage;
            lastUsed[lruIndex] = i;
        }

        // print frame status
        cout << "After " << currentPage << " : ";
        for (int j = 0; j < numberOfFrames; j++) {
            if (frames[j] == -1)
                cout << "- ";
            else
                cout << frames[j] << " ";
        }
        cout << endl;
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;

    return 0;
}

/*

Enter number of pages: 7
Enter page reference string:
1 2 3 4 1 2 5
Enter number of frames: 3

Totall Page Fault: 7

*/

