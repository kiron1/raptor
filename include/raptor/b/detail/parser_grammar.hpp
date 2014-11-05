//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_B_DETAIL_PARSER_GRAMMAR_HPP_INCLUDED
#define RAPTOR_B_DETAIL_PARSER_GRAMMAR_HPP_INCLUDED

#include <boost/spirit/include/qi_nonterminal.hpp>
#include <boost/spirit/include/qi_sequence.hpp>
#include <boost/spirit/include/qi_alternative.hpp>
#include <boost/spirit/include/qi_kleene.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi_int.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/qi_char.hpp> // for lit
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/qi_repeat.hpp>
#include <boost/spirit/include/qi_omit.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <raptor/b/var.hpp>

namespace raptor { namespace b { namespace detail
{

  template < typename Iterator >
  struct parser_grammar : boost::spirit::qi::grammar < Iterator, raptor::b::var::value_type() >
  {
      parser_grammar() : parser_grammar::base_type ( any )
      {
        using boost::spirit::qi::lit;
        using boost::spirit::qi::int_;
        using boost::spirit::qi::uint_;
        using boost::spirit::qi::byte_;
        using boost::spirit::qi::repeat;
        using boost::spirit::qi::omit;
        using boost::spirit::qi::labels::_1;
        using boost::spirit::qi::labels::_a;
        using boost::spirit::qi::labels::_val;
        using boost::phoenix::reserve;

        d = lit ( 'd' ) > *( s > any ) > lit ( 'e' );

        l = lit ( 'l' ) > *any > lit ( 'e' );

        s %= omit [ uint_[ _a = _1 ] ][ reserve ( _val, _a ) ] >
             lit ( ':' ) >
             repeat ( _a ) [ byte_ ];

        i = lit ( 'i' ) > int_ > lit ( 'e' );

        any = d | l | s | i;

#if !defined ( NDEBUG ) && 0
        d.name ( "dict" );
        l.name ( "list" );
        s.name ( "str" );
        i.name ( "num" );
        any.name ( "any" );

        boost::spirit::qi::debug ( d );
        boost::spirit::qi::debug ( l );
        boost::spirit::qi::debug ( s );
        boost::spirit::qi::debug ( i );
        boost::spirit::qi::debug ( any );
#endif
      }

    private:
      boost::spirit::qi::rule < Iterator, raptor::b::var::value_type() > any;
      boost::spirit::qi::rule < Iterator, raptor::b::var::dict() > d;
      boost::spirit::qi::rule < Iterator, raptor::b::var::list() > l;
      boost::spirit::qi::rule < Iterator, raptor::b::var::str(), boost::spirit::qi::locals < unsigned int > > s;
      boost::spirit::qi::rule < Iterator, raptor::b::var::num()  > i;
  };

}}}

#endif
