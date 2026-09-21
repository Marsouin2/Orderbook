#include "OrderFileParser.h"

std::shared_ptr<Order> OrderFileParser::createAnOrderWithACorrectLine(const std::string& rOrderLine)
{
    // turn rOrderLine to Order and return std::make_shared de rOutOrder
    Order rOutOrder;
    std::stringstream ss(rOrderLine);
    std::string word;
      
    std::vector<std::string> words;
      
    while (ss >> word)
        words.push_back(word);

    for (size_t i = 0; i < words.size(); ++i)
    {
        if (0 == i) // BUY | SELL
        {
            if (words[i] == "BUY")
                rOutOrder.setOrderSide(ESide::Buy);
            else // already checked synthax before so else is ok here
                rOutOrder.setOrderSide(ESide::Sell);
        }
        else if (1 == i) // quantity
            rOutOrder.setOrderQuantity(stoi(words[i]));
        else if (3 == i) // price
            rOutOrder.setOrderPrice(stoi(words[i]));
        else { /* MISRA Happy :) */ }
    }

    rOutOrder.setOrderType(EOrderType::GoodTillCancel);
    rOutOrder.setOrderId(getNewOrderId());

    return std::make_shared<Order>(rOutOrder);
}

bool OrderFileParser::isLineCorrect(const std::string& rOrderLine, const std::string& filepath)
{
    // check que la synthaxe est bien BUY 100 @ 10
    bool retVal{false};

    // synthax must be 'BUY|SELL 10 @ 100' like
    std::regex reg("^(BUY|SELL)\\s[0-9]+\\s@\\s[0-9]+$");
    if (!regex_match(rOrderLine, reg))
    {
        std::cerr << "ERROR : A line is synthaxically incorrect in file " << filepath << ". Cannot loading orders...\n";
    }
    else
    {
        retVal = true;
    }

    return retVal;
}

std::vector<std::shared_ptr<Order>> OrderFileParser::getOrdersFromFile(const std::string& filepath)
{
    std::vector<std::shared_ptr<Order>> retVal;    
    std::ifstream myFile(filepath);

    if (myFile.is_open())
    {
        std::string line;
        std::cout << "DEBUG : Successfully opened order file " << filepath << ".\n";

        while (getline(myFile, line))
        {
            if (isLineCorrect(line, filepath))
            {
                std::shared_ptr<Order> newOrder = createAnOrderWithACorrectLine(line);
                retVal.push_back(newOrder);
            }
        }
        myFile.close();
    }
    else
    {
        std::cerr << "ERROR : Loading order file " << filepath << " encountered an error. Please check your file.\n";
    }

    return retVal;
}
