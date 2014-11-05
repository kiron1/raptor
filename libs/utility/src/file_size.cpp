//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#include <raptor/file_size.hpp>

namespace raptor
{

  std::istream::pos_type file_size ( std::istream& file )
  {
    const std::istream::pos_type oldpos = file.tellg();
    file.seekg ( 0, std::ios_base::end );
    const std::istream::pos_type s = file.tellg();
    file.seekg ( oldpos, std::ios_base::beg );
    return s;
  }
}
