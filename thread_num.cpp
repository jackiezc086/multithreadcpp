#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <future>

using namespace std;
using namespace std::chrono;

using LL = long long;

LL calc(LL start, LL end){
    LL ret = 0;
    for (LL i = start; i <= end; i ++)
    {
        ret += i;
    }
    return ret;
}

int main()
{
    vector<future<LL>> task;
    int thread_num = thread::hardware_concurrency();
    // int thread_num = max(2, (int)thread::hardware_concurrency() - 2);
    // cout << thread::hardware_concurrency() << endl;
    LL n = 100000000;
    if (n < thread_num)
    {
        thread_num = 1;
    }
    LL div = n / thread_num;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < thread_num; i ++ )
    {
        if (i != thread_num - 1)
        {
            task.push_back(async(calc, div * i + 1, div * (i + 1)));
        }
        else 
        {
            task.push_back(async(calc, div * i + 1, n));
        }
    }
    LL ans = 0;
    for (int i = 0; i < thread_num; i ++ ){
        ans += task[i].get();
    }
    cout << ans << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "消耗了： "
         << duration.count() * 1.0 / 10000000 << " 秒" << endl;
    
    return 0;
}
