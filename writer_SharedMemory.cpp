#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
    // Create shared memory (equivalent to shmget with IPC_CREAT)
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,  // use paging file (equivalent to creating new segment)
        NULL,                  // default security
        PAGE_READWRITE,        // read/write access (equivalent to 0666)
        0,                     // maximum object size (high-order DWORD)
        1024,                  // maximum object size (low-order DWORD) - 1024 bytes
        TEXT("SharedMemory")); // name of mapping object (equivalent to key from ftok)

    if (hMapFile == NULL)
    {
        cout << "Could not create file mapping object. Error: " << GetLastError() << endl;
        return 1;
    }

    // Map the shared memory into this process's address space (equivalent to shmat)
    char *str = (char *)MapViewOfFile(
        hMapFile,              // handle to map object
        FILE_MAP_ALL_ACCESS,   // read/write permission
        0,
        0,
        1024);

    if (str == NULL)
    {
        cout << "Could not map view of file. Error: " << GetLastError() << endl;
        CloseHandle(hMapFile);
        return 1;
    }

    // Write to shared memory
    cout << "Write data: ";
    cin.getline(str, 1024);
    cout << "Data written: " << str << endl;

    // Detach from shared memory (equivalent to shmdt)
    UnmapViewOfFile(str);

    // Close the handle
    CloseHandle(hMapFile);

    return 0;
}

