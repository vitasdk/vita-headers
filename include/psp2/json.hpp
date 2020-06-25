/**
 * \usergroup{SceLibJson}
 * \usage{psp2/json.hpp,SceLibJson_stub,SCE_SYSMODULE_JSON}
 */

#ifndef _PSP2_JSON_H
#define _PSP2_JSON_H

#include <psp2/types.h>

namespace sce
{
namespace Json
{

typedef enum ValueType 
{
    SCE_JSON_VALUE_EMPTY    = 0, //!< Empty value
    SCE_JSON_VALUE_BOOL     = 1, //!< Boolean value
    SCE_JSON_VALUE_INT64    = 2, //!< Long integer value
    SCE_JSON_VALUE_UINT64   = 3, //!< Unsigned long integer value
    SCE_JSON_VALUE_DOUBLE   = 4, //!< Double precision float value
    SCE_JSON_VALUE_STRING   = 5, //!< String value
    SCE_JSON_VALUE_ARRAY    = 6, //!< Array value
    SCE_JSON_VALUE_OBJECT   = 7  //!< Object value
} ValueType;

typedef enum SceJsonError
{
    SCE_JSON_ERROR_PARSE_INVALID_CHAR   = 0x80920101, //!< Invalid character in the parsed data.
    SCE_JSON_ERROR_NOMEM                = 0x80920102, //!< Internal Memory Allocation failure(returned nullptr).
    SCE_JSON_ERROR_NOFILE               = 0x80920103, 
    SCE_JSON_ERROR_NOROOT               = 0x80920104,
    SCE_JSON_ERROR_NOBUF                = 0x80920105,
    SCE_JSON_ERROR_NOINIT               = 0x80920110, //!< The module has not been initialised. 
    SCE_JSON_ERROR_MULTIPLEINIT         = 0x80920111, //!< The module has already been initialised.
    SCE_JSON_ERROR_INVALID_ARGUMENT     = 0x80920112
} SceJsonError;

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
     * 
     * @return Pointer the allocated memory
     */
    virtual void* AllocateMemory(size_t size, void* unk) = 0;
    /**
     * Virtual Function for memory deallocation.
     * 
     * @param[in] ptr - Pointer to memory.
     * @param[in] unk - Unknown field, not required.
     */
    virtual void  FreeMemory(void* ptr, void* unk) = 0;

    virtual void  notifyError(int unk1, size_t size, void *unk3);
};

struct InitParameter
{
    MemAllocator*   allocator; //!< Pointer to a MemAllocator object for internal memory allocations. Required field.
    void*           unk_0x4;   //!< Unknown
    size_t          unk_0x8;   //!< Unknown, but must be set to more than 0.
};

/**
 * Utility class for initialising the library
 */
class Initializer
{
public:
    typedef void (*AllocatorInfoCallback)(int, sce::Json::ValueType, void*);

    Initializer();
    ~Initializer();

    /**
     * Initialise the library.
     * 
     * @param[in] initParams - Initialisation parameters for the library.
     * 
     * @return 0 on success, <0 on error.
     */
    int         initialize(const InitParameter* initParams);
    /**
     * Terminate the library
     * 
     * @return 0 on success, <0 on error.
     */
    int         terminate();

    void        setAllocatorInfoCallBack(AllocatorInfoCallback cb, void* param2);
};

class Value;

class Array
{
public:
    class iterator
    {
    public:
        iterator();
        iterator(const iterator& iter);
        ~iterator();

        void        advance(size_t adv);

        iterator&   operator=(const iterator& iter);
        void        operator++(int adv);
        void        operator++();
        Value       operator*() const;
        bool        operator!=(iterator iter) const;
        Value*      operator->() const;
    private:
        Value*      ptr;
    };

    Array();
    Array(const Array& arr);
    ~Array();

    iterator    begin() const;
    iterator    end() const;
    Value&      back() const;

    void        clear();
    void        erase();
    void        insert(const iterator& iter, const Value& val);
    void        push_back(const Value& val);
    void        pop_back();

    size_t      size() const;
    bool        empty() const;

    Array&      operator=(const Array& arr);

private:
    void*       impl_data; //!< Pointer to internal implementation data
};

class String
{
public:
    String();
    String(const char* s);
    String(const String& str);
    ~String();

    static int npos;

    /**
     * Append string s to the end
     * 
     * @param[in] s - Pointer to the C string to append.
     */
    String&     append(const char* s);
    /**
     * Append string s to position pos
     * 
     * @param[in] s   - Pointer to the C string to append.
     * @param[in] pos - Position in the String to append to.
     */
    String&     append(const char* s, size_t pos);
    /**
     * Append string str
     * 
     * @param[in] str - String to append.
     */
    String&     append(const String& str);
    
    /**
     * Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
     * 
     * @param[in] pos - The starting position of the sub-string.
     * @param[in] len - The length of the sub-string.
     * 
     * @return The sub-string found at pos.
     */
    String      substr(size_t pos = 0, size_t len = npos);
    /**
     * Returns the character found at pos
     * 
     * @param[in] pos - The position of the desired character.
     * 
     * @return The character found.
     */
    const char& at(size_t pos) const;

    /**
     * Searches the string for the first instance of a sequence
     * 
     * @param[in] s   - The sequence to search for.
     * @param[in] pos - Position to start searching from.
     * 
     * @return The position of the first instance of the sequence. Will return String::npos if not found
     */
    size_t      find(const char* s, size_t pos) const;
    /**
     * Searches the string for the first instance of a sequence
     * 
     * @param[in] s   - The sequence to search for.
     * @param[in] pos - Position to start searching from.
     * @param[in] n   - Length of the sequence.
     * 
     * @return The position of the first instance of the sequence. Will return String::npos if not found
     */
    size_t      find(const char* s, size_t pos, size_t n) const;
    /**
     * Searches the string for the first instance of a sequence
     * 
     * @param[in] str - The sequence to search for.
     * @param[in] pos - Position to start searching from.
     * 
     * @return The position of the first instance of the sequence. Will return String::npos if not found
     */
    size_t      find(const String& str, size_t pos) const;/**
     * Searches the string for the first instance of a sequence
     * 
     * @param[in] c   - The sequence to search for.
     * @param[in] pos - Position to start searching from.
     * 
     * @return The position of the first instance of the sequence. Will return String::npos if not found
     */
    size_t      find(char c, size_t pos) const;

    /**
     * Searches the string for the last instance of a sequence
     * 
     * @param[in] s   - The sequence to search for.
     * @param[in] pos - Position to start searching from.
     * 
     * @return The position of the last instance of the sequence. Will return String::npos if not found
     */
    size_t      rfind(const char* s, size_t pos) const;
    /**
     * Searches the string for the last instance of a sequence
     * 
     * @param[in] s   - The sequence to search for.
     * @param[in] pos - Position to start searching from.
     * @param[in] n   - Length of the sequence.
     * 
     * @return The position of the last instance of the sequence. Will return String::npos if not found
     */
    size_t      rfind(const char* s, size_t pos, size_t n) const;
    /**
     * Searches the string for the last instance of a sequence
     * 
     * @param[in] str - The sequence to search for.
     * @param[in] pos - Position to start searching from.
     * 
     * @return The position of the last instance of the sequence. Will return String::npos if not found
     */
    size_t      rfind(const String& str, size_t pos) const;/**
     * Searches the string for the last instance of a sequence
     * 
     * @param[in] c   - The sequence to search for.
     * @param[in] pos - Position to start searching from.
     * 
     * @return The position of the last instance of the sequence. Will return String::npos if not found
     */
    size_t      rfind(char c, size_t pos) const;

    /**
     * Clears the string's contents.
     */
    void        clear();
    /**
     * Returns whether the string is empty or not.
     * 
     * @return true if empty, false if not
     */
    bool        empty() const;
    /**
     * Returns the length of the String in bytes.
     * 
     * @return The string's length.
     */
    size_t      size() const;
    /**
     * Returns the length of the String in bytes.
     * 
     * @return The string's length.
     */
    size_t      length() const;
    /**
     * Returns a C style string buffer of the String.
     * 
     * @return The C string
     */
    const char* c_str() const;
    /**
     * Resizes the string to a length of n characters.
     */
    void        resize(size_t n);

    /**
     * Compares the string to s.
     * 
     * @return true if equivalent, false if not
     */
    bool        compare(const char* s) const;
    /**
     * Compares the string to str.
     * 
     * @return true if equivalent, false if not
     */
    bool        compare(const String& str) const;

    String&     operator=(const String& str); //!< Assignment operator.
    /**
     * Appends s to the string.
     * 
     * @return A reference to the resulting String.
     */
    String&     operator+=(const char* s);
    /**
     * Appends c to the string.
     * 
     * @return A reference to the resulting String.
     */
    String&     operator+=(unsigned char c);
    /**
     * Compares the string to s.
     * 
     * @return true if equivalent, false if not
     */
    bool        operator==(const char* s) const;
    /**
     * Compares the string to str.
     * 
     * @return true if equivalent, false if not
     */
    bool        operator==(const String& str) const;

private:
    void*       impl_data; //!< Pointer to internal implementation data
};

class Object;
class Value
{
public:
    typedef int (*SerializeCallback)(const String&, void*);
    typedef Value const&(*NullAccessCallback)(ValueType, const Value *, void *);

    Value();
    Value(ValueType type);
    Value(bool value);
    Value(int64_t value);
    Value(uint64_t value);
    Value(double value);
    Value(const String& value);
    Value(const Array& value);
    Value(const Object& value);
    Value(const Value& value);
    ~Value();

    void        toString(String& string); //!< Returns a string representation.
    void        swap(Value& value);
    void        clear();

    size_t      count();

    ValueType   getType() const;

    /**
     * Set the type
     * 
     * @param[in] type - The type to set the value to.
     */
    void        set(ValueType type);
    /**
     * Set the value to a boolean
     * 
     * @param[in] value - New value
     */
    void        set(bool value);
    /**
     * Set the value to a long integer(64 bits)
     * 
     * @param[in] value - New value
     */
    void        set(int64_t value);
    /**
     * Set the value to an unsigned long integer(64 bits)
     * 
     * @param[in] value - new value
     */
    void        set(uint64_t value);
    /**
     * Set the value to a double precision float
     * 
     * @param[in] value - New value
     */
    void        set(double value);
    /**
     * Set the value to a String
     * 
     * @param[in] value - New value
     */
    void        set(const String& value);

    void        set(const Array& value);
    void        set(const Object& value);
    void        set(const Value& value);

    int         setNullAccessCallback(NullAccessCallback cb, void *param2);

    void        getRoot() const;
    bool&       getBoolean() const;
    int64_t&    getInteger() const;
    uint64_t&   getUInteger() const;
    double&     getReal() const;
    String&     getString() const;
    Array&      getArray() const;
    Object&     getObject() const;
    Value&      getValue(size_t param1) const;
    Value&      getValue(const String& name) const;

    bool*       referBoolean();
    int64_t*    referInteger();
    uint64_t*   referUInteger();
    double*     referReal();
    Array*      referArray();
    Object*     referObject();
    Value*      referValue(size_t param1);
    Value*      referValue(const String& name);

    void        serialize(const String& param1, SerializeCallback cb, void* param3);
    void        serialize(const String& param1);

    Value&      operator=(const Value& value);
    int         operator[](const String& param1) const;
    int         operator[](const char* param1) const;
    int         operator[](const size_t& param1) const;
    operator    bool() const;

private:
    Value*      unk_0x0;        //!< Unknown.
    void*       nullAccessCB;   //!< The value's NullAccessCallback.
    union                       //!< Union of different types of values
    {
    bool        boolean;
    int64_t     integer;
    uint64_t    uinteger;
    double      real;
    String*     string;
    Array*      array;
    Object*     object;
    };
    char        unk_0x10[0x4];  //!< Unknown.
    ValueType   type;           //!< The type of the value.
};

class Object
{
public:
    /**
     * Name-Value Pair of json element
     */
    class Pair
    {
    public:
        Pair();
        Pair(const String& name, const Value& value);
        ~Pair();

        String      name;   //!< Name assigned to the property
        char        unk[4]; //!< Unknown
        Value       data;   //!< %Value assigned to the property
    };
    class iterator
    {
    public:
        iterator();
        iterator(const iterator& iter);
        ~iterator();

        /**
         * Advance the iterator
         * 
         * @param[in] adv - Number by which to advance.
         */
        void        advance(size_t adv);

        iterator&   operator=(const iterator& iter); 
        void        operator++(int adv);             //!< Increment the iterator by adv
        void        operator++();                    //!< Increment the iterator
        Pair        operator*() const;               //!< Value the 
        bool        operator==(iterator iter) const;
        bool        operator!=(iterator iter) const;
        Pair*       operator->() const;

    private:
        void*       impl_data;
    };

    Object();
    Object(const Object &obj);
    ~Object();

    /**
     * Returns an iterator to the first child element
     * 
     * @return The iterator
     */ 
    iterator    begin() const;
    /**
     * Returns an iterator to after the last child element
     * 
     * @return The iterator
     */
    iterator    end() const;
    void        clear();
    void        erase(const String& str);
    void        insert(const Pair& p);
    Value&      find(const String& str) const;

    size_t      size() const;

    bool        empty() const;
    
private:
    void* impl_data; //!< Pointer to internal implementation data
};

class Parser
{
public:
    typedef int (*ParseCallback)(char&, void*);

    static int  parse(Value &val, ParseCallback cb, void* data);

    /**
     * Parses a string buffer
     * @param[out] val  - Reference to the Value the data is written to.
     * @param[in]  buf  - String buffer to parse
     * @param[in]  size - Size of buf
     * 
     * @return 0 on success, <0 on error.
     */
    static int  parse(Value& val, const char* buf, size_t size);

    /**
     * Parse a json file
     * 
     * @param[out] val  - Reference to the Value the data is written to.
     * @param[in]  path  - Path to the json file.
     * 
     * @return 0 on success, <0 on error.
     */
    static int  parse(Value& val, const char* path);
};

} /* namespace Json */
} /* namespace sce  */

#endif /* _PSP2_JSON_H */
