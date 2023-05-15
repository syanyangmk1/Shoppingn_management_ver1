
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

```

void printCustomers(const std::vector<Customer>& customers) {
    std::cout << "Customers:" << std::endl;
    for (const auto& customer : customers) {
        std::cout << customer.getName() << ", " << customer.getAddress() << std::endl;
    }
    std::cout << std::endl;
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
```

**(a) Product add/search/update/remove**</br>

step-by-step explanation of the code:</br>
AddProduct function: This function adds a new product to the list of products.</br>
Collects the product information from the user (name, price, and type).</br>
Creates a new Product object and sets its properties using the setName, setPrice, and setType methods.</br>
Adds the new Product object to the list of products (products_) using the push_back method.</br>
Outputs a message to inform the user that the product has been added.</br>

SearchProduct function: This is a const function that searches for a product in the list by name.</br>
Prompts the user to enter a product name.</br>
Initializes a boolean variable found to false.</br>
Loops through the list of products (products_) and checks whether the name of the current product matches the user input. </br>
If a match is found, the function outputs the product information (name, price, type), sets found to true, and exits the loop.</br>
If no matching product is found, the function outputs a message to inform the user that the product was not found.</br>

UpdateProductFromUserInput function: This function updates the information of a product in the list.</br>
Prompts the user to enter the index of the product they wish to update.</br>
Checks whether the entered index is valid. If not, an error message is displayed, and the function returns.</br>
Collects the new product information from the user (name, price, and type) and updates the corresponding fields of the product at the specified index.</br>
Outputs a message to inform the user that the product information has been updated.</br>

RemoveProduct function: This function removes a product from the list based on the user's input.</br>
Prompts the user to enter the index of the product they wish to remove.</br>
Checks whether the entered index is valid. If not, an error message is displayed, and the function returns.</br>
Removes the product at the specified index using the erase method of the list (products_).</br>
Outputs a message to inform the user that the product has been removed.</br>

```
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
```
 **(b)Customer add / modify / remove** </br>

printCustomers function: This function prints the list of customers.</br>
Outputs a header indicating the start of the customer list.</br>
Iterates through the customers vector, and for each customer, prints the customer's name and address using the getName and getAddress methods.</br>
Inserts an empty line after printing the list.</br>

addCustomer function: This function adds a new customer to the list of customers.</br>
Prompts the user to enter the customer's name and address.</br>
Uses std::getline to obtain input. This allows users to input multiline or space-separated text.</br>
Adds a new Customer object to the customers vector with the user's inputted name and address using the push_back method.</br>
Informs the user that the customer information has been added.</br>

modifyCustomer function: This function modifies the information of an existing customer in the list.</br>
Prompts the user to enter the name of the customer they wish to modify.</br>
Iterates through the customers vector. If a customer with a matching name is found, the following steps are taken:</br>
Prompts the user to enter the new name and new address.</br>

Updates the customer's name and address with the new input by calling setName and setAddress methods.</br>
Informs the user that the customer information has been modified.</br>
Exits the loop and returns from the function.</br>
If no matching customer is found, informs the user that the customer was not found.</br>

deleteCustomer function: This function deletes a customer from the list.</br>
Prompts the user to enter the name of the customer they wish to delete.</br>
Iterates through the customers vector using an iterator. If a customer with a matching name is found, the following steps are taken:</br>
Deletes the customer from the vector using the erase method and updates the iterator.</br>
Informs the user that the customer information has been deleted.</br>
Returns from the function.</br>
If no matching customer is found, informs the user that the customer was not found.</br>

***

***

※ 그림의 제목과 내용은 모두 영문으로 작성!!!!

#### 3. 결론 </br>
결과 실행 화면 + 간단한설명


※ 모든 각각의 그림에는 (a), (b).... 등 코드를 주고 제목에서 (a), (b)의 설명이 제시되어야 함!!!!
※ 모든 그래프에는 가로축과 세로축에 대한 명칭과 단위가 표시되어야 함.


   ※ 표의 제목과 내용은 모두 영문으로 작성!!!!


 
##### REFERENCE </br>
chatGPT
wrtn 

※ 모든 참고문헌은 영문으로 작성!! 국문 참고문헌일지라도 반드시 영문으로 작성한다.
※ 저자명 표기법은 이름 다음에 성이 오도록 하며 이름은 첫 문자의 약어로 표현하며 (예를 들면, Shi-Wen(이름) Deng(성) 일 경우 S. Deng으로 Shi(첫번째 이름) Wen(두번째 이름) Deng(성) 일 경우 S.W. Deng로 표기), 저자가 6명이상일 경우 6명의 성명만 나열하고 그 다음에 “et al.” 로 표기한다.
※ 논문제목, 논문지명은 전치사 및 접속사 등을 제외하고는 모든 단어의 첫글자는 대문자로 표기하며 논문지명, 도서명, 보고서명, 학술회의 초록명 등은 이탤릭체로 표기한다.
※ 논문지명, 학술회의명은 약어를 사용하지 않고 전체를 풀어서 작성한다.
※ 기타 설명되지 않은 부분은 아래의 형식을 준용한다.

