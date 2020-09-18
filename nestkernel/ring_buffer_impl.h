/*
 *  ring_buffer_impl.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RING_BUFFER_IMPL_H
#define RING_BUFFER_IMPL_H

#include "ring_buffer.h"

template < unsigned int num_values >
nest::MultiValueRingBuffer< num_values >::MultiValueRingBuffer()
  : buffer_( kernel().connection_manager.get_min_delay() + kernel().connection_manager.get_max_delay(),
      std::array< double, num_values >() )
{
}

template < unsigned int num_values >
void
nest::MultiValueRingBuffer< num_values >::add_value( const long idx0, const long idx1, const double val )
{
  buffer_[ idx0 ][ idx1 ] += val;
}

template < unsigned int num_values >
std::array< double, num_values >&
nest::MultiValueRingBuffer< num_values >::get_values( const long idx0 )
{
  assert( 0 <= idx0 and ( size_t ) idx0 < buffer_.size() );
  return buffer_[ idx0 ];
}

template < unsigned int num_values >
void
nest::MultiValueRingBuffer< num_values >::resize()
{
  size_t size = kernel().connection_manager.get_min_delay() + kernel().connection_manager.get_max_delay();
  if ( buffer_.size() != size )
  {
    buffer_.resize( size, std::array< double, num_values >() );
  }
}

template < unsigned int num_values >
void
nest::MultiValueRingBuffer< num_values >::clear()
{
  resize(); // does nothing if size is fine
  // set all elements to 0.0
  for ( index idx0 = 0; idx0 < buffer_.size(); ++idx0 )
  {
    memset( &buffer_[ idx0 ][ 0 ], 0, buffer_[ idx0 ].size() * sizeof buffer_[ idx0 ][ 0 ] );
  }
}

template < unsigned int num_values >
size_t
nest::MultiValueRingBuffer< num_values >::size() const
{
  return buffer_.size();
}

#endif