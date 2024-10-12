#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cctype>
using namespace std;

// Case Sensitive
string toLowerCase(const string& str) {
    string lowerStr = str;
    for (char& c : lowerStr){
        c = tolower(c);
    }
    return lowerStr;
}

// Item Class
class Item{
    private:
        string id;
        string name;
        int quantity;
        double price;
        string category;

    public:
        // Constructor
        Item(string id, string name, int quantity, double price, string category) {
            this->id = id;
            this->name = name;
            this->quantity = quantity;
            this->price = price;
            this->category = category;
        }

        // Getters
        string getId() const{
            return id;
        }

        string getName() const{
            return name;
        }

        int getQuantity() const{
            return quantity;
        }

        double getPrice() const{
            return price;
        }

        string getCategory() const{
            return category;
        }

        // Setters
        void setQuantity(int newQuantity){
            quantity = newQuantity;
        }

        void setPrice(double newPrice){
            price = newPrice;
        }
};

// Inventory Class
class Inventory{
    private:
        vector<Item*> items;
        int itemCount;

    public:
        // Constructor
        Inventory() : itemCount(0), items(100, nullptr) {}

        // Destructor
        ~Inventory(){
            for(int i = 0; i < itemCount; i++) {
                delete items[i];
            }
        }

        // Add Item 
        void addItem(){
            string category;
            cout << "Enter Category (Clothing, Electronics, Entertainment): ";
            cin >> category;
            category = toLowerCase(category);

            if (category != "clothing" && category != "electronics"  && category != "entertainment"){
                cout << "Category " << category << " does not exist!" << endl;
                return;
            }

            string id, name;
            int quantity;
            double price;

            cout << "Enter Item ID: ";
            cin >> id;

            // Check if ID already exists
            for(int i = 0; i < itemCount; i++) {
                if(items[i]->getId() == id){
                    cout << "Item ID already exists! Please use a unique ID." << endl;
                    return;
                }
            }

            cout << "Enter Item Name: ";
            cin.ignore(); 
            getline(cin, name);

            cout << "Enter Quantity: ";
            cin >> quantity;

            // Validate quantity
            if(cin.fail() || quantity < 0){
                cin.clear(); 
                cin.ignore(10000, '\n'); 
                cout << "Invalid quantity! Please enter a non-negative integer." << endl;
                return;
            }

            cout << "Enter Price: ";
            cin >> price;

            // Validate price
            if(cin.fail() || price < 0){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid price! Please enter a non-negative number." << endl;
                return;
            }

            if(itemCount >= 100){
                cout << "Inventory is full! Cannot add more items." << endl;
                return;
            }

            items[itemCount] = new Item(id, name, quantity, price, category);
            itemCount++;
            cout << "Item added successfully!" << endl;
        }

        // Update Item Method
        void updateItem(){
            string id;
            cout << "Enter Item ID to update: ";
            cin >> id;

            for(int i = 0; i < itemCount; i++){
                if (items[i]->getId() == id){
                    cout << "Do you want to update 'quantity' or 'price'? ";
                    string choice;
                    cin >> choice;
                    choice = toLowerCase(choice);

                    if (choice == "quantity"){
                        int newQuantity;
                        cout << "Enter new quantity: ";
                        cin >> newQuantity;

                       
                        if(cin.fail() || newQuantity < 0){
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid quantity! Please input valid quantity." << endl;
                            return;
                        }

                        int oldQuantity = items[i]->getQuantity();
                        items[i]->setQuantity(newQuantity);
                        cout << "Quantity of Item " << items[i]->getName() << " is updated from " 
                             << oldQuantity << " to " << newQuantity << endl;
                    } 
                    else if(choice == "price"){
                        double newPrice;
                        cout << "Enter new price: ";
                        cin >> newPrice;

                       
                        if(cin.fail() || newPrice < 0){
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid price! Please input valid price." << endl;
                            return;
                        }

                        double oldPrice = items[i]->getPrice();
                        items[i]->setPrice(newPrice);
                        cout << "Price of Item " << items[i]->getName() << " is updated from " 
                             << oldPrice << " to " << newPrice << endl;
                    } 
                    else {
                        cout << "Invalid choice! Please choose 'quantity' or 'price'." << endl;
                    }
                    return;
                }
            }
            cout << "Item not found!" << endl;
        }

        // Remove Item Method
        void removeItem(){
            string id;
            cout << "Enter Item ID to remove: ";
            cin >> id;

            for (int i = 0; i < itemCount; i++) {
                if (items[i]->getId() == id){ 
                    cout << "Item " << items[i]->getName() << " has been removed from the inventory." << endl;
                    
                    delete items[i];
                   
                    for(int j = i; j < itemCount -1; j++) {
                        items[j] = items[j + 1];
                    }
                    items[itemCount -1] = nullptr;
                    itemCount--;
                    return;
                }
            }

            cout << "Item not found!" << endl;
        }

        
        // Display Items by Category Method
        void displayItemByCategory() {
    string category;
    cout << "Enter Category to display (Clothing, Electronics, Entertainment): ";
    cin >> category;
    category = toLowerCase(category); // Convert input to lowercase
    bool found = false;

    // Check if the category is valid
    if (category != "clothing" && category != "electronics" && category != "entertainment") {
        cout << "Category " << category << " does not exist!" << endl;
        return;
    }

    // Display Header
    cout << left << setw(10) << "ID" 
         << setw(20) << "Name" 
         << setw(10) << "Quantity" 
         << setw(10) << "Price" 
         << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    // Display items in the specified category
    for (int i = 0; i < itemCount; i++) {
        if (toLowerCase(items[i]->getCategory()) == category) {
            cout << left << setw(10) << items[i]->getId()
                 << setw(20) << items[i]->getName()
                 << setw(10) << items[i]->getQuantity()
                 << setw(10) << fixed << setprecision(2) << items[i]->getPrice()
                 << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No items in this category." << endl;
    }
}



        // Display All Items Method
        void displayAllItems(){
            if (itemCount == 0){
                cout << "No items in the inventory!" << endl;
                return;
            }
            
           
            cout << left << setw(20) << "ID" 
                 << setw(20) << "Name" 
                 << setw(20) << "Quantity" 
                 << setw(20) << "Price" 
                 << setw(20) << "Category" 
                 << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            
            // Loop through all items and display them
            for (int i = 0; i < itemCount; i++){
                cout << left << setw(20) << items[i]->getId() 
                     << setw(20) << items[i]->getName() 
                     << setw(20) << items[i]->getQuantity() 
                     << setw(20) << fixed << setprecision(2) << items[i]->getPrice() 
                     << setw(20) << items[i]->getCategory() 
                     << endl;
            }
        }

        // Search Item Method
        void searchItem(){
            string id;
            cout << "Enter Item ID to search: ";
            cin >> id;

            for  (int i = 0; i < itemCount; i++){
                if (items[i]->getId() == id){
                    cout << "Item found!" << endl;
                    cout << "ID: " << items[i]->getId() << endl;
                    cout << "Name: " << items[i]->getName() << endl;
                    cout << "Quantity: " << items[i]->getQuantity() << endl;
                    cout << "Price: $" << fixed << setprecision(2) << items[i]->getPrice() << endl;
                    cout << "Category: " << items[i]->getCategory() << endl;
                    return;
                }
            }
            cout << "Item not found!" << endl;
        }

        // Sort Items Method
        void sortItems(){
            string criterion, order;

            cout << "Sort by 'Quantity' or 'Price'?: ";
            cin >> criterion;
            criterion = toLowerCase(criterion);

            
            if (criterion != "quantity" && criterion != "price") {
                cout << "Invalid sorting criterion! Please choose 'Quantity' or 'Price'." << endl;
                return;
            }

            cout << "Sort in 'Ascending' or 'Descending'?: ";
            cin >> order;
            order = toLowerCase(order);

            
            bool ascending;
            if (order == "ascending") {
                ascending = true;
            }
            else if (order == "descending") {
                ascending = false;
            }
            else {
                cout << "Invalid sorting order! Please choose 'Ascending' or 'Descending'." << endl;
                return;
            }

            // Bubble Sort Algorithm
            for (int i = 0; i < itemCount - 1; i++) {
                for (int j = 0; j < itemCount - i - 1; j++) {
                    bool swapNeeded = false;

                    if (criterion == "quantity") {
                        if (ascending) {
                            if (items[j]->getQuantity() > items[j+1]->getQuantity()) {
                                swapNeeded = true;
                            }
                        }
                        else {
                            if (items[j]->getQuantity() < items[j+1]->getQuantity()) {
                                swapNeeded = true;
                            }
                        }
                    }
                    else if (criterion == "price") {
                        if (ascending) {
                            if (items[j]->getPrice() > items[j+1]->getPrice()) {
                                swapNeeded = true;
                            }
                        }
                        else {
                            if (items[j]->getPrice() < items[j+1]->getPrice()) {
                                swapNeeded = true;
                            }
                        }
                    }

                    if (swapNeeded) {
                        Item* temp = items[j];
                        items[j] = items[j+1];
                        items[j+1] = temp;
                    }
                }
            }

            cout << "Items have been sorted successfully!" << endl;
            displayAllItems(); // Display sorted items
        }

        // Display Low Stock Items Method
        void displayLowStockItems(){
            bool found = false;

            // Display Header
            cout << left << setw(15) << "ID" 
                 << setw(15) << "Name" 
                 << setw(15) << "Quantity" 
                 << setw(15) << "Price" 
                 << setw(15) << "Category" 
                 << endl;
            cout << "-----------------------------------------------------------------------" << endl;

            // Loop through items and display those with quantity <= 5
            for (int i = 0; i < itemCount; i++) {
                if (items[i]->getQuantity() <= 5) {
                    cout << left << setw(15) << items[i]->getId()
                         << setw(15) << items[i]->getName()
                         << setw(15) << items[i]->getQuantity()
                         << setw(14) << fixed << setprecision(2) << items[i]->getPrice()
                         << setw(15) << items[i]->getCategory()
                         << endl;
                    found = true;
                }
            }

            if (!found){
                cout << "No low stock items found." << endl;
            }
        }
};

bool isValidInput(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;  
        }
    }
    return true;  
}

// Main Function with Menu 
int main(){
    Inventory inventory;
    string choice_str;
    int choice;
    
    while(true){
        // Display Menu
        cout << "\n===== Inventory Management System =====" << endl;
        cout << "1 - Add Item" << endl;
        cout << "2 - Update Item" << endl;
        cout << "3 - Remove Item" << endl;
        cout << "4 - Display Items by Category" << endl;
        cout << "5 - Display All Items" << endl;
        cout << "6 - Search Item" << endl;
        cout << "7 - Sort Items" << endl;
        cout << "8 - Display Low Stock Items" << endl;
        cout << "9 - Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice_str;

        if (!isValidInput(choice_str)) {
            cout << "Invalid input! Please enter a valid number between 1 and 9." << endl;
            continue;
        }

        // Convert string to integer after validation
        choice = stoi(choice_str);
        

        switch(choice){
            case 1:
                inventory.addItem();
                break;
            case 2:
                inventory.updateItem();
                break;
            case 3:
                inventory.removeItem();
                break;
            case 4:
                inventory.displayItemByCategory();
                break;
            case 5:
                inventory.displayAllItems();
                break;
            case 6:
                inventory.searchItem();
                break;
            case 7:
                inventory.sortItems();
                break;
            case 8:
                inventory.displayLowStockItems();
                break;
            case 9:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please select a number between 1 and 9." << endl;
        }
    }

    return 0;
}