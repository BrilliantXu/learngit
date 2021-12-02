#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <unordered_map>
#include <set>
#include <stack>
#include <math.h>
#include <queue>
using namespace std;

class Solution {
public:
    unordered_map <long long, int> map;
    bool isPerfectSquare(int num) {
        long long i = 0;
        long long temp = 0;
        while(++i) {
            if(temp <= num) {
                temp = i * i;  
                map[temp]++;              
            }else {
                break;
            }
        }
        if(map.find(num) != map.end()) return true;
        return false;
    }
};

int main() {
    Solution S1;
    S1.isPerfectSquare(16);
    return 0;
}