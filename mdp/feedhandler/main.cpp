#include <iostream>

#include "marketdata/trade.pb.h"

namespace md = exchangesim::marketdata;

int main ()
{
    md::Trade trade;
    std::cout << "Protobuf passed: Trade size " << trade.ByteSizeLong() << std::endl;
}