/*
第四题

设计算法求孩子兄弟链表表示的树的度。
    int degree(CSTree root);      // root 为根

树的度 = 树中所有结点的孩子数的最大值。

孩子兄弟链表的结构（课件第 71 页）：

    struct TreeNode {
        elemtype data;
        struct TreeNode *firstchild;      // 第一个孩子
        struct TreeNode *nextsibling;     // 下一个兄弟
    };
    typedef struct TreeNode * CSTree;

求某个结点的孩子数：从 firstchild 出发，沿 nextsibling 链一直走到空，
链上结点个数就是它的度。整棵树的度即所有结点度的最大值。

注意：nextsibling 只在"求某结点的孩子列表"时才走；遍历树本身时，
必须先访问 firstchild 子树，再沿 nextsibling 走向下一棵子树，
否则会漏掉除长子以外的子树。

复杂度：
    时间 O(n)，每条 nextsibling 链在不同的父结点处各被扫一次，
         所有链长之和正好是 n-1（每个结点除根外恰好是一条链上的结点）；
    空间 O(h)，h 为树的高度（递归栈）。

若传入的是森林中带兄弟的根，本函数只统计以 root 为根的这一棵树，
忽略 root->nextsibling，这与"树的度"的定义一致。
*/

#include <algorithm>
#include <iostream>
using namespace std;

typedef char elemtype;

struct TreeNode {
    elemtype data;
    struct TreeNode *firstchild;
    struct TreeNode *nextsibling;
};
typedef struct TreeNode * CSTree;

int degree(CSTree root)
{
    if (root == NULL) {
        return 0;                            // 空树的度为 0
    }

    int maxChild = 0;                        // 先数 root 自己的孩子
    for (CSTree c = root->firstchild; c != NULL; c = c->nextsibling) {
        ++maxChild;
    }

    // 再递归求所有子树的度，取最大值
    for (CSTree c = root->firstchild; c != NULL; c = c->nextsibling) {
        maxChild = max(maxChild, degree(c));
    }
    return maxChild;
}

/* ---------- 以下为测试辅助，不属于答案主体 ---------- */

static CSTree NewNode(elemtype d)
{
    CSTree t = new TreeNode;
    t->data = d;
    t->firstchild = t->nextsibling = NULL;
    return t;
}

static void AddLastChild(CSTree parent, CSTree child)
{
    if (parent->firstchild == NULL) {
        parent->firstchild = child;
    } else {
        CSTree p = parent->firstchild;
        while (p->nextsibling != NULL) p = p->nextsibling;
        p->nextsibling = child;
    }
}

static void Release(CSTree t)
{
    if (t == NULL) return;
    Release(t->firstchild);
    Release(t->nextsibling);
    delete t;
}

static void Test(const char *name, CSTree root, int expect)
{
    int got = degree(root);
    cout << name << " -> 度 = " << got
         << (got == expect ? "   [OK]" : "   [FAIL]") << endl;
    Release(root);
}

int main()
{
    Test("空树", NULL, 0);
    Test("单结点", NewNode('A'), 0);

    // 树：A(B(D,E,F), C(G))  -> A 有 2 个孩子，B 有 3 个，度 = 3
    CSTree a = NewNode('A'), b = NewNode('B'), c = NewNode('C');
    CSTree d = NewNode('D'), e = NewNode('E'), f = NewNode('F'), g = NewNode('G');
    AddLastChild(a, b);
    AddLastChild(a, c);
    AddLastChild(b, d);
    AddLastChild(b, e);
    AddLastChild(b, f);
    AddLastChild(c, g);
    Test("A(B(D,E,F),C(G))", a, 3);

    // 星形：A 有 4 个孩子 -> 度 = 4
    CSTree h = NewNode('H');
    for (int i = 0; i < 4; ++i) AddLastChild(h, NewNode(char('a' + i)));
    Test("根有 4 个孩子", h, 4);

    // 单链 -> 度 = 1
    CSTree x = NewNode('X'), y = NewNode('Y'), z = NewNode('Z');
    AddLastChild(x, y);
    AddLastChild(y, z);
    Test("单链 X(Y(Z))", x, 1);

    return 0;
}
