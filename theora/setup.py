# setup.py

from distutils.core import setup, Extension

setup(
	name="CuTheora",
	version="0.0.1",
	description="Python Theora Module",
	author="Ignatius Kunjumon",
	author_email="ignatius.kunjumon@gmail.com",
	url="http://ignatius.in/",
	license="GPL",
	ext_modules=[Extension("CuTheora", ["cu_theora.c"],
		library_dirs=["/usr/lib"],
		libraries=['ogg', 'theoraenc', 'theoradec'])]
	)
