#include "Order.h"

Order::Order(EOrderType orderType, int orderId, ESide orderSide, int price, int quantity) : 
             _orderType(orderType), _orderId(orderId), _orderSide(orderSide), _iPrice(price), _iQuantity(quantity)
{

}