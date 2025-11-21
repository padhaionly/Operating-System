#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
using namespace std;
sem_t wrt;
pthread_mutex_t mutex;
int readCount = 0;
int dataVar = 0;
void* writer(void* arg) {
sem_wait(&wrt);
dataVar++;
cout << "Writer wrote: " << dataVar << endl;
sem_post(&wrt);
return NULL;
}
void* reader(void* arg) {
pthread_mutex_lock(&mutex);
readCount++;
if (readCount == 1) sem_wait(&wrt);
pthread_mutex_unlock(&mutex);
cout << "Reader read: " << dataVar << endl;
sleep(1);
pthread_mutex_lock(&mutex);
readCount--;
if (readCount == 0) sem_post(&wrt);
pthread_mutex_unlock(&mutex);
return NULL;
}
int main() {
pthread_t r[5], w[5];
sem_init(&wrt, 0, 1);
pthread_mutex_init(&mutex, NULL);
for (int i = 0; i < 3; i++) pthread_create(&w[i], NULL, writer, NULL);
for (int i = 0; i < 3; i++) pthread_create(&r[i], NULL, reader, NULL);
for (int i = 0; i < 3; i++) pthread_join(w[i], NULL);
for (int i = 0; i < 3; i++) pthread_join(r[i], NULL);
sem_destroy(&wrt);
pthread_mutex_destroy(&mutex);
}
