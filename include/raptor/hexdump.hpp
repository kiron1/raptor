//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_HEXDUMP_HPP_INCLUDED
#define RAPTOR_HEXDUMP_HPP_INCLUDED

#include <algorithm>
#include <iterator>
#include <ostream>
#include <iomanip>

#include <boost/range/iterator_range.hpp>
#include <boost/io/ios_state.hpp>

namespace raptor
{

  template < typename Iterator >
  struct hexdump_directive
  {
    typedef Iterator const_iterator;
    hexdump_directive ( const_iterator first, const_iterator last )
      : first_ ( first )
      , last_ ( last )
    {}

    friend
    std::ostream& operator << ( std::ostream& os, hexdump_directive const& hd )
    {
      boost::io::ios_flags_saver ifs ( os );
      os << std::hex;
      std::copy ( hd.first_, hd.last_, std::ostream_iterator < unsigned int > ( os ) );
      return os;
    }
  private:
    const_iterator first_;
    const_iterator last_;
  };

  template < typename Iterator >
  inline
  hexdump_directive < Iterator > hexdump ( Iterator first, Iterator last )
  {
    return hexdump_directive < Iterator > ( first, last );
  }

  template < typename Iterator >
  inline
  hexdump_directive < Iterator > hexdump ( boost::iterator_range < Iterator > r )
  {
    return hexdump_directive < Iterator > ( r.begin(), r.end() );
  }

}

#endif
