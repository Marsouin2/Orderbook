#ifndef ORDER_H_
#define ORDER_H_

enum class EOrderType
{
    GoodTillCancel, // GTC
    FillAndKill,    // FAK
    FillOrKill,     // FOK
    GoodForDay      // GFD
};

enum class ESide
{
    Buy,
    Sell
};

class Order
{
public:
    Order(EOrderType orderType, int orderId, ESide orderSide, int price, int quantity);
    Order() = default;
    ~Order() = default;

    // GETTERS
    ESide getOrderSide() const { return _orderSide; };
    int getOrderId() const { return _orderId; };
    int getOrderPrice() const { return _iPrice; };
    int getOrderQuantity() const { return _iQuantity; };
    // SETTERS
    void setOrderType(const EOrderType eOrderType) { _orderType = eOrderType; };
    void setOrderSide(const ESide eSide) { _orderSide = eSide; };
    void setOrderId(const int orderId) { _orderId = orderId; };
    void setOrderPrice(const int newPrice) { _iPrice = newPrice; };
    void setOrderQuantity(const int newQuantity) { _iQuantity = newQuantity; };
    
private:
    EOrderType _orderType;
    int _orderId;
    ESide _orderSide;
    int _iPrice;
    int _iQuantity;
    // time of the arrived order (need to get current time)
};

#endif