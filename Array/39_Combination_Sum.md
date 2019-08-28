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

**我的解法**：12 ms ，9.3MB。时间复杂度：$\ O(N^{target})$ ，空间复杂度：$\ O(target)$

使用回溯法，这里用的深度优先搜索。首先对数组排序，然后每一层对所有大等于上一个节点的值进行递归。配到和为`target`的放入`result`，然后回溯。

```cpp
class Solution {
public:
    //深度递归，sum为递归中该条路径的值的和。pre为当前节点的父节点的值。result为最终结果。temp为临时存放一个序列。
    void dfs(int target, int sum, int pre, vector<int>& candidates, vector<vector<int>>& result, vector<int>& temp)
    {
        for (auto a = candidates.begin(); a < candidates.end(); a++) {
            //当满足当前值大于等于父结点的值时，才进行下一步，主要为了防止出现重复。
            if (*a >= pre) {
                sum += *a; //向下递归，加和。
                int b = pre;//保存父节点
                pre = *a; //向下递归，设置pre
                temp.push_back(*a); //temp保存了当前递归路径
                if (sum == target) { //如果该路径满足要求，放入result
                    result.push_back(temp);
                }
                if (sum < target) //sum<target时，继续向下递归。
                    dfs(target, sum, pre, candidates, result, temp);
                sum -= *a; //回溯减去该值。
                pre = b; //恢复父节点
                temp.pop_back(); //路径中移去改值
                if(sum>target) //sum大于target时，直接结束本层递归，因为该层剩下的路径sum肯定大于当前sum。
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



**论坛解法**:12 ms ，9.4MB。时间复杂度：$\ O(N^{target})$ ，空间复杂度：$\ O(target)$

解法也是深度优先搜索，不过进行了优化。

```cpp
class Solution {
public:
    std::vector<std::vector<int> > combinationSum(std::vector<int> &candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int> > res;
        std::vector<int> combination;
        combinationSum(candidates, target, res, combination, 0);
        return res;
    }
private:
//target为深度优先路径target-路径节点值的和，判断是否等于target。begin为当前节点的索引
    void combinationSum(std::vector<int> &candidates, int target, std::vector<std::vector<int> > &res, std::vector<int> &combination, int begin) {
        //判断是否等于target。等于target时，放入res。此时不会判断大于target的情况
        if (!target) {
            res.push_back(combination);
            return;
        }
        if (target < 0) return;
        //递归循环，直接从上一次的遍历的节点向后遍历（包含上次的节点）。节点值大于target时不判断。
        for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i) {
            combination.push_back(candidates[i]);
            combinationSum(candidates, target - candidates[i], res, combination, i);
            combination.pop_back();
        }
    }
};
```