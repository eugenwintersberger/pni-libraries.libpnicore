#!/usr/bin/env python

import unittest
import ShapeTest


suite = unittest.TestSuite()
suite.addTests(unittest.defaultTestLoader.loadTestsFromModule(ShapeTest))

runner = unittest.TextTestRunner()
result = runner.run(suite)

