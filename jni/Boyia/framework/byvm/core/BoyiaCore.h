/*
============================================================================
 Name        : BoyiaCore.h
 Author      : yanbo
 Version     : BoyiaCore v0.1
 Copyright   : All Copyright Reserved
 Date        : 2012-2-5
 Description : Support Original
============================================================================
*/

#ifndef BoyiaCore_h
#define BoyiaCore_h

#include "BoyiaValue.h"

typedef struct {
	LInt             mFuncBody;
	BoyiaValue*       mParams;
	LInt             mParamSize;
	LInt             mParamCount;
} BoyiaFunction;

typedef struct {
	LUint mNameKey;
	LInt (*mAddr)();
} NativeFunction;

typedef struct {
	NativeFunction* mFun;
	LInt mSize;
} NativeFunMap;

LVoid CompileCode(char* code, LVoid* fun);
LVoid CallFunction(char* funcCall, LVoid* ret);
LInt GetLocalSize();
LVoid* GetLocalValue(LInt idx);
LVoid SetNativeResult(LVoid* result);
LVoid GetLocalStack(LInt* stack, LInt* size);
LVoid* GetNativeResult();
LVoid* CopyObject(LUint hashKey, LInt size);
//LUint HashCode(BoyiaStr* str);
LVoid ValueCopy(BoyiaValue* dest, BoyiaValue* src);
//LBool MStrcmp(BoyiaStr* src, BoyiaStr* dest);
LVoid GetGlobalTable(LInt* table, LInt* size);
LVoid NativeCall(BoyiaValue* obj);
LVoid LocalPush(BoyiaValue *value);
LVoid SaveLocalSize();

#endif
