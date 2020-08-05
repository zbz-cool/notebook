// 返回容器中最小值和最大值。max_element(first,end,cmp);其中cmp为可选择参数!

#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
    return a < b;
}

int main() {
    int num[] = {2, 3, 1, 6, 4, 5};
    cout << "最小值是 " << *min_element(num, num + 6) << endl;
    cout << "最小值是 " << *min_element(num + 4, num + 6) << endl;

    cout << "最大值是 " << *max_element(num, num + 6) << endl;
    cout << "最小值是 " << *min_element(num, num + 6, cmp) << endl;
    cout << "最大值是 " << *max_element(num, num + 6, cmp) << endl;
    return 0;
}