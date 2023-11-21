#pragma once

template <typename It>
class IteratorRange {
    public:
        IteratorRange(It begin_range, It end_range);

        It begin() const;
        
        It end() const;
        
        It size() const;
        
    private:
        It begin_;
        It end_;
        size_t size_;
};

template <typename It>
IteratorRange<It>::IteratorRange(It begin_range, It end_range) 
            : begin_(begin_range), end_(end_range),
            size_(end_range - begin_range) 
        {
        }

template <typename It>
It IteratorRange<It>::begin() const {
            return begin_;
        }

template <typename It>
It IteratorRange<It>::end() const {
            return end_;
        }

template <typename It>
It IteratorRange<It>::size() const {
            return size_;
        }

template<typename It>
std::ostream&  operator<<(std::ostream& output, const IteratorRange<It>& p) {
    for (auto page = p.begin(); page != p.end(); page++) {
        output << *page;
    }
    return output;
}


template<typename RandomIt>
class Paginator {
    public:
        explicit Paginator(RandomIt begin_range, RandomIt end_range, size_t page_size);
        
        auto begin() const;
        
        auto end() const;
        
        size_t size() const;
    
    private: 
        std::vector<IteratorRange<RandomIt>> range_list_;
};

template<typename RandomIt>
Paginator<RandomIt>::Paginator(RandomIt begin_range, RandomIt end_range, size_t page_size)
    {
        int n = (end_range - begin_range) / page_size;
        int mod_n = (end_range - begin_range) % page_size;
        auto it = begin_range;
        for (int i = 0; i < n; i++) {
            auto begin = it;
            std::advance(it, page_size);
            IteratorRange r(begin, it);
            range_list_.push_back(r);
           }
        if (mod_n != 0) {
            IteratorRange r(it, it + mod_n);
            range_list_.push_back(r);
        }
    }
        
template<typename RandomIt>
auto Paginator<RandomIt>::begin() const {
    return range_list_.begin();
   }
        
template<typename RandomIt>
auto Paginator<RandomIt>::end() const {
    return range_list_.end();
}

template<typename RandomIt>
size_t Paginator<RandomIt>::size() const {
    return range_list_.size();
}

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

