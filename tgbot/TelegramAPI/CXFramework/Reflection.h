//
//  Properties.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/14/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Properties_h
#define Properties_h
#include <exception>
#include "String.h"
#include "utils/json.hpp"

// Macros for convenience
#define CXXREFLECT_INTERNAL_PLISTNAME __CXProperties // Name of the class static field

/*
 --- 'properties' macro ---
 Declares a property block: can be used outside of a class declaration
 but should be kept in it for clarity
 Input:
 [ClassType] T - Class type
 Usage example:
 class ReflectedClass
 {
 public:
 // Class fields go here...
 
 // Define a property block for ReflectedClass
 properties(ReflectedClass) (
 // Properties go here...
 );
 };
 */
#define cxprops(T) \
typedef T __CXBaseClass; \
const std::string CXToJSON() const { \
return CX::Serialization::JSON::Serialize(*this); \
} \
static const __CXBaseClass CXFromJSON(const std::string& serialized) { \
return CX::Serialization::JSON::Deserialize<__CXBaseClass>(serialized); \
} \
constexpr static auto CXXREFLECT_INTERNAL_PLISTNAME = std::make_tuple

/*
 --- 'property' macro ---
 Declares a property: must be used in a property block
 
 Input:
 [ClassMember] member - Class/struct field to bind
 [Optional] [String] name - Name of the property: using the in-class
 field name if not specified
 Usage example:
 // Class fields
 std::string mStringMember;
 int mIntMember;
 bool mBoolMember;
 
 // Define a property block for ReflectedClass
 properties(ReflectedClass) (
 // Define a property automatically named 'mStringMember'
 property(mStringMember),
 // Define a property with a custom name
 property(mIntMember, "customPropertyName")
 );
 */
#define property(...) property_vararg(__VA_ARGS__, property_customname, property_autoname)(__VA_ARGS__)

// Internal macros for 'property'
#define property_autoname(member) CX::Reflection::Internal::DefineProperty(&__CXBaseClass::member, CXSTRINGIFY(member))
#define property_customname(member, name) CX::Reflection::Internal::DefineProperty(&__CXBaseClass::member, name)
#define property_vararg(_1,_2,NAME,...) NAME

/*
 --- 'enumerate' macro ---
 Uses a lambda to iterate through the properties of a class.
 Input:
 [TypeName] T - Class/struct typename; must have a defined property block
 [T] obj - T instance to be iterated
 Usage example:
 ReflectedClass cls;
 cls.mIntMember = 5;
 cls.mBoolMember = true;
 cls.mStringMember = "CXXRefl test";
 
 enumerate(ReflectedClass, cls) {
 std::cout << "Value " << name << " = " << value << std::endl;
 } cxxenum_end;
 */
#define cxenum(T, obj) \
constexpr auto nbProperties = std::tuple_size<decltype(T::CXXREFLECT_INTERNAL_PLISTNAME)>::value; \
CX::Reflection::Internal::ForIntSequence(std::make_index_sequence<nbProperties>{}, [&](auto i) { cxenum_init(T, obj);

#define cxenum_const(T, obj) \
constexpr auto nbProperties = std::tuple_size<decltype(T::CXXREFLECT_INTERNAL_PLISTNAME)>::value; \
CX::Reflection::Internal::ForIntSequence(std::make_index_sequence<nbProperties>{}, [&](auto i) { cxenum_init(T, obj, const);

// Internal macros for 'enumerate'
#define cxenum_init(T, obj, ...) \
constexpr auto __property = std::get<i>(T::CXXREFLECT_INTERNAL_PLISTNAME); \
__VA_ARGS__ T& __object = obj; \
const CX::String name = __property.name; \
__VA_ARGS__ auto& value = __object.*(__property.member); \
using type = typename decltype(__property)::Type
#define cxenum_end })

// Originally created for CXXReflect
namespace CX
{
    namespace Reflection
    {
        namespace Internal
        {
            template<class Class, typename MemberType>
            struct PropertyImpl
            {
                constexpr PropertyImpl(MemberType Class::*aMember, const char* aName) : member{aMember}, name{aName} {}
                MemberType Class::*member;
                const char* name;
                using Type = MemberType;
            };
        
            template <typename T, T... S, typename F>
            constexpr void ForIntSequence(std::integer_sequence<T, S...>, F&& f) {
                using unpack_t = int[];
                (void)unpack_t{(static_cast<void>((void) f(std::integral_constant<T, S>{})), 0)..., 0};
            }
        
            template<typename Class, typename T>
            constexpr auto DefineProperty(T Class::*member, const char* name) {
                return PropertyImpl<Class, T>{member, name};
            }
            
            template <class T,typename = std::void_t<>>
            struct IsCXReflectable : std::false_type {
            };
            template <class T>
            struct IsCXReflectable<T,std::void_t<decltype(T::__CXProperties)>> : std::true_type {};
            
            template <class T,typename = std::void_t<>>
            struct IsCXReference : std::false_type {
            };
            template <class T>
            struct IsCXReference<T,std::void_t<decltype(T::__CXReference)>> : std::true_type {};
            
            template <class T,typename = std::void_t<>>
            struct IsCXOptional : std::false_type {
            };
            template <class T>
            struct IsCXOptional<T,std::void_t<decltype(T::__CXOptional)>> : std::true_type {};
        }
        
        class NullReferenceException : public std::exception
        {
        public:
            const char* what() { return "CX::Reflection::Reference used without being set"; };
        };
        
        // Used for incomplete/mutual-reference types: do NOT set those manually and check whether they exist before reading
        template<class T>
        class Reference
        {
        public:
            bool __CXReference = true; // ref marker
            using ValueType = T;
            
            Reference() : mPointer(nullptr) {}
            Reference(const Reference& ref) { if(ref.Exists()) { Create(); Set(ref); } }
            // FIX MEMORY LEAKS HERE!
            
            void Create() { if(!mPointer) mPointer = new T; }
            bool Exists() const { return (mPointer != nullptr); }
            
            T& operator()() { if(mPointer) return *mPointer; else throw NullReferenceException(); }
            operator T&() { if(mPointer) return *mPointer; else throw NullReferenceException(); }
            operator const T&() const { if(mPointer) return *mPointer; else throw NullReferenceException(); }
            void Set(const T& val) { Create(); *mPointer = val; }
        private:
            T* mPointer;
        };
        
        // Optional fields for serialization: can be used as an ordinary value outside of
        template<class T>
        class Optional
        {
        public:
            bool __CXOptional = true; // opt marker
            using ValueType = T;
            
            Optional() : mExists(false), mValue() {}
            Optional(const T& val) : mExists(true), mValue(val) {}
            bool Exists() const { return mExists; }
            Optional& operator=(T& val) { mExists = true; mValue = val; return *this; }
            Optional& operator=(const T& val) { mExists = true; mValue = val; return *this; }
            
            void Set(const T& val) { mValue = val; mExists = true; }
            
            T& operator()() { return mValue; }
            operator T&() { return mValue; }
            operator const T&() const { return mValue; }
        private:
            bool mExists;
            T mValue;
        };
    }

    namespace Serialization
    {
        namespace JSON
        {
            template<class T>
            const std::string Serialize(const T& obj)
            {
                nlohmann::json j;
                cxenum_const(T, obj) {
                    if constexpr(Reflection::Internal::IsCXReference<type>::value)
                    {
                        if(!value.Exists()) return;
                        using vtype = typename type::ValueType;
                        
                        if constexpr(Reflection::Internal::IsCXReflectable<vtype>::value)
                            j[name] = nlohmann::json::parse(Serialize<vtype>(value));
                        else
                            j[name] = value;
                    }
                    else if constexpr(Reflection::Internal::IsCXOptional<type>::value)
                    {
                        if(!value.Exists()) return;
                        using vtype = typename type::ValueType;
                        
                        if constexpr(Reflection::Internal::IsCXReflectable<vtype>::value)
                            j[name] = nlohmann::json::parse(Serialize<vtype>(value));
                        else
                            j[name] = (vtype) value;
                    }
                    else
                    {
                        if constexpr(Reflection::Internal::IsCXReflectable<type>::value)
                            j[name] = nlohmann::json::parse(Serialize<type>(value));
                        else
                            j[name] = value;
                    }
                } cxenum_end;
                return j.dump(4);
            }
            
            template<class T>
            const T Deserialize(const std::string& s)
            {
                nlohmann::json j = nlohmann::json::parse(s);
                T obj;
                cxenum(T, obj)
                {
                    try {
                        if constexpr(Reflection::Internal::IsCXReference<type>::value)
                        {
                            j.at(name); // throws if there's no json node to deserialize, used to prevent the creation of useless nodes
                            value.Create();
                            using vtype = typename type::ValueType;
                            
                            if constexpr(Reflection::Internal::IsCXReflectable<vtype>::value)
                                value.Set(Deserialize<vtype>(j.at(name).dump()));
                            else
                                value = j.at(name).get<vtype>();
                        }
                        else if constexpr(Reflection::Internal::IsCXOptional<type>::value)
                        {
                            using vtype = typename type::ValueType;
                            
                            if constexpr(Reflection::Internal::IsCXReflectable<vtype>::value)
                                value = (Deserialize<vtype>(j.at(name).dump()));
                            else
                                value = (j.at(name).get<vtype>());
                        }
                        else
                        {
                            if constexpr(Reflection::Internal::IsCXReflectable<type>::value)
                                value = Deserialize<type>(j.at(name).dump());
                            else
                                value = j.at(name).get<type>();
                        }
                    } catch(...)
                    {
                        // ignore non existent fields
                    }
                } cxenum_end;
                return obj;
            }
        }
    }
}
template<class T>
using cxref = CX::Reflection::Reference<T>;
template<class T>
using cxopt = CX::Reflection::Optional<T>;

#endif /* Properties_h */
