// Copyright 2019 Kirill <your_email>
#include "header.hpp"
// Constructor from a string containing Json data.
Json::Json(const string& s)
{
    json_string = s;
    _is_object = false;
    _is_array = false;
    Json::parse(*this);
}

// The method returns true if this instance contains a JSON array.
//Otherwise false.
bool Json::is_array(const string &str) const{
    if (str[0] == '[')
        return true;
    else
        return false;
}
// The method returns true if this instance contains a JSON object.
//Otherwise false.
bool Json::is_object(const string &str) const
{
    if (str[0] == '{')
        return true;
    else
        return false;
}

// The method returns a value by key if the instance is
//a JSON object. The value can be of one of the following types:
//Json, std:: string, double, bool or be empty.
//if the instance is a JSON array, an exception is thrown.
any& Json::operator[](const string& key)
{
    if (!_is_object) throw std::bad_any_cast();
    if (_parsed_json[key].type() == typeid(string))
    {
        return _parsed_json[key];
    } else if (_parsed_json[key].type() == typeid(double)) {
        return _parsed_json[key];
    } else if (_parsed_json[key].type() == typeid(int)) {
        return _parsed_json[key];
    } else if (_parsed_json["Patric"].type() == typeid(bool)) {
        return _parsed_json[key];
    } else {
        return _parsed_json[key];
    }
}

// The method returns the value of the index index,
//if the instance is a JSON array.
// The value can be of one of the following types: Json, std:: string,
//double, bool or be empty. If the instance is a JSON object,
// an exception is thrown.
std::any& Json::operator[](int index)
{
    if (!_is_array) throw std::bad_any_cast();
    if (Array[index].type() == typeid(string))
    {
        return Array[index];
    } else if (Array[index].type() == typeid(double)) {
        return Array[index];
    } else if (Array[index].type() == typeid(int)) {
        return Array[index];
    } else if (Array[index].type() == typeid(bool)) {
        return Array[index];
    } else {
        return Array[index];
    }
//    auto it = _parsed_json.begin();
//    advance(it, index);
//    return it->second;
}

std::string Json::make_it_without_tabs(std::string& str){
    while ((str[0] == ' ') ||  (str[0] == '\n') || (str[0] == '\t')){
        str.assign(str, 1, str.length()-1);
    }
    string make_some_more_style_to_be_used_in_parse_obj_func(": ");
    make_some_more_style_to_be_used_in_parse_obj_func += str;
    str = make_some_more_style_to_be_used_in_parse_obj_func;
    return str;
}
std::string Json::get_key(std::string& str){
    if (str.find("\"") != string::npos){
        str.erase(0, str.find("\"")+1);
        if (str.find("\"") != string::npos){
            string key = str.substr(0, str.find("\""));
            str.erase(0, str.find("\"")+1);
            return key;
        } else {
            throw std::out_of_range("A");
        }
    } else {
        str.erase(0, str.find("\"")+1);
        if (str.find("\"") != string::npos){
            string key = str.substr(0, str.find("\""));
            str.erase(0, str.find("\"")+1);
            return key;
        } else {
            throw std::out_of_range("B");
        }
    }
}
std::string prepare_Pre_Value(std::string& s){
    string pre_value;
    if (s.find(",") != string::npos){
        if (s.find("{") != string::npos){
            if (s.find("{") < s.find(",")){
                if (s.find("}") == string::npos)
                    throw std::range_error("B");
                pre_value.assign(s, s.find(":")+2, s.find("}")-2);
                s.erase(0, s.find("}")+1);
            } else if (s.find("[") != string::npos) {
                if (s.find("[") < s.find(","))
                {
                    if (s.find("]") == string::npos)
                        throw std::range_error("C");
                    pre_value.assign(s, s.find(":")+2, s.find("]")-2);
                    s.erase(0, s.find("]")+1);
                } else {
                pre_value.assign(s, s.find(":")+2, s.find(",")-3);
                s.erase(0, s.find(",")+1);
                }
            } else {
            pre_value.assign(s, s.find(":")+2, s.find(",")-3);
            s.erase(0, s.find(",")+1);
            }
        } else if (s.find("[") != string::npos) {
            if (s.find("[") < s.find(","))
            {
                if (s.find("]") == string::npos)
                    throw std::range_error("D");
                pre_value.assign(s, s.find(":")+2, s.find("]")-2);
                s.erase(0, s.find("]")+1);
            } else {
            pre_value.assign(s, s.find(":")+2, s.find(",")-3);
            s.erase(0, s.find(",")+1);
            }
        } else {
            pre_value.assign(s, s.find(":")+2, s.find(",")-3);
            s.erase(0, s.find(",")+1);
        }
    } else {
        pre_value = s;
        pre_value.erase(0, pre_value.find(":")+2);
        s = "";
    }
    return pre_value;
}
std::any Json::parse_object_get_value(std::string& s){
    if ((!s.length()) || (s.find(":") == string::npos))
        throw std::range_error("A");

    any value;
    string pre_value = prepare_Pre_Value(s);

    if (pre_value[0] == '{')
    {
        pre_value.assign(pre_value, pre_value.find("\""),
                          pre_value.length()-2);
        Json sub_json();
        sub_json._is_object = true;
        while (pre_value.length() > 5)
        {
            try
            {
                string key = get_key(pre_value);
                string find_here_a_value;

                sub_json._parsed_json[key] = std::any_cast<string>
                                (parse_object_get_value(pre_value));
            }
            catch (string Error)
            {
                cout << endl << "Error occured: " << Error << endl;
                if (Error == "No keys!")
                {
                    value = -1;
                    return value;
                } else if (Error == "No objects value for the last key!") {
                    value = -1;
                    return value;
                }
            }
            catch (...)
            {
                value = -1;
                return value;
            }
        }
        value = sub_json;
    } else if (pre_value[0] == '[') {
        pre_value.assign(pre_value, pre_value.find("[")+1,
                         pre_value.rfind('\n')-1);

        Json sub_json();
        sub_json._is_array = true;

        while (pre_value.find(",") != string::npos)
        {
            string some_other_string;
            some_other_string.assign(pre_value, 0, pre_value.find(","));
            pre_value.assign(pre_value, pre_value.find(",")+1,
                             pre_value.length()-1);

            some_other_string = make_it_without_tabs(some_other_string);

            sub_json.Array.push_back(parse_object_get_value(some_other_string));
        }
        pre_value = make_it_without_tabs(pre_value);
        sub_json.Array.push_back(parse_object_get_value(pre_value));

        value = sub_json;
    } else if (pre_value.find("\"") != string::npos) {
        pre_value.assign(pre_value, pre_value.find("\"")+1,
                         pre_value.rfind("\"")-1);
        value = pre_value;
    } else if ((pre_value[0] >= NUM_ST)&&
              (pre_value[pre_value.length()-1] <= NUM_FIN)) {
        value = atof(pre_value.c_str());
    } else if ((pre_value == "true") || (pre_value == "false")) {
        if (pre_value == "true")
            value = true;
        else if (pre_value == "false")
            value = false;
        else
            throw std::invalid_argument("A");
    } else {
        throw std::bad_cast();
    }

    return value;
}



