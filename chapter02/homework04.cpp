#include <iostream>
using namespace std;

typedef struct node {
    int data;
    struct node *next;
} linknode, *link;

int getLength(link ha) {
    if (ha == nullptr) return 0;
    int len = 1;
    link p = ha->next;
    while (p != ha) {
        len++;
        p = p->next;
    }
    return len;
}

bool findSubListSumMultiple(link ha, int k, int *l, int *r) {
    if (ha == nullptr || k <= 0 || l == nullptr || r == nullptr) {
        return false;
    }

    int N = getLength(ha);

    for (int start = 1; start <= N; start++) {
        link cur = ha;
        for (int i = 1; i < start; i++) {
            cur = cur->next;
        }

        int sum = 0;
        for (int step = 1; step <= k; step++) {
            sum += cur->data;

            if ((sum % k + k) % k == 0) {
                *l = start;
                *r = start + step - 1;
                return true;
            }

            cur = cur->next;
        }
    }

    return false;
}