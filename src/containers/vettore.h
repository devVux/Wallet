#pragma once

template <class T>
class Vettore {
    public:

        using iterator = T*;
        using const_iterator = const T*;

        explicit Vettore(unsigned int s = 0): mCapacity(s == 0 ? 1 : 2 * s), mSize(s), v(new T[mCapacity]) {}

        Vettore(const Vettore& v2): mSize(v2.mSize), mCapacity(v2.mCapacity), v(v2.copy()) {}

        ~Vettore() {
            delete[] v;
        }

        Vettore& operator=(Vettore& v2) {
            if (this != &v2) {
                mSize = v2.mSize;
                mCapacity = v2.mCapacity;
                delete[] v;
                v = v2.copy();
            }
            return *this;
        }
        
        T& operator[](size_t i) const {
            return v[i];
        }

        unsigned int size() const {
            return mSize;
        };

        unsigned int cpacity() const {
            return mCapacity;
        };

        T& at(size_t index) const {
            return v[index];
        };

        void push_back(const T& t) {
            if (mSize >= mCapacity) {
                mCapacity *= 2;
                T* temp = new T[mCapacity];
                
                for(size_t i = 0; i < mSize; i++) 
                    temp[i] = v[i];
                
                delete[] v;
                v = temp;
            }
            v[mSize] = t;
            mSize++;
        }
        
        void push_front(const T& t) {
            if (mSize >= mCapacity) {
                mCapacity *= 2;
                T* temp = new T[mCapacity];
                
                // Next is equal to the previous
                for(size_t i = 0; i < mSize; i++)
                    temp[i + 1] = v[i];
                
                delete[] v;
                v = temp;
            }
            else 
                for (size_t i = mSize; i > 0; i--)
                    std::swap(v[i], v[i - 1]);
            v[0] = t;
            mSize++;
        }

        T* pop() {
            if (mSize > 0) {
                mSize--;
                return &v[mSize + 1];
            }
            return nullptr;
        }

        void remove(size_t index) {
            if (index < mSize && index >= 0) {

                // Push the element to the back and decrease the mSize
                for (index; index < mSize - 1; index++) {
                    std::swap(v[index], v[index + 1]);
                }

                mSize--;

            }
        }

        void clear() {
            mSize = 0;
        }

        void erase(typename Vettore<T>::iterator position) {
            if (position >= begin() && position < end()) {
                auto index = position - begin();
                for (auto i = index; i < mSize - 1; ++i) {
                    v[i] = v[i + 1];
                }
                --mSize;
            }
        }

        typename Vettore<T>::iterator begin() {
            return v;
        }

        typename Vettore<T>::iterator end() {
            return v + mSize;
        }           
        
        typename Vettore<T>::const_iterator begin() const {
            return v;
        }

        typename Vettore<T>::const_iterator end() const {
            return v + mSize;
        }   

    private:

        T* copy() const {
            if (mSize == 0) 
                return nullptr;

            T* v2 = new T[mSize];

            for (size_t i = 0; i < mSize; i++)
                v2[i] = v[i];

            return v2;
        }

    private:
        
        unsigned int mCapacity;
        
        unsigned int mSize;

        T* v;

};

