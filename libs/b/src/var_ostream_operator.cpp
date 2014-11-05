//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#include <ostream>
#include <iterator>

#include <boost/io/ios_state.hpp>

#include <raptor/b/var.hpp>
#include <raptor/b/detail/generate.hpp>

namespace raptor { namespace b
{

  std::ostream& operator << ( std::ostream& os, var const& u )
  {
    boost::io::ios_flags_saver ifs ( os );

    std::ostream_iterator < char > iter ( os );
    const bool ok = detail::generate ( iter, u );
    if ( ! ok )
    {
      os.setstate( std::ios_base::failbit );
    }
    return os;
  }


}}

