#include <sstream>
#include <gtest/gtest.h>

#include "serializer.hpp"
#include "deserializer.hpp"
#include "test_serializer.hpp"



class TestSeries : public ::testing::Test {};


TEST_F(TestSeries, test_default)
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    Error err = serializer.save(x);
    ASSERT_EQ(err, Error::NoError);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    err = deserializer.load(y);
    ASSERT_EQ(err, Error::NoError);

    ASSERT_TRUE(x == y);
}


TEST_F(TestSeries, test_one_bool_1)
{
    std::stringstream stream;

    OneBool obj {true}, other {false};

    Serializer serializer(stream);
    Deserializer deserializer(stream);

    Error err = serializer.save(obj);
    ASSERT_EQ(err, Error::NoError);

    err = deserializer.load(other);
    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(obj, other);
}


TEST_F(TestSeries, test_one_bool_2)
{
    std::stringstream stream;

    OneBool obj {false}, other {true};

    Serializer serializer(stream);
    Deserializer deserializer(stream);

    Error err = serializer.save(obj);
    ASSERT_EQ(err, Error::NoError);

    err = deserializer.load(other);
    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(obj, other);
}


TEST_F(TestSeries, test_one_int_1)
{
    std::stringstream stream;

    OneUint64 obj {123456}, other {23};

    Serializer serializer(stream);
    Deserializer deserializer(stream);

    Error err = serializer.save(obj);
    ASSERT_EQ(err, Error::NoError);

    err = deserializer.load(other);
    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(obj, other);
}


TEST_F(TestSeries, test_one_int_wrong_1)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "124345732467856378465738465347568347";

    OneUint64 obj {12};
    Error err = deserializer.load(obj);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_one_int_wrong_2)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "-12";

    OneUint64 obj {12};
    Error err = deserializer.load(obj);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_one_int_wrong_3)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "234|23";

    OneUint64 obj {12};
    Error err = deserializer.load(obj);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_one_bool_wrong_1)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "0";

    OneBool obj {true};
    Error err = deserializer.load(obj);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_one_bool_wrong_2)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "1";

    OneBool obj {true};
    Error err = deserializer.load(obj);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_one_bool_wrong_3)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "true|false";

    OneBool obj {true};
    Error err = deserializer.load(obj);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_1)
{
    std::stringstream stream;

    bool var = true;
    Serializer serializer(stream);
    Error ret = serializer(var);
    ASSERT_EQ(ret, Error::NoError);

    bool other_var = false;
    Deserializer deserializer(stream);
    ret = deserializer(other_var);
    ASSERT_EQ(ret, Error::NoError);
    ASSERT_EQ(var, other_var);
}


TEST_F(TestSeries, test_2)
{
    std::stringstream stream;

    uint64_t var = 43211234;
    Serializer serializer(stream);
    Error ret = serializer(var);
    ASSERT_EQ(ret, Error::NoError);

    uint64_t other_var = false;
    Deserializer deserializer(stream);
    ret = deserializer(other_var);
    ASSERT_EQ(ret, Error::NoError);
    ASSERT_EQ(var, other_var);
}


TEST_F(TestSeries, test_3)
{
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);

    BigInt b = {{23, 1234, 90, 12, 34}};
    Error ret = serializer.save(b);
    ASSERT_EQ(ret, Error::NoError);

    BigInt c = {{0}};
    ret = deserializer.load(c);
    ASSERT_EQ(ret, Error::NoError);

    for (int i = 0; i < 5; i++)
    {
        ASSERT_EQ(b.arr[i], c.arr[i]);
    }
}


TEST_F(TestSeries, test_ser_delser)
{
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    Error err;

    Data x1 = {3, false, 23};
    BigInt x2 = {{3, 2, 1, 4, 5}};

    err = serializer.save(x1);
    ASSERT_EQ(err, Error::NoError);
    err = serializer.save(x2);
    ASSERT_EQ(err, Error::NoError);
    err = serializer.save(x2);
    ASSERT_EQ(err, Error::NoError);
    err = serializer.save(x1);
    ASSERT_EQ(err, Error::NoError);

    Data x3 = {0, false, 0};
    BigInt x4 = {{0}};

    err = deserializer.load(x3);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_TRUE(x1 == x3);
    err = deserializer.load(x4);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_TRUE(x2 == x4);
    err = deserializer.load(x4);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_TRUE(x2 == x4);
    err = deserializer.load(x3);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_TRUE(x1 == x3);
}


TEST_F(TestSeries, test_diff_num_1)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "12 true";
    Data x {};
    Error err = deserializer.load(x);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_diff_num_2)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "12 true 24 24";
    Data x {}, y {12, true, 24};
    Error err = deserializer.load(x);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(x, y);
}


TEST_F(TestSeries, test_diff_num_3)
{
    std::stringstream stream;
    Deserializer deserializer(stream);

    stream << "43 12 true 24";
    Data x {};
    Error err = deserializer.load(x);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_wrong_stream_1)
{
    std::stringstream stream;
    stream << "truetrue";
    Deserializer deserializer(stream);
    bool value = true;
    Error ret = deserializer(value);
    ASSERT_EQ(ret, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_wrong_stream_2)
{
    std::stringstream stream;
    stream << "   ";
    Deserializer deserializer(stream);
    bool value = true;
    Error ret = deserializer(value);
    ASSERT_EQ(ret, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_wrong_stream_3)
{
    std::stringstream stream;
    stream << "true";
    Deserializer deserializer(stream);
    uint64_t value = 2;
    Error ret = deserializer(value);
    ASSERT_EQ(ret, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_wrong_stream_4)
{
    std::stringstream stream;
    stream << "1-234232";
    Deserializer deserializer(stream);
    uint64_t value = 2;
    Error ret = deserializer(value);
    ASSERT_EQ(ret, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_wrong_stream_5)
{
    std::stringstream stream;
    stream << "1";
    Deserializer deserializer(stream);
    bool value = true;
    Error ret = deserializer(value);
    ASSERT_EQ(ret, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_wrong_stream_6)
{
    std::stringstream stream;
    stream << "truestr";
    Deserializer deserializer(stream);
    bool value = true;
    Error ret = deserializer(value);
    ASSERT_EQ(ret, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_wrong_stream_7)
{
    std::stringstream stream;
    stream << "34string";
    Deserializer deserializer(stream);
    uint64_t value = 12;
    Error ret = deserializer(value);
    ASSERT_EQ(ret, Error::CorruptedArchive);
}


TEST_F(TestSeries, test_wrong_stream_8)
{
    std::stringstream stream;
    stream << "false1";
    Deserializer deserializer(stream);
    bool value = false;
    Error ret = deserializer(value);
    ASSERT_EQ(ret, Error::CorruptedArchive);
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
