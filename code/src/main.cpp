#include "Orderbook.h"

#include <cassert>

void automaticTests()
{
// # tests
    {
        Orderbook testOrderbookInstance;

        std::cout << "#### BEGIN Test 1 : ######\n";
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 3, ESide::Sell, 100, 5)); // orderId, price, quantity
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 3, ESide::Buy, 100, 5));
        assert(0 == testOrderbookInstance.getSize());
        std::cout << "#### Test 1 SUCCEED ######\n";

        std::cout << "#### BEGIN Test 2 : ######\n";
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 3, ESide::Sell, 100, 5)); // orderId, price, quantity
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 3, ESide::Buy, 100, 10)); // orderId, price, quantity
        assert(1 == testOrderbookInstance.getSize());
        std::cout << "#### Test 2 SUCCEED ######\n";

        std::cout << "#### BEGIN Test 3 : ######\n";
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 3, ESide::Sell, 99, 10));
        assert(1 == testOrderbookInstance.getSize());
        std::cout << "#### Test 3 SUCCEED ######\n";
    }
}

int main()
{
    //Orderbook orderbook;

    automaticTests();

    return 0;
}