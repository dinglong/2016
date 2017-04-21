#include <cstdlib>
#include <iostream>
using namespace std;

/**
 * 根据树的高度计算需要在左端留出的空白数目
 */
int count_branch(int h)
{
    if (h == 1) {
        return 0;
    } else {
        int sum = 0;
        for (int i = 1; i < h; i++) {
            sum += count_branch(i);
        }
        return (sum + 1);
    }
}

/**
 * 计算一个指定高度的节点的空白数
 */
int count_space(int h)
{
    return (count_branch(h) * 2 - 1);
}

/**
 * 打印指定数目的空白
 */
void print_space(int num)
{
    for (int i = 0; i < num; i++) {
        cout << ' ';
    }
}

/**
 * 打印指定高度的树
 */
void print_tree(int h)
{
    // TODO 目前打印的是一颗满二叉树

    for (int i = 0; i < h; i++) {
        int node_count = 1 << i; // 该层有的节点的数目
        int space_count = count_space(h - i);

        /*
         * 打印节点
         */
        for (int j = 0; j < node_count; j++) {
            print_space(space_count);
            cout << 'x';
            print_space(space_count);

            cout << ' ';
        }
        cout << endl;

        /*
         * 如果有下一层，将下一层的树枝打印出来
         */
        if (i < h - 1) {
            int branch_count = count_branch(h - i);

            for (int j = 0; j < branch_count; j++) {
                space_count--;

                for (int k = 0; k < node_count; k++) {
                    print_space(space_count);

                    cout << '/';
                    print_space(2 * j + 1);
                    cout << '\\';

                    print_space(space_count);
                    cout << ' ';
                }

                cout << endl;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <high>" << endl;
        return 1;
    }

    int high = atoi(argv[1]);
    print_tree(high);

    return 0;
}

