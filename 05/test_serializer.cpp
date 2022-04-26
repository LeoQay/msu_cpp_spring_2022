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



class TestSeries : public ::testing::Test
{
public:
};


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


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
