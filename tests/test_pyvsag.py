import pyvsag

def test_calculator_add():
    calc = pyvsag.Calculator()
    assert calc.add(5, 3) == 8