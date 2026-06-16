#ifndef SHAPESHIFTER_VENDOR_FABRIC_H
#define SHAPESHIFTER_VENDOR_FABRIC_H

#include <string>
#include <vector>
#include <atlstr.h>

struct SizeRatio {
    std::string name;
    int quantity;
};

struct FabricDetails {
    std::string name;
    std::string type;
    std::vector<SizeRatio> sizeRatios;
    int width;
    int length;
};

FabricDetails CreateFabricDetails(const std::string& name, const std::string& type, const std::vector<SizeRatio>& sizeRatios, int width, int length);
FabricDetails getFabricDetails();
CString getMyName();

#endif // SHAPESHIFTER_VENDOR_FABRIC_H
