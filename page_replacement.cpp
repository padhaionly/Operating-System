#include <iostream>
using namespace std;

int find(int f[], int fs, int p) {
    for(int i=0;i<fs;i++) if(f[i]==p) return 1;
    return 0;
}

void fifo(int r[], int n, int fs) {
    int *f = new int[fs], pos=0, faults=0;
    for(int i=0;i<fs;i++) f[i] = -1;

    cout<<"FIFO\n";
    for(int i=0;i<n;i++){
        if(!find(f,fs,r[i])){
            f[pos] = r[i];
            pos = (pos+1)%fs;
            faults++;
        }
        for(int k=0;k<fs;k++) cout<<f[k]<<" ";
        cout<<"\n";
    }
    cout<<"Faults = "<<faults<<"\n\n";
}

void lru(int r[], int n, int fs) {
    int *f = new int[fs], *t = new int[fs], time=0, faults=0;
    for(int i=0;i<fs;i++) f[i] = -1;

    cout<<"LRU\n";
    for(int i=0;i<n;i++){
        int hit = -1;
        for(int j=0;j<fs;j++) if(f[j]==r[i]) hit=j;

        if(hit!=-1) t[hit] = time++;
        else{
            int pos = 0;
            for(int j=1;j<fs;j++) if(t[j]<t[pos]) pos=j;
            f[pos] = r[i];
            t[pos] = time++;
            faults++;
        }
        for(int k=0;k<fs;k++) cout<<f[k]<<" ";
        cout<<"\n";
    }
    cout<<"Faults = "<<faults<<"\n\n";
}

void optimal(int r[], int n, int fs) {
    int *f = new int[fs], faults=0;
    for(int i=0;i<fs;i++) f[i] = -1;

    cout<<"OPTIMAL\n";
    for(int i=0;i<n;i++){
        if(!find(f,fs,r[i])){
            int pos = 0, far = -1;
            for(int j=0;j<fs;j++){
                int next = 1000;
                for(int k=i+1;k<n;k++) if(r[k]==f[j]){ next=k; break; }
                if(next > far){ far=next; pos=j; }
            }
            f[pos] = r[i];
            faults++;
        }
        for(int k=0;k<fs;k++) cout<<f[k]<<" ";
        cout<<"\n";
    }
    cout<<"Faults = "<<faults<<"\n\n";
}

int main() {
    int fs, n, ch;
    cout<<"Frames: "; cin>>fs;
    cout<<"Ref size: "; cin>>n;

    int *r = new int[n];
    cout<<"Enter refs: ";
    for(int i=0;i<n;i++) cin>>r[i];

    cout<<"1 FIFO  2 LRU  3 OPT: ";
    cin>>ch;

    if(ch==1) fifo(r,n,fs);
    if(ch==2) lru(r,n,fs);
    if(ch==3) optimal(r,n,fs);

    return 0;
}