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
                std::cout << "상품을 찾았습니다:\n";
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
        std::cout << "수정할 상품의 인덱스를 입력하세요: ";
        std::cin >> index;

        if (index < 0 || index >= products_.size()) {
            std::cout << "유효하지 않은 인덱스입니다\n";
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
        std::cout << "삭제할 상품의 인덱스를 입력하세요: ";
        std::cin >> index;

        if (index < 0 || index >= products_.size()) {
            std::cout << "유효하지 않은 인덱스입니다\n";
            return;
        }

        products_.erase(products_.begin() + index);

        std::cout << "상품이 삭제되었습니다\n";
    }

    void ListAllProducts() const {
        for (int i = 0; i < products_.size(); ++i) {
            std::cout << "인덱스: " << i << "\n";
            std::cout << "이름: " << products_[i].getName() << "\n";
            std::cout << "가격: " << products_[i].getPrice() << "\n";
            std::cout << "종류: " << products_[i].getType() << "\n";
            std::cout << "\n";
        }
    }

    void SaveProductListToFile(const std::string& filename) const {
        std::ofstream fout(filename);
        if (!fout) {
            std::cout << "파일 " << filename << "을(를) 열 수 없습니다." << std::endl;
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
            std::cout << "파일 " << filename << "을(를) 열 수 없습니다." << std::endl;
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
    std::cout << "고객 목록:" << std::endl;
    for (const auto& customer : customers) {
        std::cout << customer.getName() << ", " << customer.getAddress() << std::endl;
    }
    std::cout << std::endl;
}

void addCustomer(std::vector<Customer>& customers) {
    std::string name, address;
    std::cout << "고객 이름을 입력하세요: ";
    std::getline(std::cin, name);
    std::cout << "고객 주소를 입력하세요: ";
    std::getline(std::cin, address);
    customers.push_back(Customer(name, address));
    std::cout << "고객 정보가 추가되었습니다." << std::endl << std::endl;
}

void modifyCustomer(std::vector<Customer>& customers) {
    std::string search_name;
    std::cout << "수정할 고객의 이름을 입력하세요: ";
    std::getline(std::cin, search_name);
    for (auto& customer : customers) {
        if (customer.getName() == search_name) {
            std::string name, address;
            std::cout << "새로운 이름을 입력하세요: ";
            std::getline(std::cin, name);
            std::cout << "새로운 주소를 입력하세요: ";
            std::getline(std::cin, address);
            customer.setName(name);
            customer.setAddress(address);
            std::cout << "고객 정보가 수정되었습니다." << std::endl << std::endl;
            return;
        }
    }
    std::cout << "고객을 찾을 수 없습니다." << std::endl << std::endl;
}

void deleteCustomer(std::vector<Customer>& customers) {
    std::string search_name;
    std::cout << "삭제할 고객의 이름을 입력하세요: ";
    std::getline(std::cin, search_name);
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->getName() == search_name) {
            it = customers.erase(it);
            std::cout << "고객 정보가 삭제되었습니다." << std::endl << std::endl;
            return;
        }
    }
    std::cout << "고객을 찾을 수 없습니다." << std::endl << std::endl;
}
void SaveCustomersToFile(const std::vector<Customer>& customers, const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout) {
        std::cout << "파일 " << filename << "을(를) 열 수 없습니다." << std::endl;
        return;
    }
    for (const auto& customer : customers) {
        fout << customer.getName() << " " << customer.getAddress() << std::endl;
    }
    fout.close();
    std::cout << "고객 정보가 파일 " << filename << "에 저장되었습니다." << std::endl;
}

void LoadCustomersFromFile(std::vector<Customer>& customers, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "파일 " << filename << "을(를) 열 수 없습니다." << std::endl;
        return;
    }
    customers.clear();
    std::string name, address;
    while (fin >> name >> address) {
        customers.push_back(Customer(name, address));
    }
    fin.close();
    std::cout << "고객 정보가 파일 " << filename << "으로부터 불러왔습니다." << std::endl;
}

class Order {
public:
    void createOrder(int number, const std::string& name) {
        this->orderNumber = number;
        this->productName = name;
    }

    void modifyOrder(int number, const std::string& name) {
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

Order* searchOrder(std::vector<Order>& orders, int orderNumber) {  //
    for (Order& order : orders) {
        if (order.getOrderNumber() == orderNumber)
            return &order;
    }
    return nullptr;
}

void loadOrders(std::vector<Order>& orders, const char* filename) {
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

void saveOrders(const std::vector<Order>& orders, const char* filename) {
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

void printOrders(std::vector<Order>& orders) {
    for (const Order& order : orders)
        std::cout << order.getOrderNumber() << ' ' << order.getProductName() << std::endl;
}

int main() {
    std::vector<Customer> customers;
    std::vector<Order> orders;
    ProductList productList;

    // 파일로부터 고객 정보 로드
    LoadCustomersFromFile(customers, "customers.txt");

    // 파일로부터 주문 정보 로드
    loadOrders(orders, "orders.txt");

    int choice;
    while (true) {
        std::cout << "====== 상점 관리 프로그램 ======" << std::endl;
        std::cout << "1. 고객 관리" << std::endl;
        std::cout << "2. 상품 관리" << std::endl;
        std::cout << "3. 주문 관리" << std::endl;
        std::cout << "4. 종료" << std::endl;
        std::cout << "메뉴를 선택하세요: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            int customerChoice;
            while (true) {
                std::cout << "====== 고객 관리 ======" << std::endl;
                std::cout << "1. 고객 목록 출력" << std::endl;
                std::cout << "2. 고객 추가" << std::endl;
                std::cout << "3. 고객 수정" << std::endl;
                std::cout << "4. 고객 삭제" << std::endl;
				std::cout << "5. 고객 정보 출력" << std::endl;
                std::cout << "6. 고객 정보 저장" << std::endl;
				std::cout << "7. 고객 정보 불러오기" << std::endl;
				std::cout << "8. 이전 메뉴로" << std::endl;
                std::cout << "메뉴를 선택하세요: ";
                std::cin >> customerChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (customerChoice == 1) {
                    printCustomers(customers);
                } else if (customerChoice == 2) {
                    addCustomer(customers);
                } else if (customerChoice == 3) {
                    modifyCustomer(customers);
                } else if (customerChoice == 4) {
                    deleteCustomer(customers);
                } else if (customerChoice == 5) {
					printCustomers(customers);
                } else if (customerChoice == 6) {
					SaveCustomersToFile(customers, "고객정보.txt");
                } else if (customerChoice == 7) {
					LoadCustomersFromFile(customers, "고객정보.txt");
                } else if (customerChoice == 8) {
                    break;
                } else {
                    std::cout << "유효하지 않은 선택입니다. 다시 선택해주세요." << std::endl;
                }
            }
        } else if (choice == 2) {
            int productChoice;
            while (true) {
                std::cout << "====== 상품 관리 ======" << std::endl;
                std::cout << "1. 상품 추가" << std::endl;
                std::cout << "2. 상품 검색" << std::endl;
                std::cout << "3. 상품 수정" << std::endl;
                std::cout << "4. 상품 삭제" << std::endl;
                std::cout << "5. 상품 목록 출력" << std::endl;
                std::cout << "6. 상품 목록 저장" << std::endl;
                std::cout << "7. 상품 목록 불러오기" << std::endl;
                std::cout << "8. 이전 메뉴로" << std::endl;
                std::cout << "메뉴를 선택하세요: ";
                std::cin >> productChoice;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (productChoice == 1) {
                    productList.AddProduct();
                } else if (productChoice == 2) {
                    productList.SearchProduct();
                } else if (productChoice == 3) {
                    productList.UpdateProductFromUserInput();
                } else if (productChoice == 4) {
                    productList.RemoveProduct();
                } else if (productChoice == 5) {
                    productList.ListAllProducts();
                } else if (productChoice == 6) {
                    productList.SaveProductListToFile("상품리스트.txt");
                } else if (productChoice == 7) {
                    productList.LoadProductListFromFile("상품리스트.txt");
                } else if (productChoice == 8) {
                    break;
                } else {
                    std::cout << "유효하지 않은 선택입니다. 다시 선택해주세요." << std::endl;
                }
            }
        } else if (choice == 3) {
            int orderChoice;
            while (true) {
                std::cout << "====== 주문 관리 ======" << std::endl;
                std::cout << "1. 주문 추가" << std::endl;
                std::cout << "2. 주문 수정" << std::endl;
                std::cout << "3. 주문 삭제" << std::endl;
                std::cout << "4. 주문 목록 출력" << std::endl;
				std::cout << "5. 주문 목록 저장" << std::endl;
				std::cout << "6. 주문 목록 출력" << std::endl;
                std::cout << "7. 이전 메뉴로" << std::endl;
                std::cout << "메뉴를 선택하세요: ";
                std::cin >> orderChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (orderChoice == 1) {
					int orderNumber;
					std::string productName;
					std::cout << "주문 번호를 입력하세요: ";
					std::cin >> orderNumber;
					std::cout << "주문 상품의 이름을 입력하세요: ";
					std::cin >> productName;
					Order order;
					order.createOrder(orderNumber, productName);
					orders.push_back(order);
					break;
				} else if (orderChoice == 2) {
					int orderNumber;
					std::string productName;
					std::cout << "수정할 주문 번호를 입력하세요: ";
					std::cin >> orderNumber;
					Order* order = searchOrder(orders, orderNumber);
					if (order) {
						std::cout << "주문 상품의 이름을 입력하세요: ";
						std::cin >> productName;
						order->modifyOrder(orderNumber, productName);
					}
					else {
						std::cout << "해당 주문이 없습니다.\n";
					}
				break;
				} else if (orderChoice == 3) {
					int orderNumber;
					std::cout << "삭제할 주문 번호를 입력하세요: ";
					std::cin >> orderNumber;
					for (auto it = orders.begin(); it != orders.end(); ++it) {
						if (it->getOrderNumber() == orderNumber) {
							orders.erase(it);
							std::cout << "주문 정보가 삭제되었습니다.\n";
							break;
						}
					}
					break;
				} else if (orderChoice == 4) {
                    printOrders(orders);
				} else if (orderChoice == 5) {
                    saveOrders(orders, "주문정보.txt");
				} else if (orderChoice == 6) {
                    loadOrders(orders, "주문정보.txt");
                } else if (orderChoice == 5) {
                    break;
                } else {
                    std::cout << "유효하지 않은 선택입니다. 다시 선택해주세요." << std::endl;
                }
            }
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "유효하지 않은 선택입니다. 다시 선택해주세요." << std::endl;
        }
    }

    return 0;
}

/*
1. 고객 관리:

Customer 클래스를 사용하여 고객 정보를 저장하고 관리합니다.
std::vector<Customer> customers를 사용하여 고객 목록을 저장합니다.
printCustomers 함수를 사용하여 고객 목록을 출력합니다.
addCustomer 함수를 사용하여 새로운 고객을 추가합니다.
modifyCustomer 함수를 사용하여 고객 정보를 수정합니다.
deleteCustomer 함수를 사용하여 고객 정보를 삭제합니다.
SaveCustomersToFile 함수를 사용하여 고객 정보를 파일에 저장합니다.
LoadCustomersFromFile 함수를 사용하여 파일로부터 고객 정보를 불러옵니다.

2. 상품 관리:

Product 클래스를 사용하여 상품 정보를 저장하고 관리합니다.
ProductList 클래스를 사용하여 상품 목록을 저장합니다.
AddProduct 함수를 사용하여 새로운 상품을 추가합니다.
SearchProduct 함수를 사용하여 상품을 검색합니다.
UpdateProductFromUserInput 함수를 사용하여 상품 정보를 업데이트합니다.
RemoveProduct 함수를 사용하여 상품을 삭제합니다.
ListAllProducts 함수를 사용하여 모든 상품 목록을 출력합니다.
SaveProductListToFile 함수를 사용하여 상품 목록을 파일에 저장합니다.
LoadProductListFromFile 함수를 사용하여 파일로부터 상품 목록을 불러옵니다.

3.주문 관리:

Order 클래스를 사용하여 주문 정보를 저장하고 관리합니다.
std::vector<Order> orders를 사용하여 주문 목록을 저장합니다.
searchOrder 함수를 사용하여 주문을 검색합니다.
loadOrders 함수를 사용하여 파일로부터 주문 정보를 불러옵니다.
saveOrders 함수를 사용하여 주문 목록을 파일에 저장합니다.
printOrders 함수를 사용하여 주문 목록을 출력합니다.
*/
