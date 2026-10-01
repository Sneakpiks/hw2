#include <sstream>
#include <iomanip>
#include "book.h"

Book:: Book(const std::string category, const std::string name, 
  double price, int qty, const std::string author, const std::string isbn) : Product(category,name,price,qty) ,author_(author), ISBN(isbn) {

  }

Book::~Book(){

}

std::set<std::string> Book::keywords()const{
  std::set<std::string> keywords;
  std::string temp = category_ + " " + name_ + " " + author_;
  keywords = parseStringToWords(temp);
  keywords.insert(ISBN);
  return keywords;
}

bool Book::isMatch(std::vector<std::string>& searchTerms)const{

  std::set<std::string> keys = keywords();

  for(int i = 0; i < searchTerms.size(); i++){
    if(keys.find(convToLower(searchTerms[i]))  != keys.end()){
      return true;
    }
  }

  return false;
}

std::string Book::displayString()const{
  std::stringstream ss;
  ss << name_ << "\n" 
     << "Author: " << author_ << " ISBN: " << ISBN << "\n"
     << price_<< " " << qty_ << " left.";
  
     return ss.str();
}

void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << ISBN << "\n" << author_ << "\n";
}