#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
int main(int argc, char* argv[])
{
    //argc is argument count, de naam van programma zit erin
    //argv is argument vector
    if (argc ==4)
    {
        for (int i = 0; i < strlen(argv[2]); i++)
        {
            if (std::isdigit(argv[2][i]) == 0)
            {
                std::cout << "Usage: \"calc.exe operation intValue1 Value2\"\nExample \"ArgsDemo.exe + 12 35\"\n";
                return 0;
            }
        }
        int firstNum{ stoi(argv[2]) };
        int secondNum{ stoi(argv[3]) };
        int res{};
        int rest{};

        switch (*argv[1])
        {
        case '+':
            res = firstNum + secondNum;
            break;
        case '-':
            res = firstNum - secondNum;
            break;
        case '*':
            res = firstNum * secondNum;
            break;
        case '/':
            if (secondNum ==0)
            {
                std::cout << "Division by 0 is illegal\n";
                return 0;
            }
            res = firstNum / secondNum;
            rest = firstNum % secondNum;
            if (rest !=0)
            {
                std::cout << "The rest is: " << rest << '\n';
            }
            break;
        default:
            std::cout << "Usage: \"calc.exe operation intValue1 Value2\"\nExample \"ArgsDemo.exe + 12 35\"\n";
            return 0;
            break;
        }

        std::cout << res << '\n';

    }
    else
    {
        std::cout << "Usage: \"calc.exe operation intValue1 Value2\"\nExample \"ArgsDemo.exe + 12 35\"\n";
        return 0;
    }
   

    std::cin.get();
}

