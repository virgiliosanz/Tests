#ifndef TYPELIST_HPP
#define TYPELIST_HPP

// this ones only purpose is to store a template parameter list. it does not have
// a definition, because it will never be instantiated
template<typename...>
struct ParameterPack;

// define a type list
template<typename...>
struct TypeList;

template<typename T, typename... TT>
struct TypeList<T, TT...> {
    typedef T type;
    typedef TypeList<TT...> tail;
};

template<>
struct TypeList<> {

};

// the following functions returns the size of a list
template<typename List>
struct GetSize;

template<typename... Items>
struct GetSize<TypeList<Items...>> {
    enum {
        value = sizeof...(Items)
    };
};

// the following meta-function smelts TypeLists together into one list
template<typename... T>
struct ConcatList;

template<typename... First, typename... Second, typename... Tail>
struct ConcatList<TypeList<First...>, TypeList<Second...>, Tail...> {
    typedef typename ConcatList<TypeList<First..., Second...>,
            Tail...>::type type;
};

template<typename T>
struct ConcatList<T> {
    typedef T type;
};

// appends an item to a list
template<typename NewItem, typename List>
struct AppendItem;

template<typename NewItem, typename...Items>
struct AppendItem<NewItem, TypeList<Items...>> {
    typedef TypeList<Items..., NewItem> type;
};

// prepends an item to a list
template<typename NewItem, typename List>
struct PrependItem;

template<typename NewItem, typename...Items>
struct PrependItem<NewItem, TypeList<Items...>> {
    typedef TypeList<NewItem, Items...> type;
};

// gets the item on the Nth position
template<typename List, int N, typename = void>
struct GetItem {
    static_assert(N>0, "index cannot be negative");
    static_assert(GetSize<List>::value>0, "index too high");
    typedef typename GetItem<typename List::tail, N-1>::type type;
};

template<typename List>
struct GetItem<List, 0> {
    static_assert(GetSize<List>::value>0, "index too high");
    typedef typename List::type type;
};

// finds an item using a Matcher policy
template<typename List, template<typename, typename...> class Matcher, typename... Keys>
struct FindItem {
    static_assert(GetSize<List>::value>0, "Could not match any item.");
    typedef typename List::type current_type;
    typedef typename Conditional<Matcher<current_type, Keys...>::value,
            Identity<current_type>, // found!
            FindItem<typename List::tail, Matcher, Keys...>>
    ::type::type type;
};

// replaces one item at a certain index I
template<typename List, int I, typename NewItem>
struct ReplaceItem {
    static_assert(I>0, "index cannot be negative");
    static_assert(GetSize<List>::value>0, "index too high");
    typedef typename PrependItem<typename List::type,
            typename ReplaceItem<typename List::tail, I-1,
                    NewItem>::type>
    ::type type;
};

template<typename NewItem, typename Type, typename... T>
struct ReplaceItem<TypeList<Type, T...>, 0, NewItem> {
    typedef TypeList<NewItem, T...> type;
};

#endif
