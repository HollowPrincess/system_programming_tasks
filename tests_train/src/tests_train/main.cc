#include <sstream>
#include <iostream>
#include <string>
using namespace std;

template <class Head>
void messageOut(::ostream &localOut, ::string::iterator str_iter_current, ::string::iterator str_iter_end, Head head)
{
    while ((*str_iter_current != '%') && (str_iter_current != str_iter_end))
    {
        localOut << *str_iter_current;
        *++str_iter_current;
    };
    *++str_iter_current;
    localOut << head;
    localOut << *str_iter_current;
}

template <class Head, class... Tail>
void messageOut(::ostream &localOut, ::string::iterator str_iter_current, ::string::iterator str_iter_end, Head head, Tail... tail)
{
    while ((*str_iter_current != '%') && (str_iter_current != str_iter_end))
    {
        localOut << *str_iter_current;
        *++str_iter_current;
    };
    *++str_iter_current;
    localOut << head;

    messageOut(localOut, str_iter_current,str_iter_end, tail...);
}

template <class... Args>
void message(::ostream &localOut, ::string regularTemplate, Args &&... args)
{
    //check num of symbols
    int specSymCounter = 0;
    int argsNumber = sizeof...(args);

    for (string::iterator iter = regularTemplate.begin(); iter != regularTemplate.end(); ++iter)
    {
        if (*iter == '%')
        {
            specSymCounter++;
        };
    };

    if (specSymCounter != argsNumber)
    {
        localOut << "Number of arguments and number of places are not equal";
    }
    else
    {
        ::string::iterator str_iter_begin = regularTemplate.begin();
        ::string::iterator str_iter_end= regularTemplate.end();
        messageOut(localOut, str_iter_begin,str_iter_end, args...);
    };
}

int main()
{
    message(cout, "%+%=%\n", 'a', 'b', 'c');
    return 0;
}