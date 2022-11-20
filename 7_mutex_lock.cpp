#include <iostream>
#include <thread>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

using LL = long long;

void sum_here(LL adder, LL& s)
{
    static std::mutex locker;
    {
        std::lock_guard<std::mutex> lk(locker); // RAII
        s += adder;
    }
}

void calc(LL start, LL end, LL& result){
    LL ret = 0;
    for (LL i = start; i <= end; i ++)
    {
        ret += i;
    }
    sum_here(ret, result);
}

int main()
{
    vector <thread> task;
    int thread_num = 10;
    LL n = 100000, result = 0;
    LL div = n / thread_num;
    for (int i = 0; i < thread_num; i ++ ){
        if (i != thread_num - 1){
            task.emplace_back(thread(calc, div * i + 1, div * (i + 1), ref(result)));
        } else { 
            task.emplace_back(thread(calc, div * i + 1, n, ref(result)));
        }
    }
    for (int i = 0; i < thread_num; i ++ ){
        task[i].join();
    }
    cout << result << endl;
    return 0;
}
