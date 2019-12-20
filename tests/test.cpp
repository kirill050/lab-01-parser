// Copyright 2019 Kirill <your_email>

#include <gtest/gtest.h>
#include <header.hpp>
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
    EXPECT_EQ(std::any_cast<string>(object[string("lastname")]),
              string("Ivanov"));
    EXPECT_EQ(std::any_cast<bool>(object.[string("islegal")]), false);
    EXPECT_EQ(std::any_cast<double>(object.[string("age")]), 25);

    auto marks = std::any_cast<std::vector <std::any>>
                                   (object.[string("marks")]);

    EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
    EXPECT_EQ(std::any_cast<double>(marks[1]), 5);

    auto address = std::any_cast<std::map<std::string,
                         std::string>>(object.[string("address")]);
    EXPECT_EQ(std::any_cast<string>(address[string("city")]),
              string("Moscow"));
    EXPECT_EQ(std::any_cast<string>(address[string("street")]),
              string("Vozdvijenka"));
//
//    EXPECT_EQ(std::any_cast<string>(object["lastname"]), "Ivanov");
//    EXPECT_EQ(std::any_cast<bool>(object._parsed_json["islegal"]), false);
//    EXPECT_EQ(std::any_cast<double>(object._parsed_json["age"]), 25);
//
//    auto marks = std::any_cast<std::vector <std::any>>
//                                   (object._parsed_json["marks"]);
//
//    EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
//    EXPECT_EQ(std::any_cast<double>(marks[1]), 5);
//
//    auto address = std::any_cast<std::map<std::string,
//                         std::string>>(object._parsed_json["address"]);
//    EXPECT_EQ(std::any_cast<string>(address["city"]), "Moscow");
//    EXPECT_EQ(std::any_cast<string>(address["street"]), "Vozdvijenka");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
