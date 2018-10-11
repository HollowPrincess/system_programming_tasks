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
};

int main()
{
    return 0;
}