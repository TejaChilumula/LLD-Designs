#pragma once

#include<string>
#include<vector>
#include<memory>

using namespace std;

class InventoryObserver {
public:
    virtual void onOutofStock(int shelfId, const string& itemName) = 0;
    virtual void onLowChange(int denomination) = 0;
    virtual ~InventoryObserver() {}

};

class InventoryNotifier{
private:
    vector<InventoryObserver*> observers;

public:
    void addObserver(InventoryObserver* observer){
        observers.push_back(observer);
    }

    void notifyOutofStock(int shelfId, const string& itemName){
        for(auto* observer : observers){
            observer->onOutofStock(shelfId, itemName);
        }
    }

    void notifyLowChange(int denomination){
        for(auto* observer : observers){
            observer -> onLowChange(denomination);
        }
    }
};