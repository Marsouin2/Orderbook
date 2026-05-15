#include "Orderbook.h"

int main()
{
    Orderbook orderbook;

    std::cout << "BUY 11 @ 100\n";
    orderbook.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 1, ESide::Buy, 100, 11));
    std::cout << "orderbook size = " << orderbook.getSize() << '\n'; // 1
    std::cout << "SELL 10 @ 100\n";
    orderbook.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 2, ESide::Sell, 100, 10));
    std::cout << "orderbook size = " << orderbook.getSize() << '\n'; // 0

    return 0;
}