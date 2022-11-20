#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using LL = long long;
using namespace std;
using namespace std::chrono;


int main()
{
    vector <int> all;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10000000; i ++ )
    {
        all.push_back(rand());
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "消耗了："
         << duration.count() * 1.0 / 1000000 << " 秒" << endl;
    
    return 0;
}
