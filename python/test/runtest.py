#!/usr/bin/env python

import unittest
import ShapeTest
import IndexTest
import ScalarTest
import ArrayTest


suite = unittest.TestSuite()
suite.addTests(unittest.defaultTestLoader.loadTestsFromModule(ShapeTest))
suite.addTests(unittest.defaultTestLoader.loadTestsFromModule(IndexTest))
suite.addTests(unittest.defaultTestLoader.loadTestsFromModule(ScalarTest))
suite.addTests(unittest.defaultTestLoader.loadTestsFromModule(ArrayTest))

runner = unittest.TextTestRunner()
result = runner.run(suite)

