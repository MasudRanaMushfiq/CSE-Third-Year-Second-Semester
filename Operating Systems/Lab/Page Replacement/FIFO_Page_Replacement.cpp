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

    int pageFaults = 0, pageHits = 0;
    int pointer = 0;

    for (int i = 0; i < numberOfPages; i++) {
        int currentPage = pageReference[i];
        bool found = false;

        // check hit
        for (int j = 0; j < numberOfFrames; j++) {
            if (frames[j] == currentPage) {
                found = true;
                pageHits++;
                break;
            }
        }

        // page fault
        if (!found) {
            frames[pointer] = currentPage;
            pointer = (pointer + 1) % numberOfFrames;
            pageFaults++;
        }
    }

    cout << "\nPage Hits: " << pageHits << endl;
    cout << "Page Faults: " << pageFaults << endl;

    return 0;
}



/*

Input:
Pages = 7
Reference String = 7 0 1 2 0 3 0 4 2 3 0 3 2
Frames = 3

Output:
Page Hits: 2
Page Faults: 5

*/

