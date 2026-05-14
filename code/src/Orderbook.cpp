#include "Orderbook.h"

Orderbook::Orderbook()
{

}

Orderbook::~Orderbook()
{
    //_bidOrders.empty();
    //_askOrders.empty();
}

size_t Orderbook::getSize() const
{
    std::cout << "bidOrder size = " << _bidOrders.size() << '\n';
    std::cout << "askOrder size = " << _askOrders.size() << '\n';
    return static_cast<size_t>(_bidOrders.size() + _askOrders.size());
}

void Orderbook::addNewBuyOrder(std::shared_ptr<Order> pNewOrder)
{
    std::cout << "Orderbook::addNewBuyOrder()\n";
    _bidOrders.insert({pNewOrder->getOrderId(), pNewOrder});
}

void Orderbook::addNewSellOrder(std::shared_ptr<Order> pNewOrder)
{
    std::cout << "Orderbook::addNewSellOrder()\n";
    _askOrders.insert({pNewOrder->getOrderId(), pNewOrder});
}

void Orderbook::addOrder(std::shared_ptr<Order> pNewOrder)
{
    switch(pNewOrder->getOrderSide())
    {
        case ESide::Buy:
            addNewBuyOrder(pNewOrder);
            break;
        case ESide::Sell:
            addNewSellOrder(pNewOrder);
            break;
        default:
            std::cerr << "Unknown order side for order# " << pNewOrder->getOrderId() << ". Order has not been taken in account...\n";
            break;
    }
}

std::shared_ptr<Order> Orderbook::getOrderById(const int orderId)
{
    // find and return a pointer to an order ()
}

void Orderbook::cancelOrder(const int orderId)
{
    if (_bidOrders.count(orderId))
    {
        _bidOrders.erase(orderId);
    }
    else if (_askOrders.count(orderId))
    {
        _askOrders.erase(orderId);
    }
    else
    {
        std::cerr << "ERROR : orderId#" << orderId << " is not corresponding to any order...Deleting this order was not possible...\n";
    }
}