#include <iostream>
#include <string.h>
#include <unistd.h>

class N {
    private:
        char ann[100];
        int v;

    public:
        N(int v) { this->v = v; };
        int     operator+(const N& rhs) { return this->v + rhs.v; };
        int     operator-(const N& rhs) { return this->v - rhs.v; };

        void    setAnnotation(char* str) { memcpy(this->ann, str, strlen(str)); };
};

int main(int ac, char **av) {
    if (ac <= 1)
        _exit(1);

    N*  a;
    N*  b;

    a = new N(0x5);
    b = new N(0x6);

    a->setAnnotation(av[1]);
    return *b + *a;
}