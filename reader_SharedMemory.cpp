#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
    // Open existing shared memory (equivalent to shmget with existing segment)
    HANDLE hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        TEXT("SharedMemory")); // name of mapping object (equivalent to key)

    if (hMapFile == NULL)
    {
        cout << "Could not open file mapping object. Error: " << GetLastError() << endl;
        cout << "Make sure the writer process has created the shared memory first." << endl;
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

    // Read data from shared memory
    cout << "Data read from memory: " << str << endl;

    // Detach from shared memory (equivalent to shmdt)
    UnmapViewOfFile(str);

    // Close the handle
    CloseHandle(hMapFile);

    // Destroy shared memory (equivalent to shmctl with IPC_RMID)
    // Note: This should typically be done by the creator process
    // Uncomment if you want to destroy it here:
    // hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, TEXT("SharedMemory"));
    // if (hMapFile != NULL) {
    //     CloseHandle(hMapFile);
    // }

    return 0;
}

