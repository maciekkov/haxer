#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include "messages/GetChartLastRequest.hpp"
#include "messages/Login.hpp"
#include "socket/SSLConnection.hpp"


int main()
{

    Login::Request login{"login", {10671564, "xoh22217"}};
    SSLConnection  ssl(5124, "81.2.190.166");

    //    json j;
    //    j["command"]               = "login";
    //    j["arguments"]["userId"]   = 10671564;
    //    j["arguments"]["password"] = "xoh22217";

    ssl.send(login);

    auto result = ssl.recive();
    std::cout << result.size() << std::endl;

    for (auto x : result)
    {
        std::cout << x;
    }

    GetChartLastRequest::Request history240{"getChartLastRequest", {{240, 1555953332696, "EURUSD"}}};

    ssl.send(history240);
    auto result2 = ssl.recive();

    auto jData = json::parse(result2);

    auto temp = jData.at("status").get<bool>();


    if(temp == true)
    std::cout <<  "true";
//    std::string str;

//    for (auto& el : jData.items())
//    {
//        str.append(el.value().dump());
//    }
//    std::cout << jData.dump(4) << std::endl;

//    std::cout << "Size of 1 element" << jData.size() << std::endl;
//    std::cout << "  is arrey : " << jData["returnData"]["rateInfos"].size() << std::endl;

//    std::vector<std::string> buffor;
//    std::istringstream       ss(str);
//    std::string              buf;
//    while (std::getline(ss, buf, '\"'))
//    {
//        buffor.emplace_back(buf);
//    }

//    int                           num = std::count(buffor.begin(), buffor.end(), "close");
//    GetChartLastRequest::Response data;
//    data.ret.rates.resize(21);
//    data = jData.get<GetChartLastRequest::Response>();

//    std::cout << data.status;
//    std::cout << data.ret.rates[0].ctmString;

    //

    //    std::cout << "\n"
    //              << "STATUS" << data.status << std::endl;

    return 0;
}
