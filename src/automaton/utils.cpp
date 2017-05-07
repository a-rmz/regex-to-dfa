
#include <iostream>
#include <vector>

void print_vec(std::vector<int> vec) {
  std::cout << "{";
  for(std::vector<int>::const_iterator i=vec.begin(); i != vec.end(); i++){
    if(i != vec.end()-1){
      std::cout << *i << ",";
    }
    else{
      std::cout << *i;
    }
  }
  std::cout << "} ";
}
