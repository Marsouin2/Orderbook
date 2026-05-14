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
    size_t retVal{0};

    for (auto& it : _bidOrders)
    {
        ++retVal;
    }
    for (auto& it : _askOrders)
    {
        ++retVal;
    }

    return retVal;
}

void Orderbook::addNewBuyOrder(std::shared_ptr<Order> pNewOrder)
{
    _bidOrders.insert({pNewOrder->getOrderId(), pNewOrder});
}

void Orderbook::addNewSellOrder(std::shared_ptr<Order> pNewOrder)
{
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