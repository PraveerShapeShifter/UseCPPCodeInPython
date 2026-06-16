from shapeshifter import fabric


def test_default_constructed_fabric_has_sample_details():
    # The default constructor seeds the object with getFabricDetails().
    d = fabric.Fabric().getDetails()
    assert d.name == "Cotton"
    assert d.type == "Natural"
    assert d.width == 100
    assert d.length == 200
    assert [(r.name, r.quantity) for r in d.sizeRatios] == [
        ("S", 10),
        ("M", 20),
        ("L", 30),
    ]


def test_get_name_returns_project_name():
    # Exercises the CString -> str caster through the class method.
    assert fabric.Fabric().getName() == "ShapeShifter project"


def test_fabric_constructed_from_details():
    details = fabric.getFabricDetails()
    f = fabric.Fabric(details)
    assert f.getDetails().name == details.name
    assert f.getDetails().length == details.length
    assert f.getDetails().width == details.width


def test_details_accessor_returns_internal_reference():
    # getDetails() is bound with return_value_policy::reference_internal, so it
    # returns a view into the Fabric's own member rather than a copy: a mutation
    # is visible on the next read.
    f = fabric.Fabric()
    f.getDetails().name = "Linen"
    assert f.getDetails().name == "Linen"
