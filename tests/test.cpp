// Copyright 2019 Kirill <your_email>

#include <gtest/gtest.h>
#include "header.hpp"
#include <iostream>
#include <string>
#include <any>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

using std::string;

TEST(Parse, Text){
Json object("{\n"
                   "    \"lastname\" : \"Ivanov\",\n"
                   "    \"firstname\" : \"Ivan\",\n"
                   "    \"age\" : 25,\n"
                   "    \"islegal\" : false,\n"
                   "    \"marks\" : [\n"
                   "    \t4,5,5,5,2,3\n"
                   "    ],\n"
                   "    \"address\" : {\n"
                   "    \t\"city\" : \"Moscow\",\n"
                   "        \"street\" : \"Vozdvijenka\"\n"
                   "    }\n"
                   "}");

    EXPECT_EQ(std::any_cast<string>(object._parsed_json["lastname"]), "Ivanov");
    EXPECT_EQ(std::any_cast<bool>(object._parsed_json["islegal"]), false);
    EXPECT_EQ(std::any_cast<double>(object._parsed_json["age"]), 25);

    auto marks = std::any_cast<std::vector <std::any>>
                                   (object._parsed_json["marks"]);

    EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
    EXPECT_EQ(std::any_cast<double>(marks[1]), 5);

    auto address = std::any_cast<std::map<std::string,
                         std::string>>(object._parsed_json["address"]);
    EXPECT_EQ(std::any_cast<string>(address["city"]), "Moscow");
    EXPECT_EQ(std::any_cast<string>(address["street"]), "Vozdvijenka");
}

using json = nlohmann::json;

TEST1(nlohmann, Text){
nlohmann::json outputJson;
    auto j3 = json::parse("[\n"
                          "    [\"Si-9.15\", \"RTS-9.15\", \"GAZP-9.15\"],\n"
                          "    [100024, 100027, 100050],\n"
                          "    [\"Futures contract for USD/RUB\", "
                          "\"Futures contract for index RTS\", "
                          "\"Futures contract for Gazprom shares\"]\n"
                          "]");
    uint64_t tmp;

    for (uint64_t i = 0; i < j3[0].size(); ++i) {
        tmp = 0;
        while (tmp < j3.size()) {
            outputJson.push_back(
                    nlohmann::json
                            {
                                    {"ticker",      j3[tmp++][i]},
                                    {"id",          j3[tmp++][i]},
                                    {"description", j3[tmp++][i]},
                            });
        }
    }
    std::cout << outputJson;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
