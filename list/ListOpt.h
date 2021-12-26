#include "ListNode.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

void printfList(ListNode* head) {
    while(head != nullptr) {
        cout << head->val << "->";
        head = head->next;
    }
    cout << endl;
}

void printfListAsInt(ListNode* head) {
    while(head != nullptr) {
        cout << head->val;
        head = head->next;
    }
    cout << endl;
}

bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while(slow != nullptr) {
        slow = slow->next;

        if(nullptr == slow) {
            break;
        }

        if(fast->next == nullptr) {
            break;
        }

        fast = fast->next->next;

        if(slow == fast) {
            return true;
        }
    }

    return false;
}

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;

    while(head != nullptr) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

void removeNode(ListNode* head, int num) {
    ListNode* cur = head;

    while(cur->next != nullptr && cur->next->val != num) {
        cur = cur->next;
    }

    if(cur->next != nullptr) {
        ListNode* next = cur->next->next;
        cur->next = next;
    }
}

// 将一个整数转换为链表存储
ListNode* int2List(int num) {
    int theBit;
    ListNode* head = new ListNode(num % 10);
    ListNode* cur = head;
    num /= 10;
    while(num > 0) {
        theBit = num % 10;
        num /= 10;
        cur->next = new ListNode(theBit);
        cur = cur->next;
    }
    return reverseList(head);
}

// 全是数字的字符串转换成链表
ListNode* str2List(string str) {
    if(str.size() < 1) {
        return nullptr;
    }

    ListNode* head = new ListNode(str[0] - '0');
    ListNode* cur = head;
    int len = str.size();

    for(int i = 1; i < len; ++i) {
        cur->next = new ListNode(str[i] - '0');
        cur = cur->next;
    }
    return head;
}

// 将两个链表存储的整数相加
ListNode* twoListSum(ListNode* list1, ListNode* list2) {
    ListNode* l1 = reverseList(list1);
    ListNode* l2 = reverseList(list2);
    ListNode* head = l1;
    ListNode* pre = nullptr;

    int curBit = 0;
    int nextBit = 0;

    while(l1 != nullptr && l2 != nullptr) {
        int sum = l1->val + l2->val + nextBit;
        curBit = sum % 10;
        nextBit = sum / 10;

        l1->val = curBit;
        pre = l1;
        l1 = l1->next;
        l2 = l2->next;
    }

    if(l1 != nullptr) {
        while(nextBit > 0 && l1 != nullptr) {
            int sum = l1->val + nextBit;
            curBit = sum % 10;
            nextBit = sum / 10;

            l1->val = curBit;
            pre = l1;
            l1 = l1->next;
        }

        if(nextBit > 0) {
            pre->next = new ListNode(1);
        }
    }

    if(l2 != nullptr) {
        pre->next = l2;

        while(nextBit > 0 && l2 != nullptr) {
            int sum = l2->val + nextBit;
            curBit = sum % 10;
            nextBit = sum / 10;

            l2->val = curBit;
            pre = l2;
            l2 = l2->next;
        }

        if(nextBit > 0) {
            pre->next = new ListNode(1);
        }
    }
    return reverseList(head);
}