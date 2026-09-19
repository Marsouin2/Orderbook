#include "Orderbook.h"

size_t Orderbook::getSize() const
{
    return static_cast<size_t>(_bidOrders.size() + _askOrders.size());
}

void Orderbook::addNewBuyOrder(const std::shared_ptr<Order>& pNewOrder)
{
    if (0 < pNewOrder->getOrderQuantity())
    {
        const auto insertRet = _bidOrders.insert({pNewOrder->getOrderId(), pNewOrder});
        if (!insertRet.second)
        {
            std::cerr << "WARN : orderId#" << pNewOrder->getOrderId() << " has not been added in the bid orders.\n";
        }
    }
}

void Orderbook::addNewSellOrder(const std::shared_ptr<Order>& pNewOrder)
{
    if (0 < pNewOrder->getOrderQuantity())
    {
        const auto insertRet = _askOrders.insert({pNewOrder->getOrderId(), pNewOrder});
        if (!insertRet.second)
        {
            std::cerr << "WARN : orderId#" << pNewOrder->getOrderId() << " has not been added in the ask orders.\n";
        }
    }
}

void Orderbook::updateAskAndBidValues(const std::shared_ptr<Order>& pAskOrder, const std::shared_ptr<Order>& pBidOrder) const
{
    if (pAskOrder->getOrderQuantity() == pBidOrder->getOrderQuantity())
    {
        pAskOrder->setOrderQuantity(0);
        pBidOrder->setOrderQuantity(0);
    }
    else if (pAskOrder->getOrderQuantity() > pBidOrder->getOrderQuantity())
    {
        pAskOrder->setOrderQuantity(pAskOrder->getOrderQuantity() - pBidOrder->getOrderQuantity());
        pBidOrder->setOrderQuantity(0);
    }
    else
    {
        pBidOrder->setOrderQuantity(pBidOrder->getOrderQuantity() - pAskOrder->getOrderQuantity());
        pAskOrder->setOrderQuantity(0);
    }
}

void Orderbook::matchBidWithAsk(const std::shared_ptr<Order>& pNewBidOrder)
{
    std::vector<int> vectorOfAskOrdersToDelete;

    // try to match the new buy order with a sell order already in the orderbook...
    for (auto& it : _askOrders)
    {
        if (pNewBidOrder->getOrderPrice() >= it.second->getOrderPrice())
        {
            updateAskAndBidValues(it.second, pNewBidOrder);

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

void Orderbook::matchAskWithBid(const std::shared_ptr<Order>& pNewAskOrder)
{
    std::vector<int> vectorOfBidOrdersToDelete;

    // try to match the new buy order with a sell order already in the orderbook...
    for (auto& it : _bidOrders)
    {
        if (it.second->getOrderPrice() >= pNewAskOrder->getOrderPrice())
        {
            updateAskAndBidValues(pNewAskOrder, it.second);

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

bool Orderbook::doOrderAlreadyExistInBid(const std::shared_ptr<Order>& pNewOrder) const
{
    bool retVal{false};

    const auto found = _bidOrders.find(pNewOrder->getOrderId());
    if (found != _bidOrders.end())
    {
        retVal = true;
    }

    return retVal;
}

bool Orderbook::doOrderAlreadyExistInAsk(const std::shared_ptr<Order>& pNewOrder) const
{
    /*bool retVal{false};

    const auto found = _askOrders.find(pNewOrder->getOrderId());
    if (found != _askOrders.end())
    {
        retVal = true;
    }

    return retVal;*/

    return _askOrders.find(pNewOrder->getOrderId()) != _askOrders.end() ? true : false;
}

void Orderbook::addOrder(const std::shared_ptr<Order>& pNewOrder)
{
    if (0 >= pNewOrder->getOrderQuantity())
    {
        std::cerr << "ERROR : orderId#" << pNewOrder->getOrderId() << " contain a quantity of 0. Not taken in account.\n";
    }
    else
    {
        if ((!doOrderAlreadyExistInBid(pNewOrder)) && (!doOrderAlreadyExistInAsk(pNewOrder)))
        {
            if (ESide::Buy == pNewOrder->getOrderSide())
            {
                matchBidWithAsk(pNewOrder);
                addNewBuyOrder(pNewOrder);
            }
            else if (ESide::Sell == pNewOrder->getOrderSide())
            {
                matchAskWithBid(pNewOrder);
                addNewSellOrder(pNewOrder); 
            }
            else
            {
                std::cerr << "Unknown order side for order# " << pNewOrder->getOrderId() << ". Order has not been taken in account...\n";
            }
        }
        else
        {
            std::cerr << "ERROR : orderId#" << pNewOrder->getOrderId() << " sell order already exist internally. Nothing changed.\n";
        }
    }
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