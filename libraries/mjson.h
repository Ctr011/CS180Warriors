#ifndef MJSON_H
#define MJSON_H
#include <iostream>
#include <utility>
#include <vector>
#include "../webserver/nlohmann/json.hpp"
using json = nlohmann::json;

json create_json(std::vector<std::pair<std::string,std::string>>n){
    json list = json::array();

    for(int i = 0; i < n.size(); i++){
        json j = {
            {"name", n[i].first },
            {"description", n[i].second}
        };
        list.push_back(j);
    }
    return list;
}

#endif