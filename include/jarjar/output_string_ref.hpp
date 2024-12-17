//
// Copyright (c) 2024 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef JARJAR_OUTPUT_STRING_REF_HPP
#define JARJAR_OUTPUT_STRING_REF_HPP

#include <cstddef>
#include <type_traits>

#include "jarjar/string_view.hpp"

namespace jarjar {

// TODO: guard this for pre-C++20 compilers
// Represents a type that can be passed as the output parameter
// to algorithms producing strings
template <class T>
concept output_string = requires(T& t, const char* data, std::size_t sz) { t.append(data, sz); };

// Type-erased reference type for output_string
class output_string_ref
{
    using append_fn_t = void (*)(void*, const char*, std::size_t);

    append_fn_t append_fn_;
    void* container_;

    template <class T>
    static void do_append(void* container, const char* data, std::size_t size)
    {
        static_cast<T*>(container)->append(data, size);
    }

public:
    template <
        output_string T,
        class = typename std::enable_if<!std::is_same<T, output_string_ref>::value>::type>
    output_string_ref(T& str) noexcept : append_fn_(&do_append<T>), container_(&str)
    {
    }

    void append(string_view data)
    {
        if (data.size() > 0u)
            append_fn_(container_, data.data(), data.size());
    }
};

}  // namespace jarjar

#endif
