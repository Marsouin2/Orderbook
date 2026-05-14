
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
    Order() = default;
    ~Order() = default;

    ESide getOrderSide() const { return _orderSide; };
private:
    int _orderId;
    EOrderType _orderType;
    ESide _orderSide;
    unsigned int _uIQuantity;
    unsigned int _uIPrice;
    // time of the arrived order (need to get current time)
};