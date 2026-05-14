#include "Order.h"

Order::Order(EOrderType orderType, int orderId, ESide orderSide, unsigned int price, unsigned int quantity) : 
             _orderType(orderType), _orderId(orderId), _uIPrice(price), _uIQuantity(quantity)
{

}