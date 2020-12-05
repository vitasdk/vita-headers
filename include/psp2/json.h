/**
 * \usergroup{SceLibJson}
 * \usage{psp2/json.h,SceLibJson_stub,SCE_SYSMODULE_JSON}
 *
 * \note Compiling and linking with this library requires you
 *       to compile your code with the compiler flag -fno-rtti.
 */

#ifndef _PSP2_JSON_H_
#define _PSP2_JSON_H_

#ifdef __cplusplus

#include <psp2/types.h>

/**
 * Enumerator of different errors in this library.
 */
typedef enum SceJsonErrorCode
{
	/**
	 * The module has not been initialised.
	 */
	SCE_JSON_ERROR_UNLOADED              = 0x80920110,
	/**
	 * The module has already been initialised.
	 */
	SCE_JSON_ERROR_LOADED                = 0x80920111,
	/**
	 * Internal Memory Allocation failure(returned nullptr).
	 */
	SCE_JSON_ERROR_MEM_ALLOC             = 0x80920102,
	/**
	 * InitParameter.bufSize is 0.
	 */
	SCE_JSON_PARSER_ERROR_EMPTY_BUF      = 0x80920105,
	/**
	 * Parser failed to load file.
	 */
	SCE_JSON_PARSER_ERROR_FILE_LOAD      = 0x80920103,
	/**
	 * Invalid character in the parsed data.
	 */
	SCE_JSON_PARSER_ERROR_INVALID_TOKEN  = 0x80920101,
} SceJsonErrorCode;

namespace sce
{

namespace Json
{

/**
 * Strongly typed Enumerator of different types of Values.
 */
typedef enum class ValueType
{
	NullValue            = 0, //!< Null value
	BoolValue            = 1, //!< Boolean value
	IntValue             = 2, //!< Long integer value
	UIntValue            = 3, //!< Unsigned long integer value
	RealValue            = 4, //!< Double precision float value
	StringValue          = 5, //!< String value
	ArrayValue           = 6, //!< Array value
	ObjectValue          = 7  //!< Object value
} ValueType;

/**
 * Base class for reimplementation of memory allocation.
 * This class must be derived from.
 */
class MemAllocator
{
public:
	MemAllocator();
	virtual ~MemAllocator();

	/**
	 * Virtual Function for memory allocation.
	 *
	 * @param[in] size - Size of the allocated memory
	 * @param[in] data - User defined data for the function.
	 *
	 * @return  Pointer to the allocated memory
	 */
	virtual void* allocateMemory(SceSize size, void* userData) = 0;
	/**
	 * Virtual Function for memory deallocation.
	 *
	 * @param[in] ptr  - Pointer to memory.
	 * @param[in] data - User defined data for the function.
	 */
	virtual void freeMemory(void* ptr, void* userData) = 0;

	/**
	 * The base class definition prints an error to sceClibPrintf.
	 */
	virtual void notifyError(int errorCode, SceSize size, void* userData);
};

/**
 * Utility Data Structure to pass on initialisation parameters.
 */
class InitParameter
{
public:
	/**
	 * Pointer to a MemAllocator object for internal memory allocations.
	 * Required field.
	 */
	MemAllocator* allocator;
	/**
	 * User defined data sent to overriden MemAllocator functions.
	 */
	void* userData;
	/**
	 * Size of the buffer used for reading JSON file data in
	 * Parser::parse(Value&, const char*).
	 *
	 * Does not have to be the size of the file, but a smaller
	 * buffer size will result in more IO calls.
	 */
	SceSize bufSize;
};

/**
 * Utility class for initialising and terminating the library.
 */
class Initializer
{
public:
	Initializer();
	~Initializer();

	/**
	 * Initialise the library.
	 *
	 * @param[in] initParams - Initialisation parameters for the library.
	 *
	 * @return  0 on success, <0 on error.
	 */
	int initialize(const InitParameter* initParams);
	/**
	 * Terminate the library
	 *
	 * @return  0 on success, <0 on error.
	 */
	int terminate();
};

class Value;
/**
 * Class for JSON arrays.
 */
class Array
{
public:
	/**
	 * Class for iterating over Array members.
	 */
	class iterator
	{
	public:
		iterator();
		iterator(const iterator& iter);
		~iterator();

		/**
		 * Advance the iterator by adv
		 */
		void advance(SceSize adv);

		/**
		 * Assignment operator
		 */
		iterator& operator=(const iterator& iter);
		/**
		 * Advance the iterator by adv
		 */
		void operator++(int adv);
		/**
		 * Increment the iterator
		 */
		void operator++();
		/**
		 * Dereference the iterator.
		 *
		 * @return  The Value the iterator is pointing to.
		 */
		Value& operator*() const;
		/**
		 * Compare to another iterator.
		 *
		 * @param[in] iter - The iterator to compare to.
		 *
		 * @return  true if they are not equivalent.
		 */
		bool operator!=(iterator iter) const;
		/**
		 * Access the Value being pointed to.
		 */
		Value* operator->() const;
	private:
		void* implData; //!< Pointer to internal implementation data.
	};

	Array();
	Array(const Array& arr);
	~Array();

	/**
	 * Get an iterator pointing to the start of the Array
	 *
	 * @return  The iterator.
	 */
	iterator begin() const;
	/**
	 * Get an iterator pointing to after the end of the Array
	 *
	 * @return  The iterator.
	 */
	iterator end() const;
	/**
	 * Insert a Value at pos
	 *
	 * @param[in] pos - An iterator pointing to the point to insert the Value.
	 * @param[in] val - The Value to insert.
	 *
	 * @return  An iterator pointing to the inserted value.
	 */
	iterator insert(const iterator& pos, const Value& val);
	/**
	 * Erase the Value at pos
	 *
	 * @param[in] pos - The position of the Value to erase.
	 *
	 * @return  iterator following the removed Value
	 */
	iterator erase(const iterator& pos);
	/**
	 * Returns a reference to the last element in the Array
	 *
	 * @return  The refence to the value.
	 */
	Value& back() const;

	/**
	 * Will empty the Array, removing all child valus.
	 */
	void clear();
	/**
	 * Adds val to the end of the Array
	 */
	void push_back(const Value& val);
	/**
	 * Removes the last child value.
	 */
	void pop_back();

	/**
	 * Get the size of the array
	 *
	 * @return  The size of the array.
	 */
	SceSize size() const;
	/**
	 * Is the array empty.
	 *
	 * @return  true if empty, false otherwise.
	 */
	bool empty() const;

	/**
	 * Assignment Operator
	 */
	Array& operator=(const Array& arr);

private:
	void* implData; //!< Pointer to internal implementation data.
};

/**
 * Class for JSON strings.
 */
class String
{
public:
	String();
	String(const char* s);
	String(const String& str);
	~String();

	const static SceSize npos = -1;

	/**
	 * Append string s to the end
	 *
	 * @param[in] s - Pointer to the C string to append.
	 *
	 * @return  A reference the new string
	 */
	String& append(const char* s);
	/**
	 * Append string s to position pos
	 *
	 * @param[in] s   - Pointer to the C string to append.
	 * @param[in] pos - Position in the String to append to.
	 *
	 * @return  A reference the new string
	 */
	String& append(const char* s, SceSize pos);
	/**
	 * Append string str
	 *
	 * @param[in] str - String to append.
	 *
	 * @return  A reference the new string
	 */
	String& append(const String& str);

	/**
	 * Returns a newly constructed string object with its value
	 * initialized to a copy of a substring of this object.
	 *
	 * @param[in] pos - The starting position of the sub-string.
	 * @param[in] len - The length of the sub-string.
	 *
	 * @return  The sub-string found at pos.
	 */
	String substr(SceSize pos = 0, SceSize len = npos) const;
	/**
	 * Returns the character found at pos
	 *
	 * @param[in] pos - The position of the desired character.
	 *
	 * @return  The character found.
	 */
	char at(SceSize pos) const;

	/**
	 * Searches the string for the first instance of a sequence
	 *
	 * @param[in] s   - The sequence to search for.
	 * @param[in] pos - Position to start searching from.
	 *
	 * @return  The position of the first instance of the sequence.
	 *          Will return String::npos if not found
	 */
	SceSize find(const char* s, SceSize pos) const;
	/**
	 * Searches the string for the first instance of a sequence
	 *
	 * @param[in] s   - The sequence to search for.
	 * @param[in] pos - Position to start searching from.
	 * @param[in] n   - Length of the sequence.
	 *
	 * @return  The position of the first instance of the sequence.
	 *          Will return String::npos if not found
	 */
	SceSize find(const char* s, SceSize pos, SceSize n) const;
	/**
	 * Searches the string for the first instance of a sequence
	 *
	 * @param[in] str - The sequence to search for.
	 * @param[in] pos - Position to start searching from.
	 *
	 * @return  The position of the first instance of the sequence.
	 *          Will return String::npos if not found
	 */
	SceSize find(const String& str, SceSize pos) const;
	/**
	 * Searches the string for the first instance of a sequence
	 *
	 * @param[in] c   - The sequence to search for.
	 * @param[in] pos - Position to start searching from.
	 *
	 * @return  The position of the first instance of the sequence.
	 *          Will return String::npos if not found
	 */
	SceSize find(char c, SceSize pos) const;

	/**
	 * Searches the string for the last instance of a sequence
	 *
	 * @param[in] s   - The sequence to search for.
	 * @param[in] pos - Position to start searching from.
	 *
	 * @return  The position of the last instance of the sequence.
	 *          Will return String::npos if not found
	 */
	SceSize rfind(const char* s, SceSize pos) const;
	/**
	 * Searches the string for the last instance of a sequence
	 *
	 * @param[in] s   - The sequence to search for.
	 * @param[in] pos - Position to start searching from.
	 * @param[in] n   - Length of the sequence.
	 *
	 * @return  The position of the last instance of the sequence.
	 *          Will return String::npos if not found
	 */
	SceSize rfind(const char* s, SceSize pos, SceSize n) const;
	/**
	 * Searches the string for the last instance of a sequence
	 *
	 * @param[in] str - The sequence to search for.
	 * @param[in] pos - Position to start searching from.
	 *
	 * @return  The position of the last instance of the sequence.
	 *          Will return String::npos if not found
	 */
	SceSize rfind(const String& str, SceSize pos) const;/**
	 * Searches the string for the last instance of a sequence
	 *
	 * @param[in] c   - The sequence to search for.
	 * @param[in] pos - Position to start searching from.
	 *
	 * @return  The position of the last instance of the sequence.
	 *          Will return String::npos if not found
	 */
	SceSize rfind(char c, SceSize pos) const;

	/**
	 * Clears the string's contents.
	 */
	void clear();
	/**
	 * Returns whether the string is empty or not.
	 *
	 * @return  true if empty, false if not
	 */
	bool empty() const;
	/**
	 * Returns the length of the String in bytes.
	 *
	 * @return  The string's length.
	 */
	SceSize size() const;
	/**
	 * Returns the length of the String in bytes.
	 *
	 * @return  The string's length.
	 */
	SceSize length() const;
	/**
	 * Returns a C style string buffer of the String.
	 *
	 * @return  The C string
	 */
	const char* c_str() const;
	/**
	 * Resizes the string to a length of n characters.
	 */
	void resize(SceSize n);

	/**
	 * Compares the string to s.
	 *
	 * @return  true if equivalent, false if not
	 */
	bool compare(const char* s) const;
	/**
	 * Compares the string to str.
	 *
	 * @return  true if equivalent, false if not
	 */
	bool compare(const String& str) const;

	/**
	 * Appends s to the string.
	 *
	 * @return  A reference to the resulting String.
	 */
	String& operator+=(const char* s);
	/**
	 * Appends c to the string.
	 *
	 * @return  A reference to the resulting String.
	 */
	String& operator+=(unsigned char c);
	/**
	 * Compares the string to s.
	 *
	 * @return  true if equivalent, false if not
	 */
	bool operator==(const char* s) const;
	/**
	 * Compares the string to str.
	 *
	 * @return  true if equivalent, false if not
	 */
	bool operator==(const String& str) const;

	/**
	 * Assignment Operator
	 */
	String& operator=(const String& str);

private:
	void* implData; //!< Pointer to internal implementation data.
};

class Object;
/**
 * Class for value of JSON property.
 */
class Value
{
public:
	/**
	 * Callback for serialization.
	 * It is called at certain points in the serialization process.
	 *
	 * @param[in,out] str      - The current state of the parser output.
	 * @param[in]     userData - User defined data for the function.
	 */
	typedef int (*SerializeCallback)(String& str, void* userData);
	/**
	 * Callback for NullValue access.
	 * It is called when the type of the Value is
	 * ValueType::NullValue and the Value is accessed.
	 *
	 * @param[in] type      - The type of value requested.
	 * @param[in] parent    - A pointer to the parent of the Value accessed.
	 * @param[in] userData  - User defined data for the function.
	 *
	 * @return  A valid Value of the type given.
	 */
	typedef Value const&(*NullAccessCallback)(ValueType type, const Value* parent, void* userData);

	Value();
	Value(ValueType type);
	Value(SceBool value);
	Value(SceInt64 value);
	Value(SceUInt64 value);
	Value(double value);
	Value(const String& value);
	Value(const Array& value);
	Value(const Object& value);
	Value(const Value& value);
	~Value();

	/**
	 * Sets s to be a string representation of the value
	 *
	 * @param[out] s - The resultant string
	 */
	void toString(String& s) const;

	/**
	 * Swaps the value with another Value.
	 *
	 * @param[in] val - The Value to swap with.
	 */
	void swap(Value& val);
	/**
	 * Clears the value by setting to null.
	 */
	void clear();

	/**
	 * Returns number of children
	 *
	 * @return  Number of children
	 */
	SceSize count() const;

	/**
	 * Returns the ValueType of the value
	 *
	 * @return  The value's type
	 */
	ValueType getType() const;

	/**
	 * Set the type
	 *
	 * @param[in] type - The type to set the value to.
	 */
	void set(ValueType type);
	/**
	 * Set the value to a boolean
	 *
	 * @param[in] value - New value
	 */
	void set(SceBool value);
	/**
	 * Set the value to a long integer(64 bits)
	 *
	 * @param[in] value - New value
	 */
	void set(SceInt64 value);
	/**
	 * Set the value to an unsigned long integer(64 bits)
	 *
	 * @param[in] value - new value
	 */
	void set(SceUInt64 value);
	/**
	 * Set the value to a double precision float
	 *
	 * @param[in] value - New value
	 */
	void set(double value);
	/**
	 * Set the value to a String
	 *
	 * @param[in] value - String to copy from.
	 */
	void set(const String& value);
	/**
	 * Set the value to an Array
	 *
	 * @param[in] value - Array to copy from.
	 */
	void set(const Array& value);
	/**
	 * Set the value to an Object
	 *
	 * @param[in] value - Object to copy from.
	 */
	void set(const Object& value);
	/**
	 * Set the value
	 *
	 * @param[in] value - Value to copy from.
	 */
	void set(const Value& value);

	/**
	 * Set the Value's NullAccessCallback
	 *
	 * @param[in] cb   - The callback.
	 * @param[in] data - Data to pass to the callback function.
	 *
	 * @return  0 on success, <0 on error
	 */
	int setNullAccessCallback(NullAccessCallback cb, void* userData);

	/**
	 * Returns a reference to the root Value
	 *
	 * @return  The root value.
	 */
	Value& getRoot() const;

	/**
	 * Returns a constant reference to the value.
	 *
	 * @return  The value. Will return false if the Value is not of type
	 *          ValueType::BoolValue.
	 */
	const SceBool& getBoolean() const;
	/**
	 * Returns a constant reference to the value.
	 *
	 * @return  The value. Will return 0 if the Value is not of type
	 *          ValueType::IntValue or ValueType::UIntValue.
	 */
	const SceInt64& getInteger() const;
	/**
	 * Returns a constant reference to the value.
	 *
	 * @return  The value. Will return 0 if the Value is not of type
	 *          ValueType::IntValue or ValueType::UIntValue.
	 */
	const SceUInt64& getUInteger() const;
	/**
	 * Returns a constant reference to the value.
	 *
	 * @return  The value. Will return 0 if the Value is not of type
	 *          ValueType::RealValue.
	 */
	const SceDouble& getReal() const;
	/**
	 * Returns a constant reference to the string. Only constant functions
	 * can be used, and the string cannot be altered.\n
	 * referString() is the alternative function for altering the string.
	 *
	 * @return  The string. Will return a garbage string if the Value is
	 *          not of type ValueType::StringValue.
	 */
	const String& getString() const;
	/**
	 * Returns a constant reference to the array. Only constant functions
	 * can be used, and the array and its members cannot be altered.\n
	 * referArray() is the alternative function for altering the array.
	 *
	 * @return  The array. Will return an empty array if the Value is
	 *          not of type ValueType::ArrayValue.
	 */
	const Array& getArray() const;
	/**
	 * Returns a constant reference to the object. Only constant functions
	 * can be used, and the object and its members cannot be altered.\n
	 * referObject() is the alternative function for altering the array.
	 *
	 * @return  The object. Will return an empty object if the Value is
	 *          not of type ValueType::ObjectValue.
	 */
	const Object& getObject() const;

	/**
	 * Returns a constant reference to the value. Only constant functions
	 * can be used, and the value cannot be altered.\n
	 * referValue(SceSize) is the alternative function for altering the value.
	 *
	 * @param[in] pos - The position of the value.
	 *
	 * @return  The value. Will return an empty value if the it doesn't exist.
	 */
	const Value& getValue(SceSize pos) const;
	/**
	 * Returns a constant reference to the value. Only constant functions
	 * can be used, and the value cannot be altered.\n
	 * referValue(const String&) is the alternative function
	 * for altering the value.
	 *
	 * @param[in] key - The key of the value.
	 *
	 * @return  The value. Will return an empty value if the it doesn't exist.
	 */
	const Value& getValue(const String& key) const;

	/**
	 * Returns a pointer to the value.
	 *
	 * @return  The value. Will return nullptr if the Value is not of type
	 *          ValueType::BoolValue.
	 */
	SceBool* referBoolean();
	/**
	 * Returns a pointer to the value.
	 *
	 * @return  The value. Will return nullptr if the Value is not of type
	 *          ValueType::IntValue or ValueType::UIntValue.
	 */
	SceInt64* referInteger();
	/**
	 * Returns a pointer to the value.
	 *
	 * @return  The value. Will return nullptr if the Value is not of type
	 *          ValueType::IntValue or ValueType::UIntValue.
	 */
	SceUInt64* referUInteger();
	/**
	 * Returns a pointer to the value.
	 *
	 * @return  The value. Will return 0 if the Value is not of type
	 *          ValueType::RealValue.
	 */
	SceDouble* referReal();
	/**
	 * Returns a pointer to the string.\n
	 * getString() is the alternative function for only reading the string.
	 *
	 * @return  The string. Will return a garbage string if the Value is
	 *          not of type ValueType::StringValue.
	 */
	String* referString();
	/**
	 * Returns a pointer to the array.\n
	 * getArray() is the alternative function for only reading the array.
	 *
	 * @return  The array. Will return an empty array if the Value is
	 *          not of type ValueType::ArrayValue.
	 */
	Array* referArray();
	/**
	 * Returns a pointer to the object.\n
	 * getObject() is the alternative function for only reading the object.
	 *
	 * @return  The object. Will return an empty object if the Value is
	 *          not of type ValueType::ObjectValue.
	 */
	Object* referObject();

	/**
	 * Returns a pointer to the value.\n
	 * getValue(SceSize) is the alternative function for only reading the Value.
	 *
	 * @param[in] pos - The position of the value.
	 *
	 * @return  The value. Will return an empty value if the it doesn't exist.
	 */
	Value* referValue(SceSize pos);
	/**
	 * Returns a pointer to the value.\n
	 * getValue(String&) is the alternative function for only reading the Value.
	 *
	 * @param[in] key - The key of the value.
	 *
	 * @return  The value. Will return an empty value if the it doesn't exist.
	 */
	Value* referValue(const String& key);

	/**
	 * Serializes the data into a string in JSON format
	 *
	 * @param[out] s - The resulting string, can be written to a file or parsed.
	 *
	 * @return  0 on success, <0 on error.
	 */
	int serialize(String& s);
	/**
	 * Serializes the values into a string in JSON format.
	 * Allows for a callback for the different stages in the serialization.
	 *
	 * @param[in,out] s       - The resulting string, can be written to a file or parsed again.
	 * @param[in]    cb       - Callback for the internal serialization. Can be used to format
	 *                          the output string, as the string is not formatted internally.
	 * @param[in]    userData - User defined data passed to the SerializeCallback
	 *
	 * @return  0 on success, <0 on error.
	 */
	int serialize(String& str, SerializeCallback cb, void* userData);

	/**
	 * Returns constant reference of the Value of key.
	 *
	 * @return  The Value.
	 */
	const Value& operator[](const String& key) const;
	/**
	 * Returns constant reference of the Value of key.
	 *
	 * @return  The Value.
	 */
	const Value& operator[](const char* key) const;
	/**
	 * Returns constant reference of the Value at pos.
	 *
	 * @return  The Value.
	 */
	const Value& operator[](SceSize pos) const;

	/**
	 * Assignment Operator
	 */
	Value& operator=(const Value& value);

	operator bool() const;

private:
	Value* parent;         //!< Pointer to the value's parent.
	NullAccessCallback cb; //!< The value's NullAccessCallback.
	union
	{
	SceBool boolean;
	SceInt64 integer;
	SceUInt64 uinteger;
	SceDouble real;
	String* string;
	Array* array;
	Object* object;
	} value;              //!< Union of different value types.
	char unused[4];       //!< Unused.
	ValueType type;       //!< The type of the value.
};

/**
 * Class for JSON objects.
 */
class Object
{
public:
	/**
	 * Key-Value Pair of JSON Object property.
	 */
	class Pair
	{
	public:
		Pair();
		Pair(const String& name, const Value& value);
		~Pair();

		String key;     //!< Name assigned to the property.
		char unused[4]; //!< Unused.
		Value value;    //!< Value assigned to the property.
	};
	/**
	 * Class for iterating over Object members.
	 */
	class iterator
	{
	public:
		iterator();
		iterator(const iterator& iter);
		~iterator();

		/**
		 * Advance the iterator.
		 *
		 * @param[in] adv - Number by which to advance.
		 */
		void advance(SceSize adv);

		/**
		 * Increment the iterator.
		 *
		 * @param[in] adv - The amount to increment it by.
		 */
		iterator& operator++(int adv);
		/**
		 * Increment the iterator.
		 */
		iterator& operator++();
		/**
		 * Dereference the iterator.
		 *
		 * @return  A reference to the pair the iterator is
		 * 			currently pointing to.
		 */
		Pair& operator*() const;
		/**
		 * Compare to another iterator.
		 *
		 * @return  true if equivalent, false otherwise.
		 */
		bool operator==(iterator iter) const;
		/**
		 * Compare to another iterator.
		 *
		 * @return  true if not equivalent, false otherwise.
		 */
		bool operator!=(iterator iter) const;
		/**
		 * Access the Pair the iterator is pointing to.
		 */
		Pair* operator->() const;

		/**
		 * Assignment Operator
		 */
		iterator& operator=(const iterator& iter);

	private:
		void* implData; //!< Pointer to internal implementation data.
	};

	Object();
	Object(const Object& obj);
	~Object();

	/**
	 * Returns an iterator to the first child element.
	 *
	 * @return  The iterator.
	 */
	iterator begin() const;
	/**
	 * Returns an iterator to after the last child element.
	 *
	 * @return  The iterator.
	 */
	iterator end() const;
	/**
	 * Inserts a pair into the Object.
	 *
	 * @param[in] p - The Pair to insert.
	 *
	 * @return  An iterator pointing to the inserted Pair.
	 */
	iterator insert(const Pair& p);
	/**
	 * Finds a Pair with a matching key.
	 *
	 * @param[in] key - The key to search for.
	 *
	 * @return  An iterator pointing to the Pair with the matching key.
	 */
	iterator find(const String& key);
	/**
	 * Empty the object.
	 */
	void clear();
	/**
	 * Remove the Pair with the key str.
	 *
	 * @param[in] str - key of the Pair to remove.
	 */
	void erase(const String& str);

	/**
	 * Gets the number of child Pairs.
	 */
	SceSize size() const;
	/**
	 * Is the object empty?
	 *
	 * @return  true if there are no child Pairs.
	 */
	bool empty() const;

	/**
	 * Searches for a pair with a key matching str.
	 *
	 * @return  The corresponding value of the matching key.
	 */
	Value& operator[](const String& str);

	/**
	 * Assignment Operator
	 */
	Object& operator=(const Object& obj);

private:
	void* implData; //!< Pointer to internal implementation data.
};

/**
 * Static Class for parsing.
 */
class Parser
{
public:
	/**
	 * Callback for outputing a character to parse.
	 * @par Example:
	 * @code
	 *  struct Data
	 *  {
	 *      char *buf; // Character buffer storing the JSON data.
	 *  };
	 *
	 *  int Parse_Callback(char& ch, void* userData)
	 *  {
	 *      Data *dat = (Data *)data;
	 *      int uVar1;
	 *
	 *      ch = *dat->buf;
	 *      ret = SCE_JSON_ERROR_PARSE_INVALID_CHAR;
	 *      if (ch != '\0')
	 *      {
	 *          dat->buf = dat->buf + 1;
	 *          ret = 0;
	 *      }
	 *      return ret;
	 *  }
	 *  @endcode
	 *
	 * @param[out] ch       - The character to be sent back to the parser.
	 * @param[in]  userData - User defined data for the function.
	 */
	typedef int (*ParseCallback)(char& ch, void* userData);

	/**
	 * Parses user defined data using characters from a
	 * user defined callback function.
	 *
	 * @param[out] val  - Reference to the value the data is written to.
	 * @param[in]  cb   - The callback function which gives the
	 *                    current character.
	 * @param[in]  data - Data to pass to the callback function
	 */
	static int parse(Value& val, ParseCallback cb, void* userData);

	/**
	 * Parses a string buffer.
	 *
	 * @param[out] val  - Reference to the Value the data is written to.
	 * @param[in]  buf  - String buffer to parse
	 * @param[in]  size - Size of buf
	 *
	 * @return  0 on success, <0 on error.
	 */
	static int parse(Value& val, const char* buf, SceSize size);

	/**
	 * Parse a JSON file. Will parse until EOF.
	 *
	 * @param[out] val  - Reference to the Value the data is written to.
	 * @param[in]  path  - Path to the JSON file.
	 *
	 * @return  0 on success, <0 on error.
	 */
	static int parse(Value& val, const char* path);
};

} /* namespace Json */
} /* namespace sce  */

#endif /* __cplusplus */

#endif /* _PSP2_JSON_H_ */
