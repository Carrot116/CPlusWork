#include <iostream>
#include "../head/funHead.h"
#include "../head/FunMysql.h"

using namespace std;

class Base{
public:
    Base();
    ~Base();
private:
    int  num;
    string name;

public:
    void print();
};

Base::Base(){
    num = 10;
    name = "Base";
}

Base::~Base() {

}

void Base::print() {
    cout << num << name << endl;
}


int main() {
    cout << "Hello, World!" << endl;
    Base base;
    base.print();

    GetUserInfo();
    GetHostInfo();
//    testMenu();
//    testMenu2();

    connect2mysql();
    return 0;
}