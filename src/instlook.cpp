/***********************************************************************
 *
 *		INSTLOOKUP.C
 *		Instruction Table Lookup Routine for 68000 Assembler
 *
 *    Function: instLookup()
 *		Parses an instruction and looks it up in the instruction
 *		table. The input to the function is a pointer to the
 *		instruction on a line of assembly code. The routine
 *		scans the instruction and notes the size code if
 *		present. It then (binary) searches the instruction
 *		table for the specified opcode. If it finds the opcode,
 *		it returns a pointer to the instruction table entry for
 *		that instruction (via the instPtrPtr argument) as well
 *		as the size code or 0 if no size was specified (via the
 *		sizePtr argument). If the opcode is not in the
 *		instruction table, then the routine returns INV_OPCODE.
 *		The routine returns an error value via the standard
 *		mechanism.
 *
 *	 Usage:	char *instLookup(p, instPtrPtr, sizePtr, errorPtr)
 *		char *p;
 *		instruction *(*instPtrPtr);
 *		char *sizePtr;
 *		int *errorPtr;
 *
 *	Errors: SYNTAX
 *		INV_OPCODE
 *		INV_SIZE_CODE
 *
 *      Author: Paul McKee
 *		ECE492    North Carolina State University
 *
 *        Date:	9/24/86
 *
 *    Modified: Charles Kelly
 *              Monroe County Community College
 *              http://www.monroeccc.edu/ckelly
 *
 ************************************************************************/

#include <cstdio>
#include <cctype>
#include "../include/asm.h"
#include "../include/symbol.h"
#include "../include/build.h"
#include "../include/macro.h"

#include <map>
#include <string>

//extern instruction instTable[];
//extern int tableSize;
extern int macroFP;            // location of macro in input file
extern char buffer[256];  //ck used to form messages for display in windows
extern bool BITflag;
extern bool pass2;

instruction asmMac = { "ASMMACRO", NULL, 0, false, asmMacro };

char* instLookup(char *p, instruction *(*instPtrPtr), char *sizePtr,
		int *errorPtr) {
	char opcode[SIGCHARS + 1];
	symbolDef *symbol;

	try {
		/*	printf("InstLookup: Input string is \"%s\"\n", p); */
		int i = 0;
		do {
			if (i < SIGCHARS)
				opcode[i++] = *p;
			p++;
		} while (isalnum(*p) || *p == '_' || *p == '-');
		opcode[i] = '\0';
		if (*p == '.')
			if (isspace(p[2]) || !p[2]) {
				if (p[1] == 'B')
					*sizePtr = BYTE_SIZE;
				else if (p[1] == 'W' || isspace(p[1]))  // *ck 12-8-2005
					*sizePtr = WORD_SIZE;
				else if (p[1] == 'L')
					*sizePtr = LONG_SIZE;
				else if (p[1] == 'S')
					*sizePtr = SHORT_SIZE;
				else {
					*sizePtr = 0;
					NEWERROR(*errorPtr, INV_SIZE_CODE);
				}
				p += 2;
			} else {
				NEWERROR(*errorPtr, SYNTAX);
				return (NULL);
			}
		else if (!isspace(*p) && *p) {
			NEWERROR(*errorPtr, SYNTAX);
			return (NULL);
		} else
			*sizePtr = 0;

//		int lo = 0;
//		int hi = tableSize - 1;
//		int mid = (hi + lo) / 2;
//
//		// search for opcode in instTable
//		int cmp = 0;
//		do {
//			mid = (hi + lo) / 2;
//			cmp = strcmp(opcode, instTable[mid].mnemonic);
//			if (cmp > 0)
//				lo = mid + 1;
//			else if (cmp < 0)
//				hi = mid - 1;
//		} while (cmp && (hi >= lo));

//		if ( auto instrIter{ instTable.find( "key" ) }; instrIter != std::end( instTable ) ) {
//		// if opcode found
////		if (!cmp) {
////			// if bitfield instruction and BITflag is false
////			if (instTable[mid].flavorPtr
////					&& instTable[mid].flavorPtr->exec == bitField && !BITflag) {
////				NEWERROR(*errorPtr, INV_OPCODE);        // error invalid opcode
////				return (NULL);
////			}
////			*instPtrPtr = &instTable[mid];
////			return (p);
//			const auto&[ key, value ] { *instrIter };
//			instruction instr = value;
//			if (instr.flavorPtr && instr.flavorPtr->exec == bitField && !BITflag) {
//				NEWERROR(*errorPtr, INV_OPCODE);        // error invalid opcode
//				return (NULL);
//			}
//			*instPtrPtr = &instr;
//			return (p);
			// else, opcode not found
//		} else {
//
//			// search for matching macro definition in symbol table
//			symbol = lookup(opcode, false, errorPtr);
//			if ((*errorPtr < ERRORN) && (symbol->flags & MACRO_SYM)) { // if found
//				if (pass2 && !(symbol->flags & BACKREF)) // if forward reference
//					NEWERROR(*errorPtr, FORWARD_REF);     // warning
//				*instPtrPtr = &asmMac;   // point to asmMac function description
//				macroFP = symbol->value;  // get file pointer to macro
//				return (p);                // return pointer to macro parameters
//			} else {
//
//				// not a macro call either, so must be invalid opcode
//				NEWERROR(*errorPtr, INV_OPCODE);
//				return (NULL);
//			}
//		}
	} catch (...) {
		NEWERROR(*errorPtr, EXCEPTION);
		sprintf(buffer,
				"ERROR: An exception occurred in routine 'instLookup'. \n");
		return (NULL);
	}
}
