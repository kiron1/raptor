//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#include <istream>

#include <boost/io/ios_state.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <raptor/b/var.hpp>
#include <raptor/b/detail/parse.hpp>

namespace raptor { namespace b
{

  std::istream& operator >> ( std::istream& is, var& u )
  {
    typedef std::istreambuf_iterator < char > base_iterator_type;
    typedef boost::spirit::multi_pass < base_iterator_type > multi_pass_iterator_type;

    boost::io::ios_flags_saver ifs ( is );
    is.unsetf ( std::ios_base::skipws );

    multi_pass_iterator_type first = boost::spirit::make_default_multi_pass ( base_iterator_type ( is ) );
    multi_pass_iterator_type last = boost::spirit::make_default_multi_pass ( base_iterator_type() );

    const bool ok = detail::parse ( first, last, u );
    if ( ! ok || first != last )
    {
      is.setstate( std::ios_base::failbit );
    }
    return is;
  }

}}
