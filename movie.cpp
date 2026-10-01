#include <sstream>
#include <iomanip>
#include "movie.h"

Movie :: Movie(const std::string category, const std::string name, 
  double price, int qty, const std::string genre, const std::string rating) : Product(category,name,price,qty) , genre_(genre),rating_(rating) {

  }

Movie::~Movie(){

}

std::set<std::string> Movie::keywords()const{
  std::set<std::string> keywords;
  std::string temp = category_ + " " + name_ + " " + genre_ + " " + rating_;
  keywords = parseStringToWords(temp);
  return keywords;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms)const{

  std::set<std::string> keys = keywords();

  for(int i = 0; i < searchTerms.size(); i++){
    if(keys.find(convToLower(searchTerms[i]))  != keys.end()){
      return true;
    }
  }

  return false;
}

std::string Movie::displayString()const{
  std::stringstream ss;
  ss << name_ << "\n" 
     << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
     << price_<< " " << qty_ << " left.";
  
     return ss.str();
}

void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << "\n";
}