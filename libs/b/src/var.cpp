//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#include <utility>

#include <boost/variant/apply_visitor.hpp>

#include <raptor/b/var.hpp>

namespace raptor { namespace b
{

  var::var()
  {}

  var::~var()
  {}

  var::var ( var const& other )
    : u_ ( other.u_ )
  {}

  var::var ( value_type const& other )
    : u_ ( other )
  {}

  var::var ( var::dict const& other )
    : u_ ( other )
  {}

  var::var ( var::list const& other )
    : u_ ( other )
  {}

  var::var ( var::str const& other )
    : u_ ( other )
  {}

  var::var ( var::str::traits_type::char_type const* c_str )
    : u_ ( std::string ( c_str ) )
  {}

  var::var ( var::num const& other )
    : u_ ( other )
  {}

  var& var::operator = ( var other )
  {
    this->swap ( other );
    return *this;
  }

  var& var::operator = ( var::value_type const& other )
  {
    u_ = other;
    return *this;
  }

  var& var::operator = ( var::dict const& other )
  {
    u_ = other;
    return *this;
  }

  var& var::operator = ( var::list const& other )
  {
    u_ = other;
    return *this;
  }

  var& var::operator = ( var::str const& other )
  {
    u_ = other;
    return *this;
  }


  var& var::operator = ( var::str::traits_type::char_type const* c_str )
  {
    u_ = std::string ( c_str );
    return *this;

  }

  var& var::operator = ( var::num const& other )
  {
    u_ = other;
    return *this;
  }

  void var::swap ( var& other )
  {
    u_.swap ( other.u_ );
  }

  var::operator var::dict const&() const
  {
    return boost::get < dict const& > ( u_ );
  }

  var::operator var::list const&() const
  {
    return boost::get < list const& > ( u_ );
  }

  var::operator var::str const&() const
  {
    return boost::get < str const& > ( u_ );
  }

  var::operator var::num const&() const
  {
    return boost::get < num const& > ( u_ );
  }


  namespace
  {
    struct are_strict_equals : boost::static_visitor < bool >
    {
        template < typename T, typename U >
        bool operator ()( T const&, U const& ) const
        {
          return false; // cannot compare different types
        }

        template < typename T >
        bool operator()( T const& lhs, T const& rhs ) const
        {
          return lhs == rhs;
        }
    };
  }

  bool operator == ( var const& lhs, var const& rhs )
  {
    return boost::apply_visitor ( are_strict_equals(), lhs.value(), rhs.value() );
  }

}}
