#include <sstream>
#include <gtest/gtest.h>

#include "serializer.hpp"
#include "deserializer.hpp"


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer & serializer)
    {
        return serializer(a, b, c);
    }

    template<class Deserializer>
    Error deserialize(Deserializer & deserializer)
    {
        return deserializer(a, b, c);
    }
};


struct BigInt
{
    uint64_t arr[5];


    template <class Serializer>
    Error serialize(Serializer & serializer)
    {
        return serializer(arr[0], arr[1], arr[2], arr[3], arr[4]);
    }

    template<class Deserializer>
    Error deserialize(Deserializer & deserializer)
    {
        return deserializer(arr[0], arr[1], arr[2], arr[3], arr[4]);
    }
};


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

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}


TEST_F(TestSeries, test_1)
{
    std::stringstream stream;

    bool var = true;
    Serializer serializer(stream);
    Error ret = serializer.process(var);
    ASSERT_EQ(ret, Error::NoError);

    bool other_var = false;
    Deserializer deserializer(stream);
    ret = deserializer.process(other_var);
    ASSERT_EQ(ret, Error::NoError);
    ASSERT_EQ(var, other_var);
}


TEST_F(TestSeries, test_2)
{
    std::stringstream stream;

    uint64_t var = 43211234;
    Serializer serializer(stream);
    Error ret = serializer.process(var);
    ASSERT_EQ(ret, Error::NoError);

    uint64_t other_var = false;
    Deserializer deserializer(stream);
    ret = deserializer.process(other_var);
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


TEST_F(TestSeries, test_wrong_stream_1)
{
    std::stringstream stream;
    stream << "truetrue";
    Deserializer deserializer(stream);
    bool value = true;
    Error ret = deserializer.process(value);
    ASSERT_NE(ret, Error::NoError);
}


TEST_F(TestSeries, test_wrong_stream_2)
{
    std::stringstream stream;
    stream << "   ";
    Deserializer deserializer(stream);
    bool value = true;
    Error ret = deserializer.process(value);
    ASSERT_NE(ret, Error::NoError);
}


TEST_F(TestSeries, test_wrong_stream_3)
{
    std::stringstream stream;
    stream << "true";
    Deserializer deserializer(stream);
    uint64_t value = 2;
    Error ret = deserializer.process(value);
    ASSERT_NE(ret, Error::NoError);
}



int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
