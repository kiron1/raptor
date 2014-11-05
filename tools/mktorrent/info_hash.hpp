//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_MKTORRENT_INFO_HASH_HPP_INCLUDED
#define RAPTOR_MKTORRENT_INFO_HASH_HPP_INCLUDED

#include <raptor/b/var.hpp>

#include <raptor/sha.hpp>

namespace raptor
{

  sha1::digest_type info_hash ( raptor::b::var const& torrent );

}

#endif
