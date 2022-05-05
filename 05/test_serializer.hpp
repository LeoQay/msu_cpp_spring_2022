#ifndef HW_CPP_VK_TEST_SERIALIZER_HPP
#define HW_CPP_VK_TEST_SERIALIZER_HPP


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    bool operator== (const Data & obj) const
    {
        return a == obj.a && b == obj.b && c == obj.c;
    }

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

    bool operator== (const BigInt & obj) const
    {
        for (int i = 0; i < 5; i++)
        {
            if (arr[i] != obj.arr[i])
            {
                return false;
            }
        }
        return true;
    }

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


struct OneBool
{
    bool val;

    bool operator== (const OneBool & obj) const
    {
        return val == obj.val;
    }

    template <class Serializer>
    Error serialize(Serializer & serializer)
    {
        return serializer(val);
    }

    template<class Deserializer>
    Error deserialize(Deserializer & deserializer)
    {
        return deserializer(val);
    }
};


struct OneUint64
{
    uint64_t val;

    bool operator== (const OneUint64 & obj) const
    {
        return val == obj.val;
    }

    template <class Serializer>
    Error serialize(Serializer & serializer)
    {
        return serializer(val);
    }

    template<class Deserializer>
    Error deserialize(Deserializer & deserializer)
    {
        return deserializer(val);
    }
};



#endif //HW_CPP_VK_TEST_SERIALIZER_HPP
