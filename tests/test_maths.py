from shapeshifter import maths


def test_add():
    assert maths.add_Numbers(5, 10) == 15
    assert maths.add_Numbers(-5, 5) == 0


def test_multiply():
    assert maths.multiply_Numbers(5, 10) == 50
    assert maths.multiply_Numbers(7, 0) == 0


def test_subtract():
    assert maths.subtract_Numbers(10, 5) == 5
    assert maths.subtract_Numbers(5, 10) == -5
