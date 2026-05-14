#include "Orderbook.h"

int main()
{
    Orderbook orderbook;

    std::cout << "BUY 10 @ 100\n";
    //                                                                                          price, quantity
    orderbook.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 1, ESide::Buy, 100, 10));
    std::cout << "orderbook size = " << orderbook.getSize() << '\n'; // 1
    std::cout << "Trying to delete order#" << 13 << '\n';
    orderbook.cancelOrder(13);
    std::cout << "SELL 10 @ 100\n";
    orderbook.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 2, ESide::Sell, 100, 10));
    std::cout << "orderbook size = " << orderbook.getSize() << '\n'; // 0

    return 0;
}