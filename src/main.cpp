#include <ios>
#include <iostream>
#include <spdlog/spdlog.h>

int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    spdlog::info("Hello World");
    return 0;
}