
# C++ 기반의 온라인 쇼핑몰 시스템</br>
*김홍빈, *양용석, *최성욱</br>
*3조</br>
Online shopping mall system based on C++</br>
*Hongbin kim, Yongseok Yang, Seonguk Choi</br>
*Team 3</br>


● **투고분야 : 온라인 쇼핑몰 관리 시스템**</br>

● Corresponding Author : Jaechang Shim</br>
- Address : (36729) 1375 Gyeongdong-ro, Andong-si, Gyeongsangbuk-do, Republic of Korea</br>
- TEL : +82-54-820-5645</br>
- FAX : +82-54-820-6164</br>
- E-mail : jcshim@anu.ac.kr</br>



**C++ 기반의 온라인 쇼핑몰 시스템**</br>

Online shopping mall system based on C++ </br>

**Abstract**</br>
The goal of this project is to create an accessible and efficient online shopping platform </br>
that facilitates easy product search and purchase for customers,</br>
while providing sellers with the tools to manage product information and sales. </br>
To achieve this, the system incorporates various programming concepts such as</br>
classes, inheritance, polymorphism, templates, and STL containers to ensure efficient management of product, customer, and order details.</br>
Additionally, it uses file input/output techniques for reliable data storage and retrieval. </br>
Key functions include comprehensive product, customer, and order management that cover</br>
adding, modifying, deleting, searching, and displaying lists of the respective data. </br>
With this system in place, businesses can expand their reach to a wider range of customers without geographical limitations, </br>
enhancing user experience and convenience for all parties involved.</br>

**Keyword** : E-commerce, Customer management, Product management, Order management, C++ based system </br>


## 1. 서론</br>

이번 프로젝트의 목적은 고객이 인터넷을 통해 상품을 쉽게 검색하고 구매할 수 있도록 하는 것이다.</br>
이를 위해 고객은 온라인으로 상품을 선택하고 결제할 수 있으며, 판매자는 상품 정보를 업로드하고 판매 관리를 할 수 있다.</br>
온라인 쇼핑몰 시스템은 온라인 상거래 시장이 크게 성장하면서 많은 기업들이 사용하고 있는 중요한 비즈니스 도구이다.</br>
이를 통해 기업은 지리적 제한 없이 광범위한 고객층을 대상으로 상품을 판매할 수 있으며, 고객들은 편리하게 원하는 상품을 구매할 수 있다.</br>
따라서 이번 프로젝트에서는 고객과 판매자 모두에게 편리하고 쉬운 사용 경험을 제공하며, 간단한 기능을 갖춘 온라인 쇼핑몰 시스템을 개발하고자 한다.</br>
이 시스템의 관리자의 입장에서는 효율적인 관리를 위해 다양한 기능이 필요하다. 아래가 요구사항 및 주요 기능이다. </br>
 
□ **요구사항**</br>

○ 클래스를 사용하여 상품, 고객, 주문 정보를 표현</br>

○ 상속을 활용하여 다양한 상품 및 고객 유형 구현</br>

○ 다형성을 사용하여 상품 및 고객 관련 처리를 일반화</br>

○ 템플릿 및 STL 컨테이너를 사용하여 상품, 고객, 주문 정보 관리</br>

○ 파일 입출력을 사용하여 데이터 저장 및 로드 기능 구현</br>
</br>
□ **주요 기능**</br>

○ 상품 관리: 상품 추가, 수정, 삭제, 검색, 목록 출력</br>

○ 고객 관리: 고객 등록, 수정, 삭제, 검색, 목록 출력</br>

○ 주문 관리: 주문 생성, 수정, 삭제, 검색, 목록 출력</br>



### 2. 본론</br>
-main function (Customers, Product, Order) 

```
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
```

**(a) Product part**</br>

The Product class represents a product with a name, price, and type. Using member functions,</br>
you can set and get these attributes. The class also has overloaded stream operators to read and write the attributes to and from standard input and output.</br>
The ProductList class manages a list of Product objects. It provides the following functionalities:</br>

AddProduct(): Add a new product to the list by prompting the user for the product's name, price, and type.</br>

SearchProduct(): Search for a product by its name. If found, display its information.</br>

UpdateProductFromUserInput(): Update an existing product by index, prompting the user for the new name, price, and type.</br>

RemoveProduct(): Remove a product by its index.</br>

ListAllProducts(): Display the information of all the products in the list.</br>

```

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

```
 **(b)Customer part** </br>

A constructor that initializes the customer object with a given name and address.</br>
Getter functions for the name and address.</br>
Setter functions to change the name and address.</br>

The following functions are provided for customer management:</br>

printCustomers: prints the list of customers along with their names and addresses.</br>
addCustomer: prompts the user to enter a name and address, creates a new customer object, and adds it to the list of customers.</br>
modifyCustomer: searches for a customer by name, and if found, prompts the user to enter new name and address values, and modifies the customer object accordingly.</br>
deleteCustomer: searches for a customer by name, and if found, removes it from the list of customers.</br>
SaveCustomersToFile: saves the list of customers to a file with the given filename.</br>
LoadCustomersFromFile: loads a list of customers from a file with the given filename and stores them in the customers vector.</br>

```
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
```
**(c) Order create/search/modify** </br>


class Order: This class has two private member variables, orderNumber (an integer) and productName (a string). </br>
There are provided public member functions to create, modify, and access these variables:</br>
createOrder(int number, const std::string& name): Initializes an Order object with the specified order number and product name.</br>

modifyOrder(int number, const std::string& name): Modifies an existing Order object, updating its order number and product name.</br>

getOrderNumber() const: Returns the order number of an Order object.</br>

getProductName() const: Returns a constant reference to the product name of an Order object.</br>

Order* searchOrder(std::vector<Order>& orders, int orderNumber): This function takes a reference to a vector of Orders and an order number.</br>
 It searches for an order with the given order number in the vector and returns a pointer to that order if found, or nullptr if not found.</br>

void loadOrders(std::vector<Order>& orders, const char* filename): This function reads a file specified by the filename and loads Order objects</br>
 from the file into the provided orders vector. It reads the order number and product name from the file and uses the createOrder function to initialize</br>
 the Order objects. If the file cannot be opened, it prints an error message.</br>
 
void saveOrders(const std::vector<Order>& orders, const char* filename): This function writes the orders from the provided orders vector to a file </br>
 specified by the filename. It writes the order number and product name of each order in the vector. If the file cannot be created, it prints an error message.</br>

void printOrders(std::vector<Order>& orders): This function prints the order number and product name of each order in the provided orders vector to the standard output.</br>




#### 3. 결론 </br>

<img src="실행 화면/1메뉴.png">
(a) excute screen </br>
categorized into customer, order, and product menu</br>

<img src="실행 화면/2-1고객정보추가.png">
(b) AddCustomer </br>
Enter and add customer information</br>

<img src="실행 화면/2-2고객출력.png">
(c) PrintCustomer </br>
Prints out a list of saved customers</br>

<img src="실행 화면/3-1상품추가.png">
(d) Add Product</br>
Enter product information and add it to the list</br>

<img src="실행 화면/3-2상품검색.png">
(e) Search Product</br>
Search for items stored in the list</br>

<img src="실행 화면/3-3상품목록.png">
(f) ProductList</br>
Show products stored in the list</br>
<img src="실행 화면/4-1주문추가.png">
(g) Add Order</br>
Add an order and save it to the list</br>
<img src="실행 화면/4-2주문출력.png">
(h) Print Order</br>
Loads and prints orders stored in the list</br>
          

 
##### - REFERENCE </br>
chatGPT</br>
wrtn 

