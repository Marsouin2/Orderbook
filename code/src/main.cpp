#include "Orderbook.h"

int main()
{
    Orderbook orderbook;

    const int orderId = 1;
    //                                                                                          price, quantity
    orderbook.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, orderId, ESide::Buy, 100, 10));
    std::cout << "orderbook size = " << orderbook.getSize() << '\n'; // 1
    orderbook.cancelOrder(13);
    std::cout << "orderbook size = " << orderbook.getSize() << '\n'; // 0

    return 0;
}