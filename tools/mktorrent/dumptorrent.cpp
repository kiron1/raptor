//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdexcept>

#include <boost/range.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/io/ios_state.hpp>
#include <boost/program_options.hpp>

#include <raptor/b/var.hpp>

#include <raptor/sha.hpp>
#include <raptor/hexdump.hpp>
#include <raptor/char_array.hpp>
#include <raptor/file_size.hpp>
#include "info_hash.hpp"

using raptor::b::var;
using raptor::sha1;
using raptor::file_size;
using raptor::info_hash;
using raptor::hexdump;
using raptor::char_array;


int main ( int argc, char** argv )
{
  using std::cout;
  using std::cerr;
  using std::string;
  namespace po = boost::program_options;

  try
  {
    po::options_description desc ( "Allowed options" );
    desc.add_options()
      ( "help,h", "Produce help message." )
      ( "quiet,q", po::value < bool >()->default_value ( false ), "Quiet mode." )
      ( "input-file", po::value < string >(), "Input file for the torrent." );

    po::positional_options_description p;
    p.add ( "input-file", -1 );

    po::variables_map vm;
    po::store ( po::command_line_parser ( argc, argv )
        .options ( desc )
        .positional ( p ).run()
      , vm );
    po::notify ( vm );

    const bool need_help = false
      || ! vm.count ( "input-file" );

    if ( vm.count ( "help" ) || need_help )
    {
      cout << desc << "\n";
      return 1;
    }

    const string input_file = vm [ "input-file" ].as < string >();
    std::ifstream is ( input_file.c_str(), std::ios_base::binary );

    var torrent;

    if ( ! ( is >> torrent ) )
    {
      throw std::runtime_error ( "Failed to open torrent file `" + input_file + "'." );
    }

    const sha1::digest_type dig = info_hash ( torrent );

    cout << "info_hash = " << hexdump ( char_array ( dig ) ) << "\n";

  }
  catch ( std::exception const& e)
  {
    cerr << "Exception: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
