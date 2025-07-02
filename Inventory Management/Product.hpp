#pragma once
#include <string>
#include <cstdint>
#include "ProductType.hpp"
#include<set>

class Product {
public:
    using Id = std::uint64_t;

    Product() : id_(0), name_(), description_(), typeId_(0) {}

    Product(Id id, const std::string& name, const std::string& desc, ProductType::Id typeId)
        : id_(id), name_(name), description_(desc), typeId_(typeId) {}

    Id id() const { return id_; }
    const std::string& name() const { return name_; }
    const std::string& description() const { return description_; }
    ProductType::Id typeId() const { return typeId_; }

private:
    Id id_;
    std::string name_;
    std::string description_;
    ProductType::Id typeId_;
};
