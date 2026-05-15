#pragma once

#include <iostream>
#include <cstddef>
#include <unordered_map>
#include <memory>

#include "Order.h"

class Orderbook
{
public:
    Orderbook();
    ~Orderbook();

    size_t getSize() const;
    void addOrder(std::shared_ptr<Order> pNewOrder);
    void cancelOrder(const int orderId);
    std::shared_ptr<Order> getOrderById(const int orderId);
    void addNewBuyOrder(std::shared_ptr<Order> pNewOrder);
    void addNewSellOrder(std::shared_ptr<Order> pNewOrder);

private: // functions
    void matchBidWithAsk(std::shared_ptr<Order> pNewOrder);
    void matchAskWithBid(std::shared_ptr<Order> pNewAskOrder);
    void updateAskAndBidValues(std::shared_ptr<Order> pAskOrder, std::shared_ptr<Order> pBidOrder);

private: // attributes
    std::unordered_map<int, std::shared_ptr<Order>> _askOrders;
    std::unordered_map<int, std::shared_ptr<Order>> _bidOrders;
};