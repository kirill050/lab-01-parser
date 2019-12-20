// Copyright 2019 Kirill <your_email>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <any>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#define NUM_ST 48
#define NUM_FIN 57

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::map;
using std::any;

class Json {
public:
    Json(){
        _is_object = false;
        _is_array = false;
    }
    explicit Json(const string& s);
    bool is_array(const string &str) const;
    bool is_object(const string &str) const;
    any& operator[] (const string& key);
    any& operator[] (int index);

private:
    string make_it_without_tabs(string& str);
    string get_key(string& str);

public:
    any parse_object_get_value(string& s);

    static Json parse(const std::string& s)
    {
        return Json(s);
    }

    static Json parse(Json& JSON)
    {
        string str;
        try
        {
            str.assign(JSON.json_string, 1,
                       JSON.json_string.length()-2);
            if (str[0] == '[')
            {
                _is_array = true;
                str.assign(str, str.find("[")+1,
                         str.rfind('\n')-1);
                while (str.find(",") != string::npos)
                {
                    string some_other_string;
                    some_other_string.assign(str, 0, str.find(","));
                    str.assign(str, str.find(",")+1,
                                     str.length()-1);

                    some_other_string = make_it_without_tabs(
                                                    some_other_string);

                    JSON.Array.push_back(parse_object_get_value(
                                                    some_other_string));
                    //cout << ", ";
                }
                pre_value = make_it_without_tabs(pre_value);
                JSON.Array.push_back(parse_object_get_value(pre_value));
//                while (str.length() > 5)
//                {
//                    try
//                    {
//                        JSON.Array.push_back(
//                                JSON.parse_object_get_value(str));
//                    }
//                    catch (string Error)
//                    {
//                        cout << endl << "Error occured: " << Error << endl;
//                        break;
//                    }
//                }

            } else {
                _is_object = true;
                while (str.length() > 5)
                {
                    try
                    {
                        string key = JSON.get_key(str);
                        JSON._parsed_json[key] =
                                       JSON.parse_object_get_value(str);
                    }
                    catch (string Error)
                    {
                        cout << endl << "Error occured: " << Error << endl;
                        break;
                    }
                }
            }
            return JSON;
        }
        catch (std::bad_any_cast())
        {
            cout << "This is not a Json-object or Json-array!" << endl;
            return Json(string(""));
        }
    }

    static Json parseFile(const string& path_to_file)
    {
        std::ifstream JSON_file(path_to_file);
        string s;
        Json JSON(s);
        char ch;
        if (JSON_file.is_open())
        {
            while (true)
            {
                JSON_file.get(ch);
                if (JSON_file.eof()) break;
                JSON.json_string.append(1, ch);
            }
            JSON_file.close();
        }
        JSON = Json::parse(JSON.json_string);
        return JSON;
    }

public:
    std::string json_string;
    bool _is_object;
    std::map <std::string, std::any> _parsed_json;
    bool _is_array;
    std::vector <std::any> Array;
};
#endif // INCLUDE_HEADER_HPP_
