#include <bits/stdc++.h>

using namespace std;

// Create & write file
void createFile() {
    char filename[100], content[1000];
    FILE *file;

    cout << "Enter file name (.txt): ";
    cin >> filename;

    file = fopen(filename, "w");
    if (file == NULL) {
        cout << "Error creating file!\n";
        return;
    }

    cout << "Enter content: ";
    cin.ignore(); //clear input buffer
    cin.getline(content, 1000);

    fputs(content, file);
    fclose(file);

    cout << "File created successfully.\n";
}

// Read file
void readFile() {
    char filename[100], ch;
    FILE *file;

    cout << "Enter file name: ";
    cin >> filename;

    file = fopen(filename, "r");
    if (file == NULL) {
        cout << "File not found!\n";
        return;
    }

    cout << "\nFile content:\n";
    while ((ch = fgetc(file)) != EOF) {
        cout << ch;
    }

    fclose(file);
}

// Delete file
void deleteFile() {
    char filename[100];

    cout << "Enter file name to delete: ";
    cin >> filename;

    if (remove(filename) == 0) { //remove to delette file
        cout << "File deleted successfully.\n";
    } else {
        cout << "Error deleting file.\n";
    }
}

// Copy file
void copyFile() {
    char source[100], destination[100], ch;
    FILE *src, *dest;

    cout << "Enter source file: ";
    cin >> source;

    cout << "Enter destination file: ";
    cin >> destination;

    src = fopen(source, "r");
    if (src == NULL) {
        cout << "Source file not found!\n";
        return;
    }

    dest = fopen(destination, "w");

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    cout << "File copied successfully.\n";
}

// Move file (rename)
void moveFile() {
    char source[100], destination[100];

    cout << "Enter source file: ";
    cin >> source;

    cout << "Enter new file name/location: ";
    cin >> destination;

    if (rename(source, destination) == 0) {
        //if same folder = file is renamed, if different folder path = file is moved
        cout << "File moved successfully.\n";
    } else {
        cout << "Error moving file.\n";
    }
}

// List .txt files (OS command)
void listFiles() {
    cout << "Listing .txt files:\n";
    system("dir *.txt"); // Windows (use "ls *.txt" for Linux)
}

int main() {
    int choice;

    while (true) {
        cout << "\n--- FILE OPERATIONS ---\n";
        cout << "1. Create File\n";
        cout << "2. Read File\n";
        cout << "3. Delete File\n";
        cout << "4. Copy File\n";
        cout << "5. Move File\n";
        cout << "6. List .txt Files\n";
        cout << "7. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createFile(); break;
            case 2: readFile(); break;
            case 3: deleteFile(); break;
            case 4: copyFile(); break;
            case 5: moveFile(); break;
            case 6: listFiles(); break;
            case 7: return 0;
            default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}

