//!
//! (c) Copyright 2011-2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: Jan 08, 2013
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!/

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

namespace pni{
namespace core{
    
    /*!
    \brief counter template

    This template implements a simple counter. An instance of counter<T> starts
    with an initial value which can be incremented or decremented by calling the
    appropriate member functions. 
    When the counter value becomes lower than its initial value an underflow has
    occured and when it exceeds its stop value an overflow occurs. In both cases
    a function will be called. This procedure can be used to build cascades of
    counters. 

    */
    template<typename T> class counter
    {
        private:
            //==================private member variables=======================
            //! starting value of the counter
            T _start;     
            //! stop value of the counter
            T _stop;
            //! increment 
            T _increment;
            //! actual value
            T _value;
            //! function called when an overflow occurs
            std::vector<std::function<void()> >_overflow_callbacks;
            //! function called when an underflow occurs
            std::vector<std::function<void()> > _underflow_callbacks;

        public:
            //=======================public types==============================
            //! value type of the counter
            typedef T value_type;
            //! type for callbacks
            typedef std::function<void()> callback_type; 

            //===================constructors and destructor===================
            //! default constructor
            counter():
                _start(T(0)),
                _stop(T(0)),
                _increment(T(0)),
                _value(_start),
                _overflow_callbacks(),
                _underflow_callbacks()
            {}

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            Constructor taking a start and stop value for the counter
            \param start first value of the counter
            \param stop last value of the counter
            \param inc the value the counter is increment at each step
            */
            counter(T start,T stop,T inc=T(1)):
                _start(start),
                _stop(stop),
                _increment(inc),
                _value(_start),
                _overflow_callbacks(),
                _underflow_callbacks()
            {}

            //==================public member functions========================
            /*!
            \brief counter  reset

            This member function resets the counter to its initial state. 
            */
            void reset() { _value = _start; }

            //-----------------------------------------------------------------
            /*!
            \brief increment counter

            Increment the counter by adding the increment value to the current
            value of the counter. The only parameter of this function determines
            whether the counter should be reseted in the case of an overflow or
            not.
            \param reset_if_overflow if true the counter will perform a reset
            */
            void increment(bool reset_if_overflow=false); 

            //-----------------------------------------------------------------
            /*!
            \brief decrement counter

            Decrementing the counter by one step by subtracting the increment
            value from the current counter value. The only argument of this
            function determines whether the counter should be reset in the case
            of an underflow. 
            \param reset_if_underflow if true counter will perform a reset on
            underflow
            */
            void decrement(bool reset_if_underflow=false);

            //-----------------------------------------------------------------
            /*!
            \brief register overflow callback

            Register a new overflow callback function. This method appends a new
            overflow callback function to the overflow callback stack. 
            \param cb callback function object
            */
            void register_overflow_callback(callback_type &&cb)
            {
                _overflow_callbacks.push_back(cb);
            }

            //-----------------------------------------------------------------
            /*!
            \brief register underflow callback

            Register a new underflow callback function. This method registers a
            new callback function to the underflow callback stack.
            \param cb callback function object
            */
            void register_underflow_callback(callback_type &&cb)
            {
                _underflow_callbacks.push_back(cb);
            }
            
            //-----------------------------------------------------------------
            //! get current counter value
            T value() const { return _value; }

            //-----------------------------------------------------------------
            //! set value manually
            void value(T v) { _value = v; }

            //-----------------------------------------------------------------
            //! get start value
            T start() const { return _start; }

            //-----------------------------------------------------------------
            //! get stop value
            T stop() const { return _stop; }

            //-----------------------------------------------------------------
            //! get increment
            T inc() const { return _increment; }


    };

    //=================implementation of member functions======================
    template<typename T> void counter<T>::increment(bool reset_if_overflow)
    {
        if(_value+_increment <= _stop)
        {
            //everything is fine - we can increase the counter value
            _value += _increment; 
        }
        else
        {
            //an overflow occurred - we need to take some action
            for(auto iter = _overflow_callbacks.begin();
                     iter!=_overflow_callbacks.end();
                     ++iter)
                (*iter)();

            if(reset_if_overflow) this->reset();
        }
    }

    //-------------------------------------------------------------------------
    template<typename T> void counter<T>::decrement(bool reset_if_underflow)
    {
        if(_value - _increment >= _start)
        {
            //everything is fine - we can decrease the counter value
            _value -= _increment;
        }
        else
        {
            //an underflow occurred - we need to take some action here
            for(auto iter=_underflow_callbacks.begin();
                     iter!=_underflow_callbacks.end();
                     ++iter)
                (*iter)();

            if(reset_if_underflow) this->reset();
        }
    }

    //=================factory functions to create a counter object============
    //the factory functions are defined outside the scope of the template body
    //in order determine the counter type from the argument type of the
    //functions.

    /*!
    \brief counter factory

    This factory function for a counter takes only the stop value as its only
    argument. The start value is assumed to be the 0 of the argument type and
    the increment is assumed to be the 1 of type T.
    \tparam T counter value type
    \param stop final value of the counter
    \return instance of counter<T>
    */
    template<typename T> 
    counter<T> create_counter(T stop)
    {
        return counter<T>(T(0),stop,T(1));
    }

    //-------------------------------------------------------------------------
    /*!
    \brief counter factory 

    Factory function for a counter taking start and stop value. The increment
    is assumed to be 1 of type T.
    \tparam T value type of the counter
    \param start first (initial) value of the counter
    \param stop final value of the counter
    \return instance of counter<T>
    */
    template<typename T> 
    counter<T> create_counter(T start,T stop)
    {
        return counter<T>(start,stop,T(1));
    }

    //-------------------------------------------------------------------------
    /*!
    \brief counter factory

    Factory function for counters. The function takes the initial value the
    number of steps and the increment as arguments. 
    \tparam T value type of the counter
    \param start initial value of the counter
    \param N number of steps
    \param inc increment for the counter
    \return instance of counter<T>
    */
    template<typename T> 
    counter<T> create_counter(T start,size_t N,T inc=T(1))
    {
        return counter<T>(start,start+N*inc,inc); 
    }

//end of namespace 
}
}
