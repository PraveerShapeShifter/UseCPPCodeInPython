from shapeshifter import fabric


def test_fabric_details_fields():
    details = fabric.getFabricDetails()
    assert details.name == "Cotton"
    assert details.type == "Natural"
    assert details.width == 100
    assert details.length == 200


def test_size_ratios():
    details = fabric.getFabricDetails()
    ratios = [(r.name, r.quantity) for r in details.sizeRatios]
    assert ratios == [("S", 10), ("M", 20), ("L", 30)]


def test_to_dict_is_json_ready():
    d = fabric.getFabricDetails().to_dict()
    assert d == {
        "name": "Cotton",
        "type": "Natural",
        "sizeRatios": [
            {"name": "S", "quantity": 10},
            {"name": "M", "quantity": 20},
            {"name": "L", "quantity": 30},
        ],
        "width": 100,
        "length": 200,
    }


def test_get_my_name_cstring_conversion():
    assert fabric.getMyName() == "ShapeShifter project"
