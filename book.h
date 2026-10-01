#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h"


class Book : public Product{
  private:
    std::string author_;
    std::string ISBN;

  public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn);
    ~Book();

    std::set<std::string> keywords()const;
    bool isMatch(std::vector<std::string>& searchTerms)const;
    std::string displayString()const;
    void dump(std::ostream& os) const;

};
#endif