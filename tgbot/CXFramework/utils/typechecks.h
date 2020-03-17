//
//  typechecks.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/16/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef typechecks_h
#define typechecks_h
#include <type_traits>
template <class T,typename = std::void_t<>>
struct has_field : std::false_type {
};
template <class T>
struct has_field<T,std::void_t<decltype(T::__CXProperties)>> : std::true_type {};
template <class T>
constexpr static bool has_field_t = has_field<T>::value;


#endif /* typechecks_h */
