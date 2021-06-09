// table.h

#include <iostream>
#include <cstring>
#include <math.h>

/* Andy Fleischer - CS163 - Program #4 - 5/21/2021
 * -----------------------------------------------
 * This class is a Table ADT used to map concepts
 * to a description, sample code, and related link
 * stored in a binary search tree data structure,
 * sorted alphabetically by concept. */

struct item //struct to hold term, description, sample code and related link
{
    char* concept;
    char* description;
    char* example_code;
    char* link; //related webpage for more information
};

struct node //BST node
{
    ~node();
    item data;
    node* left;
    node* right;
};

class table
{
    public:
        table(); //constructor - make table (Task 1)
        ~table(); //destructor - remove and deallocate all data (Task 1)

        //public wrapper functions below return 1 if success, 0 if fail
        int add(const item& to_add); //add an item to tree (Task 2)
        int display_all() const; //display all data for every node (Task 2)
        int display_item(const item to_display) const; //display data for one item
        int retrieve(const char* concept, item& found) const; //retrive data for concept into item found (Task 3)
        int remove(const char* concept); //remove the node matching a given concept name (Task 4)
        //function below returns 0 for no data in range, 1 for success, and 2 for invalid range
        int display_range(const char start, const char end) const; //display concepts between start and end strings (Task 7)

        //these public wrapper functions return the actual number matching their function name
        int height() const; //find and return the height of the tree (Task 5)
        float efficiency() const; //find and return the efficiency of the tree based on height and number of items (Task 6)

    private:
        void delete_all(node*& root); //recursive function for destructor
        int copy_item(item& destination, const item& source) const; //copy data from one item to another
        void display_all_tree(node* root, int depth) const; //display shape of tree, but only name of concepts
        void display_all_data(node* root) const; //display all data (no shape)
        void find_smallest(node* root, node*& parent, node*& fill) const; //find the in-order successor to help with remove

        //private recursive functions that match their partner above but take in an extra argument for the current node
        int add(const item& to_add, node*& root);
        int retrieve(const char* concept, item& found, node* root) const;
        int remove(const char* concept, node*& root);
        int display_range(const char start, const char end, node* root) const;
        int height(node* root) const;
        int count(node* root) const; //partner of efficiency

        node* root; //actual root of tree
};
