# setup.py

from distutils.core import setup, Extension

setup(
	name="CuOgg",
	version="0.0.1",
	description="Python Ogg Module",
	author="Ignatius Kunjumon",
	author_email="ignatius.kunjumon@gmail.com",
	url="http://ignatius.in/",
	license="GPL",
	ext_modules=[Extension("CuOgg", ["cu_ogg.c"],
		library_dirs=["/usr/lib"],
		libraries=['ogg'])]
	)
