#include <iostream>
#include <sstream>
#include <string>


int main()
{
    auto fn = []( int i ) -> int
    {
        std::cout << i << std::endl;
        return i * 2;
    };

    for( int i = 0; i < 10; ++ i ) {
        std::cout << fn( i ) <<  std::endl;
    }

    return 0;
}
