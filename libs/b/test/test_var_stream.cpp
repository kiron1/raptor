//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#define BOOST_TEST_MODULE raptor_b_var_stream
#include <boost/test/included/unit_test.hpp>

#include <sstream>
#include <string>
#include <vector>
#include <utility>

#include <raptor/b/var.hpp>

using raptor::b::var;

struct var_fixture {
  var_fixture()
  {
    using std::string;

    samples.reserve ( 32 );

    // var::num samples
    add ( 0, "i0e" );
    add ( 42, "i42e" );
    add ( -23, "i-23e" );
    add ( -2147483647, "i-2147483647e" );
    add ( 2147483647, "i2147483647e" );

    // var::str samples
    //add ( "", "0:" );
    add ( "A", "1:A" );
    add ( "foo", "3:foo" );
    add ( string ( "\nar", 3UL ), string ( "3:\nar", 5UL ) );
    add ( string ( "\0ar", 3UL ), string ( "3:\0ar", 5UL ) );
    BOOST_CHECK_EQUAL ( samples.back().second.at ( 2 ), '\0' );

    // var::list samples
    add ( var::list(), "le" );

    // var::dict smaples
    add ( var::dict(), "de" );
  }

  ~var_fixture()
  {}

  void add ( var const& u, std::string const& s )
  {
    samples.push_back ( std::make_pair ( u, s ) );
  }

  typedef std::vector < std::pair < raptor::b::var, std::string > > samples_type;
  typedef samples_type::iterator iterator;
  std::vector < std::pair < raptor::b::var, std::string > > samples;
};

BOOST_FIXTURE_TEST_SUITE( raptor_b_var_stream, var_fixture )

BOOST_AUTO_TEST_CASE( b_var_ostream )
{
  for ( iterator it = samples.begin(), last = samples.end()
      ; it != last
      ; ++it )
  {
    BOOST_MESSAGE ( "ostream " << it->second );
    std::stringstream os;
	const bool ok = static_cast < bool > (os << it->first);
    BOOST_CHECK_EQUAL ( ok, true );
    BOOST_CHECK_EQUAL ( os.str(), it->second );
  }
}

BOOST_AUTO_TEST_CASE( b_var_istream )
{
  for ( iterator it = samples.begin(), last = samples.end()
      ; it != last
      ; ++it )
  {
    BOOST_MESSAGE ( "istream " << it->second );
    var u;
    std::stringstream is ( it->second );
	const bool ok = static_cast < bool > (is >> u);
    BOOST_CHECK_EQUAL ( ok, true );
    BOOST_CHECK_EQUAL ( u, it->first );
  }
}

BOOST_AUTO_TEST_CASE( b_var_simple )
{
  var v;

  const std::string ex = "d3:bari42e3:fooi23ee";
  std::stringstream is ( ex );
  const bool pok = static_cast < bool > ( is >> v );

  BOOST_CHECK_EQUAL ( pok, true );

  var::optional_dict od ( v );
  BOOST_REQUIRE ( od );
  BOOST_CHECK_EQUAL ( od->size(), 2UL );

  var::dict d = v;
  BOOST_CHECK_EQUAL ( d.size(), 2UL );

  std::stringstream os;
  const bool gok = static_cast < bool > (os << v);
  BOOST_CHECK_EQUAL ( gok, true );
  BOOST_CHECK_EQUAL ( os.str(), ex );
}

BOOST_AUTO_TEST_SUITE_END()
