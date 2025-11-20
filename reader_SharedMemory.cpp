#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
using namespace std;
int main()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666);
    char *str = (char *)shmat(shmid, NULL, 0);
    // Get existing segment
    cout << "Data read from memory: " << str << endl;
    shmdt(str); // Detach
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
    // Destroy shared memory
}