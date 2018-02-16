/**************************************************************
 * File: Collection.h
 *
 * Description: Basic replacement for the std::vector class.
 *              Has complete ownership of elements inside
 * 
 * Notes: IR sensor reading requires the user to manually read
 *        the sensors. Library does not contain any threads
 *        because of memory constraints.
 *
 * Public Functions: void addListener(IRListener&)
 *                   void readSensors()
 * 
 * @author Group 1
 **************************************************************/

#ifndef Collection_h
#define Collection_h

/* Includes */
#include <Arduino.h>
#include <stdint.h>

/* Class Definitions */
template<typename T>
class Collection {
    public:
	Collection();
        ~Collection();
        void push(const T& data);
        size_t size();
        T &operator[](size_t i);

    private:
        size_t c_size;
        size_t capacity;
        T *payload;
        boolean resize();
};

#endif // define

