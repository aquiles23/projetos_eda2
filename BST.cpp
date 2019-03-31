#include <iostream>
using namespace std;
template <typename T>
class BST
{
  public:
    struct Node
    {
        T info;
        Node *left, *right;
    };
    Node *root;

    BST() : root(nullptr) {}
    Node *getroot()
    {
        return root;
    }

    void delete_by_copying(Node **n)
    {
        auto node = *n;
        if (node == nullptr)
            return;

        if (node->right == nullptr)
            *n = node->left;
        else if (node->left == nullptr)
            *n = node->right;
        else
        {
            auto temp = &(*n)->left;

            while ((*temp)->right)
                temp = &(*temp)->right;

            node->info = (*temp)->info;
            return delete_by_copying(temp);
        }

        delete node;
    }

    void erase(const T &info)
    {
        Node **node = &root;

        while (*node)
        {
            if ((*node)->info == info)
                break;

            if (info < (*node)->info)
                node = &(*node)->left;
            else
                node = &(*node)->right;
        }

        delete_by_copying(node);
    }
    void insert(const T &info)
    {
        Node *node = root, *prev = nullptr;

        while (node)
        {
            prev = node;
            if (node->info == info)
                return;
            else if (info < node->info)
                node = node->left;
            else
                node = node->right;
        }
        node = new Node{info, nullptr, nullptr};

        if (!root)
            root = node;
        else if (info < prev->info)
            prev->left = node;
        else
            prev->right = node;
    }
    void truncate(Node *no)
    {
        truncate(no->left);
        truncate(no->right);
        delete no;
    }
    void print_no(Node *no)
    {
        if (no == nullptr)
            return;
        print_no(no->left);
        print_no(no->right);
        cout << no->info << "\n";
    }
};

int main()
{
    int qtd,info;
    BST<int> bst;
    cout << "how many to insert?\n";
    cin >> qtd;
    while (qtd)
    {
        cout << "insert\n";
        cin >> info;
        bst.insert(info);
        qtd--;
    }
    bst.print_no(bst.getroot());
    return 0;
}