/*
 * @Author: stone
 * @Date: 2019-08-20 20:13:39
 * @LastEditTime: 2019-08-21 16:43:00
 * @LastEditors: stone
 * @Description: 
 */

#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
int search2(vector<int>& nums, int target)
{
    int lo = 0, hi = nums.size();
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (nums[mid] == target)
            return mid;
        double num = (nums[mid] < nums[0]) == (target < nums[0])
            ? nums[mid] < target ? lo = mid + 1 : hi = mid
            : target < nums[0] ? lo = mid + 1 : hi = mid;

        // if (num < target)
        //     lo = mid + 1;
        // else if (num > target)
        //     hi = mid;
        // else
        //     return mid;
    }
    return -1;
}

int search(vector<int>& nums, int target)
{
    int length = nums.size();
    int start = 0;
    int end = length - 1;
    while (start <= end) {
        int half = int((start + end) / 2);
        if (nums[half] == target)
            return half;
        bool flag = false;
        if (nums[start] < nums[half])
            flag = true;

        if (flag) {
            if (nums[start] > target || nums[half] < target)
                flag = false;
        } else {
            if (nums[half] > target || nums[end] < target)
                flag = true;
        }

        if (flag)
            end = half - 1;
        else
            start = half + 1;
    }
    return -1;
}

int main()
{
    //[4,5,6,7,0,1,2]
    //3
    vector<int> nums = { 4, 5, 6, 7, 0, 1, 2 };

    int target = 0;
    cin >> target;
    while (target != -1) {
        auto result = search2(nums, target);
        cout << result << endl;

        cin >> target;
    }
    // for (auto a =  result.begin(); a < result.end(); a++)
    // {
    //     for (auto b =  (*a).begin(); b <(*a).end(); b++)
    //     {
    //         cout<<*b;
    //     }
    //     cout<<endl;
    // }
}