#include <ostream>
#include <string>

template <class Head>
void messageOut(std::ostream &localOut, std::string::iterator str_iter_current, std::string::iterator str_iter_end, Head head)
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
void messageOut(std::ostream &localOut, std::string::iterator str_iter_current, std::string::iterator str_iter_end, Head head, Tail... tail)
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
bool message(std::ostream &localOut, std::string regularTemplate, Args &&... args)
{
    //check num of symbols
    int specSymCounter = 0;
    int argsNumber = sizeof...(args);

    for (std::string::iterator iter = regularTemplate.begin(); iter != regularTemplate.end(); ++iter)
    {
        if (*iter == '%')
        {
            specSymCounter++;
        };
    };

    if (specSymCounter != argsNumber)
    {
        localOut << "Number of arguments and number of places are not equal";
        return false;
    }
    else
    {
        //run message function
        std::string::iterator str_iter_begin = regularTemplate.begin();
        std::string::iterator str_iter_end= regularTemplate.end();
        messageOut(localOut, str_iter_begin,str_iter_end, args...);
    };
    return true;
}

int main()
{
    return 0;
}