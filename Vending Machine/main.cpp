#include "VendingMachine.hpp"
#include "ItemFactory.hpp"
#include "InventoryObserver.hpp"
#include "CashPayment.hpp"
#include <iostream>

class ConsoleAlert : public InventoryObserver {
public:
    void onOutofStock(int shelfId, const std::string& itemName) override {
        std::cout << "[ALERT] Shelf " << shelfId << " is out of stock for item: " << itemName << "\n";
    }

    void onLowChange(int denomination) override {
        std::cout << "[ALERT] Low coins for denomination: ₹" << denomination << "\n";
    }
};

int main() {
    VendingMachine vm;

    // Attach observer
    ConsoleAlert alert;
    vm.addObserver(&alert);

    // Load inventory
    vm.loadItem(ItemShelf(0, ItemFactory::createItem(1), 5)); // Coke
    vm.loadItem(ItemShelf(1, ItemFactory::createItem(3), 3)); // Chips
    vm.loadItem(ItemShelf(2, ItemFactory::createItem(4), 2)); // Candy

    // Refill coins
    vm.refillCoins(1, 10);
    vm.refillCoins(5, 10);
    vm.refillCoins(10, 10);
    vm.refillCoins(20, 10);
    vm.refillCoins(50, 10);

    // Set payment strategy
    CashPayment cash(vm.getCoinInventory(), vm.getChangeDispenser());
    vm.setPaymentStrategy(&cash);

    try {
        vm.selectItem(0); // Coke
        vm.insertMoney(10);
        vm.insertMoney(10);
        vm.insertMoney(5);
        vm.insertMoney(1);
        vm.insertMoney(1);
        vm.insertMoney(1);
        vm.insertMoney(1); // Total ₹29

        vm.dispense();     // Coke costs ₹25 → change ₹4
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        vm.cancelTransaction();
    }

    return 0;
}
