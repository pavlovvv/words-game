#ifndef API_H
#define API_H

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <cstdlib>
#include <json/json.h>
#include <fstream>

using namespace std;

class API {
public:
    static size_t write_callback(char *ptr, size_t size, size_t nmemb, string *data);
    static string findContent(const string &data);
    string apiRequest(string request);
    string getApiKeyFromConfig();
};

#endif // API_H
