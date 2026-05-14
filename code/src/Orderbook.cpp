#include "Orderbook.h"

Orderbook::Orderbook() : _size(0)
{

}

Orderbook::~Orderbook()
{
    _size = 0;
}

size_t Orderbook::getSize() const
{
    return _size;
}

void Orderbook::addOrder(std::unique_ptr<Order> pNewOrder)
{
    switch(pNewOrder->getOrderSide())
    {
        /*case Order::Buy:
            addNewBuyOrder();
            break;
        case Order::Sell:
            addNewSellOrder();
            break;*/
    }
}

void Orderbook::cancelOrder()
{

}