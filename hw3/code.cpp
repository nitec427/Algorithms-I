#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits.h>
using namespace std;
/*
İsmail Çetin
150180065
BLG 335E - Homework3
# compiled with ->  g++ -std=c++11 .\150180065.cpp -Werror -o
*/

// Black is 0 and Red 1
// B->0     R->1

// First create the node and then add accordingly. (If the node already exists update its data count)
class Node
{
public:
    string name, game_name;
    double na_sales, eu_sales, other_sales;
    Node *parent;
    Node *left;
    Node *right;
    int color;

    Node(string name, double na = 0, double eu = 0, double other = 0)
    {
        na_sales = na;
        eu_sales = eu;
        other_sales = other;
        this->name = name;
        left = nullptr;
        right = nullptr;
        color = 1; // set to red initially
    }
    // Update helper function
    void updateNode(double na = 0, double eu = 0, double other = 0)
    {
        na_sales += na;
        eu_sales += eu;
        other_sales += other;
    }
};

class RBTree
{
public:
    Node *root;
    // Utility functions
    RBTree()
    {
        root = nullptr;
    }
    void RBInsert(Node *z, Node *parent);
    void RBInFixUp(Node *z);
    Node *findRoot(Node *x);
    void left_rotate(Node *z);
    void right_rotate(Node *z);
    void preOrder(Node *x);
    Node *searchMax(Node *x, double key, string continent);
    double findMax(Node *x, string continent); // find the node with the maximum sale count
    Node *BSTSearch(Node *x, string name);     // Binary search tree search function
    int findDepth(Node *top, string name);     // find the depth to print indentation by using publisher name
};
// This function returns the node according to sale number.
// It is used when finding the maximum sale is required.
Node *RBTree::searchMax(Node *x, double key, string continent)
{
    static Node *found = nullptr;
    // Static keyword is used to preserve the found node between recursion calls.
    if (!x)
        return nullptr;
    if (continent == "eu")
    {
        if (x->eu_sales == key)
        {
            found = x;
            return x;
        }
    }

    else if (continent == "na")
    {
        if (x->na_sales == key)
        {
            found = x;
            return x;
        }
    }
    else
    {
        if (x->other_sales == key)
        {
            found = x;
            return x;
        }
    }
    searchMax(x->left, key, continent);
    searchMax(x->right, key, continent);
    return found;
}
Node *RBTree::findRoot(Node *x)
{
    while (x->parent)
        x = x->parent;
    return x;
}
Node *RBTree::BSTSearch(Node *x, string key)
{
    // Use this function to check whether there is a match
    if (!x)
        return 0;
    else if (x->name == key)
        return x;
    else if (x->name > key)
        return BSTSearch(x->left, key);
    return BSTSearch(x->right, key);
}
void RBTree::preOrder(Node *x)
{
    // Preorder Printing Helper Function
    if (!x)
        return;
    for (int i = 0; i < findDepth(root, x->name); i++)
    {
        cout << "-";
    }
    if (x->color)
        cout << "(RED) ";
    else
        cout << "(BLACK) ";
    cout << x->name << "\n";
    preOrder(x->left);
    preOrder(x->right);
}
int RBTree::findDepth(Node *top, string name)
{
    // Find the depth of the current node. The depth of the current node is the maximum distance to null pointer.
    // If block helps us to find this path.
    if (!top)
        return -1;
    int depth = -1;
    if (top->name == name || (depth = findDepth(top->left, name)) >= 0 || (depth = findDepth(top->right, name)) >= 0)
        return depth + 1;
    return depth;
}

// Max finding functions are coded. According to results, find the node.
double RBTree::findMax(Node *x, string continent)
{
    // This function returns the maximum sale number within the tree for the given continent value
    double result = 0;
    // Return maximum of 3 values
    if (x == nullptr)
        return -100000; // INT_MIN is assumed here
    if (continent == "na")
        result = x->na_sales;
    else if (continent == "eu")
        result = x->eu_sales;
    else
        result = x->other_sales;

    double left_res = findMax(x->left, continent);
    double right_res = findMax(x->right, continent);

    if (left_res > result)
        result = left_res;
    if (right_res > result)
        result = right_res;
    return result;
}
void RBTree::left_rotate(Node *z)
{
    Node *y = z->right;
    z->right = y->left;
    if (y->left)
        y->left->parent = z;
    y->parent = z->parent;
    if (!(z->parent))
    {
        root = y;
    }
    else if (z == z->parent->left)
    {
        z->parent->left = y;
    }
    else
    {
        z->parent->right = y;
    }
    y->left = z;
    z->parent = y;
}
void RBTree::right_rotate(Node *z)
{
    Node *y = z->left;
    z->left = y->right;
    if (y->right)
        y->right->parent = z;
    y->parent = z->parent;
    if (!(z->parent))
    {
        root = y;
    }
    else if (z == z->parent->right)
    {
        z->parent->right = y;
    }
    else
    {
        z->parent->left = y;
    }
    y->right = z;
    z->parent = y;
}
void RBTree::RBInsert(Node *z, Node *parent = nullptr)
{
    // Z is incoming node and parent holds a reference to parent node. It will be used when a new node is created
    // Here is coded the same as given pseudocode.
    Node *y = nullptr;
    Node *x = root;

    while (x != nullptr)
    {
        y = x;
        if ((z->name) < (x->name))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->name < y->name)
        y->left = z;
    else
        y->right = z;
    RBInFixUp(z);
}
// Red Black tree functions are coded according to given pseudocode
void RBTree::RBInFixUp(Node *z)
{
    // Always check for dangling pointers.
    if (!z->parent || z->parent->parent == nullptr)
    {
        if (root)
            root->color = 0;
        return;
    }
    while (z->parent && z->parent->color == 1)
    {
        if (z->parent->parent != nullptr && z->parent == z->parent->parent->left)
        {
            Node *uncle = z->parent->parent->right;
            if (uncle && uncle->color == 1) // if uncle is red
            {
                z->parent->color = 0;
                uncle->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    // Left Rotate z;
                    left_rotate(z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                // Right rotate (grandparent)
                right_rotate(z->parent->parent);
            }
        }
        else
        {
            // Else not changed yet
            Node *uncle = z->parent->parent->left;
            if (uncle && uncle->color == 1) // if uncle is red
            {
                z->parent->color = 0;
                uncle->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    // Change z with its parent
                    z = z->parent;
                    // right Rotate z;
                    right_rotate(z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                // left rotate (grandparent)
                left_rotate(z->parent->parent);
            }
        }
    }
    root->color = 0; // set root to black
}

RBTree read_file(RBTree my_tree)
{
    fstream in_file;
    in_file.open("VideoGames.csv", ios::in);
    string name, platf, year_release, publisher, na_sales, eu_sales, other_sales;
    string input;
    bool first_91, first_01, first_11;      // to check the first input of the new decade
    first_01 = first_91 = first_11 = false; // set them to true when their first value comes and find the max of the prev decade
    int lc = 0;                             // line counter
    Node *root;                             // root node will be called in certain functions below, so make it general (though it is not a good practice). Had I have a time, I would have revised my code.
    while (getline(in_file, input))
    {
        stringstream ss(input);
        getline(ss, name, ',');
        getline(ss, platf, ',');
        getline(ss, year_release, ',');
        getline(ss, publisher, ',');
        // After reading variables below will be converted to doubles
        getline(ss, na_sales, ',');
        getline(ss, eu_sales, ',');
        getline(ss, other_sales, ',');
        if (na_sales == "NA_Sales")
            continue; // Do not read the first line
        else
        {
            // In the first case read as a node then go accordingly
            Node *search_node = my_tree.BSTSearch(root, publisher); // BSTsearch, searches the tree with the given publisher name
            // Control decade change with the lines below
            if (year_release == "1991")
            {
                if (!first_91)
                {
                    // Find maximum for each continent and then do search operation
                    double val_eu = my_tree.findMax(root, "eu");
                    double val_na = my_tree.findMax(root, "na");
                    double val_other = my_tree.findMax(root, "other");

                    Node *max_eu = my_tree.searchMax(root, val_eu, "eu");
                    Node *max_na = my_tree.searchMax(root, val_na, "na");
                    Node *max_other = my_tree.searchMax(root, val_other, "other");
                    cout << "End of the year 1990" << endl;
                    cout << "Best seller in North America: " << max_na->name << " - " << val_na << " million.";
                    cout << "\nBest seller in Europe: " << max_eu->name << " - " << val_eu << " million.";
                    cout << "\nBest seller in rest of the world: " << max_other->name << " - " << val_other << " million." << endl
                         << endl;
                    first_91 = true; // set this true so that for the next iteration do not enter this block
                }
            }
            if (year_release == "2001")
            {
                if (!first_01)
                {
                    // Find maximum for each continent and then do search operation with the sale number.
                    double val_eu = my_tree.findMax(root, "eu");
                    double val_na = my_tree.findMax(root, "na");
                    double val_other = my_tree.findMax(root, "other");
                    // Extract the node with sale value
                    Node *max_eu = my_tree.searchMax(root, val_eu, "eu");
                    Node *max_na = my_tree.searchMax(root, val_na, "na");
                    Node *max_other = my_tree.searchMax(root, val_other, "other");
                    cout << "End of the year 2000" << endl;
                    cout << "Best seller in North America: " << max_na->name << " - " << val_na << " million.";
                    cout << "\nBest seller in Europe: " << max_eu->name << " - " << val_eu << " million.";
                    cout << "\nBest seller in rest of the world: " << max_other->name << " - " << val_other << " million." << endl
                         << endl;
                    first_01 = true;
                }
            }
            if (year_release == "2011")
            {
                if (!first_11)
                {
                    // Find maximum for each continent and then do search operation
                    double val_eu = my_tree.findMax(root, "eu");
                    double val_na = my_tree.findMax(root, "na");
                    double val_other = my_tree.findMax(root, "other");

                    Node *max_eu = my_tree.searchMax(root, val_eu, "eu");
                    Node *max_na = my_tree.searchMax(root, val_na, "na");
                    Node *max_other = my_tree.searchMax(root, val_other, "other");
                    cout << "End of the year 2010" << endl;
                    cout << "Best seller in North America: " << max_na->name << " - " << val_na << " million.";
                    cout << "\nBest seller in Europe: " << max_eu->name << " - " << val_eu << " million.";
                    cout << "\nBest seller in rest of the world: " << max_other->name << " - " << val_other << " million." << endl
                         << endl;
                    first_11 = true;
                }
            }
            if (lc == 0)
            {
                // Make the first line root initially. Though, root is updated in findRoot function below
                root = new Node(publisher, stod(na_sales), stod(eu_sales), stod(other_sales));
                my_tree.RBInsert(root);
            }
            // Search BST and if exists do not add to data, update the given node

            else if (search_node)
            {
                // If search node returns true, then match is found, so update given node
                search_node->updateNode(stod(na_sales), stod(eu_sales), stod(other_sales));
            }
            else
            {
                // A new node came, update RB tree accordingly, and in case root needs changing, change it with findRoot function
                Node *nn = new Node(publisher, stod(na_sales), stod(eu_sales), stod(other_sales));
                my_tree.RBInsert(nn);
                // Update root
                root = my_tree.findRoot(root);
            }
        }
        lc++;
    }
    // When the while loop terminates, close the file.
    // Before closing finish the last bestseller line.
    double val_eu = my_tree.findMax(root, "eu");
    double val_na = my_tree.findMax(root, "na");
    double val_other = my_tree.findMax(root, "other");

    Node *max_eu = my_tree.searchMax(root, val_eu, "eu");
    Node *max_na = my_tree.searchMax(root, val_na, "na");
    Node *max_other = my_tree.searchMax(root, val_other, "other");
    cout << "End of the year 2020" << endl;
    cout << "Best seller in North America: " << max_na->name << " - " << val_na << " million.";
    cout << "\nBest seller in Europe: " << max_eu->name << " - " << val_eu << " million.";
    cout << "\nBest seller in rest of the world: " << max_other->name << " - " << val_other << " million." << endl
         << endl;
    my_tree.preOrder(root); // print the tree as asked
    in_file.close();
    return my_tree; // return the tree for further processing (but it is not necessary for the purpose of this homework)
}
int main()
{
    RBTree my_tree;               // create the instance of red black tree here and send it to function
    my_tree = read_file(my_tree); // in here everything is done
}
