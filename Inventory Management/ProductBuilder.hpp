#pragma once
#include "Product.hpp"
#include "ProductType.hpp"
#include <string>
#include <atomic>
#include<set>

class ProductBuilder {
public:
    ProductBuilder& setName(const std::string& name) {
        name_ = name;
        return *this;
    }

    ProductBuilder& setDescription(const std::string& desc) {
        description_ = desc;
        return *this;
    }

    ProductBuilder& setType(ProductType::Id typeId) {
        typeId_ = typeId;
        return *this;
    }

    Product build() {
        return Product(generateId(), name_, description_, typeId_);
    }

private:
    static Product::Id generateId() {
        static std::atomic<Product::Id> counter{1};
        return counter++;
    }

    std::string name_;
    std::string description_;
    ProductType::Id typeId_{0};
};
