#ifndef ORDER_FILE_PARSER_H_
#define ORDER_FILE_PARSER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <memory>

#include "Orderbook.h"

class OrderFileParser
{
public: // ## functions
    OrderFileParser() : _currentOrderId(0) {};
    ~OrderFileParser() = default;
    std::vector<std::shared_ptr<Order>> getOrdersFromFile(const std::string& filepath);

private: // ## functions
    std::shared_ptr<Order> createAnOrderWithACorrectLine(const std::string& rOrderLine);
    bool isLineCorrect(const std::string& rOrderLine, const std::string& filepath);
    int getNewOrderId() { ++_currentOrderId; return _currentOrderId; };

private: // ## attributes
    int _currentOrderId;
};

#endif