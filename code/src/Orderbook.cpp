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
    return static_cast<size_t>(_bidOrders.size() + _askOrders.size());
}

void Orderbook::addNewBuyOrder(std::shared_ptr<Order> pNewOrder)
{
    if (0 < pNewOrder->getOrderQuantity())
    {
        _bidOrders.insert({pNewOrder->getOrderId(), pNewOrder});
    }
}

void Orderbook::addNewSellOrder(std::shared_ptr<Order> pNewOrder)
{
    if (0 < pNewOrder->getOrderQuantity())
    {
        _askOrders.insert({pNewOrder->getOrderId(), pNewOrder});
    }
}

void Orderbook::updateAskAndBidValues(std::shared_ptr<Order> pAskOrder, std::shared_ptr<Order> pBidOrder)
{
    if (pAskOrder->getOrderQuantity() == pBidOrder->getOrderQuantity())
    {
        std::cout << "on fout tout a zero\n";
        pAskOrder->setOrderQuantity(0);
        pBidOrder->setOrderQuantity(0);
    }
    else if (pAskOrder->getOrderQuantity() > pBidOrder->getOrderQuantity())
    {
        std::cout << "on fout le bid a zero\n";
        pAskOrder->setOrderQuantity(pAskOrder->getOrderQuantity() - pBidOrder->getOrderQuantity());
        pBidOrder->setOrderQuantity(0);
    }
    else
    {
        std::cout << "on fout le ask a zero\n";
        pBidOrder->setOrderQuantity(pBidOrder->getOrderQuantity() - pAskOrder->getOrderQuantity());
        pAskOrder->setOrderQuantity(0);
    }
}

void Orderbook::matchBidWithAsk(std::shared_ptr<Order> pNewBidOrder)
{
    std::vector<int> vectorOfAskOrdersToDelete{};

    // try to match the new buy order with a sell order already in the orderbook...
    for (size_t i = 0; i < _askOrders.size(); ++i)
    for (auto& it : _askOrders)
    {
        if (it.second->getOrderPrice() <= pNewBidOrder->getOrderPrice())
        {
            updateAskAndBidValues(it.second, pNewBidOrder);

            if (pNewBidOrder->getOrderQuantity() > 0)
            {
                _bidOrders.insert({pNewBidOrder->getOrderId(), pNewBidOrder});
            }

            // will delete the sell orders with quantities to zero from the orderbook
            if (0 == it.second->getOrderQuantity())
            {
                vectorOfAskOrdersToDelete.push_back(it.first);
            }
        }
        // keep looping to find if another seller is found now that the bid order has been updated at least once...
    }

    for (auto& it : vectorOfAskOrdersToDelete)
    {
        _askOrders.erase(it);
    }
}

void Orderbook::matchAskWithBid(std::shared_ptr<Order> pNewAskOrder)
{
    std::vector<int> vectorOfBidOrdersToDelete{};

    // try to match the new buy order with a sell order already in the orderbook...
    for (auto& it : _bidOrders)
    {
        if (it.second->getOrderPrice() <= pNewAskOrder->getOrderPrice())
        {
            updateAskAndBidValues(pNewAskOrder, it.second);

            if (pNewAskOrder->getOrderQuantity() > 0)
            {
                _askOrders.insert({pNewAskOrder->getOrderId(), pNewAskOrder});
            }

            // will delete the sell orders with quantities to zero from the orderbook
            if (0 == it.second->getOrderQuantity())
            {
                vectorOfBidOrdersToDelete.push_back(it.first);
            }
        }
        // keep looping to find if another seller is found now that the bid order has been updated at least once...
    }

    for (auto& it : vectorOfBidOrdersToDelete)
    {
        _bidOrders.erase(it);
    }
}

void Orderbook::addOrder(std::shared_ptr<Order> pNewOrder)
{
    switch(pNewOrder->getOrderSide())
    {
        case ESide::Buy:
            matchBidWithAsk(pNewOrder);
            addNewBuyOrder(pNewOrder);
            break;
        case ESide::Sell:
            matchAskWithBid(pNewOrder);
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