import unittest
import pyfile2passwd


class File2PasswdTests(unittest.TestCase):

    def test_get_passwd(self):
        fpo = pyfile2passwd.File2Passwd("LICENSE")
        self.assertEqual(fpo.get_passwd(), "1eeb22037fbc98193fbd60f6cad7ec6c")

    def test_get_md5(self):
        fpo = pyfile2passwd.File2Passwd("LICENSE")
        self.assertEqual(fpo.get_md5_hash(), "5cbe034c343ead03a139a598a5d27d55")


if __name__ == '__main__':
    unittest.main()
