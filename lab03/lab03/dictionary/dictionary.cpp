#include "dictionary.h"
#include<cmath>
using namespace std;

Dictionary::Dictionary(){
    N = DICT_SIZE;
};


int Dictionary::hashValue(char key[]){
    int hashValue = 0;
    // compute hash
    int p = 31;
    long long int m = 64;
    double a = (sqrt(5) - 1) / 2;
    int n = sizeof(key) / sizeof(key[0]);
    int pow = 1;
    for(int i = 0; i < n; ++i) {
        hashValue += (key[i] - 'a' + 1) * pow;
        pow = pow * p;
    }
    double frac = (a * hashValue) - int(a * hashValue);
    hashValue = int(frac * m);
    return hashValue;
}

int Dictionary::findFreeIndex(char key[]){
    int hash=Dictionary::hashValue(key);
    int count=0;
    while(A[hash].key!=nullptr){
        hash=(hash+1)%N;
        count++;
        if(count>N) break;
    }
    if(A[hash].key==nullptr){
        // A[hash].key=key;
        return hash;
    }
    return -1;
}

struct Entry* Dictionary::get(char key[]){
    
    return NULL;
}

bool Dictionary::put(Entry e) {
    return false; // Dummy return
}

bool Dictionary::remove(char key[]){
    return false; // Dummy return
}
