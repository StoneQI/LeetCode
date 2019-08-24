39. Combination Sum

Given a **set** of candidate numbers (`candidates`) **(without duplicates)** and a target number (`target`), find all unique combinations in `candidates` where the candidate numbers sums to `target`.

The **same** repeated number may be chosen from `candidates` unlimited number of times.

**Note:**

- All numbers (including `target`) will be positive integers.
- The solution set must not contain duplicate combinations.

**Example 1:**

```cpp
Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]
```

**Example 2:**

``` cpp
Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
```

**题意**：从`candidates`中查找和为`target`的一个序列，`candidates`中的数字可以重复，但不能有相同的序列。

**我的解法**：12 ms ，9.3MB。时间复杂度：$\ O(N^{target})$ ，空间复杂度：$\ O(1)$

```cpp
class Solution {
public:
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
                if(sum>target)
                    return;
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
};
```