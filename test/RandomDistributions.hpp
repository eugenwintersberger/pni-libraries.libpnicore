#ifndef __RANDOMDISTRIBUTIONS_HPP__
#define __RANDOMDISTRIBUTIONS_HPP__

#include "TypeInfo.hpp"
#include "Types.hpp"

using namespace pni::utils;

template<typename CT,bool is_int,bool is_complex> class UniformDistribution;

//create integer data uniformly distributed
template<typename CT> class UniformDistribution<CT,true,false> 
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            CT container(n);
            
            std::mt19937_64 engine;
            std::uniform_int_distribution<> 
                dist(TypeInfo<value_type>::min(),TypeInfo<value_type>::max());

#ifdef NOFOREACH
            for(auto iter=container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
                v = dist(engine);
            }

            return container;
        }
};

//create floating point uniform distribution
template<typename CT> class UniformDistribution<CT,false,false>
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            CT container(n);
            
            std::mt19937_64 engine;
            std::uniform_real_distribution<> 
                dist(TypeInfo<Float32>::min(),TypeInfo<Float32>::max());

#ifdef NOFOREACH
            for(auto iter=container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
                v = dist(engine);
            }

            return container;
        }
};

//create complex uniform distribution
template<typename CT> class UniformDistribution<CT,false,true>
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            typedef typename value_type::value_type base_type;
            CT container(n);
            
            std::mt19937_64 engine;
            std::uniform_real_distribution<>
                dist(TypeInfo<Float32>::min(),
                     TypeInfo<Float32>::max());

#ifdef NOFOREACH
            for(auto iter = container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
                v = value_type(dist(engine),dist(engine));
            }

            return container;
        }
};

class RandomDistribution
{
    public:
        template<typename CT> static CT uniform(size_t n)
        {
            return UniformDistribution<CT,
                                       TypeInfo<typename CT::value_type>::is_integer,
                                       TypeInfo<typename CT::value_type>::is_complex>
                                           ::create_data(n);
        }
};
#endif
