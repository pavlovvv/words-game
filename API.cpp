#include "API.h"

string getApiKeyFromConfig() {
    ifstream config_file("config.json");
    Json::Value config;
    config_file >> config;
    return config["openai_api_key"].asString();
}

string apiKey = getApiKeyFromConfig();

size_t API::write_callback(char *ptr, size_t size, size_t nmemb, string *data) {
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

string API::findContent(const string &data) {
    Json::Value root;
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();
    string errors;

    if (!reader->parse(data.c_str(), data.c_str() + data.size(), &root, &errors)) {
        cerr << "Failed to parse JSON: " << errors << endl;
        delete reader;
        return "";
    }
    delete reader;

    if (root.isMember("choices") && root["choices"].isArray()) {
        const Json::Value &choices = root["choices"];
        if (choices.size() > 0) {
            const Json::Value &message = choices[0]["message"];
            if (message.isMember("content")) {
                return message["content"].asString();
            }
        }
    }
    return "";
}

string API::apiRequest(string request) {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        string request_data =
                "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"" + request +
                "\"}]}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_data.c_str());

        string response_data;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "Failed to perform HTTP request: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        return findContent(response_data);
    } else {
        cerr << "Failed to initialize CURL" << endl;
    }

    return "";
}
