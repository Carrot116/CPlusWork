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

int testEggs(){
    int count = 0;
    bool bFind = false;
    do {
        count++;
        if (count % 2 == 1 && count % 3 == 0 && count % 4 == 1 && count % 5 == 4 &&
            count % 6 == 3 && count % 7 == 5 && count % 8 == 1 && count % 9 == 0){
            bFind = true;
        }
    } while (bFind == false);
    return count;
};

int test(){
    return 1;
}

int main() {
    cout << "Hello, World!" << endl;
//    Base base;
//    base.print();

//    GetUserInfo();
//    GetHostInfo();
//    testMenu();
//    testMenu2();

//    connect2mysql();
//    testWrapper();

    cout << "Eggs: " << testEggs() << endl;
    return 0;
}