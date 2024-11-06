//Full Name: Võ Thành Danh
//MSSV     : 22520201
//Lab 03 
//Notes or Remarks:
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <cmath>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

class ExponentialBackoffSearch {
private:
    const int MAX_RETRIES = 5;
    const int BASE_DELAY_MS = 100;
    const int MAX_DELAY_MS = 3000;
    
    int addJitter(int delay) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(-50, 50);
        return delay + dis(gen);
    }

    bool searchRequest(const string& query) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);
        return dis(gen) > 0.7;
    }

public:
    bool search(const string& query) {
        int retryCount = 0;
        
        while (retryCount < MAX_RETRIES) {
            if (searchRequest(query)) {
                cout << "Search successful on attempt " << retryCount + 1 << endl;
                return true;
            }

            int delay = min(
                MAX_DELAY_MS,
                static_cast<int>(BASE_DELAY_MS * pow(2, retryCount))
            );

            delay = addJitter(delay);

            cout << "Search failed. Retrying in " << delay << "ms. Attempt "
                 << retryCount + 1 << "/" << MAX_RETRIES << endl;

            sleep_for(milliseconds(delay));
            retryCount++;
        }

        cout << "Search failed after " << MAX_RETRIES << " attempts." << endl;
        return false;
    }
};

int main() {
    ExponentialBackoffSearch searcher;
    string query = "test query";
    
    cout << "Starting search with exponential backoff..." << endl;
    searcher.search(query);
    
    return 0;
}
