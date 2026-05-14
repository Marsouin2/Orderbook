#include <iostream>
#include <memory>

#include "Orderbook.h"

int main()
{
    Orderbook orderbook;

    const int orderId = 1;
    //                                                                                          price, quantity
    //orderbook.addOrder(std::make_unique<Order>(OrderType::GoodTillCancel, orderId, Side::Buy, 100, 10));
    std::cout << orderbook.getSize() << '\n'; // 1
    //orderBook.cancelOrder();
    std::cout << orderbook.getSize() << '\n'; // 0

    return 0;
}