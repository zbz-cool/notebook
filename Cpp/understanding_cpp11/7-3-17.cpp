#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
vector<int> nums;
void Add(const int val) {
    auto print = [&] {
        for (auto s : nums) {
            cout << s << '\t';
        }
        cout << endl;
    };  
    
    // 传统 的 for 循环 方式
    for (auto i = nums.begin(); i != nums.end(); ++i) {
        *i = *i + val;
    }
    print();
    for_each(nums.begin(), nums.end(), bind2nd(plus<int>(), val));  // for_each 及内置仿函数
    print();
    transform(nums.begin(), nums.end(), nums.begin(), bind2nd(plus<int>(), val));  // 实际这里需要使用 STL 的一个变动性算法：transform
    print();
    for_each(nums.begin(), nums.end(), [=](int& i) { i += val; });  // 不过在 lambda 的支持下，我们还是可以只使用 for_each
    print();
}
int main() {
    for (int i = 0; i < 10; i++) {
        nums.push_back(i);
    }
    Add(10);
    return 1;
}