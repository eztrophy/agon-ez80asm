#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <stdarg.h>
#include "assemble.h"
#include "globals.h"
#include "utils.h"
#include "label.h"
#include "str2num.h"

// parses the given string to the operand, or throws errors along the way
// will destruct parts of the original string during the process
void parse_operand(char *string, operand *operand) {
    char *ptr = string;
    uint8_t len = strlen(string);

    // defaults
    operand->type = OP_EMPTY;
    operand->reg = 0;
    operand->displacement = 0;
    operand->immediate = 0;
    // direct or indirect
    if(*ptr == '(') {
        operand->indirect = true;
        // find closing bracket or error out
        if(string[len-1] == ')') string[len-1] = 0; // terminate on closing bracket
        else error(message[ERROR_CLOSINGBRACKET]);
        ptr = &string[1];
    }
    else {
        operand->indirect = false;
        // should not find a closing bracket
        if(string[len-1] == ')') error(message[ERROR_OPENINGBRACKET]);
    }

    switch(*ptr++) {
        case 0: // empty operand
            break;
        case 'a':
            switch(*ptr++) {
                case 0:
                    operand->type = OP_R;
                    operand->reg = R_A;
                    return;
                case 'f':
                    switch(*ptr++) {
                        case 0:
                        case '\'':
                            operand->type = OP_RR;
                            operand->reg = RR_AF;
                            if(operand->indirect) error(message[ERROR_INVALIDREGISTER]);
                            return;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 'b':
            switch(*ptr++) {
                case 0:
                    operand->type = OP_R;
                    operand->reg = R_B;
                    return;
                case 'c':
                    if(*ptr == 0) {
                        if(operand->indirect) operand->type = OP_INDIRECT_RR;
                        else operand->type = OP_RR;
                        operand->reg = RR_BC;
                        return;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 'c':
            switch(*ptr++) {
                case 0:
                    operand->type = OP_R;
                    operand->reg = R_C;
                    return;
                default:
                    break;
            }
            break;
        case 'd':
            switch(*ptr++) {
                case 0:
                    operand->type = OP_R;
                    operand->reg = R_D;
                    return;
                case 'e':
                    switch(*ptr++) {
                        case 0:
                            if(operand->indirect) operand->type = OP_INDIRECT_RR;
                            else operand->type = OP_RR;
                            operand->reg = RR_DE;
                            return;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 'e':
            switch(*ptr++) {
                case 0:
                    operand->type = OP_R;
                    operand->reg = R_E;
                    return;
                default:
                    break;
            }
            break;
        case 'h':
            switch(*ptr++) {
                case 0:
                    operand->type = OP_R;
                    operand->reg = R_H;
                    return;
                case 'l':
                    if(*ptr == 0) {
                        if(operand->indirect) operand->type = OP_INDIRECT_HL;
                        else operand->type = OP_RR;
                        operand->reg = RR_HL;
                        return;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 'i':
            switch(*ptr++) {
                case 0:
                    operand->type = OP_OTHER;
                    operand->reg = R_I;
                    return;
                case 'x':
                    switch(*ptr++) {
                        case 0:
                            if(operand->indirect) operand->type = OP_INDIRECT_IXY;
                            else operand->type = OP_IXY;
                            operand->reg = RR_IX;
                            return;
                        case 'h':
                            operand->type = OP_IXY;
                            operand->reg = RR_IXH;
                            return;
                        case 'l':
                            operand->type = OP_IXY;
                            operand->reg = RR_IXL;
                            return;
                        case '+':
                            if(isdigit(*ptr)) {
                                operand->displacement = (uint8_t) str2num(ptr);
                                return;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case 'y':
                    switch(*ptr++) {
                        case 0:
                            if(operand->indirect) operand->type = OP_INDIRECT_IXY;
                            else operand->type = OP_IXY;
                            operand->reg = RR_IY;
                            return;
                        case 'h':
                            operand->type = OP_IXY;
                            operand->reg = RR_IYH;
                            return;
                        case 'l':
                            operand->type = OP_IXY;
                            operand->reg = RR_IYL;
                            return;
                        case '+':
                            if(isdigit(*ptr)) {
                                operand->displacement = (uint8_t) str2num(ptr);
                                return;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 'l':
            switch(*ptr++) {
                case 0:
                    operand->type = OP_R;
                    operand->reg = R_L;
                    return;
                default:
                    break;
            }
            break;
        case 'm':
            if((*ptr == 'b') && ptr[1] == 0) {
                operand->type = OP_OTHER;
                operand->reg = RR_MB;
                return;
            }
            break;
        case 'r':
            if(*ptr == 0) {
                operand->type = OP_OTHER;
                operand->reg = R_R;
                return;
            }
        case 's':
            if((*ptr == 'p') && ptr[1] == 0) {
                if(operand->indirect) operand->type = OP_INDIRECT_SP;
                else operand->type = OP_RR;
                operand->reg = RR_SP;
                return;
            }
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '$':
        case 'f':
            operand->immediate = str2num(ptr-1);
            return;
        default:
            break;
    }
    if(*string) { // not on empty lines
        // check for hex string that ends with 'h'
        if(string[strlen(string)-1] == 'h') operand->immediate = str2num(string);
        else error(message[ERROR_INVALIDREGISTER]);
    }
}

enum {
    STATE_LINESTART,
    STATE_MNEMONIC,
    STATE_SUFFIX,
    STATE_OPERAND1,
    STATE_OPERAND2,
    STATE_COMMENT,
    STATE_DONE,
    STATE_MISSINGOPERAND
};

void parse(char *line) {
    uint8_t state;
    char *ptr;
    char *token;
    char *tstart;

    currentline.label[0] = 0;
    currentline.mnemonic[0] = 0;
    currentline.suffix_present = false;
    currentline.suffix[0] = 0;
    currentline.operand1[0] = 0;
    currentline.operand2[0] = 0;
    currentline.comment[0] = 0;
    currentline.size = 0;

    state = STATE_LINESTART;

    while(1) {
        switch(state) {
            case STATE_LINESTART:
                ptr = line;
                while(isspace(*ptr) != 0) ptr++; // skip over whitespace
                tstart = ptr;
                if(isalnum(*ptr)) {
                    state = STATE_MNEMONIC;
                    token = currentline.mnemonic;
                    break;
                }
                if(*ptr == ';') {
                    token = currentline.comment;
                    state = STATE_COMMENT;
                    ptr++;
                    break;
                }
                state = STATE_DONE; // empty line
                break;
            case STATE_MNEMONIC:
                switch(*ptr) {
                    case 0:
                        *token = 0;
                        state = STATE_DONE;
                        break;
                    case ';':
                        *token = 0;
                        token = currentline.comment;
                        state = STATE_COMMENT;
                        ptr++;
                        break;
                    case ':':
                        // token proves to be a label after all
                        *token = 0; // close string
                        *ptr = 0;
                        strcpy(currentline.label, tstart);
                        currentline.mnemonic[0] = 0; // empty mnemonic again
                        ptr++;
                        while(isspace(*ptr) != 0) ptr++; // skip over whitespace
                        token = currentline.mnemonic;
                        // no change in state - MNEMONIC expected
                        break;
                    case '.':
                        *token = 0; // terminate token string
                        state = STATE_SUFFIX;
                        ptr++;
                        while(isspace(*ptr) != 0) ptr++; // skip over whitespace
                        token = currentline.suffix;
                        break;
                    case ',':
                        state = STATE_MISSINGOPERAND;
                        break;
                    default:
                        if(isspace(*ptr) == 0) *token++ = *ptr++;
                        else {
                            // close out token
                            *token = 0;
                            ptr++;
                            while(isspace(*ptr) != 0) ptr++; // skip over whitespace
                            token = currentline.operand1;
                            state = STATE_OPERAND1;
                        }
                }
                break;
            case STATE_SUFFIX:
                if(*ptr == ',') {
                    state = STATE_MISSINGOPERAND;
                    break;
                }
                if(isspace(*ptr) == 0) {
                    *token++ = *ptr++;
                }
                else {
                    // close out token
                    *token = 0;
                    ptr++;
                    while(isspace(*ptr) != 0) ptr++; // skip over whitespace
                    token = currentline.operand1;
                    state = STATE_OPERAND1;
                }
                break;
            case STATE_OPERAND1:
                switch(*ptr) {
                    case 0:
                        *token = 0;
                        state = STATE_DONE;
                        break;
                    case '.':
                    case ':':
                        state = ERROR_INVALIDOPERAND;
                        break;
                    case ',':
                        *token = 0;
                        ptr++;
                        while(isspace(*ptr) != 0) ptr++; // skip over whitespace
                        token = currentline.operand2;
                        state = STATE_OPERAND2;
                        break;
                    case ';':
                        *token = 0;
                        ptr++;
                        token = currentline.comment;
                        state = STATE_COMMENT;
                        break;
                    default:
                        *token++ = *ptr++;
                        while(isspace(*ptr) != 0) ptr++; // skip over whitespace
                }
                break;
            case STATE_OPERAND2:
                switch(*ptr) {
                    case 0:
                        *token = 0;
                        state = STATE_DONE;
                        break;
                    case '.':
                    case ':':
                    case ',':
                        state = ERROR_INVALIDOPERAND;
                        break;
                    case ';':
                        *token = 0;
                        ptr++;
                        token = currentline.comment;
                        state = STATE_COMMENT;
                        break;
                    default:
                        *token++ = *ptr++;
                        while(isspace(*ptr) != 0) ptr++; // skip over whitespace
                }
                break;
            case STATE_COMMENT:
                if((*ptr != 0) && (*ptr != '\r') && (*ptr != '\n')) *token++ = *ptr++;
                else {
                    *token = 0;
                    state = STATE_DONE;
                }
                break;
            case STATE_DONE:
                parse_operand(currentline.operand1, &operand1);
                parse_operand(currentline.operand2, &operand2);
                return;
            case STATE_MISSINGOPERAND:
                error(message[ERROR_MISSINGOPERAND]);
                state = STATE_DONE;
                break;
        }
    }
}

void definelabel(uint8_t size){
    // add label to label if defined
    if(strlen(currentline.label)) {
        if(label_table_insert(currentline.label, address) == false){
            error("Out of label space");
        }
    }
    address += size;
}

// return ADL prefix code, or 0 if none present
uint8_t getADLsuffix(adltype allowed) {
    uint8_t code=0;

    if(currentline.suffix_present) {
        switch(strlen(currentline.suffix)) {
            case 1: // .s or .l
                switch(currentline.suffix[0]) {
                    case 's':
                        if(adlmode) code=0x52;    // SIL
                        else code=0x40;           // SIS
                        break;
                    case 'l':
                        if(adlmode) code=0x5B;    // LIL
                        else code=0x49;           // LIS
                        break;
                    default: // illegal suffix
                        break;
                }
                break;
            case 2: // .is or .il
                if(currentline.suffix[0] != 'i') break; // illegal suffix
                switch(currentline.suffix[1]) {
                    case 's':
                        if(adlmode) code=0x49;    // LIS
                        else code=0x40;           // SIS
                        break;
                    case 'l':
                        if(adlmode) code=0x5B;    // LIL
                        else code=0x52;           // SIL
                        break;
                    default: // illegal suffix
                        break;
                }
                break;
            case 3:
                if(currentline.suffix[1] != 'i') break; // illegal suffix
                switch(currentline.suffix[0]) {
                    case 's':
                        if(currentline.suffix[2] == 's') code=0x40;
                        if(currentline.suffix[2] == 'l') code=0x52;
                        // illegal suffix
                        break;
                    case 'l':
                        if(currentline.suffix[2] == 's') code=0x49;
                        if(currentline.suffix[2] == 'l') code=0x5B;
                        // illegal suffix
                        break;
                    default: // illegal suffix
                        break;
                }
                break;
            default: // illegal suffix
                break;
        }
        if(code == 0) error("Illegal ADL suffix");
        // check for allowed suffixes
        switch(allowed) {
            case NONE:
                error("No suffix allowed");
                break;
            case L_ONLY:
                if((code == 0x40) || (code == 0x52)) error("Only .L allowed");
                break;
            case SL_ONLY:
                if((code == 0x40) || (code == 0x5B)) error("No SIS or LIL allowed");
                if((code == 0x49) && adlmode) error("L only allowed in z80 mode");
                if((code == 0x52) && !adlmode) error("S only allowed in ADL mode");
                break;
            case SISLIL:
                if((code == 0x49) || (code == 0x52)) error("No SIL or LIS allowed");
                if((code == 0x40) && (!adlmode)) error("SIS only allowed in ADL mode");
                if((code == 0x5B) && adlmode) error("LIL only allowed in z80 mode");
                break;
            case ANY:
                break;
        }
    }
    return code;
}

void emit_ld_from_immediate(uint8_t prefix, uint8_t opcode, char *valstring) {
    uint8_t suffix;
    uint8_t immsize;
    uint32_t tmp32 = str2num(valstring);

    suffix = getADLsuffix(ANY); // only takes care of illegal suffixes
    if(adlmode) {
        switch(suffix) {
            case 0: // According to mode
                immsize = 3;
                break;
            case 0x40: // SIS
                immsize = 2;
                break;
            default:
                immsize = 0;
                break;
        }
    }
    else {
        switch(suffix) {
            case 0: // According to mode
                immsize = 2;
                break;
            case 0x5B: // LIL
                immsize = 3;
                break;
            default:
                immsize = 0;
                break;
        }
    }
    if(immsize) {
        emit_instruction(immsize, suffix, prefix, opcode);
        if(immsize == 2) emit_16bit(tmp32);
        if(immsize == 3) emit_24bit(tmp32);
    }
    else error("Illegal ADL suffix");
}

void adl_action() {
    if(strcmp(currentline.operand1, "0") == 0) adlmode = false;
    if(strcmp(currentline.operand1, "1") == 0) adlmode = true;
    if(pass == 1) {
        if(debug_enabled) {
            if(adlmode) printf("ADLmode: 1\n");
            else printf("ADLmode: 0\n");
        }
    }
}

void emit_instruction(uint8_t immsize, uint8_t suffix, uint8_t prefix, uint8_t opcode) {
    uint8_t size;

    if(pass == 1) {
        size = immsize + (suffix>0)?1:0 + (prefix>0)?1:0 + 1;
        definelabel(size);
    }
    if(pass == 2) {
        if(suffix) printf("0x%02x-",suffix);
        if(prefix) printf("0x%02x-",prefix);
        printf("0x%02x-",opcode);
    }
}

void emit_8bit(uint8_t value) {
    if(pass == 2) printf("0x%02x\n",value);
}

void emit_16bit(uint16_t value) {
    if(pass == 2) {
        printf("0x%02x-0x%02x\n",value&0xFF, (value>>8)&0xFF);
    }
}

void emit_24bit(uint32_t value) {
    if(pass == 2) {
        printf("0x%02x-0x%02x-0x%02x\n", value&0xFF, (value>>8)&0xFF, (value>>16)&0xFF);
    }
}

void argcheck(bool passed)
{
    if (passed == false)
        error("arguments not correct for mnemonic");
}

void extcheck(bool passed)
{
    if (passed == false)
        error("extension not correct for mnemonic");
}


bool process(void){
    instruction *i;

    // return on empty lines
    if(strlen(currentline.mnemonic) == 0) {
        // check if there is a single label on a line in during pass 1
        if(pass == 1) definelabel(0);
        return true; // valid line, but empty
    }

    if(currentline.mnemonic[0]) {
        i = instruction_table_lookup(currentline.mnemonic);
        if(i == NULL) {
            error(message[ERROR_INVALIDMNEMONIC]);
            return false;
        }
        if(i->type == ASSEMBLER)
        {
            adl_action();
        }
        // NEW PROCESS FUNCTION GOES HERE
        //i->function();
    }
    return true;
}

void print_linelisting(void) {

    printf("Line %04d - \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"", linenumber, currentline.label, currentline.mnemonic, currentline.suffix, currentline.operand1, currentline.operand2, currentline.comment);
    printf("\n");

    printf("Line %04d - %10s %4s - %d %d %d %d %d - %d %d %d %d %d\n",linenumber, currentline.mnemonic, currentline.suffix, operand1.type, operand1.reg, operand1.indirect, operand1.displacement, operand1.immediate, operand2.type, operand2.reg, operand2.indirect, operand2.displacement, operand2.immediate);
    /*
    printf("Line       %04d\n", linenumber);
    printf("Operand1:\n");
    printf("Type:        %02x\n", operand1.type);
    printf("Register:    %02x\n", operand1.reg);
    printf("Indirect:    %02x\n", operand1.indirect);
    printf("d:           %02x\n", operand1.displacement);
    printf("Immediate: %04x\n", operand1.immediate);
    printf("Operand2:\n");
    printf("Type:        %02x\n", operand2.type);
    printf("Register:    %02x\n", operand2.reg);
    printf("Indirect:    %02x\n", operand2.indirect);
    printf("d:           %02x\n", operand2.displacement);
    printf("Immediate: %04x\n", operand2.immediate);
    */
}


void parsed_listing(void) {
    printf("Line       %04d - ", linenumber);
    printf("Operand1:\n");
    printf("Type:        %02x\n", operand1.type);
    printf("Register:    %02x\n", operand1.reg);
    printf("Indirect:    %02x\n", operand1.indirect);
    printf("d:           %02x\n", operand1.displacement);
    printf("Immediate: %04x\n", operand1.immediate);
    printf("Operand2:\n");
    printf("Type:        %02x\n", operand2.type);
    printf("Register:    %02x\n", operand2.reg);
    printf("Indirect:    %02x\n", operand2.indirect);
    printf("d:           %02x\n", operand2.displacement);
    printf("Immediate: %04x\n", operand2.immediate);

}
bool assemble(FILE *infile, FILE *outfile){
    char line[LINEMAX];

    adlmode = true;
    global_errors = 0;

    // Assemble in two passes
    // Pass 1
    printf("Pass 1...\n");
    pass = 1;
    linenumber = 1;
    address = START_ADDRESS;
    while (fgets(line, sizeof(line), infile)){
        parse(line);
        process();
        if(listing_enabled) print_linelisting();
        linenumber++;
    }
    if(debug_enabled) print_label_table();
    printf("%d lines\n", linenumber);
    printf("%d labels\n", label_table_count());
    if(global_errors) return false;

    // Pass 2
    printf("Pass 2...\n");
    rewind(infile);
    pass = 2;
    linenumber = 1;
    address = START_ADDRESS;
    while (fgets(line, sizeof(line), infile)){
        parse(line);
        process();
        linenumber++;
    }
    return true;
}

