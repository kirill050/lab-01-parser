// Copyright 2019 Kirill Tikhonov <kirilltikhonov050@gmail.com>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <any>
#include <map>
#include <vector>
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
    // Конструктор из строки, содержащей Json-данные.
    Json(const string& s);

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array(const string &str) const;
   	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object(const string &str) const;

    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    any& operator[](const string& key);

    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    any& operator[](int index);

private:
    string make_it_without_tabs(string& str);

    string get_key(string& str);
public:
    any parse_object_get_value(string& s);

    static Json parse(const std::string& s){
        string str;
        try{
            Json JSON(s);
            str.assign(s, 1, s.length()-2);

            while(str.length()>5){
                try{
                    string key = JSON.get_key(str);
                    JSON._parsed_json[key] = JSON.parse_object_get_value(str);
                    //cout << endl;
                }
                catch(string Error){
                    //cout << endl << "Error occured: " << Error << endl;
                    break;
                }
            }
            return JSON;
        }
        catch(std::bad_any_cast()) {
            cout << "This is not a Json-object "
                         "or Json-array!" << endl;
            return Json();
    }

    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const string& path_to_file){
        std::ifstream JSON_file(path_to_file);
        string s;
        Json JSON(s);
        char ch;
        if(JSON_file.is_open()){
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
    std::map <std::string, std::any> _parsed_json;
};
#endif // INCLUDE_HEADER_HPP_
