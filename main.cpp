#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <set>
#include <numeric>

using namespace std;


struct ListNode {
    int val;
    struct ListNode *next;

    explicit
    ListNode(int x) :
            val(x), next(nullptr) {
    }
};

ListNode *CreateList(vector<int> v) {
    if (v.empty())
        return nullptr;
    ListNode *head = new ListNode(v[0]), *p = head;
    for (int i = 1; i < v.size(); i++) {
        auto *s = new ListNode(v[i]);
        p->next = s;
        p = s;
    }
    return head;
}

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;

    explicit
    TreeNode(int x) :
            val(x), left(nullptr), right(nullptr) {
    }
};

TreeNode *buildTreePreIn(vector<int> &preorder, vector<int> &inorder) {
    if (preorder.empty())
        return nullptr;
    auto *t = new TreeNode(preorder[0]);
    int i;
    vector<int> in1, in2, pre1, pre2;
    for (i = 0; i < inorder.size(); i++) {
        if (inorder[i] == preorder[0])
            break;
        in1.push_back(inorder[i]);
    }
    preorder.erase(preorder.begin());
    pre1.assign(preorder.begin(), preorder.begin() + i);
    pre2.assign(preorder.begin() + i, preorder.end());
    i++;
    for (; i < inorder.size(); i++) {
        in2.push_back(inorder[i]);
    }
    t->left = buildTreePreIn(pre1, in1);
    t->right = buildTreePreIn(pre2, in2);
    return t;
}

vector<int> printListFromTailToHead(ListNode *head) {
    vector<int> a;
    if (head == nullptr || head->next == nullptr)
        return a;
    while (head != nullptr) {
        a.push_back(head->val);
        head = head->next;
    }
    reverse(a.begin(), a.end());
    return a;
}


ListNode *ReverseList(ListNode *pHead) {
    ListNode *pre = nullptr;
    ListNode *cur = pHead;
    ListNode *nex; // 这里可以指向nullptr,循环里面要重新指向
    while (cur) {
        nex = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nex;
    }
    return pre;
}

ListNode *Merge(ListNode *pHead1, ListNode *pHead2) {
    auto *vhead = new ListNode(-1);
    ListNode *cur = vhead;
    while (pHead1 && pHead2) {
        if (pHead1->val <= pHead2->val) {
            cur->next = pHead1;
            pHead1 = pHead1->next;
        } else {
            cur->next = pHead2;
            pHead2 = pHead2->next;
        }
        cur = cur->next;
    }
    cur->next = pHead1 ? pHead1 : pHead2;
    return vhead->next;
}

ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
    ListNode *ta = pHead1, *tb = pHead2;
    while (ta != tb) {
        ta = ta ? ta->next : pHead2;
        tb = tb ? tb->next : pHead1;
    }
    return ta;
}

ListNode *EntryNodeOfLoop1(ListNode *pHead) {
    unordered_set<ListNode *> st;
    while (pHead) {
        if (st.find(pHead) == st.end()) {
            st.insert(pHead);
            pHead = pHead->next;
        } else {
            return pHead;
        }
    }
    return nullptr;
}

ListNode *EntryNodeOfLoop(ListNode *pHead) {
    if (pHead == nullptr)return nullptr;
    ListNode *slow = pHead, *fast = pHead;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)break;
    }
    if (fast == nullptr || fast->next == nullptr)return nullptr;
    fast = pHead;
    while (slow != fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

ListNode *FindKthToTail(ListNode *pHead, int k) {
    // write code here
    ListNode *slow = pHead, *fast = pHead;
    for (int i = 0; i < k; ++i) {
        if (fast == nullptr)
            return nullptr;
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

ListNode *deleteDuplication(ListNode *pHead) {
    auto *vhead = new ListNode(-1);
    vhead->next = pHead;
    ListNode *pre = vhead, *p = pHead;
    while (p != nullptr) {
        if (p->next != nullptr && p->next->val == p->val) {
            while (p->next != nullptr && p->next->val == p->val) {
                p = p->next;
            }
            pre->next = p->next;
            p = p->next;
        } else {
            pre = p;
            p = p->next;
        }
    }
    return vhead->next;
}

ListNode *deleteNode(ListNode *head, int val) {
    // write code here
    if (head == nullptr)
        return nullptr;
    auto *vhead = new ListNode(-1);
    vhead->next = head;
    ListNode *pre = vhead, *p = head;
    while (p != nullptr) {
        if (p->val == val) {
            pre->next = p->next;
        }
        pre = p;
        p = p->next;
    }
    return vhead->next;
}

// 按之字形顺序打印二叉树
vector<vector<int>> Print(TreeNode *pRoot) {
    vector<vector<int>> output;
    if (pRoot == nullptr)
        return output;
    queue<pair<TreeNode *, int>> qu;
    vector<pair<TreeNode *, int>> data;
    TreeNode *p = pRoot;
    pair<TreeNode *, int> tmp;
    qu.push(pair<TreeNode *, int>(p, 1));
    while (!qu.empty()) {
        tmp = qu.front();
        qu.pop();
        data.push_back(tmp);
        if (tmp.first->left != nullptr)
            qu.push(pair<TreeNode *, int>(tmp.first->left, tmp.second + 1));
        if (tmp.first->right != nullptr)
            qu.push(pair<TreeNode *, int>(tmp.first->right, tmp.second + 1));
    }
    vector<int> lvl_order;
    int level = 1;
    for (auto &i: data) {
        if (i.second == level) {
            lvl_order.push_back(i.first->val);
        } else {
            output.push_back(lvl_order);
            lvl_order.clear();
            level = i.second;
            lvl_order.push_back(i.first->val);
        }
    }
    if (!lvl_order.empty()) {
        output.push_back(lvl_order);
    }
    for (int i = 1; i < output.size(); i += 2) {
        reverse(output[i].begin(), output[i].end());
    }
    return output;
}


TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin) {
    if (pre.size() == 0 || vin.size() == 0)
        return nullptr;
    auto t = new TreeNode(pre[0]);
    int i = 0;
    for (; i < vin.size(); i++) {
        if (vin[i] == pre[0]) {
            break;
        }
    }
    vector<int> pre1, pre2, in1, in2;
    pre1.assign(pre.begin() + 1, pre.begin() + 1 + i);
    pre2.assign(pre.begin() + 1 + i, pre.end());
    in1.assign(vin.begin(), vin.begin() + i);
    in2.assign(vin.begin() + i + 1, vin.end());
    t->left = reConstructBinaryTree(pre1, in1);
    t->right = reConstructBinaryTree(pre2, in2);
    return t;
}


TreeNode *Mirror(TreeNode *pRoot) {
    // write code here
    if (pRoot == nullptr)
        return nullptr;
    TreeNode *tmp = pRoot->left;
    pRoot->left = pRoot->right;
    pRoot->right = tmp;
    pRoot->left = Mirror(pRoot->left);
    pRoot->right = Mirror(pRoot->right);
    return pRoot;
}

vector<int> PrintFromTopToBottom(TreeNode *root) {
    queue<TreeNode *> qu;
    vector<int> data;
    if (root == nullptr)
        return data;
    qu.push(root);
    while (!qu.empty()) {
        TreeNode *p = qu.front();
        qu.pop();
        data.push_back(p->val);
        if (p->left != nullptr)
            qu.push(p->left);
        if (p->right != nullptr)
            qu.push(p->right);
    }
    return data;
}

bool VerifySquenceOfBST(vector<int> sequence) {
    if (sequence.empty())
        return false;
    else if (sequence.size() == 1)
        return true;
    int root_node = sequence.back();
    int i = 0, j = 0;
    bool flag;
    vector<int> pre, post;
    if (sequence[0] < root_node) {
        for (; i < sequence.size() - 1; i++) {
            if (sequence[i] > root_node) {
                pre.assign(sequence.begin(), sequence.begin() + i);
                post.assign(sequence.begin() + i, sequence.end() - 1);
                break;
            }
        }
    } else {
        post.assign(sequence.begin(), sequence.end() - 1);
    }

    for (; j < post.size(); j++) {
        if (post[j] < root_node) {
            flag = false;
            break;
        }
    }
    if (j == post.size())
        flag = true;
    bool l_flag = true, r_flag = true;
    if (!pre.empty())
        l_flag = VerifySquenceOfBST(pre);
    if (!post.empty())
        r_flag = VerifySquenceOfBST(post);
    bool result = flag && l_flag && r_flag;
    return result;
}

bool hasRePathSum(TreeNode *root, int sum) {
    if (root == nullptr)
        return false;
    if (root->val == sum)
        return true;
    bool l_flag = hasRePathSum(root->left, sum - root->val);
    bool r_flag = hasRePathSum(root->right, sum - root->val);
    return l_flag || r_flag;
}

bool hasPathSum(TreeNode *root, int sum) {
    // write code here
    if (root == nullptr)
        return false;
    else if (root->val == sum && (root->left != nullptr || root->right != nullptr))
        return false;
    else if (root->val == sum && (root->left == nullptr || root->right == nullptr))
        return true;
    else
        return hasRePathSum(root, sum);
}

void *ReInOrder(TreeNode *&pRootOfTree) {
    if (pRootOfTree->left != nullptr)
        ReInOrder(pRootOfTree->left);
    TreeNode *preNode;

    if (pRootOfTree->right != nullptr)
        ReInOrder(pRootOfTree->right);

}

TreeNode *Convert(TreeNode *pRootOfTree) {
    if (pRootOfTree == nullptr)
        return nullptr;
    else
        return pRootOfTree;
}

int Post_order(TreeNode *pRoot, int depth) {
    int l = 0, r = 0;
    if (pRoot->left) {
        l = Post_order(pRoot->left, depth + 1);
    }
    if (pRoot->right) {
        r = Post_order(pRoot->right, depth + 1);
    }
    if (pRoot->left == nullptr && pRoot->right == nullptr)
        return depth;
    else if (pRoot->left != nullptr && pRoot->right == nullptr) {
        if (abs(l - depth) > 1)
            return -1;
        else
            return l;
    } else if (pRoot->left == nullptr && pRoot->right != nullptr) {
        if (abs(r - depth) > 1)
            return -1;
        else
            return r;
    } else if (l == -1 || r == -1 || abs(l - r) > 1)
        return -1;
    else
        return l > r ? l : r;
}

// 后序遍历二叉树
bool IsBalanced_Solution(TreeNode *pRoot) {
    if (pRoot == nullptr)
        return true;
    else {
        int n = Post_order(pRoot, 1);
        if (n != -1)
            return true;
        else
            return false;
    }
}

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;

    explicit
    TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {
    }
};

bool Symmetr(TreeNode *pLeft, TreeNode *pRight) {
    if (!pLeft && !pRight)
        return true;
    if (!pLeft || !pRight)
        return false;
    return pLeft->val == pRight->val && Symmetr(pLeft->left, pRight->right) &&
           Symmetr(pLeft->right, pRight->left);
}

bool isSymmetrical(TreeNode *pRoot) {
    return Symmetr(pRoot->left, pRoot->right);
}


vector<vector<int>> PrintLevel(TreeNode *pRoot) {
    vector<vector<int>> output;
    if (pRoot == nullptr)
        return output;
    queue<pair<TreeNode *, int>> qu;
    vector<pair<TreeNode *, int>> data;
    TreeNode *p = pRoot;
    pair<TreeNode *, int> tmp;
    qu.push(pair<TreeNode *, int>(p, 1));
    while (!qu.empty()) {
        tmp = qu.front();
        qu.pop();
        data.push_back(tmp);
        if (tmp.first->left != nullptr)
            qu.push(pair<TreeNode *, int>(tmp.first->left, tmp.second + 1));
        if (tmp.first->right != nullptr)
            qu.push(pair<TreeNode *, int>(tmp.first->right, tmp.second + 1));
    }
    vector<int> lvl_order;
    int level = 1;
    for (auto &i: data) {
        if (i.second == level) {
            lvl_order.push_back(i.first->val);
        } else {
            output.push_back(lvl_order);
            lvl_order.clear();
            level = i.second;
            lvl_order.push_back(i.first->val);
        }
    }
    if (!lvl_order.empty()) {
        output.push_back(lvl_order);
    }
    return output;
}

// ------------------------------------------------------------------
// 二叉树中和为某一值的路径(三)
//描述
//给定一个二叉树root和一个整数值 sum ，求该树有多少路径的的节点值之和等于 sum 。
//1.该题路径定义不需要从根节点开始，也不需要在叶子节点结束，但是一定是从父亲节点往下到孩子节点
//2.总节点数目为n
//3.保证最后返回的路径个数在整形范围内
int num_path = 0;

void FFF(TreeNode *root, int sum) {
    if (root == nullptr)return;
    sum -= root->val;
    if (sum == 0)num_path++;
    FFF(root->left, sum);
    FFF(root->right, sum);
}

int FindPath(TreeNode *root, int sum) {
    // write code here
    if (!root)
        return num_path;
    else {
        FFF(root, sum);
        FindPath(root->left, sum);
        FindPath(root->right, sum);
        return num_path;
    }
}

// ------------------------------------------------------------------
//在二叉树中找到两个节点的最近公共祖先
//描述
//给定一棵二叉树(保证非空)以及这棵树上的两个节点对应的val值 o1 和 o2，请找到 o1 和 o2 的最近公共祖先节点。
//数据范围：树上节点数满足1≤n≤10^5
//节点值val满足区间 [0,n)
//要求：时间复杂度 O(n)
//注：本题保证二叉树中每个节点的val值均不相同。
vector<int> tmp;

void Ancestor(TreeNode *root, int target, vector<int> p) {
    if (root == nullptr)
        return;
    else if (root->val == target) {
        p.push_back(target);
        tmp = p;
        return;
    }
    p.push_back(root->val);
    Ancestor(root->left, target, p);
    Ancestor(root->right, target, p);
}


int lowestCommonAncestor(TreeNode *root, int o1, int o2) {
    // write code here
    vector<int> o1_path, o2_path;
    Ancestor(root, o1, {});
    o1_path = tmp;
    Ancestor(root, o2, {});
    o2_path = tmp;

    int a=0;
    set<int> s;
    for (int i: o1_path) {
        s.insert(i);
    }
    for (int i: o2_path) {
        if (s.find(i) != s.end())
            a=i;
    }
    return a;
}
// ------------------------------------------------------------------

int main() {
    vector<int> pre = {3, 5, 6, 2, 7, 4, 1, 0, 8};
    vector<int> in = {6, 5, 7, 2, 4, 3, 0, 1, 8};
    TreeNode *t = buildTreePreIn(pre, in);
    int a = lowestCommonAncestor(t, 5, 1);
    return 0;
}
