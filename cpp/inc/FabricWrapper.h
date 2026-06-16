#ifndef SHAPESHIFTER_FABRIC_WRAPPER_H
#define SHAPESHIFTER_FABRIC_WRAPPER_H

#include <utility>  // std::move

#include "Fabric.h"  // vendored: SizeRatio, FabricDetails, getFabricDetails(), getMyName()

// Project-owned convenience wrapper around the vendored fabric functions.
// Lives in cpp/inc (not cpp/vendor) because it is our code, not upstream's.
class Fabric {
public:
    // Default-constructs with the sample fabric so the object is usable out of the box.
    Fabric() : m_details(getFabricDetails()) {}
    explicit Fabric(FabricDetails details) : m_details(std::move(details)) {}

    const FabricDetails& getDetails() const { return m_details; }

    // Returns CString; the binding layer's cstring_caster.h converts it to a Python str.
    CString getName() const { return getMyName(); }

private:
    FabricDetails m_details;
};

#endif // SHAPESHIFTER_FABRIC_WRAPPER_H
