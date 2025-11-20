#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
using namespace std;
int main()
{
    key_t key = ftok("shmfile", 65);                 // Create a unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Create shared memo
    char *str = (char *)shmat(shmid, NULL, 0);       // Attach
    cout << "Write data: ";
    cin.getline(str, 1024); // Write to shared memory
    cout << "Data written: " << str << endl;
    shmdt(str); // Detach
    return 0;
}