#define ll long long
class Solution {
private:
  ll ans, sums;
  const ll MOD = 10e9 + 7;

  void calculatSum(TreeNode *node, ll &sum) {
    sum += node->val;
    if (node->left)
      calculatSum(node->left, sum);
    if (node->right)
      calculatSum(node->right, sum);
  }

  void dfs(TreeNode *node) {
    ll leftTree = 0, rightTree;
    calculatSum(node, leftTree);
    rightTree = sums - leftTree;
    ans = max(ans, (leftTree * rightTree) % MOD);
    if (node->left)
      dfs(node->left);
    if (node->right)
      dfs(node->right);
  }

public:
  int maxProduct(TreeNode *root) {
    calculatSum(root, sums);
    dfs(root);
    return ans;
  }
};
