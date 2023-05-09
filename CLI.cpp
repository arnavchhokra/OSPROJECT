#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

class Directory {
public:
    static void listDirectory(const string& path) {
        HANDLE hFind;
        WIN32_FIND_DATA data;
        string searchPath = path + "\\*.*";
        hFind = FindFirstFile(searchPath.c_str(), &data);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
                    cout << "<DIR> ";
                }
                else {
                    cout << "      ";
                }
                cout << data.cFileName << endl;
            } while (FindNextFile(hFind, &data));
            FindClose(hFind);
        }
        else {
            throw runtime_error("Error: Unable to list directory");
        }
    }

    static bool createDirectory(const string& path) {
        if (CreateDirectory(path.c_str(), NULL)) {
            cout << "Directory created: " << path << endl;
            return true;
        }
        else {
            throw runtime_error("Error: Unable to create directory");
        }
    }

    static bool deleteDirectory(const string& path) {
        if (RemoveDirectory(path.c_str())) {
            cout << "Directory deleted: " << path << endl;
            return true;
        }
        else {
            throw runtime_error("Error: Unable to delete directory");
        }
    }
};

class CommandLine {
public:
    static void displayHelp() {
        cout << "Commands:\n";
        cout << "dir [path] - List the files in the specified path\n";
        cout << "md [path] - Create a new directory in the specified path\n";
        cout << "rd [path] - Delete the directory of the specified path\n";
        cout << "exit - Exit the program\n";
    }

    static void run() {
        string command;
        string path;

        while (true) {
            cout << "> ";
            cin >> command;

            try {
                if (command == "dir") {
                    cin >> path;
                    Directory::listDirectory(path);
                }
                else if (command == "md") {
                    cin >> path;
                    Directory::createDirectory(path);
                }
                else if (command == "rd") {
                    cin >> path;
                    Directory::deleteDirectory(path);
                }
                else if (command == "exit") {
                    break;
                }
                else if (command == "help") {
                    displayHelp();
                }
                else {
                    cout << "Wrong input \n";
                }
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
            }
        }
    }
};

int main() {
    CommandLine::run();
    return 0;
}
