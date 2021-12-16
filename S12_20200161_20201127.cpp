//Amr Riyad - 20201127 || Hussien Mostafa - 20200161 || S12 Online Shopping
#include <iostream>
using namespace std;

//Class declaration.
class Item 
{
    string name_;
    int quantity_, ID_;
    double price_;
    static int counter_;
public:
    //Default constructor sets values to 0.
    Item(){
        name_ = "No Item";
        price_ = 0;
        quantity_ = 0;
        ID_ = 0;
    }


    //Parameterized constructor which takes the name quantity and price and sets them.
    Item(string name, int quantity, double price) : quantity_(quantity){
        name_ = name;
        price_ = price;
        ID_ = counter_;
        ++counter_;
    }


    //Copy constructor to copy an object into another.
    Item(const Item &rhs){
        name_ = rhs.name_;
        quantity_ = rhs.quantity_;
        price_ = rhs.price_;
        ID_ = counter_;
    }


    //Function to update the ID counter.
    void incrementID()
        {counter_++;}


    //Setters for the member varibales, each setter takes a value and sets it
    //and returns nothing.
    void setName(string name)
        {name_  = name;}
    void setID(int ID)
        {ID_ = ID;}
    void setQuantity(int quantity)
        {quantity_ = quantity;}
    void setPrice(int price)
        {price_ = price;}


    //Getters for the member variables, each getter takes nothing and returns the value.
    string getName()
        {return name_;}
    int getID()
        {return ID_;}
    int getQuantity()
        {return quantity_;}
    int getPrice()
        {return price_;}


    //Operator overloading.
    bool operator==(const Item &rhs) {
        return this->name_ == rhs.name_;
    }
    Item operator+=(const Item &rhs) {
        this->quantity_ += rhs.quantity_;
        return *this;
    }
    Item operator-=(const int rhs) {
        this->quantity_ -= rhs;
        return *this;
    }


    //cin operator overloading while also checking for valid input.
    friend istream &operator>>(istream &input, Item &rhs) {
        input >> rhs.name_;
        do{
            input >> rhs.quantity_ >> rhs.price_;
            if(rhs.quantity_ < 0 || rhs.price_ <= 0)
                cout << "Invalid Quantity renter the Quantity and the Price: ";
        }while(rhs.quantity_ < 0 || rhs.price_ <= 0);
        return input;
    }


    //cout operator overloading.
    friend ostream &operator<<(ostream &output, const Item &rhs){
        output << "\n"
               << "Name: "      << rhs.name_     << "\n"
               << "ID: "        << rhs.ID_       << "\n"
               << "Quanitity: " << rhs.quantity_ << "\n"
               << "Price: "     << rhs.price_    << "\n";
        return output;
    }

};

//initializing ID counter.
int Item::counter_ = 1;

//2nd Class declaration.
class Seller
{
private:
    string name_, email_;
    Item *items_;
    int maxItem_;
    static int addedItem_;
public:
    //Default constructor.
    Seller(){}


    //Paramterized constructor, which takes the name, email and max items and sets them.
    Seller(string name, string email, int maxItem): maxItem_(maxItem){
        name_ = name;
        items_ = new Item[maxItem_];
        email_ = email;
    }


    //method to add an item to an already existing one or adding a new one.
    //this method takes an item object as a param 
    //and returns true if the item is added and false otherwise. 
    bool addItem(Item item) {
        for (int i = 0; i < maxItem_; i++) {
            if (item == items_[i]) {
                items_[i] += item;
                return true;
            }
        }
        if (addedItem_ >= maxItem_) {
            return false;
        }

        //add the Item and Increment it's ID if it doesn't exist.
        items_[addedItem_] = item;
        items_[addedItem_].incrementID();
        addedItem_++;
        return true;
    }

    //Member function to sell an item.
    //this method takes an item name and the quantity 
    //and substracts the quantity if there are enough items.
    bool sellItem(string itemName, int quantity) {
        int itemQuantity = -1, itemID;
        for (int i = 0; i < maxItem_; ++i) {
            if (items_[i].getName() == itemName) {
                itemQuantity = items_[i].getQuantity();
                itemID = i;
                break;
            }
        }

        //check if the sold amount is larger than the available amount.
        if (itemQuantity == -1) return false;
        if (quantity <= itemQuantity) {
            items_[itemID] -= quantity;
        } else {
            cout << "There is only " << items_[itemID].getQuantity() 
            << " left for this item\n";
        }
        return true;
    }


    //Printing method takes nothing and returns nothing.
    void printItems(){
        for(int i = 0; i < maxItem_; i++){
            cout << items_[i];
        }
    }


    //method to return item by its ID, takes a number and returns a pointer to an item object.
    Item *FindItem(int ID) {
        for (int i = 0; i < maxItem_; i++) {
            if (ID == items_[i].getID()) {
                return &items_[i];
            }
        }
        return nullptr;
    }


    friend ostream &operator<<(ostream &output, Seller &rhs) {
        output << "Name: "                   << rhs.name_     << "\n";
        output << "Email: "                  << rhs.email_    << "\n";
        output << "Slots available in Shop: "<< rhs.maxItem_  << "\n";
        output << "Items in shop: "          << rhs.addedItem_<< "\n";
        return output;
    }
    
    //destructor to free the allocated memory.
    ~Seller() {
        delete[] items_;
    }
};

//initializing items added to the shop's counter.
int Seller::addedItem_ = 0;

//Main function.
int main()
{

    //Required variables.
    string name1, email1, itemName;
    cout << "Enter your details (name, Email): ";
    cin >> name1 >> email1;
    
    int maxItem, quantity;
    cout << "Enter the max number of items for your store capactiy: ";
    cin >> maxItem;
    Seller seller1(name1, email1, maxItem);
    Item item;
    
    //delaring a choice number to use for the switches.
    int choice;

    //as long as the choice is not equal to 6 the loop will go forever and printing the menu.
    while (true) {
        cout << "\n" << "choose from 1 to 6 what you want to do"
             << "\n" << "1. Print My Info."     << "\n" << "2. Add An Item."
             << "\n" << "3. Sell An Item."      << "\n" << "4. Print Items."
             << "\n" << "5. Find an Item by ID" << "\n" << "6. Exit"
             << "\n";

        //Entering the variable.
        cin >> choice;
        switch(choice)
        {
            case 1: 
                cout << "\n" << seller1 << "\n";
                break;
            
            case 2:
                cout << "Enter the item name, quantity and price: ";
                cin >> item;
                if(!seller1.addItem(item)){
                      cout << "No slots left to add this Item." << "\n";
                }else cout << "Item added successfully!"        << "\n";
                break;

            case 3:
                cout << "Enter the item's name and its quantity : ";
                cin >> itemName >> quantity;
                if(!seller1.sellItem(itemName, quantity)){
                    cout << "No such item exists!" << "\n";
                }
                break;
        
            case 4: 
                seller1.printItems();
                break;
        
            case 5:
                int ID;
                cout << "Enter item's ID that you want: ";
                cin >> ID;
                if(seller1.FindItem(ID) == nullptr){
                    cout<<"Item not found\n";
                }else{
                    cout << *(seller1.FindItem(ID)) << "\n";
                }
                break;
        
            case 6: 
                return 0;
                
            default:
                cout << "Invalid input";
        }
    }
}
