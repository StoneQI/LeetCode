/*
 * @Author: stone
 * @Date: 2019-08-24 14:22:28
 * @LastEditTime: 2019-08-24 19:01:53
 * @LastEditors: stone
 * @Description: 
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void dfs(int target, int sum, int pre, vector<int>& candidates, vector<vector<int>>& result, vector<int>& temp)
{
    for (auto a = candidates.begin(); a < candidates.end(); a++) {
        if (*a >= pre) {
            sum += *a;
            pre = *a;
            temp.push_back(*a);
            if (sum == target) {
                result.push_back(temp);
            }
            if (sum < target)
                dfs(target, sum, pre, candidates, result, temp);
            sum -= *a;
            pre = *a;
            temp.pop_back();
        }
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    sort(candidates.begin(), candidates.end());
    int pre = *(candidates.begin());
    vector<vector<int>> result;
    vector<int> temp;
    int sum = 0;
    dfs(target, sum, pre, candidates, result, temp);
    return result;
}

int main()
{

    vector<int> nums = { 2, 3, 6, 7 };

    int target = 7;
    // int a = 1;
    auto result = combinationSum(nums, target);

    cout << endl;
    // for (auto a =  result.begin(); a < result.end(); a++)
    // {
    //     for (auto b =  (*a).begin(); b <(*a).end(); b++)
    //     {
    //         cout<<*b;
    //     }
    //     cout<<endl;
    // }
}