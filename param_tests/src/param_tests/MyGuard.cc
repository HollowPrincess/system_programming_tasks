#include <ostream>
#include <ios>

class MyGuard
{
    std::ostream &out;
    std::ios::fmtflags sourceFlags;
    char sourceFill;

    MyGuard(std::ostream &currentOut) : out(currentOut)
    {
        sourceFlags = out.flags();
        sourceFill = out.fill();
    }

    ~MyGuard()
    {
        out.flags(sourceFlags);
        out.fill(sourceFill);
    }
    MyGuard(const MyGuard&) = delete;
    MyGuard& operator=(const MyGuard&) = delete;
};

int main()
{
    return 0;
}
