#include "example.h"
#include "move_me_out.h"

#include <iostream>

class MyClass {
public:
     MyClass(int v) {
        std::cout << "MyClass created with value: " << std::endl;
    }
};

class MyClass2 {
public:
     MyClass2(int v) {
        std::cout << "MyClass created with value: " << std::endl;
    }
};

void foo(MyClass &a, MyClass2 &b) {
    std::cout << "Function foo called." << std::endl;
}


int main() {
	cout << "Hello, World!" << endl;

	const int a{32};
	const int b{32};
	
	foo(a,b);

	example_function();
	todo_move_me_out();
	
	return 0;
}