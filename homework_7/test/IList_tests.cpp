#include <iostream>

#include <gtest/gtest.h>

#include "../IList.hpp"

class ListTest_F : public testing::Test {
    protected:
        IList<int>* expected = nullptr;

        void SetUp() override {
            expected = new IList<int>;
        }

        void TearDown() override {
            delete expected;
        }
};

TEST_F(ListTest_F, create) {
    
    ASSERT_NO_THROW(IList<int> actual);

    ASSERT_NE(expected, nullptr);
    ASSERT_EQ(expected->size(), 0);

}

TEST_F(ListTest_F, push_back) {
    
    ASSERT_NO_THROW(expected->push_back(7));

    ASSERT_EQ(expected->size(), 1);

    auto it = expected->begin();
    ASSERT_EQ(*it, 7);

}

TEST_F(ListTest_F, insert_first) {
    expected->push_back(2);
    expected->push_back(3);

    ASSERT_NO_THROW(expected->insert(0,7));

    ASSERT_EQ(expected->size(), 3);

    auto it = expected->begin();
    ASSERT_EQ(*it, 7);

}

TEST_F(ListTest_F, insert_middle) {
    expected->push_back(2);
    expected->push_back(3);
    expected->push_back(5);
    expected->push_back(6);
    auto it = expected->begin();

    ASSERT_NO_THROW(expected->insert(2,7));

    ASSERT_EQ(expected->size(), 5);

    ASSERT_EQ(it[2], 7);
    ASSERT_EQ(it[1], 3);
    ASSERT_EQ(it[3], 5);

}

TEST_F(ListTest_F, erase_first) {
    expected->push_back(2);
    expected->push_back(3);
    expected->push_back(5);
    const size_t arrange_expected_size = expected->size();

    ASSERT_NO_THROW(expected->erase(0));

    ASSERT_EQ(expected->size(), 2);

    ASSERT_LT(expected->size(), arrange_expected_size);

    auto it = expected->begin();
    ASSERT_EQ(it[0], 3);
    ASSERT_EQ(it[1], 5);
}

TEST_F(ListTest_F, erase_middle) {
    expected->push_back(2);
    expected->push_back(3);
    expected->push_back(5);
    expected->push_back(6);
    const size_t arrange_expected_size = expected->size();

    ASSERT_NO_THROW(expected->erase(2));
    
    ASSERT_EQ(expected->size(), 3);

    ASSERT_LT(expected->size(), arrange_expected_size);

    auto it = expected->begin();
    ASSERT_EQ(it[2], 6);
    ASSERT_EQ(it[1], 3);
}

TEST_F(ListTest_F, erase_back) {
    expected->push_back(3);
    expected->push_back(5);
    const size_t arrange_expected_size = expected->size();

    ASSERT_NO_THROW(expected->erase(1));

    ASSERT_EQ(expected->size(), 1);

    ASSERT_LT(expected->size(), arrange_expected_size);

    auto it = expected->begin();
    ASSERT_EQ(it[0], 3);
    
    ASSERT_THROW(it[1], std::out_of_range);
}

TEST_F(ListTest_F, get_size) {

    ASSERT_NO_THROW(expected->size());

    ASSERT_EQ(expected->size(), 0);
}

TEST_F(ListTest_F, get_size_multi) {
    expected->push_back(3);
    expected->push_back(5);

    ASSERT_NO_THROW(expected->size());

    ASSERT_EQ(expected->size(), 2);
}

TEST_F(ListTest_F, get_elemets) {
    expected->push_back(1);
    expected->push_back(2);
    expected->push_back(3);
    expected->push_back(4);
    auto it = expected->begin();
    
    ASSERT_NO_THROW(it[0]);
    ASSERT_NO_THROW(it[1]);
    ASSERT_NO_THROW(it[2]);
    ASSERT_NO_THROW(it[3]);
    ASSERT_THROW(it[-1], std::out_of_range);
    ASSERT_THROW(it[4], std::out_of_range);

    ASSERT_NO_THROW(*it);

    ASSERT_EQ(it[0], 1);
    ASSERT_EQ(it[1], 2);
    ASSERT_EQ(it[2], 3);
    ASSERT_EQ(it[3], 4);
    ASSERT_EQ(*it, 1);
}

TEST(ListTest_noF, copy_list) {
    //Arrange
    IList<int> list_out;
    IList<int> list_in;
    list_out.push_back(2);
    list_out.push_back(3);
    list_out.push_back(4);
    const size_t list_out_size = list_out.size();
    const size_t list_in_size = list_in.size();


    //Act
    ASSERT_NO_THROW(list_in = list_out);

    //Assert
    ASSERT_EQ(list_in.size(), list_out_size);
    ASSERT_GT(list_in.size(), list_in_size);

    auto it_in = list_in.begin();
    auto it_out = list_out.begin();

    for (size_t i{0}; i < list_out_size; ++i) {
        ASSERT_EQ(it_in[i], it_out[i]);
    }
}