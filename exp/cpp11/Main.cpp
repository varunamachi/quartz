
#include <iostream>
#include <sstream>


class Stream
{
public:
    static const struct ToStrType
    {

    } ToStr;

    Stream()
    {

    }


    template< typename T >
    Stream & operator << ( const T &t )
    {
        m_stream << t;
        return *this;
    }

    typedef std::ostream& ( manip )( std::ostream& );

    Stream & operator << ( manip& m ) {
        m_stream << m;
        return *this;
    }

    std::string operator << (ToStrType )
    {
        return m_stream.str();
    }

private:
    std::stringstream m_stream;

};


int main()
{
    auto str = "Hello!";
    auto i = 100;
    auto w = 200.45;

    Stream stream;
    std::string s = stream << str << " -- " << i << " -- " << " -- " << w << Stream::ToStr;

}
