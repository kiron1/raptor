//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef INCLUDE_GUARD_E54AA297_A6E2_4778_9A6E2
#define INCLUDE_GUARD_E54AA297_A6E2_4778_9A6E2

#include <streambuf>

namespace raptor
{

  template < typename Ch, typename Traits = std::char_traits < Ch > >
  class basic_nullbuf : public std::basic_streambuf < Ch, Traits >
  {
  public:
    typedef std::basic_streambuf < Ch, Traits > base_type;
    typedef typename base_type::int_type int_type;
    typedef typename base_type::traits_type traits_type;

    virtual int_type overflow ( int_type c )
    {
      return traits_type::not_eof ( c );
    }
  };

  typedef basic_nullbuf < char > nullbuf;

  typedef basic_nullbuf < wchar_t > wnullbuf;

}

#endif
