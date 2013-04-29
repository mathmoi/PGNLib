env = Environment()

# Unit test target
unit = env.Clone()
unit.VariantDir('unit/tests', 'tests', duplicate=0)
unit.Append(CFLAGS = ['-g', '-Wall', '-D_DEBUG'])
unit.Append(LIBPATH = ['./libs/UnitTest++'], LIBS='UnitTest++')

unit_target = unit.Program('pgnparser-tests', Glob('unit/tests/*.cpp'))

# We create a test alias to run unit tests
test_target = Alias('test', [unit_target], unit_target[0].abspath)
AlwaysBuild(test_target)

# We nedd to tell SCons to clean up the build folders on during clean.
Clean(unit_target, 'unit')

# Definition of alias and the default target
Alias('unit', unit_target)
Default('test')
