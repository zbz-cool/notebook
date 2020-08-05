#include <vector>
#include <algorithm>
using namespace std;
vector<int> nums;
vector<int> largeNums;
class LNums {
public:
    LNums(int u)
        : ubound(u) {
    }
    void operator()(int i) const {
        if (i > ubound)
            largeNums.push_back(i);
    }

private:
    int ubound;
};
void Above(int ubound) {  // 传统的 for 循环
    for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
        if (*itr >= ubound)
            largeNums.push_back(*itr);
    }
    for_each(nums.begin(), nums.end(), LNums(ubound));  // 使用仿函数
    for_each(nums.begin(), nums.end(), [=](int i) {     // 使用 lambda 函数 和 算法for_each
        if (i > ubound)
            largeNums.push_back(i);
    });
}
