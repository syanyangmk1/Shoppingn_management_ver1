#include <iostream>
#include <vector>
#include <string>

// 고객 클래스
class Customer {
public:
    Customer(const std::string& name, const std::string& address) : name_(name), address_(address) {}

    std::string getName() const { return name_; }
    std::string getAddress() const { return address_; }

    void setName(const std::string& name) { name_ = name; }
    void setAddress(const std::string& address) { address_ = address_; }

private:
    std::string name_;
    std::string address_;
};

// 고객 목록 출력 함수
void printCustomers(const std::vector<Customer>& customers) {
    std::cout << "Customers:" << std::endl;
    for (const auto& customer : customers) {
        std::cout << customer.getName() << ", " << customer.getAddress() << std::endl;
    }
    std::cout << std::endl;
}

// 고객 추가 함수
void addCustomer(std::vector<Customer>& customers) {
    std::string name, address;
    std::cout << "Enter customer name: ";
    std::getline(std::cin, name);
    std::cout << "Enter customer address: ";
    std::getline(std::cin, address);
    customers.push_back(Customer(name, address));
    std::cout << "Customer information added." << std::endl << std::endl;
}

// 고객 수정 함수
void modifyCustomer(std::vector<Customer>& customers) {
    std::string search_name;
    std::cout << "Enter customer name to modify: ";
    std::getline(std::cin, search_name);
    for (auto& customer : customers) {
        if (customer.getName() == search_name) {
            std::string name, address;
            std::cout << "Enter new name: ";
            std::getline(std::cin, name);
            std::cout << "Enter new address: ";
            std::getline(std::cin, address);
            customer.setName(name);
            customer.setAddress(address);
            std::cout << "Customer information modified." << std::endl << std::endl;
            return;
        }
    }
    std::cout << "Customer not found." << std::endl << std::endl;
}

// 고객 삭제 함수
void deleteCustomer(std::vector<Customer>& customers) {
    std::string search_name;
    std::cout << "Enter customer name to delete: ";
    std::getline(std::cin, search_name);
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->getName() == search_name) {
            it = customers.erase(it);
            std::cout << "Customer information deleted." << std::endl << std::endl;
            return;
        }
    }
    std::cout << "Customer not found." << std::endl << std::endl;
}

int main() {
    std::vector<Customer> customers;

    // 메뉴 출력
    char command;
    do {
        std::cout << "===== Customer List =====" << std::endl;
        std::cout << "1. Print customers" << std::endl;
        std::cout << "2. Add a customer" << std::endl;
        std::cout << "3. Modify a customer" << std::endl;
        std::cout << "4. Delete a customer" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter command: ";
        std::cin >> command;
        std::cin.ignore(); // 버퍼 비우기
        std::cout << std::endl;

        switch (command) {
        case '1':
            printCustomers(customers);
            break;
        case '2':
            addCustomer(customers);
            break;
        case '3':
            modifyCustomer(customers);
            break;
        case '4':
            deleteCustomer(customers);
            break;
        case '0':
            std::cout << "Good bye!" << std::endl;
            break;
        default:
            std::cout << "Invalid command." << std::endl << std::endl;
            break;
        }
    } while (command != '0');

    return 0;
}
