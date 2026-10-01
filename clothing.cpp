#include <sstream>
#include <iomanip>
#include "clothing.h"

Clothing:: Clothing(const std::string category, const std::string name, 
  double price, int qty, const std::string size, const std::string brand) : Product(category,name,price,qty) , size_(size),brand_(brand) {

  }

Clothing::~Clothing(){

}

std::set<std::string> Clothing::keywords()const{
  std::set<std::string> keywords;
  std::string temp = category_ + " " + name_ + " " + brand_ + " " + size_;
  keywords = parseStringToWords(temp);
  return keywords;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms)const{

  std::set<std::string> keys = keywords();

  for(int i = 0; i < searchTerms.size(); i++){
    if(keys.find(convToLower(searchTerms[i]))  != keys.end()){
      return true;
    }
  }

  return false;
}

std::string Clothing::displayString()const{
  std::stringstream ss;
  ss << name_ << "\n" 
     << "Size: " << size_ << " Brand: " << brand_ << "\n"
     << price_<< " " << qty_ << " left.";
  
     return ss.str();
}

void Clothing::dump(std::ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << "\n";
}