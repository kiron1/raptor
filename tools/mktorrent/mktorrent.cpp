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


static const std::size_t default_piece_length = 1UL << 18; // 256 KiB


var::str make_torrent_pieces ( std::istream& file
                             , std::size_t piece_length )
{
  const std::size_t fsize = file_size ( file );
  const std::size_t piece_count = ( fsize + ( piece_length - 1 ) ) / piece_length;
  std::string pieces;
  pieces.reserve ( raptor::sha1_digest_size * piece_count );

  file.clear();

  std::vector < char > buf ( piece_length );
  for ( std::size_t remain = fsize
      ; remain
      ; remain -= std::min ( piece_length, remain ) )
  {
    const std::size_t piece_size = std::min ( piece_length, remain );
    const bool read_ok = static_cast < bool > ( file.read ( buf.data(), piece_size ) );
    //assert ( read_ok ); // TODO proper error handling

    sha1 sha;
    sha1::digest_type dig = sha.digest ( buf.begin(), buf.begin() + piece_size );
    pieces.append ( boost::begin ( char_array ( dig ) )
                  , boost::end ( char_array ( dig ) ) );
  }
  return pieces;
}

var::dict make_torrent_info ( std::string const& name
                            , std::istream& file
                            , std::size_t piece_length )
{
  typedef var::dict::value_type kv;

  const std::istream::pos_type fsize = file_size ( file );
  const var::str pieces = make_torrent_pieces ( file, piece_length );
  var::dict info;
  info.insert ( kv ( "name", name ) );
  info.insert ( kv ( "length", fsize ) );
  info.insert ( kv ( "piece length", piece_length ) );
  info.insert ( kv ( "pieces", pieces ) );
  return info;
}

var make_torrent ( std::string const& announce
                 , std::string const& name
                 , std::istream& file
                 , std::size_t piece_length )
{
  typedef var::dict::value_type kv;
  var::dict root;

  if ( ! announce.empty() )
  {
    root.insert ( kv ( "announce", announce ) );
  }
  const var::dict info = make_torrent_info ( name, file, piece_length );
  root.insert ( kv ( "info", info ) );

  return var ( root );
}


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
      ( "announce,a", po::value < string >()->default_value ( "" ), "Tracker announce URL." )
      ( "name,n", po::value < string >(), "Name of torrent content." )
      ( "file,f", po::value < string >(), "Torrent output file name.")
      ( "piece-length", po::value < std::size_t >()->default_value ( default_piece_length), "Piece length." )
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
      || ! vm.count ( "name" )
      || ! vm.count ( "file" )
      || ! vm.count ( "input-file" );

    if ( vm.count ( "help" ) || need_help )
    {
      cout << desc << "\n";
      return 1;
    }

    const string announce = vm [ "announce" ].as < string >();
    const string name = vm [ "name" ].as < string >();
    const std::size_t piece_length = vm [ "piece-length" ].as < std::size_t >();
    std::ifstream file ( vm [ "input-file" ].as < string >().c_str() );

    var torrent = make_torrent ( announce, name, file, piece_length );
    std::ofstream of ( vm [ "file" ].as < string >().c_str(), std::ios_base::binary );
    of << torrent;

    if ( ! vm [ "quiet" ].as < bool >() )
    {
      const sha1::digest_type dig = info_hash ( torrent );

      cout << "info_hash = " << hexdump ( char_array ( dig ) ) << "\n";
    }

  }
  catch ( std::exception const& e)
  {
    cerr << "Exception: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
