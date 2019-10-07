#ifndef TCONTAINER_H
#define TCONTAINER

#include<stdlib.h>

    template <class T, class C>
    class tContainer_t{
        typedef typename C::iterator iter_t;
        typedef typename C::const_iterator citer_t;

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
            void remove_destroy();
            T* operator[](size_t index);

        private:
            C container;
            tContainer_t(const tContainer_t& );
            tContainer_t& operator=(const tContainer_t&);
    };
template <class T, class C>
inline size_t tContainer_t<T, C>::size() const { return container.size();}

template <class T, class C>
inline bool tContainer_t<T, C>::empty() const { return container.empty();}

template <class T, class C>
inline void tContainer_t<T, C>::push_back(const T* elem) { container.push_back(elem);}

template <class T, class C>
inline const T* tContainer_t<T, C>::front() const { return container.front();}

template <class T, class C>
inline const T* tContainer_t<T, C>::back() const { return container.back();}

#endif