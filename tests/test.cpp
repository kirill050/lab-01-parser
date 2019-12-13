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
//try
//{
    EXPECT_EQ(object["lastname"], "Ivanov");
    EXPECT_EQ(object["islegal"], false);
    EXPECT_EQ(object["age"], 25);

    auto marks = std::any_cast<std::vector <std::any> >(object["marks"]);

    EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
    EXPECT_EQ(std::any_cast<double>(marks[1]), 5);

    auto address = std::any_cast<Json>(object["address"]);
    EXPECT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
    EXPECT_EQ(std::any_cast<std::string>(address["street"]),
               "Vozdvijenka");
//}
//catch (std::bad_any_cast& e)
//{
 //   cout << "Bad any cast!";
//}
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
