#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <algorithm> // For std::find_if

using namespace std;

class Item
{
private:
    string name;
    int quantity;
    float price;

public:
    Item(string name, int quantity, float price)
        : name{move(name)}, quantity{quantity}, price{price} {}

    string get_name() const { return name; }
    int get_quantity() const { return quantity; }
    void set_quantity(int new_quantity) { quantity = new_quantity; }
    float get_price() const { return price; }
    bool is_match(const string &other) const { return name == other; }
};

class Inventory
{
private:
    vector<Item> items;
    float total_money;

    static void display_data(const Item &item)
    {
        cout << "\nItem name: " << item.get_name();
        cout << "\nQuantity: " << item.get_quantity();
        cout << "\nPrice: " << item.get_price();
    }

    template <typename T>
    T get_valid_input(const string &prompt, const string &error_message, T min_value)
    {
        T value;
        while (true)
        {
            cout << prompt;
            if (cin >> value && value >= min_value)
                break;

            cout << error_message;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

    auto find_item(const string &name)
    {
        return find_if(items.begin(), items.end(), [&name](const Item &item)
                       { return item.is_match(name); });
    }

public:
    Inventory() : total_money{0} {}

    void add_item()
    {
        string name;
        cout << "\nEnter item name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        int quantity = get_valid_input<int>("Enter quantity: ", "Invalid input. Enter a positive integer: ", 1);
        float price = get_valid_input<float>("Enter price: ", "Invalid input. Enter a positive number: ", 0.01f);

        items.emplace_back(name, quantity, price);
    }

    void sell_item()
    {
        string item_to_check;
        cout << "\nEnter item name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, item_to_check);

        auto it = find_item(item_to_check);
        if (it == items.end())
        {
            cout << "\nThis item is not in your Inventory";
            return;
        }

        int input_quantity = get_valid_input<int>("Enter number of items to sell: ", "Invalid input. Enter a positive integer: ", 1);

        if (input_quantity <= it->get_quantity())
        {
            float money_earned = it->get_price() * input_quantity;
            it->set_quantity(it->get_quantity() - input_quantity);
            cout << "\nItems sold";
            cout << "\nMoney received: " << money_earned;
            total_money += money_earned;

            if (it->get_quantity() == 0)
            {
                items.erase(it); // Remove item if quantity is 0
            }
        }
        else
        {
            cout << "\nCannot sell more items than you have.";
        }
    }

    void list_items() const
    {
        if (items.empty())
        {
            cout << "\nInventory empty.";
            return;
        }

        for (const auto &item : items)
        {
            display_data(item);
            cout << "\n";
        }
    }
};

int main()
{
    int choice;
    Inventory inventory_system;
    cout << "Welcome to the inventory!";

    while (true)
    {
        cout << "\n\nMENU\n"
             << "1. Add new item\n"
             << "2. Sell item\n"
             << "3. List items\n"
             << "4. Exit\n\n"
             << "Enter your choice: ";
        if (!(cin >> choice))
        {
            cout << "\nInvalid input. Please enter a number between 1 and 4.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            inventory_system.add_item();
            break;

        case 2:
            inventory_system.sell_item();
            break;

        case 3:
            inventory_system.list_items();
            break;

        case 4:
            return 0;

        default:
            cout << "\nInvalid choice entered";
            break;
        }
    }
}