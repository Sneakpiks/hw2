#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
  std::set<Product*>::iterator it;
  for(it = products_.begin(); it != products_.end(); it++){
    delete *it;
  }
  for(int i =0 ; i<users_.size(); i++){
    delete users_[i];
  }
}
void MyDataStore::addProduct(Product* p){
  products_.insert(p);
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
  carts_.push_back(std::vector<Product*>());
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::vector<Product*> searchResults;

  std::set<std::string> termset;
  for(int i = 0; i<terms.size(); i++){
    termset.insert(convToLower(terms[i]));
  }

  if(terms.empty()) return searchResults;

  std::set<Product*>::iterator it;
  for(it = products_.begin(); it != products_.end(); it++){
    std::set<std::string> keys = (*it)->keywords();
    std::set<std::string> commonTerms = setIntersection(termset,keys);

    if(type == 0 && commonTerms.size() == terms.size()){
      searchResults.push_back(*it);
    }
    else if(type == 1 && !commonTerms.empty()){
      searchResults.push_back(*it);
    }
  }
  hits_ = searchResults;
  return searchResults;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << "\n";
  std::set<Product*>::iterator it;
  for(it = products_.begin(); it != products_.end(); it++){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << "\n";
  ofile << "<users>" << "\n";
  for(int i =0; i < users_.size(); i++){
    users_[i]->dump(ofile);
  }
  ofile << "</users>" << "\n";
}

int MyDataStore::findUser(std::string username){
  for(int i = 0; i<users_.size(); i++){
    if((users_[i]->getName()) == username)
    {
      return i;
    }
  }
  return -1;
}

bool MyDataStore::addToCart(const std::string& username, int hit){
  int idx = findUser(username);
  if( idx == -1){
    return false;
  }
  if (hit <1 || hit > hits_.size()){
     return false;
  }
  carts_[idx].push_back(hits_[hit-1]);
  return true;
}

bool MyDataStore::viewCart(const std::string& username){
  int idx = findUser(username);
  if( idx == -1){
    return false;
  }

  for(int i =0; i < carts_[idx].size(); i++){
    std::cout << "Item " << i+1 << "\n";
    std::cout << carts_[idx][i]->displayString() <<  "\n";

  }
  return true;

}

bool MyDataStore::buyCart(const std::string& username){
  int idx = findUser(username);
  if( idx == -1){
    return false;
  }

  std::vector<Product*> leftOver;
  for(int i = 0; i<carts_[idx].size();i++){
    Product* p = carts_[idx][i];
    if(p->getQty() >0 && users_[idx]->getBalance() >= p->getPrice()){
      p->subtractQty(1);
      users_[idx] -> deductAmount(p->getPrice());
    }
    else{
      leftOver.push_back(p);
    }
  }
  carts_[idx] = leftOver;
  return true;
}