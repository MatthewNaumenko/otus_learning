#include <iostream>

#include <gtest/gtest.h>

#include "../IVector.hpp"

class VectorTest_F : public testing::Test {
    protected:
        IVector<int>* expected = nullptr;

        void SetUp() override {
            expected = new IVector<int>(4);
        }

        void TearDown() override {
            delete expected;
        }
};

class DestructorTest{
    public:
        static int count_destructor;

        DestructorTest() = default;
        ~DestructorTest() {
            ++count_destructor;
        };
};

int DestructorTest::count_destructor = 0;

class MoveTest{
    public:
        static int count_move;

        MoveTest() = default;
        MoveTest(const MoveTest& other) = default;
        MoveTest& operator=(const MoveTest& other) = default;

        MoveTest(MoveTest&& other) noexcept {
            ++count_move;
        }

        MoveTest& operator=(MoveTest&& other) noexcept {
            ++count_move;
            return *this;
        }

        ~MoveTest() = default;
};

int MoveTest::count_move = 0;

TEST_F(VectorTest_F, create) {

    ASSERT_NO_THROW(IVector<int> test_expected(3));

    ASSERT_NE(expected, nullptr);
    ASSERT_EQ(expected->size(), 4);
    ASSERT_EQ(expected->get_real_size(), 4);
}

TEST_F(VectorTest_F, push_back) {

    ASSERT_NO_THROW(expected->push_back(7));

    ASSERT_EQ(expected->size(), 5);
    ASSERT_EQ(expected->get_real_size(), 8);

    ASSERT_EQ(expected->at(4), 7);

}

TEST_F(VectorTest_F, insert_first) {

    ASSERT_NO_THROW(expected->insert(0,1));

    ASSERT_EQ(expected->size(), 5);
    ASSERT_EQ(expected->get_real_size(), 8);

    ASSERT_EQ(expected->at(0), 1);

}

TEST_F(VectorTest_F, insert_middle) {

    ASSERT_NO_THROW(expected->insert(2,9));

    ASSERT_EQ(expected->size(), 5);
    ASSERT_EQ(expected->get_real_size(), 8);

    ASSERT_EQ(expected->at(2), 9);

}

TEST_F(VectorTest_F, erase_first) {
    expected->insert(0,8);
    const size_t arrange_expected_size = expected->size();
    const size_t arrange_expected_real_size = expected->get_real_size();

    ASSERT_NO_THROW(expected->erase(0));

    ASSERT_EQ(expected->size(), 4);
    ASSERT_EQ(expected->get_real_size(), 8);

    ASSERT_LT(expected->size(), arrange_expected_size);
    ASSERT_EQ(expected->get_real_size(), arrange_expected_real_size);

    ASSERT_EQ(expected->at(0), 0);
}

TEST_F(VectorTest_F, erase_middle) {
    expected->insert(2,8);
    const size_t arrange_expected_size = expected->size();
    const size_t arrange_expected_real_size = expected->get_real_size();

    ASSERT_NO_THROW(expected->erase(2));
    
    ASSERT_EQ(expected->size(), 4);
    ASSERT_EQ(expected->get_real_size(), 8);

    ASSERT_LT(expected->size(), arrange_expected_size);
    ASSERT_EQ(expected->get_real_size(), arrange_expected_real_size);

    ASSERT_EQ(expected->at(2), 0);
}

TEST_F(VectorTest_F, erase_back) {
    expected->push_back(9);
    const size_t arrange_expected_size = expected->size();
    const size_t arrange_expected_real_size = expected->get_real_size();

    ASSERT_NO_THROW(expected->erase(4));

    ASSERT_EQ(expected->size(), 4);
    ASSERT_EQ(expected->get_real_size(), 8);

    ASSERT_LT(expected->size(), arrange_expected_size);
    ASSERT_EQ(expected->get_real_size(), arrange_expected_real_size);

    ASSERT_THROW(expected->at(4), std::out_of_range);
}

TEST_F(VectorTest_F, get_elemets_at) {
    expected->push_back(9);
    expected->insert(0,8);
    expected->insert(3,7);

    ASSERT_NO_THROW(expected->at(0));
    ASSERT_NO_THROW(expected->at(3));
    ASSERT_NO_THROW(expected->at(6));
    ASSERT_THROW(expected->at(7), std::out_of_range);
    ASSERT_THROW(expected->at(-1), std::out_of_range);

    ASSERT_EQ(expected->at(0), 8);
    ASSERT_EQ(expected->at(3), 7);
    ASSERT_EQ(expected->at(6), 9);
}

TEST_F(VectorTest_F, get_size) {

    ASSERT_NO_THROW(expected->size());

    ASSERT_EQ(expected->size(), 4);
}

TEST(Vector_noF, get_elemets_indexation) {
    IVector<int> test_indexation(4);
    
    test_indexation.push_back(9);
    test_indexation.insert(0,8);
    test_indexation.insert(3,7);

    ASSERT_NO_THROW(test_indexation[0]);
    ASSERT_NO_THROW(test_indexation[3]);
    ASSERT_NO_THROW(test_indexation[6]);
    ASSERT_NO_THROW(test_indexation[9]); // У [] нет проверки границ

    ASSERT_EQ(test_indexation[0], 8);
    ASSERT_EQ(test_indexation[3], 7);
    ASSERT_EQ(test_indexation[6], 9);
}

TEST(Vector_noF, destructor) {
    //Arrange
    DestructorTest::count_destructor = 0;
    const int elements_destructor = 5; // Не забываем про создание временного объекта

    //Act
    {
        IVector<DestructorTest> expected(4);
    }

    //Assert
    ASSERT_EQ(DestructorTest::count_destructor, elements_destructor);

}

TEST(Vector_noF, move_operator) {
    //Arrange
    MoveTest::count_move = 0;
    const int elements_move = 1; 
    IVector<MoveTest> expected(5);
    IVector<MoveTest> actual;

    //Act
    actual = std::move(expected);

    //Assert
    ASSERT_EQ(MoveTest::count_move, elements_move);
}