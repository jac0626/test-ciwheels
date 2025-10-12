try:
    from ._version import __version__
except ImportError:
    __version__ = "0.0.0"

try:
    from ._hello import hello
except ImportError:
    def hello():
        return "Hello (Python fallback)"

__all__ = ['hello', '__version__']
