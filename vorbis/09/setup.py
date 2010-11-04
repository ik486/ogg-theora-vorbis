# setup.py

from distutils.core import setup, Extension

setup(
	name="CuVorbis",
	version="0.0.1",
	description="Python Vorbis Module",
	author="Ignatius Kunjumon",
	author_email="ignatius.kunjumon@gmail.com",
	url="http://ignatius.in/",
	license="GPL",
	ext_modules=[Extension("CuVorbis", ["cu_vorbis.c"],
		library_dirs=["/usr/lib"],
		libraries=['ogg', 'vorbisenc', 'vorbis'])]
	)
