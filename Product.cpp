#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Product {
public:
    void setName(const std::string& name) { name_ = name; }
    std::string getName() const { return name_; }

    void setPrice(int price) { price_ = price; }
    int getPrice() const { return price_; }

    void setType(const std::string& type) { type_ = type; }
    std::string getType() const { return type_; }

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

    bool SaveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file " << filename << " for writing\n";
            return false;
        }

        for (const auto& product : products_) {
            file << product.getName() << "," << product.getPrice() << "," << product.getType() << "\n";
        }

        file.close();
        return true;
    }

    bool LoadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file " << filename << " for reading\n";
            return false;
        }

        products_.clear();

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, type;
            int price;

            if (!(iss >> name >> price >> type)) {
                std::cerr << "Failed to parse line: " << line << "\n";
                return false;
            }

            Product product;
            product.setName(name);
            product.setPrice(price);
            product.setType(type);
            products_.push_back(product);
        }

        file.close();
        return true;
    }

private:
    std::vector<Product> products_;
};

int main() {
    ProductList productList;
    std::string filename = "products.csv";

    bool loaded = productList.LoadFromFile(filename);
    if (!loaded) {
        std::cerr << "Failed to load products from file " << filename << "\n";
    }

    while (true) {
        std::cout << "Choose an option:\n";
        std::cout << "1: 상품 추가\n";
        std::cout << "2: 상품 검색\n";
        std::cout << "3: 상품 수정\n";
        std::cout << "4: 상품 제거\n";
        std::cout << "5: 상품 목록\n";
        std::cout << "6: 저장\n";
        std::cout << "7: 종료\n";

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
            bool saved = productList.SaveToFile(filename);
            if (saved) {
                std::cout << "Products saved to file " << filename << "\n";
            } else {
                std::cerr << "Failed to save products to file " << filename << "\n";
            }
        } else if (option == 7) {
            break;
        } else {
            std::cout << "Invalid option\n";
        }
    }

    return 0;
}
