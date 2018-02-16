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

/* Includes */
#include "Collection.h"
#include "IRSensorControl.h"

/* TODO: This is pretty ugly but I need it to compile */
template class Collection<IRListener*>;

template<typename T>
Collection<T>::Collection() {
    /* Initialize our collection to be empty */
    this->c_size = 0;
    this->capacity = 0;
    this->payload = NULL;
}

template<typename T>
Collection<T>::~Collection() {
    free(this->payload);
}

template<typename T>
void Collection<T>::push(const T& data) {
    /* If we hit the max size then resize the array */
    if (this->c_size == this->capacity) {
        if (!this->resize()) {
            /* We could not allocate required memory so don't add new elements */
            return;
        }
    }

    /* Set the data and increase our size */
    this->payload[this->c_size] = data;
    this->c_size++;
}

template<typename T>
size_t Collection<T>::size() {
    return this->c_size;
}

template<typename T>
T& Collection<T>::operator[](size_t i) {
    return this->payload[i];
}

template<typename T>
boolean Collection<T>::resize() {
    /* If we were empty let's set our size to 1 otherwise double it */
    this->capacity = (!this->capacity) ? 1 : this->capacity * 2;

    /* Re-allocate memory to the data pointer */
    T* newPayload;
    if ((newPayload = (T*) realloc(this->payload, this->capacity * sizeof(T)))) {
        /* Only update if we were able to re-allocate enough memory */
        this->payload = newPayload;
        return true;
    } else {
        return false;
    }
}
