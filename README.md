# agon-ez80asm
## Installation and requirements
Download the latest binaries from the [releases](https://github.com/envenomator/agon-ez80asm/releases) page and place both 'ez80asm.bin' and 'ez80asm.ldr' in the /mos/ directory of your microSD card. This enables the assembler to be loadable as a regular MOS command.

The assembler requires MOS 1.03 at minimum. 
## Usage

    ez80asm <filename> [output filename] [OPTION]
    -v List version information
    -h List help information
    -o Org start address in hexadecimal format, default is 40000
    -b Fillbyte in hexadecimal format, default is FF
    -a ADL mode 1/0, default is 1
    -l Listing to file with .lst extension
    -s Export symbols
    -d Direct listing to console

The given filename will be assembled into these files:
- filename.bin -- output executable file
- filename.lst -- output assembler listing (optionally selected by -l flag)
- filename.symbols -- symbol export when the -s option is used

## Defaults

The compiler defaults to ADL=1 mode. This can be overridden using the .ASSUME directive.

The default address is 0x40000.

## Source file format
Lines in the source file should have the following format:

    [Label:] [Operator] [Operand] [;Comment]

All fields are optional.

- Labels are defined as first token on a line, terminated by a colon (':')
- Operators are either Assembler directives, or ez80 opcodes. Opcodes without a label should start with whitespace. Assembler directives can start with a dot (.)
- Comments start with a semi-colon (;). A line with just a comment can start without whitespace

Examples

    LABEL:                  ; Label without operator
    LABEL:LD A,B            ; operator after label without whitespace
    LABEL: LD A,B           ; operator after label with whitespace
     LD A,B                     ; operator without label, starting with whitespace
    ; comment on empty line

## Global labels

Global labels are reachable in the entire source file and cannot have the same name as ez80 mnemonics, nor assembler directives.

Global labels are case-sensitive.
## Local labels
Local labels start with the '@' symbol, terminated by a colon (':') and define a temporary label between two global labels. As soon as a new global label starts, all local labels become out of scope and a new scoped local label space starts.

64 local labels are currently supported in each scope.

Local labels are case-sensitive.

## Anonymous labels
Anonymous labels are labeled '@@', terminated by a colon (':') and define a temporary label. As soon as a new anonymous label is defined, the previous is no longer reachable.
Code can use @f/@n or @b/@p, to get the label in the FORWARD/NEXT, or BACKWARD/PREVIOUS direction.

## Numeric constants

The following formats are supported:

- Hexadecimal - constants starting with 0x, $, or #
- Hexadecimal - constants ending with h
- Binary - constants starting with 0b or %
- Binary - constants ending with b
- Decimal

Examples:

    $0A     ; Hex
    0x0A    ; Hex
    #0A     ; Hex
    0Ah     ; Hex
    0Bh     ; Hex (not binary - 'h' suffix takes priority over '0B' prefix)
    0b1010  ; Bin
    1010b   ; Bin
    %1010   ; bin
    10      ; Dec

$ represents the current program counter

## Character constants
Character constants are surrounded by single quotes. Supported escape sequences are:

\\n - newline

\\r - carriage return

\\t - tab

\\b - backspace

\\\ - backslash

\\' - single quote

\\" - double quote

Examples:

    DB 'a'  ; Defines byte with hex value 61
    DB 'B'  ;                   hex value 41
    DB '\n' ;                   hex value 0A

## String expressions
Strings are defined as literal characters surrounded by double quotes. The supported character escape sequence constants are supported in strings as well.

Examples:

    DB "Test"   ; Outputs hex values 54, 65, 73, 74
    DB "Test",0 ; Outputs hex values 54, 65, 73, 74, 0
    DB "Test\n" ; Outputs hex values 54, 65, 73, 74, 0A
## Supported Assembler directives
All assembler directives can be used with, or without leading dot (.)

| Directive              | Description                                                                        | Usage                                                                                                                                                                                                                                                                                                                                                                     |
|------------------------|------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| ALIGN                  |  Select alignment for the program counter, pad bytes up to new boundary alignment  | ALIGN \<boundary\>  The boundary, expressed in bytes, must be a power of two (1,2,4,8 etc)  Example: ALIGN 256 ; align next instruction at boundary of 256                                                                                                                                                                                                                |
| ASSUME ADL             | Sets default ADL status (0 or 1)                                                   | Example: ASSUME ADL=1 ; set ADL mode to 1                                                                                                                                                                                                                                                                                                                                 |
| BLKB/BLKW/ BLKP/BLKL   | Allocate a block with a number of Bytes/ 16-bit words/24-bit Pointers/32-bit words | BLKx \<number\> [, value]  Example: BLKB 16 ; allocate 16 uninitialized bytes Example: BLKB 16, 0xFF ; allocate 16 bytes and initialize them to 0xFF                                                                                                                                                                                                                      |
| DB / DEFB ASCII / BYTE | Define byte(s)                                                                     | DB \| DEFB \| ASCII \| BYTE \<value \| string\> [, ...]  Reserve and initialize a byte, or a list of bytes. Within a string, these escape characters are supported and converted to their respective ascii code: \ \r \t \b \\\ \\' \\"  Strings are not automatically terminated by a null byte. You can use either an additional ',0' value, or use the ASCIZ directive |
| ASCIZ                  | Same as above, but terminated with a 0 Used for zero-terminated strings mostly     | ASCIZ \<value \| string\> [, ...]                                                                                                                                                                                                                                                                                                                                         |
| DW / DEFW              | Define 16-bit word(s)                                                              | DW \| DEFW \<value\> [, ...]  Reserve and initialize a word/long value, or a list of values                                                                                                                                                                                                                                                                               |
| DL / DW24              | Define 24-bit word(s)                                                              | DL \| DW24 \<value\> [, ...]                                                                                                                                                                                                                                                                                                                                              |
| DW32                    | Define 32-bit word(s)                                                              | DW32 \<value\> [, ...]                                                                                                                                                                                                                                                                                                                                              |
| DS / DEFS              | Defines storage location in bytes                                                  | DS \| DEFS \<number\> [, value]  Example: DS 10 ; reserve 10 byte, no reserved value Example: DS 10, 0xFF ; reserve 10 bytes, all value 0xFF                                                                                                                                                                                                                              |
| EQU                    | Assign symbolic name to label                                                      | Example: LABEL: EQU 0xFF                                                                                                                                                                                                                                                                                                                                                  |
| FILLBYTE               | Change the byte value that is used for filling unused space                        | FILLBYTE \<value\>                                                                                                                                                                                                                                                                                                                                                        |
| INCBIN                 | Include binary file                                                                | Allows the insertion of binary data from another file  Example: INCBIN "sprite.bin"                                                                                                                                                                                                                                                                                       |
| INCLUDE                | Include file in source code                                                        | Allows the insertion of source code from another file into the current source file during assembly. The included file is assembled into the current source file immediately after the directive. When the EOF (End of File) of the included file is reached, the assembly resumes on the line after the INCLUDE directive  Example: INCLUDE "example.inc"                 |
| MACRO / ENDMACRO       | Define a macro, see below for detailed explanation                                 | MACRO [arg1, arg2 ...]  [macro body] ENDMACRO                                                                                                                                                                                                                                                                                                                             |
| ORG                    | Define location counter origin. No padding.                                        | Sets the assembler location counter to a specified value. The directive must be followed by an integer constant, which is the value of the new origin. Example: ORG $40000                                                                                                                                                                                                |

## Macros
The 'macro' directive defines a macro, optionally followed by a maximum of 8 arguments. The following lines will be stored as the macro-body, until the 'endmacro' directive is encountered. A macro have to be defined before use.

Macro names have a maximum length of 16 characters.

Example macro definition without arguments:

        macro addhla ; start of macro definition
        add a,l
        jr nc, @1
        inc h
    @1:
        ld l,a
        endmacro    ; end of macro definition

Global labels are not allowed in macro definitions, but local/anonymous labels are.

Example macro with arguments:

        macro pointless arg1, arg2
        add a, arg1
        add l, arg2
        endmacro

Example macro usage / expansion later in the code:

        pointless 10, 15
        ; will expand to add a, 10
        ;                add l, 15

## Simple conditional assembly support
The assembler supports simple conditional assembly using if/else/endif assembler directives. There is no support for nested conditions.

The 'if' directive assesses the value of the given value, usually a label. When this is non-zero, the lines following the directive are assembled up to the 'else' or 'endif' statement. If the value is zero, any lines after an appearing 'else' statement are assembled up to the 'endif' statement.

## Known limitations

- Operators in expressions currently have no precendence other than left-to-right and parenthesis aren't supported yet. So be careful using more than one operator in an expression

## Platform targets and building from source
While AgonLight is the primary target platform, in order to have easy access to the regular cadre of Unix tools in developing and testing, a small MOS abstraction layer is provided that takes care of abstracting the MOS file API calls to Unix file API calls. This layer also takes care of the differences in file handling and file structures between both platforms.

It appears there is some demand for people to use the assembler on their platform of choice and cross-assemble sources from there to the ez80. I'll not provide direct support for other platforms than Agon, but I have adopted a number of changes to the build scripts, kindly provided by Rob Prouse, to facilitate building on other platforms such as MacOS/Windows. You'll probably see warnings and/or errors on non-Linux builds because I don't test my code on these platforms.