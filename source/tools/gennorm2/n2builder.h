/*
*******************************************************************************
*
*   Copyright (C) 2009, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
*******************************************************************************
*   file name:  n2builder.h
*   encoding:   US-ASCII
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 2009nov25
*   created by: Markus W. Scherer
*/

#ifndef __N2BUILDER_H__
#define __N2BUILDER_H__

#include "unicode/utypes.h"
#include "unicode/errorcode.h"
#include "unicode/unistr.h"
#include "toolutil.h"
#include "utrie2.h"

#define DATA_TYPE "nrm"

U_NAMESPACE_BEGIN

extern UBool beVerbose, haveCopyright;

// TODO: move to toolutil library
class IcuToolErrorCode : public ErrorCode {
public:
    IcuToolErrorCode(const char *loc) : location(loc) {}
    virtual ~IcuToolErrorCode();
protected:
    virtual void handleFailure() const;
private:
    const char *location;
};

struct Norm;

class Normalizer2DataBuilder {
public:
    Normalizer2DataBuilder(UErrorCode &errorCode);
    ~Normalizer2DataBuilder();

    enum OverrideHandling {
        OVERRIDE_NONE,
        OVERRIDE_ANY,
        OVERRIDE_PREVIOUS
    };

    void setOverrideHandling(OverrideHandling oh);

    void setCC(UChar32 c, uint8_t cc);
    void setOneWayMapping(UChar32 c, const UnicodeString &m);
    void setRoundTripMapping(UChar32 c, const UnicodeString &m);

    void setUnicodeVersion(const char *v);

private:
    // TODO: no copy, assign, etc.

    Norm *allocNorm();
    Norm *getNorm(UChar32 c);
    Norm *createNorm(UChar32 c);
    Norm *createNormForMapping(UChar32 c);

    UTrie2 *normTrie;
    UToolMemory *normMem;
    Norm *norms;

    int32_t phase;
    OverrideHandling overrideHandling;

    UVersionInfo unicodeVersion;
};

U_NAMESPACE_END

#endif  // __N2BUILDER_H__
