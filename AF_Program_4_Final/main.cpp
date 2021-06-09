// main.cpp

#include "table.h"
using namespace std;

/* Andy Fleischer - CS163 - Program #4 - 5/21/2021
 * ----------------------------------------------
 * This sample client code handles a table of
 * terms that map to a description and a set of
 * links. */

void add(table* my_table);
void display_all(table* my_table);
void retrieve(table* my_table, item& retrieved);
void display_retrieved(table* my_table, item retrieved);
void remove(table* my_table);
void height(table* my_table);
void efficiency(table* my_table);
void display_range(table* my_table);
void help();
void clean_input(char* string, int size);
void delete_item(item& to_delete);

int main() //main method
{
    table* my_table = new table();
    item retrieved; //set up item to be retrieved
    retrieved.concept = NULL;
    retrieved.description = NULL;
    retrieved.example_code = NULL;
    retrieved.link = NULL;

    cout << "----------------" << endl;
    cout << " Welcome to BST " << endl;
    cout << "----------------" << endl;
    help();
    
    char input[20] = "";
    while (strcmp(input, "quit") != 0) //main game loop
    {
        cout << ">> ";
        clean_input(input, 20);

        //check command
        if (strcmp(input, "add") == 0)
            add(my_table);
        else if (strcmp(input, "dall") == 0)
            display_all(my_table);
        else if (strcmp(input, "ret") == 0)
            retrieve(my_table, retrieved);
        else if (strcmp(input, "dret") == 0)
            display_retrieved(my_table, retrieved);
        else if (strcmp(input, "remove") == 0)
            remove(my_table);
        else if (strcmp(input, "height") == 0)
            height(my_table);
        else if (strcmp(input, "efficiency") == 0)
            efficiency(my_table);
        else if (strcmp(input, "drange") == 0)
            display_range(my_table);
        else if (strcmp(input, "help") == 0)
            help();
        else if (strcmp(input, "quit") != 0)
            cout << "Invalid command. Type \"help\" for list of valid commands." << endl;
    }

    delete my_table;
    delete_item(retrieved);
    return 0;
}

//add - prompt for data to add to table
void add(table* my_table)
{
    item to_add;

    to_add.concept = new char[20];
    cout << "Concept: ";
    clean_input(to_add.concept, 20);

    to_add.description = new char[200];
    cout << "Description: ";
    clean_input(to_add.description, 200);

    to_add.example_code = new char[200];
    cout << "Example code: "; //TODO - maybe make this so it can be multiple lines
    clean_input(to_add.example_code, 200);

    to_add.link = new char[100];
    cout << "Link: ";
    clean_input(to_add.link, 100);

    if (my_table->add(to_add))
        cout << "Added." << endl;
    else 
        cout << "Could not add." << endl;

    delete_item(to_add);
}

//display_all - display all data
void display_all(table* my_table)
{
    if (!my_table->display_all())
        cout << "No data!" << endl;
}

//retrieve - retrieve an item from the table and store in retrieved
void retrieve(table* my_table, item& retrieved)
{
    char concept[20];
    cout << "Concept: ";
    clean_input(concept, 20);

    if (my_table->retrieve(concept, retrieved))
        cout << "Retrieved." << endl;
    else
        cout << "Could not find that concept." << endl;
}

//display_retrieved - display the last retrieved item
void display_retrieved(table* my_table, item retrieved)
{
    my_table->display_item(retrieved);
}

//remove - remove an item by the concept name
void remove(table* my_table)
{
    char concept[20];
    cout << "Concept: ";
    clean_input(concept, 20);

    if (my_table->remove(concept))
        cout << "Removed." << endl;
    else
        cout << "Could not find that concept." << endl;
}

//height - print out the height of the tree
void height(table* my_table)
{
    cout << my_table->height() << endl;
}

//efficiency - print out the efficiency of the tree
void efficiency(table* my_table)
{
    float num = my_table->efficiency();
    if (num == -1)
        cout << "No data!" << endl;
    else
        cout << num << endl;
}

//display_range - display data that falls in a certain range
void display_range(table* my_table)
{
    //get the start and end letters
    char start;
    cout << "From: ";
    cin >> start;
    cin.clear();
    cin.ignore(1000, '\n');

    char end;
    cout << "To: ";
    cin >> end;
    cin.clear();
    cin.ignore(1000, '\n');

    int result = my_table->display_range(start, end); //store result to check for multiple cases
    if (result == 0)
        cout << "No data within that range." << endl;
    else if (result == 2)
        cout << "Invalid range." << endl;
}

//help - list all valid commands
void help()
{
    cout << "Valid commands are:" << endl;
    cout << "  add        - Add an item" << endl;
    cout << "  dall       - Display all data" << endl;
    cout << "  ret        - Retrieve an item" << endl;
    cout << "  dret       - Display the last retrieved item" << endl;
    cout << "  remove     - Remove an item by the concept name" << endl;
    cout << "  height     - List the height of the tree" << endl;
    cout << "  efficiency - List the efficiency of the tree" << endl;
    cout << "  drange     - Display a range of data" << endl;
    cout << "  help       - Display all valid commands" << endl;
    cout << "  quit       - Leave the program" << endl;
}

//clean_input - take in input into string and clean the buffer
void clean_input(char* string, int size)
{
    cin.get(string, size);
    cin.clear();
    cin.ignore(1000, '\n');
}

//delete_item - delete all data from an item if not NULL
void delete_item(item& to_delete)
{
    if (to_delete.concept) {delete [] to_delete.concept;}
    if (to_delete.description) {delete [] to_delete.description;}
    if (to_delete.example_code) {delete [] to_delete.example_code;}
    if (to_delete.link) {delete [] to_delete.link;}
}
