//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_B_PARSER_HPP_INCLUDED
#define RAPTOR_B_PARSER_HPP_INCLUDED

#include <boost/spirit/include/qi_parse.hpp>

#include <raptor/b/detail/parser_grammar.hpp>

namespace raptor { namespace b { namespace detail
{

  template < typename Iterator >
  bool parse ( Iterator& first, Iterator const& last, raptor::b::var& u )
  {
    typedef raptor::b::detail::parser_grammar < Iterator > grammar;
    grammar b;
    return boost::spirit::qi::parse ( first, last, b, u.value() );
  }

}}}

#endif
