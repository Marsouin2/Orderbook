#include "Orderbook.h"
#include "OrderFileParser.h"

#include <cassert>

void automaticTests()
{
// # tests
    {
        Orderbook testOrderbookInstance;

        std::cout << "#### BEGIN Test 1 : ######\n";
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 1, ESide::Sell, 100, 5)); // orderId, price, quantity
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 2, ESide::Buy, 100, 5));
        assert(0 == testOrderbookInstance.getSize());
        std::cout << "#### Test 1 SUCCEED ######\n";

        std::cout << "#### BEGIN Test 2 : ######\n";
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 3, ESide::Sell, 100, 5)); // orderId, price, quantity
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 4, ESide::Buy, 100, 10)); // orderId, price, quantity
        assert(1 == testOrderbookInstance.getSize());
        std::cout << "#### Test 2 SUCCEED ######\n";

        std::cout << "#### BEGIN Test 3 : ######\n";
        testOrderbookInstance.addOrder(std::make_shared<Order>(EOrderType::GoodTillCancel, 5, ESide::Sell, 99, 10));
        assert(1 == testOrderbookInstance.getSize());
        std::cout << "#### Test 3 SUCCEED ######\n";
    }
}

int main()
{
    Orderbook orderbook;

    OrderFileParser orderFileParserInstance;
    std::vector<std::shared_ptr<Order>> ordersFromFile = orderFileParserInstance.getOrdersFromFile("./TradeSamples/sample1.txt");
    for (const auto& it : ordersFromFile)
    {
        orderbook.addOrder(it);
    }
    orderFileParserInstance.getOrdersFromFile("./TradeSamples/sample2.txt");
    std::cout << "size of the orderbook = " << orderbook.getSize() << '\n';

    // TESTS
    //automaticTests();

    return 0;
}