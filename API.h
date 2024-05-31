#include <iostream>
#include <curl/curl.h>

using namespace std;

class API {
public:
    static size_t write_callback(char* ptr, size_t size, size_t nmemb, string* data) {
        data->append(ptr, size * nmemb);
        return size * nmemb;
    }

    static string findContent(const string& data) {
        size_t pos_content = data.find("\"content\":");

        if (pos_content != string::npos) {
            // Знаходимо початок значення content
            size_t start_quote = data.find('"', pos_content + 10); // "+ 10" щоб пропустити ": "content": "

            if (start_quote != string::npos) {
                // Знаходимо кінець значення content
                size_t end_quote = data.find('"', start_quote + 1);

                if (end_quote != string::npos) {
                    // Витягуємо значення content
                    return data.substr(start_quote + 1, end_quote - start_quote - 1);
                }
            }
        }

        return ""; // Повертаємо порожній рядок, якщо значення не знайдено
    }

    string apiRequest(string request) {
        CURL* curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            headers = curl_slist_append(headers, "Authorization: Bearer ");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            string request_data = "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"" + request + "\"}]}";
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

    }
};
