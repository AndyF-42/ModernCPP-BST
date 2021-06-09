// table.cpp

#include "table.h"

/* Andy Fleischer - CS163 - Program #4 - 5/21/2021
 * -----------------------------------------------
 * This class is a Table ADT used to map concepts
 * to a description, sample code, and related link
 * stored in a binary search tree data structure,
 * sorted alphabetically by concept. */

//node destructor - release all memory
node::~node()
{
    if (data.concept) {delete [] data.concept;}
    if (data.description) {delete [] data.description;}
    if (data.example_code) {delete [] data.example_code;}
    if (data.link) {delete [] data.link;}
}

//constructor - simply set root to null
table::table()
{
    root = NULL;
}

//destructor - call recursive function delete_all
table::~table()
{
    delete_all(root);
}

//delete_all - recursively delete every node from tree
void table::delete_all(node*& root)
{
    if (!root)
        return;

    delete_all(root->left);
    delete_all(root->right);    
    delete root; //call node destructor
}

//copy_item - private function to copy data from one item to another
int table::copy_item(item& destination, const item& source) const
{
    if (!source.concept || !source.description || !source.example_code || !source.link)
        return 0;

    //allocate memory for data
    destination.concept = new char[strlen(source.concept) + 1];
    destination.description = new char[strlen(source.description) + 1];
    destination.example_code = new char[strlen(source.example_code) + 1];
    destination.link = new char[strlen(source.link) + 1];

    //copy in the data
    strcpy(destination.concept, source.concept);
    strcpy(destination.description, source.description);
    strcpy(destination.example_code, source.example_code);
    strcpy(destination.link, source.link);
    
    return 1;
}

//add - public, copy data from to_add into new node
int table::add(const item& to_add)
{
    if (!to_add.concept || !to_add.description || !to_add.example_code || !to_add.link)
        return 0;
    return add(to_add, root);
}

//add - private recursive add
int table::add(const item& to_add, node*& root)
{
    if (!root)
    {
        root = new node; //create the new node and copy the item
        root->left = NULL;
        root->right = NULL;
        copy_item(root->data, to_add);
        return 1;
    }
    
    if (strcmp(to_add.concept, root->data.concept) >= 0) //move the proper direction
        return add(to_add, root->right); 
    return add(to_add, root->left);
}

//display_all - public, display all nodes' data
int table::display_all() const
{
    if (!root)
        return 0;
    display_all_tree(root, 0);
    std::cout << std::endl;
    display_all_data(root);
    return 1;
}

//display_item - public, display data for one item
int table::display_item(const item to_display) const
{
    if (!to_display.concept || !to_display.description || !to_display.example_code || !to_display.link)
        return 0; //error: no data to display

    //display all the data
    std::cout << to_display.concept << std::endl;
    for (int i = 0; i < (int)strlen(to_display.concept); ++i)
        std::cout << "-";
    std::cout << "\n" << to_display.description << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << to_display.example_code << std::endl;
    std::cout << "Related link: " << to_display.link << "\n" << std::endl;
    return 1;
}

//display_all_tree - private recursive function to display shape of tree and concepts
void table::display_all_tree(node* root, int depth) const
{
    if (!root)
        return;

    display_all_tree(root->right, depth+1); //call right side first since we are tilting 90 degrees left

    for (int i = 0; i < depth; ++i) //for whatever our depth/height is, put that much spacing then display data
        std::cout << "        ";
    std::cout << root->data.concept << std::endl;

    display_all_tree(root->left, depth+1);
}

//display_all_data - private recursive function to display all data of tree, no shape
void table::display_all_data(node* root) const
{
    if (!root)
        return;

    display_all_data(root->left);
    display_item(root->data); //display data
    display_all_data(root->right); 
}

//retrieve - public, find matching concept name and fill data into found
int table::retrieve(const char* concept, item& found) const
{
    if (!concept)
        return 0;
    return retrieve(concept, found, root);
}

//retrieve - private recursive retrieve
int table::retrieve(const char* concept, item& found, node* root) const
{
    if (!root)
        return 0;

    if (strcmp(concept, root->data.concept) == 0) //found match
    {
        copy_item(found, root->data);
        return 1;
    }

    if (strcmp(concept, root->data.concept) > 0) //need to move right
        return retrieve(concept, found, root->right);
    return retrieve(concept, found, root->left); //need to move left
}

//remove - public, remove a node matching a given concept
int table::remove(const char* concept)
{
    return remove(concept, root);
}

//remove - private recursive remove
int table::remove(const char* concept, node*& root)
{
    if (!root)
        return 0;

    if (strcmp(concept, root->data.concept) == 0) //found the match
    {
        node* temp = NULL;

        if (!root->right && root->left) //only left child
            temp = root->left;
        else if (!root->left && root->right) //only right child
            temp = root->right;
        else if (root->left && root->right) //both children
        {
            find_smallest(root->right, root, temp); //fill temp with the smallest in-order successor and update its left and right
            temp->left = root->left;
            temp->right = root->right;
        }

        delete root; //delete root and set to temp (still NULL if no children)
        root = temp;
        return 1;
    }

    if (strcmp(concept, root->data.concept) > 0) //need to move right
        return remove(concept, root->right);
    return remove(concept, root->left); //need to move left
}

//find_smallest - private, recursive, aids remove by finding the in-order successor if targeted node had two children
void table::find_smallest(node* root, node*& parent, node*& fill) const
{
    if (!root->left) //at the smallest node
    {
        fill = root;
        if (parent->right == root) //if the parent is the one about to be deleted, root is the right child
            parent->right = root->right;
        else //otherwise, just set the left child to root's right
            parent->left = root->right;
        return;
    }
    find_smallest(root->left, root, fill); //recursive call to the left
}

//height - public, return the height of the tree
int table::height() const
{
    return height(root);
}

//height - private recursive height
int table::height(node* root) const
{
    if (!root)
        return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

//efficiency - public, return the efficiency of the tree, -1 if no data
float table::efficiency() const
{
    if (!root)
        return -1;
    return (floor(log2(count(root))) + 1) / height(root); //return optimal height divided by actual height
}

//efficiency - private recursive count number of nodes
int table::count(node* root) const
{
    if (!root)
        return 0;
    return 1 + count(root->left) + count(root->right); //count the current plus all of left and right
}

//display_range - public, display data that falls in range
int table::display_range(const char start, const char end) const
{
    if (((isupper(start) && isupper(end)) || (islower(start) && islower(end))) && start < end) //check if range is valid
        return display_range(toupper(start), toupper(end), root);
    return 2; //error: invalid range
}

//display_range - private recursive display_range
int table::display_range(const char start, const char end, node* root) const
{
    if (!root)
        return 0;

    int displayed = 0; //keep track of if something was displayed
    displayed += display_range(start, end, root->left);
    if (toupper(root->data.concept[0]) >= start && toupper(root->data.concept[0]) <= end) //if the concept is in range, display it
        displayed = display_item(root->data);
    displayed += display_range(start, end, root->right);
    return displayed > 0; //only returns 0 if neither left, right, nor root was displayed
}
