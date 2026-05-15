
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
    ~Order() = default;

    // GETTERS
    ESide getOrderSide() const { return _orderSide; };
    int getOrderId() const { return _orderId; };
    int getOrderPrice() const { return _iPrice; };
    int getOrderQuantity() const { return _iQuantity; };
    // SETTERS
    void setOrderQuantity(const int newQuantity) { _iQuantity = newQuantity; };

    int buyOrderQuantity(int buyQuantity);
private:
    int _orderId;
    EOrderType _orderType;
    ESide _orderSide;
    int _iQuantity;
    int _iPrice;
    // time of the arrived order (need to get current time)
};