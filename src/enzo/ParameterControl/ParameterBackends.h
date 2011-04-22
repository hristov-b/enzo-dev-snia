#ifndef PARAMETERBACKENDMGR_H
#define PARAMETERBACKENDMGR_H

#include <string>
#include <vector>
#include <map>

// interpreter abstract base class
class interpreter
{
public:
	explicit interpreter( std::string fname )
	{ }
	
	virtual ~interpreter()
	{ }
	
	virtual int query( const std::string key, std::string& ret ) = 0;
	virtual int query_list( const std::string key, std::vector< std::string >& ret ) = 0;
	
	virtual size_t size( const std::string key ) = 0;
};

// abstract factory pattern
struct interpreter_creator
{
  virtual interpreter* create( std::string fname, bool from_string=false ) const = 0;
	virtual ~interpreter_creator() { }
};

std::map< std::string, interpreter_creator*>& get_interpreter();

template< class Derived >
struct interpreter_creator_concrete : public interpreter_creator
{
	interpreter_creator_concrete( const std::string& interpreter_name )
	{
		get_interpreter()[ interpreter_name ] = this;
	}
	
	interpreter * create( std::string fname, bool from_string=false ) const
	{
	  return new Derived( fname, from_string );
	}
	
};

#include <stdexcept>

//... helper stuff
//! runtime error that is thrown if type conversion fails
class ErrInvalidConversion : public std::runtime_error{
public:
	ErrInvalidConversion( std::string errmsg )
	: std::runtime_error( errmsg )
	{}
};

#endif
