#ifndef BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <boost/archive/basic_binary_iprimitive.hpp>
#include <boost/archive/basic_binary_iarchive.hpp>

namespace boost { 
namespace archive {

template<class Archive>
class binary_wiarchive_impl : 
    public basic_binary_iprimitive<Archive, std::wistream>,
    public basic_binary_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class basic_binary_iarchive<Archive>;
    friend class basic_binary_iprimitive<Archive, std::wistream>;
    friend class load_access;
protected:
#endif
    void init(){
        basic_binary_iarchive<Archive>::init();
        basic_binary_iprimitive<Archive, std::wistream>::init();
    }
    binary_wiarchive_impl(std::wistream & is, unsigned int flags = 0) :
        basic_binary_iprimitive<Archive, std::wistream>(
            is, 
            0 != (flags & no_codecvt)
        ),
        basic_binary_iarchive<Archive>()
    {}
};

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_iarchive_impl instead.  This will
// preserve correct static polymorphism.
class binary_wiarchive : 
    public binary_wiarchive_impl<binary_wiarchive>
{
public:
    binary_wiarchive(std::wistream & is, unsigned int flags = 0) :
        binary_wiarchive_impl<binary_wiarchive>(is, flags | no_header)
    {
        if(0 == (flags & no_header))
            init();
    }
};

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP
