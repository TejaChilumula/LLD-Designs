#pragma once

#include "Inventory.hpp"
#include "Coin.hpp"
#include "MachineState.hpp"
#include "Item.hpp"
#include "ItemShelf.hpp"
#include "PaymentStrategy.hpp"
#include "InventoryObserver.hpp"
#include "ChangeDispenser.hpp"

#include <memory>
#include <iostream>

using namespace std;

class VendingMachine {
private:
    MachineState state = MachineState::IDLE;

    Inventory inventory;
    CoinInventory coinInventory;
    ChangeDispenser changeDispenser;
    PaymentStrategy* paymentStrategy = nullptr;

    InventoryNotifier notifier;

    int selectedShelfId = -1;

public:
    VendingMachine() : changeDispenser(coinInventory) {}

    void setPaymentStrategy(PaymentStrategy* strategy) {
        paymentStrategy = strategy;
    }

    void addObserver(InventoryObserver* observer) {
        notifier.addObserver(observer);
    }

    void loadItem(const ItemShelf& shelf) {
        inventory.addShelf(shelf);
    }

    void refillShelf(int shelfId, int quantity) {
        inventory.refillShelf(shelfId, quantity);
    }

    void selectItem(int shelfId){
        if(state != MachineState::IDLE){
            throw runtime_error("Machine is not ready for item selection");
        }

        if(!inventory.isAvailable(shelfId)){
            const string name = inventory.getItem(shelfId).getName();
            notifier.notifyOutofStock(shelfId, name);
            throw runtime_error("Selected item is not available.");
        }

        selectedShelfId = shelfId;
        state = MachineState::ITEM_SELECTED;
        cout<< "Item selected: " << inventory.getItem(shelfId).getName()
                  << " ($" << inventory.getItem(shelfId).getPrice() << ")" << std::endl;
    }

    void insertMoney(int amount){
        if(state != MachineState::ITEM_SELECTED && state != MachineState::PAYMENT_INSERTED){
            throw runtime_error("No item selected");
        }

        paymentStrategy->insertMoney(amount);
         std::cout << "Inserted $" << amount
                  << ", Total: $" << paymentStrategy->getInsertedAmount() << std::endl;

        double price = inventory.getItem(selectedShelfId).getPrice();
        if (paymentStrategy->getInsertedAmount() >= price) {
            state = MachineState::PAYMENT_INSERTED;
        }
    }


    void dispense(){
        if(state != MachineState::PAYMENT_INSERTED){
            throw runtime_error("Cannot dispense: Payment not complete.");
        }

         double price = inventory.getItem(selectedShelfId).getPrice();
        auto change = paymentStrategy->collectChange(price);

        std::cout << "Dispensing: " << inventory.getItem(selectedShelfId).getName() << std::endl;
        if (!change.empty()) {
            std::cout << "Change returned:\n";
            for (const auto& [denom, count] : change) {
                std::cout << "₹" << denom << " x " << count << "\n";
            }
        }

        inventory.dispenseItem(selectedShelfId);
        if (!inventory.isAvailable(selectedShelfId)) {
            notifier.notifyOutofStock(selectedShelfId, inventory.getItem(selectedShelfId).getName());
        }

        state = MachineState::IDLE;
        selectedShelfId = -1;
    }

    void cancelTransaction() {
        if (state == MachineState::ITEM_SELECTED || state == MachineState::PAYMENT_INSERTED) {
            std::cout << "Transaction cancelled. Returning $"
                      << paymentStrategy->getInsertedAmount() << std::endl;
            paymentStrategy->reset();
        }
        state = MachineState::IDLE;
        selectedShelfId = -1;
    }

        void refillCoins(int denomination, int count){
            changeDispenser.refill(denomination, count);
        }

        MachineState getState() const {
            return state;
        }

};