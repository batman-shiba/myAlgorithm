#include "ListOpt.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {
    int num1 = 998, num2 = 20000;
    ListNode* head1 = int2List(num1);
    ListNode* head2 = int2List(num2);
    printfListAsInt(head1);
    printfListAsInt(head2);
    //ListNode* preHead1 = reverseList(head1);
    //printfList(preHead1);
    ListNode* sum = twoListSum(head1, head2);

    printfListAsInt(sum);
    return 0;
}