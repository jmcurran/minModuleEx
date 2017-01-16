#include <Rcpp.h>
using namespace Rcpp;

class MyClass{
  // internal variables
private:
  NumericVector data;
  bool bBender;
public:
  // default construction
  MyClass(){
    data = NumericVector::create(1,2,3);
    bBender = false;
  }

  // constructor with an argument
  MyClass(const NumericVector &x){
    data = x;
    bBender = false;
  }

  // a method that does something
  void print(void){
    if(!bBender){
      for(int i = 0; i < data.size(); i++){
        Rprintf("%f", data[i]);
        if(i < data.size() - 1)
          Rprintf(" ");
        else
          Rprintf("\n");
      }
    }else{
      Rprintf("Bite my shiny metal ass!\n");
    }
  }

  // get and set methods for the property
  bool getBender(void){
    return bBender;
  }

  void setBender(bool b){
    bBender = b;
  }
};

// Expose the class
// I prefer to give the module the same name as the class
RCPP_MODULE(MyClass) {
  using namespace Rcpp;

  class_<MyClass>( "MyClass")
    .default_constructor("Default constructor") // This exposes the default constructor
    .constructor<NumericVector>("Constructor with an argument") // This exposes the other constructor
    .method("print", &MyClass::print) // This exposes the print method
    .property("Bender", &MyClass::getBender, &MyClass::setBender) // and this shows how we set up a property
  ;
}

