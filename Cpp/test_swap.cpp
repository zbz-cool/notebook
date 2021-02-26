#include <vector>
#include <string>
#include <iostream>

using namespace std;
#define LEN 100000

typedef struct VV {
    vector<int16_t> source;
}vv;

int main() {

    vv s[LEN], d[LEN];
    for (int i = 0; i < LEN;++i) {
        s[i].source.resize(LEN);
    }
    for (int i = 0; i < LEN; ++i) {
        d[i].source = std::move(s[i].source);
    }
}