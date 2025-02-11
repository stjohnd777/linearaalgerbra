#include <gtest/gtest.h>
#include "FixMemory.h"
#include "Vector.h"

using namespace dsj;
class FixedMemoryTest : public ::testing::Test {

protected:
    FixedMemory<1024> fixed_memory; // create an instance of FixedMemory with 1KB.

    // Variable to hold the memory receipt.
    MemoryReceipt receipt;
};

TEST_F(FixedMemoryTest, RentMemoryChunk) {
    EXPECT_NO_THROW({
                        receipt = fixed_memory.RentMemoryChunk(512);
                    });
    // Check if the size of allocated memory is correct
    EXPECT_EQ(512, std::get<1>(receipt) - std::get<0>(receipt));
    // Check if memory allocated starts from the beginning
    EXPECT_EQ(0, std::get<0>(receipt));
}

TEST_F(FixedMemoryTest, ReturnMemoryChunk) {
    //first we need to rent memory
    receipt = fixed_memory.RentMemoryChunk(512);
    EXPECT_NO_THROW({
                        fixed_memory.ReturnMemoryChunk(receipt);
                    });
    // Available memory should be 1024 after returning 512-byte memory chunk
    EXPECT_EQ(1024, fixed_memory.AvailableMemory());
}

TEST_F(FixedMemoryTest, Reset) {
    //first we rent some memory
    receipt = fixed_memory.RentMemoryChunk(512);
    fixed_memory.Reset();
    // After reset, total available memory should be 1024
    EXPECT_EQ(1024, fixed_memory.AvailableMemory());
}


TEST_F(FixedMemoryTest, vec){
    MemoryReceipt memReceipt = fixed_memory.RentMemoryChunk(sizeof (Vector < float, 3 >));
    auto* ptr = std::get<2>(memReceipt);
    auto* v = new(ptr) Vector<float,3>({0.1,0.1,29.99});
    v->norm();
    fixed_memory.ReturnMemoryChunk(memReceipt);
}