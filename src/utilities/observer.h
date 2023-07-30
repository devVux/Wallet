#pragma once

#include <vector>

using std::vector;

template <class T>
class Observer {

    public:

        virtual ~Observer() = default;

        // Notifies the observer about changes in the observed object.
        virtual void notify(T&) = 0;

};

// Non copia gli osservatori
template <class T>
class ObservedBy {

    public:
       
        ObservedBy() = default;
        
        virtual ~ObservedBy() = default;   

        ObservedBy(const ObservedBy& other) {
            mObservers.clear();
        }

        ObservedBy& operator=(const ObservedBy& other) {
            if (this == &other) 
                return *this;
            mObservers.clear();
            return *this;
        }

        // Notifies all the registered observers about changes in the observed object.
        virtual void notifyAll() = 0;

        void registerObserver(T* observer) {
            const auto it = std::remove(mObservers.begin(), mObservers.end(), observer);
            if (it == mObservers.end())
                mObservers.push_back(observer);
        }

        void removeObserver(T* observer) {
            const auto it = std::remove(mObservers.begin(), mObservers.end(), observer);
            if (it != mObservers.end())
                mObservers.erase(it);
        }


    protected:

        vector<T*> mObservers;

};
