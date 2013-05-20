env = Environment()

env.Append(CXXFLAGS = ['-std=c++11', '-Wall']);

# Unit test target
unit = env.Clone()
unit.VariantDir('unit/tests', 'tests', duplicate=0)
unit.VariantDir('unit/src', 'src', duplicate=0)
unit.Append(CXXFLAGS = ['-g', '-D_DEBUG'])
unit.Append(LIBPATH = ['./libs/UnitTest++'], LIBS='UnitTest++')

unit_target = unit.Program('pgnparser-tests', Glob('unit/tests/*.cpp') + Glob('unit/src/*.cpp'))

# profiling target
prof = env.Clone()
prof.VariantDir('prof-bin/prof', 'prof', duplicate=0)
prof.VariantDir('prof-bin/src', 'src', duplicate=0)
prof.Append(CXXFLAGS = ['-O2', '-DNDEBUG', '-pg', '-g', '-fno-omit-frame-pointer', '-fno-inline-functions', '-fno-inline-functions-called-once', '-fno-optimize-sibling-calls'])
prof.Append(LINKFLAGS = ['-pg'])
prof.Append(LIBPATH = ['./libs/UnitTest++'], LIBS='UnitTest++')

prof_target = prof.Program('pgnparser-prof', Glob('prof-bin/prof/*.cpp') + Glob('prof-bin/src/*.cpp'))

# We create a test alias to run unit tests
test_target = Alias('test', [unit_target], unit_target[0].abspath)
AlwaysBuild(test_target)

# We nedd to tell SCons to clean up the build folders on during clean.
Clean(unit_target, 'unit')
Clean(prof_target, 'prof-bin')

# Definition of alias and the default target
Alias('unit', unit_target)
Alias('prof', prof_target)
Default('test')
