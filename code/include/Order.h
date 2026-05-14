
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
    Order(EOrderType orderType, int orderId, ESide orderSide, unsigned int price, unsigned int quantity);
    ~Order() = default;

    ESide getOrderSide() const { return _orderSide; };
    unsigned int getOrderId() const { return _orderId; };
private:
    int _orderId;
    EOrderType _orderType;
    ESide _orderSide;
    unsigned int _uIQuantity;
    unsigned int _uIPrice;
    // time of the arrived order (need to get current time)
};