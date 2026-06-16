#include "Fabric.h"

FabricDetails CreateFabricDetails(const std::string& name, const std::string& type, const std::vector<SizeRatio>& sizeRatios, int width, int length) {
    FabricDetails details;
    details.name = name;
    details.type = type;
    details.sizeRatios = sizeRatios;
    details.width = width;
    details.length = length;
    return details;
}

FabricDetails getFabricDetails() {
    return CreateFabricDetails("Cotton", "Natural", {{"S", 10}, {"M", 20}, {"L", 30}}, 100, 200);
}

CString getMyName() {
    return L"ShapeShifter project";
}
