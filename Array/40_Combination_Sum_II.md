40.Combination Sum II

Given a collection of candidate numbers (`candidates`) and a target number (`target`), find all unique combinations in `candidates` where the candidate numbers sums to `target`.

Each number in `candidates` may only be used **once** in the combination.

**Note:**

- All numbers (including `target`) will be positive integers.
- The solution set must not contain duplicate combinations.

**Example 1:**

```cpp
Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
```

**Example 2:**

```cpp
Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
]
```

**题意**：从给定序列中找到和为target的一组序列，序列中的值只出现一次，序列不能重复。

**我的解法**：8ms ，8.8MB。时间复杂度：$\ O(2^n)$ ，空间复杂度：$\ O(n)$

```cpp
class Solution {
public:
std::vector<std::vector<int> > combinationSum2(std::vector<int> &candidates, int target) {
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
        for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i) {
            combination.push_back(candidates[i]);
            //递归时为i+1,避免出现重复
            combinationSum(candidates, target - candidates[i], res, combination, i+1);
            combination.pop_back();
            //去除重复值的影响
            while ((i+1) != candidates.size() && candidates[i]==candidates[i+1]) i++;
        }

    }
};
```

