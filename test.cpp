#include <iostream>
#include <fstream>
#include <print>
#include <cstdlib>
#include <string>
#include <random>

void feed()
{
    // thread_local std::mt19937 gen(std::random_device{}());
    std::ofstream fout("in.txt");
    static int i=INT32_MIN+1;
    std::println("test: {}", i);
    fout << i++;
}

int main()
{
    using namespace std;

    std::string ansexe = "./ans.exe";
    std::string testexe = "./a.out";

    ansexe += " < in.txt > std.txt";
    testexe += " < in.txt > out.txt";

    while (true)
    {
        feed();
        system(ansexe.c_str());
        system(testexe.c_str());
        if (system("diff ans.txt out.txt"))
            break;
    }
    return 0;
}
