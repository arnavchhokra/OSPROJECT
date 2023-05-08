#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void displayHelp()
{
    cout << "Commands:\n";
    cout<< "dir [path] - List the files and directories in the specified path\n";
    cout<< "md [path] - Create a new directory with the specified path\n";
    cout<< "rd [path] - Delete the directory with the specified path\n";
    cout<< "exit - Exit the program\n";
}

void listDirectory(string path)
{
    HANDLE hFind;
    WIN32_FIND_DATA data;
    string searchPath = path + "\\*.*";

    hFind = FindFirstFile(searchPath.c_str(), &data);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
            {
                cout << "<DIR> ";
            }
            else
            {
                cout << "      ";
            }
            cout << data.cFileName << endl;
        } while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
    else
    {
        cout << "Error: " << GetLastError() << endl;
    }
}

bool createDirectory(string path)
{
    if (CreateDirectory(path.c_str(), NULL))
    {
        cout << "Directory created: " << path << endl;
        return true;
    }
    else
    {
        cout << "Error: " << GetLastError() << endl;
        return false;
    }
}

bool deleteDirectory(string path)
{
    if (RemoveDirectory(path.c_str()))
    {
        cout << "Directory deleted: " << path << endl;
        return true;
    }
    else
    {
        cout << "Error: " << GetLastError() << endl;
        return false;
    }
}

int main()
{
    string command;
    string path;

    while (true)
    {
        cout << "> ";
        cin >> command;

        if (command == "dir")
        {
            cin >> path;
            listDirectory(path);
        }
        else if (command == "md")
        {
            cin >> path;
            createDirectory(path);
        }
        else if (command == "rd")
        {
            cin >> path;
            deleteDirectory(path);
        }
        else if (command == "exit")
        {
            break;
        }
        else if(command == "help")
        {
            displayHelp();
        }
        else{
            cout<<"Wrong input \n";
        }
    }

    return 0;
}
