/*
 * @Author: stone
 * @Date: 2019-08-20 17:01:45
 * @LastEditTime: 2019-08-21 13:32:28
 * @LastEditors: stone
 * @Description: 
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void nextPermutation(vector<int>& nums)
{
    // int length = nums.size();
    //
    auto begin = nums.begin();
    auto last = prev(nums.end());
    auto start = last;
    for (; start > begin; start--) {
        if (*start > *(prev(start))) {
            start--;
            break;
        }
    }
    if (start == begin) {
        while (begin < last) {
            auto temp = *begin;
            *(begin++) = *last;
            *(last--) = temp;
        }
    }
    auto replace = start + 1;
    for (auto i = replace; i <= last; i++) {
        if (*i > *start && *i < *replace) {
            replace = i;
            break;
        }
    }
    auto temp = *replace;
    *(replace) = *start;
    *(start) = temp;
    start++;
    while (start < last) {
        auto temp = *start;
        *(start++) = *last;
        *(last--) = temp;
    }
}

int main()
{

    vector<int> nums = { 1, 2, 3 };

    int target = -11;
    int a = 1;
    nextPermutation(nums);

    // for (auto a =  result.begin(); a < result.end(); a++)
    // {
    //     for (auto b =  (*a).begin(); b <(*a).end(); b++)
    //     {
    //         cout<<*b;
    //     }
    //     cout<<endl;
    // }
}