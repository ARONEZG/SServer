#pragma once
#include "search_server.h"

#include <deque>

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
    
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    
    int GetNoResultRequests() const;
    
private:
    struct QueryResult {
        int time;
        int query_count;
        bool is_empty;
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const SearchServer& search_server_;
};

template <typename DocumentPredicate>
    std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        std::vector<Document> result_list = search_server_.FindTopDocuments(raw_query, document_predicate);
        const bool empty = result_list.empty();
        if (requests_.empty()) {
            requests_.push_back({1, empty ? 1 : 0, empty});
            return result_list;
        }
        int current_time = requests_.back().time + 1;
        int current_count = requests_.back().query_count;
        if (min_in_day_ - current_time >= 0) {
            requests_.push_back({current_time, empty ? current_count + 1 : current_count, empty});
        } else {
            if (requests_.front().is_empty) {
                current_count--;
            }
            requests_.push_back({current_time, empty ? current_count + 1 : current_count, empty});
            requests_.pop_front();
        }
       return result_list;
    }
    
