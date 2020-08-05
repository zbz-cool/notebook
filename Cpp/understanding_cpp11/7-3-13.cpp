#include <vector>
#include <algorithm>
using namespace std;
vector<int> nums;
vector<int> largeNums;
const int ubound = 10;
inline void LargeNumsFunc(int i) {
    if (i > ubound)
        largeNums.push_back(i);
}
void Above() {  // 传统 的 for 循环
    for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
        if (*itr >= ubound)
            largeNums.push_back(*itr);
    }
    for_each(nums.begin(), nums.end(), LargeNumsFunc);  // 使用 函数 指针
    for_each(nums.begin(), nums.end(), [=](int i) {     // 使用 lambda 函数 和 算法 for_each
        if (i > ubound)
            largeNums.push_back(i);
    });
}
