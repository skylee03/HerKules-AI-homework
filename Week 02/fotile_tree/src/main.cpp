#include "fotile_tree.h"

#include <stack>
#include <cstdio>

constexpr int MAXV = 1e5;

skylee::fotile_tree<MAXV> tree;

int main() {
    for(;;) {
        printf("\033[33m");
        puts("================================");
        printf("Current Version: %d\n", tree.version());
        puts("1: Insert a number");
        puts("2: Erase a number");
        puts("3: Find by order");
        puts("4: Rollback to history version");
        puts("0: Quit");
        puts("================================");
        printf("\033[0m");
        printf("Please input your choice: \033[0m");
        int choice;
        scanf("%d", &choice);
        if(choice == 1) {
            printf("\033[33mPlease input a number: \033[0m");
            int x;
            scanf("%d", &x);
            tree.insert(x);
        } else if(choice == 2) {
            printf("\033[33mPlease input a number: \033[0m");
            int x;
            scanf("%d", &x);
            tree.erase(x);
        } else if(choice == 3) {
            printf("\033[33mPlease input the order: \033[0m");
            int k;
            scanf("%d", &k);
            printf("\033[33m%d\033[0m\n", tree.find_by_order(k));
        } else if(choice == 4) {
            printf("\033[33mPlease input the version: \033[0m");
            int new_ver;
            scanf("%d", &new_ver);
            tree.rollback(new_ver);
            puts("\033[33mDone.\033[0m");
        } else return 0;
    }
}