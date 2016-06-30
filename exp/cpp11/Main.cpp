
#include <iostream>

template< typename... Ts>
void func( Ts&&... args ) {
    std::cout << sizeof( args... );
}


int main() {
    func( 10, 10.10 );
}
