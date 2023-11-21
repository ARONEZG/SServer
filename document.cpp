#include "document.h"

using namespace std;

Document::Document(int id, double relevance, int rating)
    : id(id)
    , relevance(relevance)
    , rating(rating) 
    {
    }

ostream&  operator<<(ostream& output, const Document& d) {
    const auto [id, relevance, rating] = d;
    output << "{ "s
         << "document_id = "s << id << ", "s
         << "relevance = "s << relevance << ", "s
         << "rating = "s << rating << " }"s;
    return output;
}