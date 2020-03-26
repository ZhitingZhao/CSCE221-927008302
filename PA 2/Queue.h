#ifndef Queue_h
#define Queue_h

#include <vector>
using namespace std;
template <typename T>
class Queue
{
public:
    Queue(){
        idx = 0;
    }
    void push(T data){
        vec.push_back(data);
        idx += 1;
    }
    void pop(){
        vec.erase(vec.begin());
        idx -= 1;
    }
    T front(){
        return vec.at(0);
    }
    int size(){
        return idx;
    }
private:
    vector <T> vec;
    int idx;
    
};

#endif /* Queue_h */

