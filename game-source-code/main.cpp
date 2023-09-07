//#include <iostream>
#include "Management.h"

using namespace std;


int main()
{
    auto game = new Management{};
    //Load game
    auto ret = game->start();
    return ret;
}
