#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"

class MyDataStore : public DataStore {
  private:
    std::set<Product*> products_;
    std::vector<User*> users_;
    std::vector<std::vector<Product*>> carts_;
    
  public:
    MyDataStore();
    ~MyDataStore();
    std::vector<Product*> hits_;
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    int findUser(std::string username);
    bool addToCart(const std::string& username, int hit);
    bool viewCart(const std::string& username);
    bool buyCart(const std::string& username);

};


#endif