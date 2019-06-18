
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include "messages/GetChartLastRequest.hpp"
#include "messages/Login.hpp"
#include "socket/SSLConnection.hpp"
#include <zmq.hpp>
int main()
{

    Login::Request login{"login", {10725508, "xoh50406"}};
    SSLConnection  ssl(5124, "81.2.190.166");

    //    json j;
    //    j["command"]               = "login";
    //    j["arguments"]["userId"]   = 10671564;
    //    j["arguments"]["password"] = "xoh22217";

    ssl.send(login);

    auto result = ssl.recive();

    auto LoginData = json::parse(result.begin(),result.end());

    std::cout << std::endl << LoginData.dump() << std::endl;;
    auto temp = LoginData.get<Login::Response>();

    std::cout << temp.streamSessionId << std::endl; ;

    GetChartLastRequest::Request history240{"getChartLastRequest", {{240, 1560820504462, "EURUSD"}}};

    ssl.send(history240);
    auto result2 = ssl.recive();

//    std::cout << result2.size() << std::endl;

//    for (auto x : result2)
//    {
//        std::cout << x;
//    }

    //    std::cout << result2.dump(5);

    auto jData = json::parse(result2.begin(), result2.end());

  //  auto temp = jData.at("status").get<bool>();

    //    if (temp == true)
    //        std::cout << "true";
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
        GetChartLastRequest::Response data;
        data.ret.rates.resize(4);
        data = jData.get<GetChartLastRequest::Response>();

        std::cout << data.status;
        std::cout << data.ret.rates[0].ctmString;
        std::cout << "high" << data.ret.rates[0].high;

        std::cout << "\n" << std::endl;
        std::cout << "\n" << std::endl;
        std::cout << jData.dump(4) << std::endl;



    return 0;
}
