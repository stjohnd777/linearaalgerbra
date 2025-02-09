#pragma once
#include <tuple>
#include <mutex>
#include <cstring>
#include <vector>

class ExceededFixedMemoryException : public std::runtime_error {
public:
    ExceededFixedMemoryException()
            : std::runtime_error("Exceeded Capacity. Cannot Allocated Fixed Memory ") {}
};

typedef std::tuple<size_t ,size_t ,char*> MemoryReceipt;

template<size_t N = 10*1024>
class FixedMemory {

public:

    size_t AvailableMemory(){
        std::lock_guard<std::mutex> guard(mtx);
        if(m_receipts.empty()){
            return N;
        } else {
            auto top = std::get<1>(m_receipts.back());
            return N - top;
        }
    }

     MemoryReceipt  RentMemoryChunk(size_t bytes){
        MemoryReceipt receipt;
        std::lock_guard<std::mutex>  guard(mtx);
        if ( AvailableMemory() >=  bytes ) {
            receipt = std::make_tuple(m_next_free_byte, m_next_free_byte + bytes, &m_memory[m_next_free_byte]);
            std::memset(m_memory + std::get<0>(receipt), 0, bytes);
            m_next_free_byte += bytes;
        }else {
            throw ExceededFixedMemoryException();
        }
        return receipt;
    }

    void ReturnMemoryChunk(MemoryReceipt returnReceipt){
        std::lock_guard<std::mutex>  guard(mtx);
        // find the receipt
        auto itReturnReceipt = std::find_if(
                std::begin(m_receipts),
                std::end(m_receipts),
                [&](const auto& val) {  // match [start,end]
                    return std::get<0>(val) == std::get<0>(returnReceipt) && std::get<1>(val) == std::get<1>(returnReceipt);
                }
        );

        if (itReturnReceipt != std::end(m_receipts)) {

            // Clear the memory
            std::memset(std::get<2>(returnReceipt), 0, std::get<1>(returnReceipt) - std::get<0>(returnReceipt));

            auto next_receipt = itReturnReceipt + 1;
            char* end_pos = std::get<2>(returnReceipt);
            for (; next_receipt != std::end(m_receipts); ++next_receipt) {
                size_t size = std::get<1>(*next_receipt) - std::get<0>(*next_receipt);
                std::memmove(end_pos, std::get<2>(*next_receipt), size);
                *next_receipt = std::make_tuple(std::get<0>(*itReturnReceipt), std::get<0>(*itReturnReceipt) + size, end_pos);
                end_pos += size;
            }

            // Erase the returned memory's receipt
            m_receipts.erase(itReturnReceipt);

            // Update m_next_free_byte
            if (!m_receipts.empty()) {
                m_next_free_byte = std::get<1>(m_receipts.back());
            } else {
                m_next_free_byte = 0;
            }

        }
    }

    void Reset(){
        std::lock_guard<std::mutex>  guard(mtx);
        m_receipts.clear();
        m_next_free_byte = 0;
        memset(m_memory,0,N);
    }

private:
    std::vector<MemoryReceipt> m_receipts;
    std::mutex mtx{};
    size_t m_next_free_byte = 0;
    char m_memory[N]{};
};

