//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_B_DETAIL_GENERATE_HPP_INCLUDED
#define RAPTOR_B_DETAIL_GENERATE_HPP_INCLUDED

#include <boost/spirit/include/karma_generate.hpp>

#include <raptor/b/detail/generator_grammar.hpp>

namespace raptor { namespace b { namespace detail
{

  template < typename OutputIterator >
  bool generate ( OutputIterator& sink, raptor::b::var const& u )
  {
    raptor::b::detail::generator_grammar < OutputIterator > grammar;
    return boost::spirit::karma::generate ( sink, grammar, u.value() );
  }

}}}

#endif
