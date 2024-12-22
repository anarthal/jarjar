//
// Copyright (c) 2024 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef JARJAR_SERIALIZE_SET_HEADER_HPP
#define JARJAR_SERIALIZE_SET_HEADER_HPP

#include <boost/config.hpp>
#include <boost/optional/optional.hpp>
#include <boost/system/result.hpp>

#include <chrono>

#include "jarjar/error_code.hpp"
#include "jarjar/output_string_ref.hpp"
#include "jarjar/string_view.hpp"

namespace jarjar {

// The SameSite cookie attribute
enum class same_site
{
    strict,
    lax,  // this is the default
    none,
};

struct cookie
{
    string_view name;
    string_view value;
    boost::optional<std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>> expires;
    boost::optional<std::chrono::seconds> max_age;  // but it can't be negative
    boost::optional<string_view> domain;            // should be a subdomain, and not empty
    boost::optional<string_view> path;
    bool secure;
    bool http_only;
    same_site same_site_value;
};

// Cookie names must be valid HTTP tokens
bool is_valid_cookie_name(string_view name) noexcept;

// Cookie values also have restrictions
bool is_valid_cookie_value(string_view value) noexcept;

//
// Serialization of the Set-Cookie header
//

// Creates the value of a Set-Cookie HTTP header.
// If the cookie's name or value aren't valid (as per is_valid_cookie_name,
// is_valid_cookie_value), returns an error and writes nothing to output.
BOOST_ATTRIBUTE_NODISCARD
error_code serialize_set_cookie(const cookie& cook, output_string_ref output);

// Same as above, but results in undefined behavior if the cookie
// name or value are not valid.
void serialize_set_cookie_unchecked(const cookie& cook, output_string_ref output);

//
// Parsing the Set-Cookie header
//
// If the Set-Cookie is malformed enough
// (that is, RFC6265 suggests to ignore the Set-Cookie header completely),
// returns an error.
// The parsed cookie::name and cookie::value are NOT validated using
// is_valid_cookie_name and is_valid_cookie_value, as recommended by RFC6265,
// to improve interoperability with older systems.
boost::system::result<cookie> parse_set_cookie(string_view from);

}  // namespace jarjar

#endif
