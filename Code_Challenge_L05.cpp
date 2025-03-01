#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>

// Function to display the inventory
void displayInventory(const std::map<std::string, int>& inventory) {
    std::cout << "Current Inventory:\n";
    for (const auto& item : inventory) {
        std::cout << item.first << ": " << item.second << " in stock\n";
    }
    std::cout << std::endl;
}

// Function to add or update a product
void addOrUpdateProduct(std::map<std::string, int>& inventory, const std::string& product, int quantity) {
    inventory[product] += quantity;  // If the product already exists, update its quantity
}

// Function to display product categories
void displayCategories(const std::set<std::string>& categories) {
    std::cout << "Product Categories:\n";
    for (const auto& category : categories) {
        std::cout << "- " << category << "\n";
    }
    std::cout << std::endl;
}

// Function to process orders
void processOrders(std::queue<std::string>& orders) {
    std::cout << "Processing Orders:\n";
    while (!orders.empty()) {
        std::cout << "Processing " << orders.front() << std::endl;
        orders.pop();  // Remove the processed order
    }
    std::cout << std::endl;
}

// Function to process restocks
void processRestocks(std::stack<std::pair<std::string, int>>& restocks) {
    std::cout << "Processing Restocks:\n";
    while (!restocks.empty()) {
        auto item = restocks.top();
        std::cout << "Restocking " << item.second << " units of " << item.first << std::endl;
        restocks.pop();  // Remove the processed restock batch
    }
    std::cout << std::endl;
}

// Function to display the shopping cart
void displayCart(const std::vector<std::string>& cart) {
    std::cout << "Items in Customer Cart:\n";
    for (const auto& item : cart) {
        std::cout << "- " << item << "\n";
    }
    std::cout << std::endl;
}

int main() {
    // Task 1: Managing products with std::map
    std::map<std::string, int> inventory;
    addOrUpdateProduct(inventory, "Laptop", 5);
    addOrUpdateProduct(inventory, "Mouse", 20);
    addOrUpdateProduct(inventory, "Keyboard", 10);
    displayInventory(inventory);

    // Update the quantity of an existing product
    addOrUpdateProduct(inventory, "Mouse", -5);  // Decrease the quantity of "Mouse" by 5
    displayInventory(inventory);

    // Task 2: Tracking unique categories with std::set
    std::set<std::string> productCategories;
    productCategories.insert("Electronics");
    productCategories.insert("Accessories");
    productCategories.insert("Peripherals");
    displayCategories(productCategories);

    // Task 3: Processing orders with std::queue
    std::queue<std::string> orders;
    orders.push("Order#1: Laptop");
    orders.push("Order#2: Mouse");
    orders.push("Order#3: Keyboard");
    processOrders(orders);

    // Task 4: Handling restocks with std::stack
    std::stack<std::pair<std::string, int>> restocks;
    restocks.push({"Mouse", 10});
    restocks.push({"Laptop", 2});
    restocks.push({"Keyboard", 5});
    processRestocks(restocks);

    // Task 5: Storing customer purchases with std::vector
    std::vector<std::string> customerCart;
    customerCart.push_back("Laptop");
    customerCart.push_back("Mouse");
    customerCart.push_back("Keyboard");
    displayCart(customerCart);

    return 0;
}
