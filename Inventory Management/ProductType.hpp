#pragma once
#include <string>
#include <atomic>
#include <cstdint>

class ProductType {
public:
    using Id = std::uint64_t;

    ProductType(const std::string& name) : id_(generateId()), name_(name) {}

    Id id() const { return id_; }
    const std::string& name() const { return name_; }

private:
    static Id generateId() {
        static std::atomic<Id> counter{1};
        return counter++;
    }

    Id id_;
    std::string name_;
};
