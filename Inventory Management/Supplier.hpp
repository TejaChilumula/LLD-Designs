#include<string>
#include<atomic>
#include<cstdint>

class Supplier{
    public:
    using Id = std::uint64_t;
    Id _id;
    std:: string _name;
    std:: string _contact;

    Supplier(const std::string& name, const std::string& contact) : _id(generateId()), _name(name), _contact(contact) {}

    Id id() const { return _id; }
    const std::string& name() const { return _name; }
    const std::string& contact() const { return _contact; }

private:
    static Id generateId() {
        static std::atomic<Id> counter{1};
        return counter++;
    }

};