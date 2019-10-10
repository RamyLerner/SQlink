#ifndef TCONTAINER_H
#define TCONTAINER

#include<stdlib.h>
#include<algorithm>
#include<typeinfo>
#include<vector>

    template <class T, template <typename> class C>
    class tContainer_t{
        typedef typename C<T>::iterator iter_t;
        typedef typename C<T>::const_iterator citer_t;

        public:
            ~tContainer_t();
            tContainer_t();
            inline size_t size() const;
            inline bool empty() const;
            inline void push_back(const T* elem);
            inline const T* front() const;
            inline const T* back() const;
            const T* findElement (const T& elem) const;
            T* removeElem (const T& elem); //should call erase()
            void clear(); //removes all elements (and destroying) without deleting!!
            void remove_destroy (T& elem);
            void clear_destroy();
            T* operator[](size_t index);

        private:
            C<T> container;
            tContainer_t(const tContainer_t& );
            tContainer_t& operator=(const tContainer_t&);
    };

    template <class T>
    class comparison{
        public:
            comparison(T t) : val(t) {}
            bool operator()(const T* param) const {return *param == val;}
        private:
            T val;
    };

template  <class T, template <typename> class C>
tContainer_t<T, C>::tContainer_t() { container = new C<T>;}

template  <class T, template <typename> class C>
tContainer_t<T, C>::~tContainer_t() { delete container;}

template  <class T, template <typename> class C>
inline size_t tContainer_t<T, C>::size() const { return container.size();}

template  <class T, template <typename> class C>
inline bool tContainer_t<T, C>::empty() const { return container.empty();}

template  <class T, template <typename> class C>
inline void tContainer_t<T, C>::push_back(const T* elem) { container.push_back(elem);}

template  <class T, template <typename> class C>
inline const T* tContainer_t<T, C>::front() const { return container.front();}

template  <class T, template <typename> class C>
inline const T* tContainer_t<T, C>::back() const { return container.back();}

template  <class T, template <typename> class C>
const T* tContainer_t<T, C>::findElement(const T& elem) const {
    citer_t it = std::find_if(container.begin(), container.end(), comparison<T>(elem));
    return *it;
}

template  <class T, template <typename> class C>
T* tContainer_t<T, C>::removeElem (const T& elem){
    iter_t it = std::find_if(container.begin(), container.end(), comparison<T>(elem));
    T* tPtr = *it;
    container.erase(it);
    return tPtr;
}

template  <class T, template <typename> class C>
void tContainer_t<T, C>::clear(){ container.clear();}

template  <class T, template <typename> class C>
void tContainer_t<T, C>::remove_destroy (T& elem){
    iter_t it = std::find_if(container.begin(), container.end(), comparison<T>(elem));
    delete *it;
    container.erase(it);
}

template  <class T, template <typename> class C>          
void tContainer_t<T, C>::clear_destroy(){
    citer_t it;
    for (it = container.begin(); it != container.end(); ++it){
        delete *it;
    }
    container.clear();
}

template  <class T, template <typename> class C>     
T* tContainer_t<T, C>::operator[](size_t index){
    int i=0;
    if (typeid(container) == typeid(std::vector<T>))
        try {
            return container[index];
        }
        catch (std::bad_alloc&){
            throw;
        }
    else
    {
        if (index >= container.size())
            throw std::bad_alloc();
        citer_t it = container.begin();
        for (i=0; i<index; i++)
            it++;
        return *it;
    }
}

#endif