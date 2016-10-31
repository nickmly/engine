#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include "StlOptions.h"
#include <string>
#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glew.h>

#include <iostream>
#include <sstream>


/**
* This is a list of graphic primitives which can be rendered by the rendering interface.
* These types include points, lines, triangles and quadrilaterals.  These can be stored
* as list of unconnected objects or as connected strips of the objects.
*/
enum GraphicPrimitiveType {
	GRAPH_PRIM_NULL = 0,	// first one is always a dummy and unused
	GRAPH_PRIM_POINT_LIST,
	GRAPH_PRIM_TRI_LIST,
	GRAPH_PRIM_TRI_STRIP,
	GRAPH_PRIM_LINE_LIST,
	GRAPH_PRIM_LINE_STRIP,
	GRAPH_PRIM_QUAD_LIST,
	GRAPH_PRIM_QUAD_STRIP
};

extern int numberGraphicPrimitiveTypes;
extern int numberKeyCodes;

/**
* This represents all of the types of texture filters that can be used.
*/
enum FilterType {
	FILT_NONE = 0,
	FILT_NEAREST_MAG,			// nearest neighbor magnifier
	FILT_LINEAR_MAG,			// linear magnifier
	FILT_NEAREST_MIN,			// nearest neighbor minifier
	FILT_LINEAR_MIN,			// linear minifier
	FILT_REPEAT_S,				// repeat texture at  X edge
	FILT_REPEAT_T,				// repeat texture at  Y edge
	FILT_REPEAT_R,				// repeat texture at  Z edge
	FILT_CLAMP_S,				// repeat X edge by sampling border color
	FILT_CLAMP_T,				// repeat Y edge by sampling border color
	FILT_CLAMP_R,				// repeat Z edge by sampling border color
	FILT_CLAMP_EDGE_S,			// repeat X edge by sampling edge color
	FILT_CLAMP_EDGE_T,			// repeat Y edge by sampling edge color
	FILT_CLAMP_EDGE_R,			// repeat Z edge by sampling edge color
	FILT_NEAREST_MIP,			// use nearest neighbor for MIP minifier & magnifier
	FILT_LINEAR_MIP				// use linear filtering for MIP minifier & magnifier
};

/**
* This is a list of texture types which can be applied to models.  Note that
* not all texture types are necesarily supported with any release of this software.
*/
enum TextureType {
	TEX_TYPE_NONE = 0,
	TEX_TYPE_1D,			// 1D texture
	TEX_TYPE_2D,			// 2D texture
	TEX_TYPE_CUBE			// cube map
};

/**
* This describes the various ways in which the pixels in a model can be combined with
* the pixels in a texture to yield the final image.
*/
enum TextureCombinationType {
	TEX_COMB_NONE = 0,
	TEX_COMB_MODULATE,		// allow model to show through texture
	TEX_COMB_REPLACE,		// replace model having alpha with texture
	TEX_COMB_DECAL			// replace model not using alpha with texture
};



/**
* This is the list of all virtual key codes defined and supported by the HD system.
*/
enum KeyCodeType {
	KEY_UNKNOWN, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_LEFT_ARROW,
	KEY_BACKSPACE, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_SPACE, KEY_ESC,
	KEY_ENTER, KEY_LEFT_MOUSE, KEY_MIDDLE_MOUSE, KEY_RIGHT_MOUSE, KEY_0,
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
	KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
	KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z
};


/**
* This is a utility classes to provide utilities for working with the
* enumerated types defined by the HD system.
* @author R. N. Robson
*/
class TypeServices
{
private:
	static KeyCodeType keyList[];
	static std::string keyNames[];
public:

	/**
	* Convert a graphic primitive type to the corresponding OpenGL type.
	* @param typ The graphic primitive type
	* @return The equivilent OpenGL type
	*/
	static GLenum graphicPrimitiveToOpenGLType(GraphicPrimitiveType typ);

	/**
	* Convert the graphic primitive type to a string representation
	*/
	static std::string graphicPrimitiveTypeToString(GraphicPrimitiveType t);


	/**
	* Convert a TextureCombinationType to the equivalent OpenGL type.
	* @param typ The combination type to convert
	* @return The equivalent OpenGL type or the default type
	*/
	static GLenum textureCombinationTypeToOpenGLType(TextureCombinationType typ);

	/**
	* Convert an int to the corresponding KeyCodeType
	* @param key The int representing the key code
	* @return the corresponding key code
	*/
	static KeyCodeType intToKeyCodeType(int key);

	/**
	* Convert an integer as a string to an int.
	* @param an integer as a string
	* @return the value of the string converted to an integer
	*/
	static int stringIntToInt(const std::string& str);

	/**
	* Convert an hex value as a string to an int.
	* @param an integer as a string
	* @return the value of the string converted to an integer
	*/
	static int	stringHexToInt(const std::string& str);

	/**
	* Convert a float as a string to a float.
	* @param f a float as a string
	* @return the value of the string as a float
	*/
	static float stringFloatToFloat(const std::string& str);

	/**
	* Convert an int to a string.
	* @param n an int to be converted
	* @return the value of the int as a string
	*/
	static std::string intToString(int n);

	/**
	* Convert a float to a string.
	* @param n a float to be converted
	* @return the value of the float as a string
	*/
	static std::string floatToString(float n);

	/**
	* Determine if the key pressed is a mouse button.
	* @param key The key to check
	* @return true if the key is a mouse button
	*/
	static bool isMouseButton(KeyCodeType key);

	/**
	* Convert a key code to a string representation
	* @param key The key to convert
	* @return a string representation of the key
	*/
	static std::string keyCodeToString(const KeyCodeType key);

};


/**
* This represents various data types that can be used.  It also has utility
* methods to convert these values to the equivalent values in various graphics
* systems.
*/
class PrimitiveDataType
{
public:
	enum PrimDataType {
		PRIM_TYPE_NONE = 0,		// a value to represent unknown or unset
		PRIM_TYPE_BYTE,
		PRIM_TYPE_SHORT,
		PRIM_TYPE_INT,
		PRIM_TYPE_LONG,
		PRIM_TYPE_UBYTE,
		PRIM_TYPE_USHORT,
		PRIM_TYPE_UINT,
		PRIM_TYPE_ULONG,
		PRIM_TYPE_FLOAT,
		PRIM_TYPE_DOUBLE,
		PRIM_TYPE_CHAR,
		PRIM_TYPE_C_STRING,
		PRIM_TYPE_STRING,
		PRIM_TYPE_POINTER,
		PRIM_TYPE_VEC2,
		PRIM_TYPE_VEC3,
		PRIM_TYPE_VEC4,
		PRIM_TYPE_BVEC2,
		PRIM_TYPE_BVEC3,
		PRIM_TYPE_BVEC4,
		PRIM_TYPE_IVEC2,
		PRIM_TYPE_IVEC3,
		PRIM_TYPE_IVEC4,
		PRIM_TYPE_MAT2,
		PRIM_TYPE_MAT3,
		PRIM_TYPE_MAT4,
		PRIM_TYPE_SAMPLER2D
	};
private:
	PrimDataType value;
public:
	/**
	*
	*/
	PrimitiveDataType() :
		value(PRIM_TYPE_NONE) {}

	/**
	*
	*/
	PrimitiveDataType(PrimitiveDataType::PrimDataType typ) :
		value(typ) {}

	/**
	* Copy Constructor.
	* @param other The value to copy
	*/
	PrimitiveDataType(const PrimitiveDataType &other);

	/**
	* Return the value in the enclosed enumerated type.
	* @return the value as an enumerated type.
	*/
	PrimDataType getValue()
	{
		return value;
	}

	/**
	* Equality operator.
	* @param other The value to compare this to
	* @return true if the values are equal
	*/
	friend bool operator==(const PrimitiveDataType &first, const PrimitiveDataType &second);

	/**
	* Inequality operator.
	* @param other The value to compare this to
	* @return true if the values are not equal
	*/
	friend bool operator!=(const PrimitiveDataType &first, const PrimitiveDataType &second);

	/**
	* Assignment operator.
	* @param other The value to assign to this.
	* @return A copy of this.
	*/
	PrimitiveDataType& operator=(const PrimitiveDataType &other);

	/**
	*  Convert the type to a printable string representation of the type.
	* @param typ The type to convert to a string
	* @return a string representation of the type.
	*/
	static std::string toString(PrimitiveDataType &typ);

	/**
	* Convert this type to the nearest OpenGL type.  This will work exaclty for
	* - [unsigned] byte
	* - [unsigned] short
	* - [unsigned] int
	* - double
	* Other conversions will be to GL_INT as there is no exact conversion or will
	* use the closest conversion which makes sense.
	* @return The nearest OpenGL type to this type
	*/
	GLenum toOpenGLType();

	/**
	* Write a textual representation of this type to an output stream.
	* @param os Stream to write to
	* @param typ value to write
	* @return stream to which data was written
	*/
	friend std::ostream& operator<<(std::ostream &os, PrimitiveDataType &typ);

	/**
	* Convert a string representation of this primitive type to the associated primitive type.
	* Acceptable strings include:
	* <ul>
	* <li>byte</li>
	* <li>short</li>
	* <li>int</li>
	* <li>long</li>
	* <li>ubyte</li>
	* <li>ushort</li>
	* <li>uint</li>
	* <li>ulong</li>
	* <li>float</li>
	* <li>double</li>
	* <li>char</li>
	* <li>c_string</li>
	* <li>string</li>
	* <li>pointer</li>
	* <li>vec2</li>
	* <li>vec3</li>
	* <li>vec4</li>
	* <li>bvec2</li>
	* <li>bvec3</li>
	* <li>bvec4</li>
	* <li>ivec2</li>
	* <li>ivec3</li>
	* <li>ivec4</li>
	* <li>mat2</li>
	* <li>mat3</li>
	* <li>mat4</li>
	* <li>sampler2d</li>
	* </ul>
	* @param str the string to convert
	* @return the primitive corresponding to the string
	* @throws CorruptException if the string is not one of the recognized lower-case strings
	*/
	static PrimitiveDataType stringToPrimitiveDataType(const std::string& str);


};

extern const PrimitiveDataType PRIM_NONE;
extern const PrimitiveDataType PRIM_BYTE;
extern const PrimitiveDataType PRIM_SHORT;
extern const PrimitiveDataType PRIM_INT;
extern const PrimitiveDataType PRIM_LONG;
extern const PrimitiveDataType PRIM_UBYTE;
extern const PrimitiveDataType PRIM_USHORT;
extern const PrimitiveDataType PRIM_UINT;
extern const PrimitiveDataType PRIM_ULONG;
extern const PrimitiveDataType PRIM_FLOAT;
extern const PrimitiveDataType PRIM_DOUBLE;
extern const PrimitiveDataType PRIM_C_STRING;
extern const PrimitiveDataType PRIM_STRING;
extern const PrimitiveDataType PRIM_POINTER;
extern const PrimitiveDataType PRIM_CHAR;



/**
* This is the root class for all exceptions to be thrown by the game engine.
* Classes which want to throw exceptions can throw an instance of this class
* or they can derive a subclass to represent a special type of exception.
* @author R. N. Robson
*/
class Exception
{
protected:
	std::string			fileName;
	int					lineNum;
	std::string			message;
	Exception			*nestedException;

public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	Exception() :
		lineNum(-1), nestedException(NULL)
	{
	}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	Exception(std::string& msg, std::string fname, int line) :
		message(msg), fileName(fname), lineNum(line), nestedException(NULL)
	{
	}

	/**
	* Copy constructor.
	*/
	Exception(Exception& e);


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	Exception(std::string& msg, std::string fname, int line, Exception& e);

	~Exception();

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();

	/**
	* Returns the message associated with the exception.
	* @return A textual explanation.
	*/
	std::string getMessage();

	/**
	* Returns the file name where the exception was raised.
	* @return The file for the exception.
	*/
	std::string getFileName();

	/**
	* Returns the line number where the exception was raised.
	* @return The line number.
	*/
	int getLine();

	/**
	* Determines if this exception contains a nested exception.
	* @return True if this contains a nested exception.
	*/
	bool hasNestedException();

	/**
	* Returns exception nested within this one.  Use hasNestedException() to
	* determine if this is a real nested exception.
	* @return The nested exception or NULL if there is none.
	*/
	Exception* getNestedException();

	/**
	* Returns a list of messages for a group of nested exceptions where each message is
	* separated from the others by a newline.
	* @return The messages for this exception and any nested exceptions.
	*/
	std::string getReasonChain();

	/**
	* Returns a string representation of this exception.  Subclasses which want to
	* alter the printed form of an exception should overide this method.
	* @return A string form of the exception.
	*/
	virtual std::string toString();

	/**
	* Insertion operator which uses string returned by toString().
	* @param e Exception to insert.
	* os Stream into which exception should be inserted.
	* @return The stream inserted into.
	*/
	friend std::ostream& operator<<(std::ostream& os, Exception& e);
};

/**
* The root of all input/Output exceptions.
* @author R.N. Robson
*/
class IOException : public Exception
{
public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	IOException() :
		Exception()
	{}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	IOException(std::string& msg, std::string fname, int line) :
		Exception(msg, fname, line)
	{}

	/**
	* Copy constructor.
	*/
	IOException(IOException& e) :
		Exception(e)
	{}


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	IOException(std::string& msg, std::string fname, int line, Exception& e) :
		Exception(msg, fname, line, e)
	{}

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();
};

/**
* The root of all input/Output exceptions.
* @author R.N. Robson
*/
class FileNotFoundException : public IOException
{
public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	FileNotFoundException() :
		IOException()
	{}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	FileNotFoundException(std::string& msg, std::string fname, int line) :
		IOException(msg, fname, line)
	{}

	/**
	* Copy constructor.
	*/
	FileNotFoundException(FileNotFoundException& e) :
		IOException(e)
	{}


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	FileNotFoundException(std::string& msg, std::string fname, int line, Exception& e) :
		IOException(msg, fname, line, e)
	{}

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();
};

/**
* This indicates an operation was attempted which is currently not supported.
* @author R.N. Robson
*/
class UnsupportedOperationException : public Exception
{
public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	UnsupportedOperationException() :
		Exception()
	{}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	UnsupportedOperationException(std::string& msg, std::string fname, int line) :
		Exception(msg, fname, line)
	{}

	/**
	* Copy constructor.
	*/
	UnsupportedOperationException(UnsupportedOperationException& e) :
		Exception(e)
	{}


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	UnsupportedOperationException(std::string& msg, std::string fname, int line, Exception& e) :
		Exception(msg, fname, line, e)
	{}

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();
};

/**
* This indicates that data being read or manipulated was found to be corrupt in some way.
* @author R.N. Robson
*/
class CorruptException : public Exception
{
public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	CorruptException() :
		Exception()
	{}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	CorruptException(std::string& msg, std::string fname, int line) :
		Exception(msg, fname, line)
	{}

	/**
	* Copy constructor.
	*/
	CorruptException(CorruptException& e) :
		Exception(e)
	{}


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	CorruptException(std::string& msg, std::string fname, int line, Exception& e) :
		Exception(msg, fname, line, e)
	{}

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();
};

/**
* This indicates that an index used to access some data structure is out of bounds.
* @author R.N. Robson
*/
class IndexOutOfBoundsException : public Exception
{
protected:
	int		badIndex;
public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	IndexOutOfBoundsException() :
		Exception(), badIndex(0)
	{}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param index The index which caused the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	IndexOutOfBoundsException(std::string& msg, int index, std::string fname, int line) :
		Exception(msg, fname, line), badIndex(index)
	{}

	/**
	* Copy constructor.
	*/
	IndexOutOfBoundsException(IndexOutOfBoundsException& e);


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param index The index which caused the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	IndexOutOfBoundsException(std::string& msg, std::string fname, int index, int line, Exception& e) :
		Exception(msg, fname, line, e), badIndex(index)
	{}

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();

	/**
	* Returns a string representation of this exception.  Subclasses which want to
	* alter the printed form of an exception should overide this method.
	* @return A string form of the exception.
	*/
	virtual std::string toString();
};

/**
* This indicates that a name which must be unique is being duplicated.
* @author R.N. Robson
*/
class DuplicateNameException : public Exception
{
protected:
	std::string			duplicateName;
public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	DuplicateNameException() :
		Exception()
	{}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param dupName The name which was duplicated
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	DuplicateNameException(std::string& msg, std::string &dupName, std::string fname, int line) :
		Exception(msg, fname, line), duplicateName(dupName)
	{}

	/**
	* Copy constructor.
	*/
	DuplicateNameException(DuplicateNameException& e);


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param dupName The name which was duplicated
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	DuplicateNameException(std::string& msg, std::string fname, std::string &dupName, int line, Exception& e) :
		Exception(msg, fname, line, e), duplicateName(dupName)
	{}

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();

	/**
	* Returns a string representation of this exception.  Subclasses which want to
	* alter the printed form of an exception should overide this method.
	* @return A string form of the exception.
	*/
	virtual std::string toString();
};

/**
* This indicates that space for some resource has been exhausted or exceeded.
* @author R.N. Robson
*/
class NoSpaceException : public Exception
{
protected:
	long			spaceLimit;
public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	NoSpaceException() :
		Exception()
	{}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param dupName The name which was duplicated
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	NoSpaceException(std::string& msg, long limit, std::string fname, int line) :
		Exception(msg, fname, line), spaceLimit(limit)
	{}

	/**
	* Copy constructor.
	*/
	NoSpaceException(NoSpaceException& e);


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param dupName The name which was duplicated
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	NoSpaceException(std::string& msg, long limit, std::string fname, int line, Exception& e) :
		Exception(msg, fname, line, e), spaceLimit(limit)
	{}

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();

	/**
	* Returns a string representation of this exception.  Subclasses which want to
	* alter the printed form of an exception should overide this method.
	* @return A string form of the exception.
	*/
	virtual std::string toString();
};

/**
* This indicates that an attempt to find a resource failed. Most likely it was looking for in in a resource
* manager but it could not be found.
* @author R.N. Robson
*/
class ResourceNotFoundException : public Exception
{
public:
	/**
	* Constructor to create an empty exception which can be recognized as being
	* empty by having a negative line number.
	*/
	ResourceNotFoundException() :
		Exception()
	{}

	/**
	* This is the constructor which will be used most of the time.  It creates a single
	* exception which specifies the file and line on which it was raised and a message
	* describing the exception.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	*/
	ResourceNotFoundException(std::string& msg, std::string fname, int line) :
		Exception(msg, fname, line)
	{}

	/**
	* Copy constructor.
	*/
	ResourceNotFoundException(ResourceNotFoundException& e) :
		Exception(e)
	{}


	/**
	* This is the constructor used when rethrowing an exception.  It creates a new exception
	* containing a nested exception.  This allows you to create chains of exceptions.
	* @param msg The nessage describing the exception
	* @param fname The name of the file where the exception was raised.  Usually the file macro is used.
	* @param line The line in the file where the exception was raised.  Usually the line macro is used.
	* @param e The exception which caused this exception to be raised.
	*/
	ResourceNotFoundException(std::string& msg, std::string fname, int line, Exception& e) :
		Exception(msg, fname, line, e)
	{}

	/**
	* Return the identifying name for this exception, usually the class name.
	* @return The name of this exeption.
	*/
	virtual std::string getExceptionName();

	/**
	* Returns a string representation of this exception.  Subclasses which want to
	* alter the printed form of an exception should overide this method.
	* @return A string form of the exception.
	*/
	virtual std::string toString();
};



#endif