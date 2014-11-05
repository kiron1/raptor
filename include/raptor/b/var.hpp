//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_B_VAR_HPP_INCLUDED
#define RAPTOR_B_VAR_HPP_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <iosfwd>

#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/optional/optional.hpp>
#include <boost/mpl/at.hpp>

namespace raptor { namespace b
{

  class var
  {
  public:
    typedef boost::make_recursive_variant
      < std::map < std::string, boost::recursive_variant_ >
      , std::vector< boost::recursive_variant_ >
      , std::string
      , int
      >::type value_type;

    typedef std::size_t       size_type;
    typedef value_type&       reference;
    typedef value_type const& const_reference;
    typedef value_type*       pointer;
    typedef value_type const* const_pointer;

    typedef boost::mpl::at_c < value_type::types, 0 >::type dict;
    typedef boost::mpl::at_c < value_type::types, 1 >::type list;
    typedef boost::mpl::at_c < value_type::types, 2 >::type str;
    typedef boost::mpl::at_c < value_type::types, 3 >::type num;

    typedef boost::optional < dict > optional_dict;
    typedef boost::optional < list > optional_list;
    typedef boost::optional < str > optional_str;
    typedef boost::optional < num > optional_num;

    var();
    ~var();

    var ( var const& );
    var ( value_type const& );
    var ( dict const& );
    var ( list const& );
    var ( str const& );
    var ( str::traits_type::char_type const* );
    var ( num const& );

    var& operator = ( var );
    var& operator = ( value_type const& );
    var& operator = ( dict const& );
    var& operator = ( list const& );
    var& operator = ( str const& );
    var& operator = ( str::traits_type::char_type const* );
    var& operator = ( num const& );

    void swap ( var& );

    operator dict const&() const;
    operator list const&() const;
    operator str const&() const;
    operator num const&() const;

    operator boost::optional < dict const& >() const
    { return get_optional < dict >(); }

    operator boost::optional < list const& >() const
    { return get_optional < list >(); }

    operator boost::optional < str const& >() const
    { return get_optional < str >(); }

    operator boost::optional < num const& >() const
    { return get_optional < num >(); }

    value_type& value() { return u_; }
    value_type const& value() const { return u_; }

  private:
    template < typename T >
    boost::optional < T const& > get_optional() const;

    value_type u_;
  };

  template < typename T >
  boost::optional < T const& > var::get_optional() const
  {
    typedef boost::optional < T const& > result_type;
    T const* const u = boost::get < T const* > ( u_ );
    if ( u ) return result_type ( *u );
    else return result_type();
  }

  inline
  void swap ( var& lhs, var& rhs )
  { lhs.swap ( rhs ); }

  bool operator == ( var const& lhs, var const& rhs );

  inline
  bool operator != ( var const& lhs, var const& rhs )
  {
    return ! ( lhs == rhs );
  }

  std::ostream& operator << ( std::ostream&, var const& );

  std::istream& operator >> ( std::istream&, var& );

}}

#endif
