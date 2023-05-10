#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <limits>

// Order 클래스 선언 및 구현- createOrder, modifyOrder, getOrderNumber, getProductName 메소드를 포함

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

//searchOrder 함수: 주어진 주문 번호를 가진 주문을 찾아 반환하는 함수
//주문 목록과 주문 번호를 입력받아 해당하는 주문 객체를 반환

Order* searchOrder(std::vector<Order>& orders, int orderNumber){  //
    for(Order& order : orders){
        if (order.getOrderNumber() == orderNumber)
            return &order;
    }
    return nullptr;
}

//loadOrders 함수: 파일에서 주문 목록을 읽어오는 함수
//ifstream을 사용하여 파일명을 입력받고 주문 목록에 주문을 추가

void loadOrders(std::vector<Order>& orders, const char* filename){
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "파일을 열 수 없습니다. \n";
        return;
    }

    int number;
    std::string name;

    // 파일에서 주문 목록 로드
    while (infile >> number >> name)
    {
        Order order;
        order.createOrder(number, name);
        orders.push_back(order);
    }

    infile.close();
}

//saveOrders 함수: 주문 목록을 파일로 저장하는 함수
// ofstream을 사용하여 주문 목록과 파일명을 입력받아 주문 목록을 파일로 쓰기

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
//printOrders 함수: 주문 목록을 화면에 출력하는 함수
void printOrders(std::vector<Order> &orders){
    for (const Order& order : orders)
        std::cout << order.getOrderNumber() << ' ' << order.getProductName() << std::endl;
}

//loadOrders를 호출하여 파일에서 주문 목록을 로드
//- while 루프를 사용하여 사용자의 요청에 따라 주문 목록을 출력, 생성, 수정, 삭제, 검색, 종료 등의 작업을 수행
//- 프로그램 종료 시에 saveOrders를 호출하여 변경된 주문 목록을 파일로 저장

int main() {
    std::vector<Order> orders;
    loadOrders(orders, "input.txt");

    int choice;
    while (true) {
        std::cout << "1. 주문 목록 출력\n";
        std::cout << "2. 주문 생성\n";
        std::cout << "3. 주문 수정\n";
        std::cout << "4. 주문 삭제\n";
        std::cout << "5. 주문 검색\n";
        std::cout << "6. 종료\n";

        std::cout << "선택해주세요: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            printOrders(orders);
        }
        else if (choice == 2) {
            int number;
            std::string productName;
            std::cout << "주문 번호: ";
            std::cin >> number;
            std::cout << "상품 이름: ";
            std::cin >> productName;

            Order order;
            order.createOrder(number, productName);
            orders.push_back(order);
        }
        else if (choice == 3) {
            int number;
            std::string productName;
            std::cout << "변경할 주문 번호: ";
            std::cin >> number;
            std::cout << "새 상품 이름: ";
            std::cin >> productName;

            Order* order = searchOrder(orders, number);
            if (order) {
                order->modifyOrder(number, productName);
            }
            else {
                std::cout << "주문을 찾을 수 없습니다.\n";
            }
        }
         else if (choice == 4) { 
            int number; 
            std::cout << "삭제할 주문 번호: "; 
            std::cin >> number; 
            
            orders.erase(std::remove_if(orders.begin(), orders.end(), [&](const Order& o) { 
                return o.getOrderNumber() == number; 
            }), orders.end()); 
         }
        else if (choice == 5) {
            int number;
            std::cout << "검색할 주문 번호: ";
            std::cin >> number;

            Order* order = searchOrder(orders, number);
            if (order) {
                std::cout << "찾은 상품: " << order->getProductName() << '\n';
            }
            else {
                std::cout << "주문을 찾을 수 없습니다.\n";
            }
        }
        else if (choice == 6) {
            break;
        }
        else {
            std::cout << "잘못 입력했습니다. 다시 입력해주세요.\n";
        }
    }

    saveOrders(orders, "output.txt");
    return 0;
}
