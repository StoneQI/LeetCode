/*
 * @Author: stone
 * @Date: 2019-08-19 11:12:48
 * @LastEditTime: 2019-08-19 11:12:48
 * @LastEditors: stone
 * @Description: 
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target)
{
    vector<vector<int>> result;
    if (nums.size() < 3)
        return result; //处理边界情况
    sort(nums.begin(), nums.end());
    // auto last=nums.end();
    auto last = prev(nums.end());

    for (auto a = nums.begin(); a < last - 2; a++) {
        if (a > nums.begin() && *a == *prev(a)) {
            continue; //重复的只处理一次
        }
        // if (*a>target) return result; //当*a>0时说明，后面相加已经不可能等于0

        for (auto d = last; d > a + 2; d--) {
            auto b = next(a);
            auto c = prev(d); //prev 1 postion
            if (d < last && *d == *next(d)) {
                continue;
            }
            // if (*d<target) break;

            while (b < c) {
                int current = *a + *b + *c + *d;
                if (current < target)
                    b++; //小于0 b增加
                else if (current > target)
                    c--; //大于0 c减少
                else {
                    result.push_back({ *a, *b, *c, *d });
                    while (b < c && *b == *(next(b)))
                        b++; //when break,b !=
                    while (b < c && *c == *(prev(c)))
                        c--;
                    b++; //因为b==prev(b)，prev(b)已经判断了，所以++
                    c--;
                }
            }
        }
    }
    return result;
}

int main()
{

    vector<int> nums = { 1, -2, -5, -4, -3, 3, 3, 5 };

    int target = 3;
    auto result = fourSum(nums, target);

    for (auto a = result.begin(); a < result.end(); a++) {
        for (auto b = (*a).begin(); b < (*a).end(); b++) {
            cout << *b;
        }
        cout << endl;
    }
}