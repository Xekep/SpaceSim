#pragma once
#include <random>

class Randomizer final
{
public:
    static Randomizer& GetInstance()
    {
        static Randomizer instance;
        return instance;
    }
    template<typename T>
    T Generate(T min, T max)
    {
        RandSeed();
        if constexpr (std::is_floating_point_v<T>)
        {
            std::uniform_real_distribution<T> distribution(min, max);
            return distribution(_Generator);
        }
        else
        {
            std::uniform_int_distribution<T> distribution(min, max);
            return distribution(_Generator);
        }
    }
    template<typename T>
    T Generate(T max)
    {
        return Generate(static_cast<T>(0), max);
    }
    int Generate()
    {
        RandSeed();
        return _Generator();
    }
private:
    inline void RandSeed()
    {
        std::random_device rd;
        _Generator.seed(rd());
    }
    std::mt19937 _Generator;
    Randomizer() {}
    Randomizer(const Randomizer& root) = delete;
    Randomizer& operator=(const Randomizer&) = delete;
};
