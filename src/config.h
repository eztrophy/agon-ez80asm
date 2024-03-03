#ifndef CONFIG_H
#define CONFIG_H

#ifndef CEDEV
#include <stdint.h>
typedef int32_t int24_t;
typedef uint32_t uint24_t;
#endif

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#pragma warning(disable:4996)			// 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead
#pragma warning(disable:4267)			// conversion from 'size_t' to 'int', possible loss of data
#pragma warning(disable:4244)			// conversion from '__int64' to 'uint16_t', possible loss of data
#endif

#define VERSION                       1
#define REVISION                      3
#define ADLMODE_START              true
#define START_ADDRESS           0x40000 // Agon default load address
#define FILLBYTE                   0xFF // Same as ZDS
#define INSTRUCTION_HASHTABLESIZE  2048 // Number of entries in the hashtable
#define FILESTACK_MAXFILES            4 // Maximum simultaneous include 'depth'
#define LINEMAX                     256 // Input line length maximum uint8_t
#define FILENAMEMAXLENGTH            64
#define FILES                         7
#define LOCAL_LABEL_BUFFERSIZE   0x4000 // 16KB local label space
#define GLOBAL_LABEL_TABLE_SIZE    8192 // 8K global labels
#define LOCAL_LABEL_TABLE_SIZE       64 //  64 local labels
#define FILE_BUFFERSIZE            8192 // For each specified input/output file (io.c)
#define LISTING_OBJECTS_PER_LINE      6 // Listing hex 'objects' between PC / Line number
#define TOKEN_MAX                   128 // Token maximum length
#define MAXNAMELENGTH                32 // Maximum name length of labels/macros/mnemonics
#define MAXIMUM_MACROS               64 // Maximum number of macros
#define MACROMAXARGS                  8 // Maximum arguments to a macro
#define MACROARGLENGTH               32 // Maximum length of macro argument
#define CLEANUPFILES               true
#endif // CONFIG_H
