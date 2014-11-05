//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_CHAR_ARRAY_HPP_INCLUDED
#define RAPTOR_CHAR_ARRAY_HPP_INCLUDED

#include <boost/array.hpp>
#include <boost/range/iterator_range.hpp>

namespace raptor
{

  template < typename T, std::size_t N >
  boost::iterator_range < const unsigned char* > char_array ( boost::array < T, N > const& a )
  {
    const unsigned char* const cptr_first = reinterpret_cast < unsigned char const* > ( a.data() );
    const unsigned char* const cptr_last = cptr_first + ( a.size() * sizeof ( T ) );

    return boost::iterator_range < const unsigned char* > ( cptr_first, cptr_last );
  }

}

#endif
