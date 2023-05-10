#include <iostream>
#include <fstream> // 파일 입출력에 이용하는 헤더 파일입니다. 
#include <sstream> // stringstream을 이용하여 문자열을 파싱하기 위한 헤더 파일입니다. 
#include <string>
#include <vector>

/* 상품 정보를 저장하는 클래스입니다. 이름, 가격, 종류의 정보를 저장할 수 있습니다.
void setName(const std::string& name): 상품 이름을 설정합니다.
std::string getName() const: 상품 이름을 반환합니다.
void setPrice(int price): 상품 가격을 설정합니다.
int getPrice() const: 상품 가격을 반환합니다.
void setType(const std::string& type): 상품 종류를 설정합니다.
std::string getType() const: 상품 종류를 반환합니다.
friend std::istream& operator>>(std::istream& is, Product& product): 상품 정보를 파일로부터 읽어올 때 사용됩니다.
friend std::ostream& operator<<(std::ostream& os, const Product& product): 상품 정보를 파일로 저장할 때 사용됩니다.
*/
class Product {
public:
    void setName(const std::string& name) { name_ = name; }
    std::string getName() const { return name_; }

    void setPrice(int price) { price_ = price; }
    int getPrice() const { return price_; }

    void setType(const std::string& type) { type_ = type; }
    std::string getType() const { return type_; }

    // 상품 정보를 파일로부터 읽어올 때 사용됩니다. 
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

    // 상품 정보를 파일로부터 읽어오며, 이를 위한 오버로드하기 위한 ">>" 연산자입니다.
    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << product.getName() << " " << product.getPrice() << " " << product.getType() << std::endl;
        return os;
    }

private:
    std::string name_;
    int price_;
    std::string type_;
};
/*
상품 정보를 관리하는 클래스입니다. Product 객체들을 vector로 관리합니다.
void AddProduct(): 상품을 추가합니다.
void SearchProduct() const: 상품을 검색합니다.
void UpdateProductFromUserInput(): 상품 정보를 업데이트합니다.
void RemoveProduct(): 상품을 제거합니다.
void ListAllProducts() const: 모든 상품을 출력합니다.
void SaveProductListToFile(const std::string& filename) const: 상품 리스트를 파일에 저장합니다.
void LoadProductListFromFile(const std::string& filename): 파일로부터 상품 리스트를 불러옵니다.
*/
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

    // 상품 정보를 파일에 저장하는 함수입니다. 
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

    // 상품 정보를 파일로부터 읽어오는 함수입니다. 
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

/*사용자가 선택한 옵션에 따라 ProductList 클래스의 멤버 함수를 호출합니다.
사용자가 1~8 이외의 옵션을 선택할 경우 "Invalid option"을 출력합니다.
*/
int main() {
    ProductList productList;

    while (true) {
        std::cout << "Choose an option:\n";
        std::cout << "1: 상품 추가\n";
        std::cout << "2: 상품 검색\n";
        std::cout << "3: 상품 수정\n";
        std::cout << "4: 상품 제거\n";
        std::cout << "5: 상품 목록\n";
        std::cout << "6: 파일에 상품 정보 저장하기\n";
        std::cout << "7: 파일에서 상품 정보 불러오기\n";
        std::cout << "8: 종료\n";

        int option;
        std::cin >> option;

        if (option == 1) {
            productList.AddProduct();
        } else if (option == 2) {
            productList.SearchProduct();
        } else if (option == 3) {
            productList.UpdateProductFromUserInput();
        } else if (option == 4) {
            productList.RemoveProduct();
        } else if (option == 5) {
            productList.ListAllProducts();
        } else if (option == 6) {
            std::string filename;
            std::cout << "상품 정보를 저장할 파일 이름을 입력하세요: ";
            std::cin >> filename;
            productList.SaveProductListToFile(filename);
        } else if (option == 7) {
            std::string filename;
            std::cout << "불러올 파일 이름을 입력하세요: ";
            std::cin >> filename;
            productList.LoadProductListFromFile(filename);
        } else if (option == 8) {
            break;
        } else {
            std::cout << "Invalid option\n";
        }
    }

    return 0;
}
