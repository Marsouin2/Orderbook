#include "Order.h"

Order::Order(EOrderType orderType, int orderId, ESide orderSide, int price, int quantity) : 
             _orderType(orderType), _orderId(orderId), _orderSide(orderSide), _iPrice(price), _iQuantity(quantity)
{

}

int Order::buyOrderQuantity(int buyQuantity)
{
    int remainingBuyQuantity{0};

    if (buyQuantity > _iQuantity) // case where the BUY order quantity is > SELL order quantity
    {
        _iQuantity = 0;
    }
    else // case where the SELL order quantity is > BUY order quantity
    {
        _iQuantity = _iQuantity - buyQuantity;
    }
    remainingBuyQuantity = buyQuantity - _iQuantity;

    return remainingBuyQuantity;
}