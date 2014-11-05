//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#include <sstream>
#include <string>

#include "info_hash.hpp"


namespace raptor
{
  sha1::digest_type info_hash ( raptor::b::var const& torrent )
  {
    using raptor::b::var;

    sha1::digest_type result;
    var::optional_dict root(torrent);

    if ( root )
    {
      var::dict::const_iterator it = root->find ( "info" );
      if ( it != root->end() )
      {
        std::stringstream os;
        os << var ( it->second );
        const std::string info_str = os.str();
        sha1 sha;
        result = sha.digest ( info_str.begin(), info_str.end() );
      }
    }
    return result;
  }
}
