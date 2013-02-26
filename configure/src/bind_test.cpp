#include<iostream>
#include<functional>

void func(double x)
{
    std::cout<<x<<std::endl;
}

int main(int argc,char **argv)
{
    auto func = std::bind(func,double(102.3));
    func();

    return 0;
}
