/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <queue>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* createParentMapping(TreeNode* root, int target, std::unordered_map<TreeNode*, TreeNode*>& nodeToParent)
    {
        TreeNode* res = nullptr;
        std::queue<TreeNode*> q;
        q.push(root);
        nodeToParent[root] = nullptr;
        while (!q.empty()) {
            TreeNode* front = q.front();
            q.pop();

            if (front->val == target) {
                res = front;
            }

            if (front->left) {
                nodeToParent[front->left] = front;
                q.push(front->left);
            }
            if (front->right) {
                nodeToParent[front->right] = front;
                q.push(front->right);
            }
        }
        return res;
    }

    int infectTime(TreeNode* root, std::unordered_map<TreeNode*, TreeNode*>& nodeToParent) {
        std::unordered_map<TreeNode*, bool> visited;
        std::queue<TreeNode*> q;
        q.push(root);
        visited[root] = true;

        int ans = 0;
        while (!q.empty()) {
            bool flag = false;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* front = q.front();
                q.pop();

                // push left right and parent node to queue
                if (front->left && !visited[front->left]) {
                    flag = true;
                    q.push(front->left);
                    visited[front->left] = true;
                }

                if (front->right && !visited[front->right]) {
                    flag = true;
                    q.push(front->right);
                    visited[front->right] = true;
                }
                if (nodeToParent[front] && !visited[nodeToParent[front]]) {
                    flag = true;
                    q.push(nodeToParent[front]);
                    visited[nodeToParent[front]] = true;
                }
            }
            if (flag == true)
                ans++;
        }
        return ans;
    }
    int amountOfTime(TreeNode* root, int start) {
        std::unordered_map<TreeNode*, TreeNode*> nodeToParent;
        TreeNode* targetNode = createParentMapping(root, start, nodeToParent);
        return infectTime(targetNode, nodeToParent);
    }
};