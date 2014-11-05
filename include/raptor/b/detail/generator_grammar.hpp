//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_B_DETAIL_GENERATOR_GRAMMAR_HPP_INCLUDEDE
#define RAPTOR_B_DETAIL_GENERATOR_GRAMMAR_HPP_INCLUDEDE

//#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/karma_nonterminal.hpp>
#include <boost/spirit/include/karma_action.hpp>
#include <boost/spirit/include/karma_sequence.hpp>
#include <boost/spirit/include/karma_alternative.hpp>
#include <boost/spirit/include/karma_kleene.hpp>
#include <boost/spirit/include/karma_int.hpp>
#include <boost/spirit/include/karma_uint.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_duplicate.hpp>
#include <boost/spirit/include/karma_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <raptor/b/var.hpp>

namespace raptor { namespace b { namespace detail
{

  template < typename Iterator >
  struct generator_grammar : boost::spirit::karma::grammar < Iterator, raptor::b::var::value_type() >
  {
    generator_grammar() : generator_grammar::base_type ( any )
    {
      using boost::spirit::karma::lit;
      using boost::spirit::karma::int_;
      using boost::spirit::karma::uint_;
      using boost::spirit::karma::byte_;
      using boost::spirit::karma::duplicate;
      using boost::spirit::karma::labels::_val;
      using boost::spirit::karma::labels::_1;
      using boost::phoenix::size;

      d = lit ( 'd' ) << *( s << any ) << lit ( 'e' );

      l = lit ( 'l' ) << *( any ) << lit ( 'e' );

      s %= duplicate [
             uint_ [ _1 = size ( _val ) ] << lit ( ':' ) << *byte_
           ];

      i = lit ( 'i' ) << int_ << lit ( 'e' );

      any = d | l | s | i;
    }

  private:
    boost::spirit::karma::rule < Iterator, raptor::b::var::value_type() > any;
    boost::spirit::karma::rule < Iterator, raptor::b::var::dict() > d;
    boost::spirit::karma::rule < Iterator, raptor::b::var::list() > l;
    boost::spirit::karma::rule < Iterator, raptor::b::var::str()  > s;
    boost::spirit::karma::rule < Iterator, raptor::b::var::num()  > i;
  };

}}}

#endif
