#include "ValidateInfo.h"
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ValidateInfo::ValidateInfo() {}
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}
bool ValidateInfo::validateNumberPhone(const std::string &input) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error iniciando cURL\n";
        return false;
    }
    std::string api_key = "2a635fd903254441a5d862737f86829f";
    std::string url = "https://phoneintelligence.abstractapi.com/v1/?api_key=" + api_key + "&phone=" + input;
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // API CALL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    
    try {
        auto j = json::parse(response);

        // Validar si existe la ruta phone_validation -> is_valid
        if (j.contains("phone_validation") && j["phone_validation"].contains("is_valid")) {
            return j["phone_validation"]["is_valid"].get<bool>();
        }

    } catch (const std::exception& e) {
        std::cerr << "Error al analizar JSON: " << e.what() << std::endl;
    }
    return false;
}