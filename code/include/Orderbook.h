#pragma once

#include <cstddef>
#include <unordered_map>

#include "Order.h"

class Orderbook
{
public:
    Orderbook();
    ~Orderbook();

    size_t getSize() const;
    void addOrder(std::unique_ptr<Order> pNewOrder);
    void cancelOrder();
private:
    std::unordered_map<int, std::unique_ptr<Order>> _askOrders;
    std::unordered_map<int, std::unique_ptr<Order>> _bidOrders;
    size_t _size;
};