#include <iostream>
#include <variant>
#include <string>

using VariantType = std::variant<int, long, float, double, std::string>;

class ObjectStoreItem {
private:
    VariantType value;

public:
    void setValue(const VariantType& newValue) {
        value = newValue;
    }

    VariantType getValue() const {
        return value;
    }

    void printValue() const {
        std::visit([](auto&& arg) {
            std::cout << arg << std::endl;
            }, value);
    }
};

int main() {
    ObjectStoreItem item;
    item.setValue(42);
    item.printValue();

    item.setValue(3.14f);
    item.printValue();

    item.setValue(123456789L);
    item.printValue();

    item.setValue("Hello, World!");
    item.printValue();

    return 0;
}