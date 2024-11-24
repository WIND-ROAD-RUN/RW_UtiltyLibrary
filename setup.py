from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import pybind11
import os
import subprocess

class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_args = [
            f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}',
            f'-DPYTHON_EXECUTABLE={os.sys.executable}',
            f'-DCMAKE_TOOLCHAIN_FILE={os.path.join(os.getenv("VCPKG_ROOT", ""), "scripts", "buildsystems", "vcpkg.cmake")}'
        ]
        build_args = ['--config', 'Release']
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp)
        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        super().__init__(name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)

setup(
    name='example',
    version='1.0',
    ext_modules=[CMakeExtension('example')],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)