"""Quick manual smoke test. The real regression suite lives in tests/ (pytest)."""

from shapeshifter import fabric, maths

print(maths.__file__)
print(fabric.__file__)

print("The result of adding 5 and 10 is:", maths.add_Numbers(5, 10))
print("The result of multiplying 5 and 10 is:", maths.multiply_Numbers(5, 10))
print("The result of subtracting 5 from 10 is:", maths.subtract_Numbers(10, 5))

fabricDetails = fabric.getFabricDetails()
print("Fabric Name:", fabricDetails.name)
print("Fabric Type:", fabricDetails.type)
print("Size Ratios:")
for sizeRatio in fabricDetails.sizeRatios:
    print(f"  Size: {sizeRatio.name}, Quantity: {sizeRatio.quantity}")

print(f"Fabric length : {fabricDetails.length}")
print(f"Fabric width : {fabricDetails.width}")

print("As dict:", fabricDetails.to_dict())
print("Project Name:", fabric.getMyName())
