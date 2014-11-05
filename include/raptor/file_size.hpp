//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_UTILITY_FILE_SIZE_HPP_INCLUDED
#define RAPTOR_UTILITY_FILE_SIZE_HPP_INCLUDED

#include <istream>

namespace raptor
{

  std::istream::pos_type file_size ( std::istream& file );

}

#endif
