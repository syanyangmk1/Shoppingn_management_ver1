#include <iostream>
#include <fstream>  
#include <sstream> 
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <limits>

class Product {
public:
    void setName(const std::string& name) { name_ = name; }
    std::string getName() const { return name_; }

    void setPrice(int price) { price_ = price; }
    int getPrice() const { return price_; }

    void setType(const std::string& type) { type_ = type; }
    std::string getType() const { return type_; }
 
    friend std::istream& operator>>(std::istream& is, Product& product) {
        std::string line;
        if (std::getline(is, line)) {
            std::stringstream ss(line);
            std::string name, type;
            int price;
            ss >> name >> price >> type;
            product.setName(name);
            product.setPrice(price);
            product.setType(type);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << product.getName() << " " << product.getPrice() << " " << product.getType() << std::endl;
        return os;
    }

private:
    std::string name_;
    int price_;
    std::string type_;
};

class ProductList {
public:
    void AddProduct() {
        std::string name, type;
        int price;

        std::cout << "상품의 이름: ";
        std::cin >> name;

        std::cout << "상품의 가격: ";
        std::cin >> price;

        std::cout << "상품의 종류: ";
        std::cin >> type;

        Product product;
        product.setName(name);
        product.setPrice(price);
        product.setType(type);

        products_.push_back(product);

        std::cout << "상품이 추가됨\n";
    }

    void SearchProduct() const {
        std::string name;
        std::cout << "상품 이름을 검색해보세요: ";
        std::cin >> name;

        bool found = false;
        for (const auto& product : products_) {
            if (product.getName() == name) {
                std::cout << "Product found:\n";
                std::cout << "이름: " << product.getName() << "\n";
                std::cout << "가격: " << product.getPrice() << "\n";
                std::cout << "종류: " << product.getType() << "\n";
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "해당 상품이 없습니다\n";
        }
    }

    void UpdateProductFromUserInput() {
        int index;
        std::cout << "Enter the index of the product you want to update: ";
        std::cin >> index;

        if (index < 0 || index >= products_.size()) {
            std::cout << "Invalid index\n";
            return;
        }

        std::string name, type;
        int price;

        std::cout << "상품의 새로운 이름: ";
        std::cin >> name;
        products_[index].setName(name);

        std::cout << "상품의 새로운 가격: ";
        std::cin >> price;
        products_[index].setPrice(price);

        std::cout << "상품의 새로운 종류: ";
        std::cin >> type;
        products_[index].setType(type);

        std::cout << "상품 정보가 업데이트 되었습니다.\n";
    }

    void RemoveProduct() {
        int index;
        std::cout << "Enter the index of the product you want to remove: ";
        std::cin >> index;

        if (index < 0 || index >= products_.size()) {
            std::cout << "Invalid index\n";
            return;
        }

        products_.erase(products_.begin() + index);

        std::cout << "Product removed\n";
    }

    void ListAllProducts() const {
        for (int i = 0; i < products_.size(); ++i) {
            std::cout << "Index: " << i << "\n";
            std::cout << "Name: " << products_[i].getName() << "\n";
            std::cout << "Price: " << products_[i].getPrice() << "\n";
            std::cout << "Type: " << products_[i].getType() << "\n";
            std::cout << "\n";
        }
    }

    void SaveProductListToFile(const std::string& filename) const {
        std::ofstream fout(filename);
        if (!fout) {
            std::cout << "Failed to open file " << filename << std::endl;
            return;
        }
        for (const auto& product : products_) {
            fout << product;
        }
        fout.close();
        std::cout << "상품 리스트가 파일 " << filename << "에 저장되었습니다." << std::endl;
    }
 
    void LoadProductListFromFile(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin) {
            std::cout << "Failed to open file " << filename << std::endl;
            return;
        }
        products_.clear();
        Product product;
        while (fin >> product) {
            products_.push_back(product);
        }
        fin.close();
        std::cout << "상품 리스트가 파일 " << filename << "에서 불러오기 완료되었습니다." << std::endl;
    }

private:
    std::vector<Product> products_;
};

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

void printCustomers(const std::vector<Customer>& customers) {
    std::cout << "Customers:" << std::endl;
    for (const auto& customer : customers) {
        std::cout << customer.getName() << ", " << customer.getAddress() << std::endl;
    }
    std::cout << std::endl;
}

void addCustomer(std::vector<Customer>& customers) {
    std::string name, address;
    std::cout << "Enter customer name: ";
    std::getline(std::cin, name);
    std::cout << "Enter customer address: ";
    std::getline(std::cin, address);
    customers.push_back(Customer(name, address));
    std::cout << "Customer information added." << std::endl << std::endl;
}

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

class Order {                                             
public:
    void createOrder(int number, const std::string& name){
        this->orderNumber = number;
        this->productName = name;
    }

    void modifyOrder(int number, const std::string& name){
        this->orderNumber = number;
        this->productName = name;
    }

    int getOrderNumber() const {
        return orderNumber;
    }

    const std::string& getProductName() const {
        return productName;
    }

private:
    int orderNumber;
    std::string productName;
};

Order* searchOrder(std::vector<Order>& orders, int orderNumber){  //
    for(Order& order : orders){
        if (order.getOrderNumber() == orderNumber)
            return &order;
    }
    return nullptr;
}

void loadOrders(std::vector<Order>& orders, const char* filename){
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "파일을 열 수 없습니다. \n";
        return;
    }

    int number;
    std::string name;

    while (infile >> number >> name)
    {
        Order order;
        order.createOrder(number, name);
        orders.push_back(order);
    }

    infile.close();
}

void saveOrders(const std::vector<Order>& orders, const char* filename){
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "파일을 저장할 수 없습니다. \n";
        return;
    }
    for (const Order& order : orders) {
        outfile << order.getOrderNumber() << ' ' << order.getProductName() << std::endl;
    }
    outfile.close();
}

void printOrders(std::vector<Order> &orders){
    for (const Order& order : orders)
        std::cout << order.getOrderNumber() << ' ' << order.getProductName() << std::endl;
}

int main() {
    ProductList productList;
    std::vector<Customer> customers;
    std::vector<Order> orders;

    int choice;
    while (true) {
        std::cout << "===== 재고 관리 시스템 =====" << std::endl;
        std::cout << "1. 상품 추가" << std::endl;
        std::cout << "2. 상품 검색" << std::endl;
        std::cout << "3. 상품 업데이트" << std::endl;
        std::cout << "4. 상품 삭제" << std::endl;
        std::cout << "5. 모든 상품 목록" << std::endl;
        std::cout << "6. 고객 추가" << std::endl;
        std::cout << "7. 고객 수정" << std::endl;
        std::cout << "8. 고객 삭제" << std::endl;
        std::cout << "9. 주문 생성" << std::endl;
        std::cout << "10. 주문 수정" << std::endl;
        std::cout << "11. 상품 목록 저장" << std::endl;
        std::cout << "12. 상품 목록 불러오기" << std::endl;
        std::cout << "13. 주문 저장" << std::endl;
        std::cout << "14. 주문 불러오기" << std::endl;
        std::cout << "15. 모든 주문 목록" << std::endl;
        std::cout << "16. 종료" << std::endl;
        std::cout << "======================================" << std::endl;
        std::cout << "메뉴 선택: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                productList.AddProduct();
                break;
            case 2:
                productList.SearchProduct();
                break;
            case 3:
                productList.UpdateProductFromUserInput();
                break;
            case 4:
                productList.RemoveProduct();
                break;
            case 5:
                productList.ListAllProducts();
                break;
            case 6:
                addCustomer(customers);
                break;
            case 7:
                modifyCustomer(customers);
                break;
            case 8:
                deleteCustomer(customers);
                break;
            case 9: {
                int orderNumber;
                std::string productName;
                std::cout << "주문 번호를 입력하세요: ";
                std::cin >> orderNumber;
                std::cout << "상품 이름을 입력하세요: ";
                std::cin.ignore();
                std::getline(std::cin, productName);

                Order order;
                order.createOrder(orderNumber, productName);
                orders.push_back(order);
                std::cout << "주문이 생성되었습니다.." << std::endl << std::endl;
                break;
            }
            case 10: {
                int orderNumber;
                std::string productName;
                std::cout << "수정할 주문 번호를 입력하세요: ";
                std::cin >> orderNumber;
                std::cout << "새로운 제품 이름을 입력하세요: ";
                std::cin.ignore();
                std::getline(std::cin, productName);

                Order* order = searchOrder(orders, orderNumber);
                if (order != nullptr) {
                    order->modifyOrder(orderNumber, productName);
                    std::cout << "주문이 수정되었습니다." << std::endl << std::endl;
                } else {
                    std::cout << "주문을 찾을 수 없습니다." << std::endl << std::endl;
                }
                break;
            }
            case 11: {
    std::string filename;
    std::cout << "상품 목록을 저장할 파일 이름을 입력하세요: ";
    std::cin >> filename;
    productList.SaveProductListToFile(filename);
    std::cout << "상품 목록이 파일로 저장되었습니다." << std::endl << std::endl;
    break;
}

case 12: {
    std::string filename;
    std::cout << "불러올 상품 목록 파일 이름을 입력하세요: ";
    std::cin >> filename;
    productList.LoadProductListFromFile(filename);
    std::cout << "상품 목록이 파일로부터 불러와졌습니다." << std::endl << std::endl;
    break;
}

case 13: {
    std::string filename;
    std::cout << "주문을 저장할 파일 이름을 입력하세요: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    saveOrders(orders, filename.c_str());
    std::cout << "주문이 파일로 저장되었습니다." << std::endl << std::endl;
    break;
}

case 14: {
    std::string filename;
    std::cout << "불러올 주문 파일 이름을 입력하세요: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    loadOrders(orders, filename.c_str());
    std::cout << "주문이 파일로부터 불러와졌습니다." << std::endl << std::endl;
    break;
}

case 15: {
    std::cout << "주문 목록:" << std::endl;
    printOrders(orders);
    std::cout << std::endl;
    break;
}

case 16: {
    std::cout << "프로그램을 종료합니다..." << std::endl;
    return 0;

default:
    std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl << std::endl;
    break;
}
		}
	}
}
