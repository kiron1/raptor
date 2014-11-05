//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_SHA_HPP_INCLUDED
#define RAPTOR_SHA_HPP_INCLUDED

// adobe/sha.hpp uses adobe::copy, but does not include
// <adobe/algorithm/copy.hpp, fixed here
#include <adobe/algorithm/copy.hpp>
#include <adobe/sha.hpp>

namespace raptor
{
  typedef adobe::sha1_t sha1;

  // size of sha1::digest_type in bytes
  enum { sha1_digest_size = sha1::digest_type::static_size * sizeof ( sha1::digest_type::value_type ) };
}

#endif
