#include "y.tab.c"
#include "lex.yy.c"

typedef struct Node
{
    int type;       // 0: num, 1: op
    int val;        // number val
    char op;        // operator
    node_t *left;
    node_t *right;
} node_t;

node_t* ast;       // Abstract Syntax Tree

int calculate(node_t *node) {
    if (node == NULL) return 0;
    if (node->type == 0) {
        return node->val;
    } else if (node->type == 1) {
        switch (node->op)
        {
        case '+':
            return calculate(node->left) + calculate(node->right);
        case '-':
            return calculate(node->left) - calculate(node->right);
        case '*':
            return calculate(node->left) * calculate(node->right);
        case '/':
            return calculate(node->left) / calculate(node->right);
        default:
            break;
        }
    }
}

void post_order(node_t *node) {
    if (node == NULL) return;
    if (node-> type == 0) {
        printf("%d", node->val);
    } else if (node->type == 1) {
        post_order(node->left);
        post_order(node->right);
        putc(node->op, stdout);
    }
}

// 打印计算结果
void presult() {
    if(ast == NULL) return;
    printf("calculating result: %d\n", calculate(ast));
}

// 转为后缀表达式打印
void to_pfix() {
    if(ast == NULL) return;
    printf("to postfix: ");
    post_order(ast);
    putc('\n', stdout);
}

// receive new line(as AST)
void newline(node_t* root) {
    ast = root;
    to_pfix();
    presult();
}

node_t* mknode(char op, node_t* left, node_t* right) {
    node_t *node = malloc(sizeof(node_t));
    node->type = 1;
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

node_t* mkleaf(int num) {
    node_t *leaf = malloc(sizeof(node_t));
    leaf->type = 0;
    leaf->val = num;
    return leaf;
}

int main() {
    yyparse();
    return 0;
}
