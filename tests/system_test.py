import unittest
import pyfile2passwd


class File2PasswdTests(unittest.TestCase):

    def test_get_passwd(self):
        fpo = pyfile2passwd.File2Passwd("LICENSE")
        self.assertEqual(fpo.get_passwd(), "1eeb22037fbc98193fbd60f6cad7ec6d")


if __name__ == '__main__':
    unittest.main()
