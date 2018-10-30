// ContainerPrinting.h
// tom bailey   1110  2 mar 10

// Define operator<< code for several containers.
// Containers with defined operator<< code can be nested.

#ifndef _CONTAINER_PRINTING_H_
#define	_CONTAINER_PRINTING_H_

#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <vector>
#include <set>
#include <map>

// Print routines for specialized containers.

// Print *itBegin up to *itEnd to outfile.
// Used for several containers accessed by iterators.
template< typename I >
void printContainer( std::ostream & outfile, I itBegin, I itEnd, 
					std::string left, std::string separator, std::string right )
{
	outfile << left;
	I it = itBegin;
	if( it != itEnd )
	{
		outfile << ( * it );
		++it;
	}
	while( it != itEnd )
	{
		outfile << separator << ( * it );
		++it;
	}
	outfile << right;
}


// Print pair< T, U > to outfile.
template< typename T, typename U >
std::ostream & operator<<( std::ostream & outfile, const std::pair< T, U > pairTU )
{
	outfile << "< " << pairTU.first << ", " << pairTU.second << " >";
	return outfile;
}


// Print list< T > to outfile.
template< typename T >
std::ostream & operator<<( std::ostream & outfile, const std::list< T > & listT )
{
	printContainer( outfile, begin(listT), end(listT),
		"( ", ", ", " )" );
	return outfile;
}


// Print set< T > to outfile.
template< typename T >
std::ostream & operator<<( std::ostream & outfile, const std::set< T > & setT )
{
	printContainer( outfile, setT.begin(), setT.end(),
		"{ ", ", ", " }" );
	return outfile;
}


// Print map< T, U > to outfile.
template< typename T, typename U >
std::ostream & operator<<( std::ostream & outfile, const std::map< T, U > & mapTU )
{
	printContainer( outfile, mapTU.begin(), mapTU.end(),
		"{ ", ", ", " }" );
	return outfile;
}


// Print vector< Type > to outfile.
template< typename T >
std::ostream & operator<<( std::ostream & outfile, const std::vector< T > & vectorT )
{
	printContainer( outfile, vectorT.begin(), vectorT.end(),
		"[ ", ", ", " ]" );
	return outfile;
}


#endif