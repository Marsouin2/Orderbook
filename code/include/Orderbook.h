#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include <iostream>
#include <cstddef>
#include <unordered_map>
#include <memory>
#include <vector>

#include "Order.h"

class Orderbook
{
public:
    Orderbook() = default;
    ~Orderbook() = default;

    size_t getSize() const;
    void addOrder(const std::shared_ptr<Order>& pNewOrder);
    void cancelOrder(const int orderId);
    void addNewBuyOrder(const std::shared_ptr<Order>& pNewOrder);
    void addNewSellOrder(const std::shared_ptr<Order>& pNewOrder);

private: // functions
    void matchBidWithAsk(const std::shared_ptr<Order>& pNewOrder);
    void matchAskWithBid(const std::shared_ptr<Order>& pNewAskOrder);
    void updateAskAndBidValues(const std::shared_ptr<Order>& pAskOrder, const std::shared_ptr<Order>& pBidOrder) const;

private: // attributes
    std::unordered_map<int, std::shared_ptr<Order>> _askOrders;
    std::unordered_map<int, std::shared_ptr<Order>> _bidOrders;
};

#endif