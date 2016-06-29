#include <cstdint>
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

template< typename... Ts >
struct EvalHelper
{
    using type = void;
};


template< typename ContainerType >
struct IsStdContainer
{
    template< typename U,
              typename  = typename
                  EvalHelper<
                      typename U::value_type,
                      typename U::iterator,
                      decltype( std::declval< U >().begin() ),
                      decltype( std::declval< U >().begin() )>::type >
    static constexpr bool test( int /*unused*/ )
    {
        return true;
    }

    template< typename U > static constexpr bool test( ... )
    {
        return false;
    }

    static constexpr bool value = test< ContainerType >( int() );
};


template< typename ContainerType >
struct IsAssociativeContainer
{
    template< typename U,
              typename = EvalHelper <
                  typename U::key_type,
                  typename U::value_type >>
    static constexpr bool test( int /*unused*/ )
    {
        return IsStdContainer< U >::value;
    }

    template< typename U > static constexpr bool test( ... )
    {
        return false;
    }

    static constexpr bool value = test< ContainerType >( int () );
};


template< typename ContainerType >
struct IsSequentialContainer
{
    static constexpr bool value = IsStdContainer< ContainerType >::value
            && ( ! IsAssociativeContainer< ContainerType >::value );

//        static constexpr bool value = true;
};


template< typename ContainerType,
          typename = typename std::enable_if<
              IsAssociativeContainer< ContainerType >::value >::type >
bool contains( const ContainerType &container,
               const typename ContainerType::key_type &key )
{
    std::cout << "AssocFind" << std::endl;
    auto it = container.find( key );
    return it != std::end( container );
}


template< typename ContainerType,
          typename = typename std::enable_if<
              IsSequentialContainer< ContainerType >::value >::type >
bool contains( const ContainerType &container,
               const typename ContainerType::value_type &elem )
{
    std::cout << "SeqFind" << std::endl;
    auto it = std::find( std::begin( container ),
                         std::end( container ),
                         elem );
    bool result = it != std::end( container );
    return result;
}


int main()
{
    std::vector< int > vec { 1, 2, 3, 4 };
    std::unordered_map< int, std::string > map {{ 1,  "one" },
                                                { 2, "two" },
                                                { 3, "three" }};
    std::cout << IsStdContainer< std::vector< int >>::value
              << std::endl;
    std::cout << IsAssociativeContainer< std::map< int, int >>::value
              << std::endl;
    std::cout << IsSequentialContainer< std::vector< int >>::value
              << std::endl;
    std::cout << IsSequentialContainer< std::map< int, int >>::value
              << std::endl;

    if( contains( vec, 2 )) {
        std::cout << "Vec contains 2" << std::endl;
    }

//    if( contains( map, 2 )) {
//        std::cout << "Map contains 2" << std::endl;
//    }
}
