#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#undef _POSIX_C_SOURCE 
#undef _XOPEN_SOURCE

#include <Python.h>
#include <ogg/ogg.h>


static PyObject * cuogg_read_page(PyObject *self, PyObject *args) {
	PyObject *res;
	int fd;
	int size1, size2;
	int ret, bytes;
        ogg_sync_state *state;
        ogg_page *page;
	PyArg_ParseTuple(args, "is#s#", &fd, &state, &size1, &page, &size2);
	ret = -1;
        while(ogg_sync_pageout(state, page) != 1) {
                char* buffer = ogg_sync_buffer(state, 4096);
		//printf("buffer reading for page\n");
                bytes = read(fd, buffer, 4096);
                if (bytes == 0) {
			printf("ERROR End of file\n");
			Py_INCREF(Py_None);
			return Py_None;
                }
                ret = ogg_sync_wrote(state, bytes);
        }
	res = Py_BuildValue("i", 1);
	return res;
};


static PyObject * cuogg_open_file(PyObject *self, PyObject *args) {
	PyObject *res;
	char *name;
	int fd;
	PyArg_ParseTuple(args, "s", &name);
	fd = open(name, O_RDONLY);
	if (fd < 1) {
		printf("ERROR Failed to open file %s\n", name);
		Py_INCREF(Py_None);
		return Py_None;
	}
	res = Py_BuildValue("i", fd);
	return res;
	};

static PyObject * cuogg_make_ogg_page(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(ogg_page);
	c_out = PyMem_New(unsigned char, size);
	if (c_out == NULL) {
		printf("ERROR Not Enough Memory\n");
		Py_INCREF(Py_None);
		return Py_None;
	}
	res = Py_BuildValue("s#", c_out, size);
	PyMem_Free(c_out);
	return res;
	};

static PyObject * cuogg_make_ogg_stream_state(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(ogg_stream_state);
	c_out = PyMem_New(unsigned char, size);
	if (c_out == NULL) {
		printf("ERROR Not Enough Memory\n");
		Py_INCREF(Py_None);
		return Py_None;
	}
	res = Py_BuildValue("s#", c_out, size);
	PyMem_Free(c_out);
	return res;
	};

static PyObject * cuogg_make_ogg_packet(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(ogg_packet);
	c_out = PyMem_New(unsigned char, size);
	if (c_out == NULL) {
		printf("ERROR Not Enough Memory\n");
		Py_INCREF(Py_None);
		return Py_None;
	}
	res = Py_BuildValue("s#", c_out, size);
	PyMem_Free(c_out);
	return res;
	};

static PyObject * cuogg_make_ogg_sync_state(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(ogg_sync_state);
	c_out = PyMem_New(unsigned char, size);
	if (c_out == NULL) {
		printf("ERROR Not Enough Memory\n");
		Py_INCREF(Py_None);
		return Py_None;
	}
	res = Py_BuildValue("s#", c_out, size);
	PyMem_Free(c_out);
	return res;
	};

static PyObject * cuogg_oggpack_adv(PyObject *self, PyObject *args) {
	oggpack_buffer * b;
	int bits;
	int size;
	PyArg_ParseTuple(args, "s#i", &b, &size, &bits);
	oggpack_adv(b, bits);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_adv1(PyObject *self, PyObject *args) {
	int size;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	oggpack_adv1(b);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_bits(PyObject *self, PyObject *args) {
	long c_out;
	int size;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	c_out = oggpack_bits(b);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cuogg_oggpack_bytes(PyObject *self, PyObject *args) {
	long c_out;
	int size;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	c_out = oggpack_bytes(b);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cuogg_ogg_packet_clear(PyObject *self, PyObject *args) {
	int size;
	ogg_packet * op;
	PyArg_ParseTuple(args, "s#", &op, &size);
	ogg_packet_clear(op);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_get_buffer(PyObject *self, PyObject *args) {
	int size;
	unsigned char * c_out;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	c_out = oggpack_get_buffer(b);
	return Py_BuildValue("s#", c_out);
	};

static PyObject * cuogg_oggpack_look1(PyObject *self, PyObject *args) {
	int size;
	long c_out;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	c_out = oggpack_look1(b);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cuogg_oggpack_look(PyObject *self, PyObject *args) {
	int size;
	long c_out;
	oggpack_buffer * b;
	int bits;
	PyArg_ParseTuple(args, "s#i", &b, &size, &bits);
	c_out = oggpack_look(b, bits);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cuogg_oggpack_read1(PyObject *self, PyObject *args) {
	int size;
	long c_out;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	c_out = oggpack_read1(b);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cuogg_oggpack_read(PyObject *self, PyObject *args) {
	int size;
	long c_out;
	oggpack_buffer * b;
	int bits;
	PyArg_ParseTuple(args, "s#i", &b, &size, &bits);
	c_out = oggpack_read(b, bits);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cuogg_oggpack_readinit(PyObject *self, PyObject *args) {
	oggpack_buffer * b;
	unsigned char * buf;
	int bytes;
	int size1, size2;
	PyArg_ParseTuple(args, "s#s#i", &b, &size1, &buf, &size2, &bytes);
	oggpack_readinit(b, buf, bytes);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_reset(PyObject *self, PyObject *args) {
	int size;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	oggpack_reset(b);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_writetrunc(PyObject *self, PyObject *args) {
	int size;
	oggpack_buffer * b;
	long bits;
	PyArg_ParseTuple(args, "s#l", &b, &size, &bits);
	oggpack_writetrunc(b, bits);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_writecheck(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	c_out = oggpack_writecheck(b);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_oggpack_writeclear(PyObject *self, PyObject *args) {
	int size;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	oggpack_writeclear(b);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_writecopy(PyObject *self, PyObject *args) {
	oggpack_buffer * b;
	void * source;
	long bits;
	int size1, size2;
	PyArg_ParseTuple(args, "s#s#l", &b, &size1, &source, &size2, &bits);
	oggpack_writecopy(b, source, bits);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_write(PyObject *self, PyObject *args) {
	oggpack_buffer * b;
	unsigned long value;
	int bits;
	int size1, size2;
	PyArg_ParseTuple(args, "s#s#i", &b, &size1, &value, &size2, &bits);
	oggpack_write(b, value, bits);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_oggpack_writeinit(PyObject *self, PyObject *args) {
	int size;
	oggpack_buffer * b;
	PyArg_ParseTuple(args, "s#", &b, &size);
	oggpack_writeinit(b);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_ogg_page_bos(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	c_out = ogg_page_bos(og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_page_checksum_set(PyObject *self, PyObject *args) {
	int size;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	ogg_page_checksum_set(og);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_ogg_page_continued(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	c_out = ogg_page_continued(og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_page_eos(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	c_out = ogg_page_eos(og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_page_granulepos(PyObject *self, PyObject *args) {
	int size;
	ogg_int64_t c_out;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	c_out = ogg_page_granulepos(og);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cuogg_ogg_page_packets(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	c_out = ogg_page_packets(og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_page_pageno(PyObject *self, PyObject *args) {
	int size;
	long c_out;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	c_out = ogg_page_pageno(og);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cuogg_ogg_page_serialno(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	c_out = ogg_page_serialno(og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_page_version(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#", &og, &size);
	c_out = ogg_page_version(og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_check(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_stream_state * os;
	PyArg_ParseTuple(args, "s#", &os, &size);
	c_out = ogg_stream_check(os);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_clear(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_stream_state * os;
	PyArg_ParseTuple(args, "s#", &os, &size);
	c_out = ogg_stream_clear(os);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_destroy(PyObject *self, PyObject *args) {
	int c_out;
	int size;
	ogg_stream_state * os;
	PyArg_ParseTuple(args, "s#", &os, &size);
	c_out = ogg_stream_destroy(os);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_flush(PyObject *self, PyObject *args) {
	int c_out;
	int size1, size2;
	ogg_stream_state * os;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#s#", &os, &size1, &og, &size2);
	c_out = ogg_stream_flush(os, og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_init(PyObject *self, PyObject *args) {
	int c_out;
	int serialno;
	int size;
	ogg_stream_state * os;
	PyArg_ParseTuple(args, "s#i", &os, &size, &serialno);
	c_out = ogg_stream_init(os, serialno);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_packetin(PyObject *self, PyObject *args) {
	int c_out;
	int size1, size2;
	ogg_stream_state * os;
	ogg_packet * op;
	PyArg_ParseTuple(args, "s#s#", &os, &size1, &op, &size2);
	c_out = ogg_stream_packetin(os, op);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_packetout(PyObject *self, PyObject *args) {
	int c_out;
	int size1, size2;
	ogg_stream_state * os;
	ogg_packet * op;
	PyArg_ParseTuple(args, "s#s#", &os, &size1, &op, &size2);
	c_out = ogg_stream_packetout(os, op);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_packetpeek(PyObject *self, PyObject *args) {
	int c_out;
	int size1, size2;
	ogg_stream_state * os;
	ogg_packet * op;
	PyArg_ParseTuple(args, "s#s#", &os, &size1, &op, &size2);
	c_out = ogg_stream_packetpeek(os, op);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_pagein(PyObject *self, PyObject *args) {
	int c_out;
	int size1, size2;
	ogg_stream_state * os;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#s#", &os, &size1, &og, &size2);
	c_out = ogg_stream_pagein(os, og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_pageout(PyObject *self, PyObject *args) {
	int c_out;
	int size1, size2;
	ogg_stream_state * os;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#s#", &os, &size1, &og, &size2);
	c_out = ogg_stream_pageout(os, og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_reset(PyObject *self, PyObject *args) {
	int c_out;
	int size;
	ogg_stream_state * os;
	PyArg_ParseTuple(args, "s#", &os, &size);
	c_out = ogg_stream_reset(os);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_stream_reset_serialno(PyObject *self, PyObject *args) {
	int c_out;
	ogg_stream_state * os;
	int serialno;
	int size;
	PyArg_ParseTuple(args, "s#i", &os, &size, &serialno);
	c_out = ogg_stream_reset_serialno(os, serialno);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_sync_buffer(PyObject *self, PyObject *args) {
	char * c_out;
	ogg_sync_state oy;
	long size;
	//long size2;
	PyArg_ParseTuple(args, "s#l", &oy, &size);
	c_out = ogg_sync_buffer(&oy, size);
	//return Py_BuildValue("s#", c_out, size);
	return Py_BuildValue("l", (long) c_out);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cuogg_ogg_sync_check(PyObject *self, PyObject *args) {
	int c_out;
	int size;
	ogg_sync_state * oy;
	PyArg_ParseTuple(args, "s#", &oy, &size);
	c_out = ogg_sync_check(oy);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_sync_clear(PyObject *self, PyObject *args) {
	int c_out;
	int size;
	ogg_sync_state * oy;
	PyArg_ParseTuple(args, "s#", &oy, &size);
	c_out = ogg_sync_clear(oy);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_sync_destroy(PyObject *self, PyObject *args) {
	int size;
	int c_out;
	ogg_sync_state * oy;
	PyArg_ParseTuple(args, "s#", &oy, &size);
	c_out = ogg_sync_destroy(oy);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_sync_init(PyObject *self, PyObject *args) {
	int c_out;
	int size;
	ogg_sync_state * oy;
	PyArg_ParseTuple(args, "s#", &oy, &size);
	c_out = ogg_sync_init(oy);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_sync_pageout(PyObject *self, PyObject *args) {
	int c_out;
	int size1, size2;
	ogg_sync_state * oy;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#s#", &oy, &size1, &og, &size2);
	c_out = ogg_sync_pageout(oy, og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_sync_pageseek(PyObject *self, PyObject *args) {
	int c_out;
	int size1, size2;
	ogg_sync_state * oy;
	ogg_page * og;
	PyArg_ParseTuple(args, "s#s#", &oy, &size1, &og, &size2);
	c_out = ogg_sync_pageseek(oy, og);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_sync_reset(PyObject *self, PyObject *args) {
	int c_out;
	int size;
	ogg_sync_state * oy;
	PyArg_ParseTuple(args, "s#", &oy, &size);
	c_out = ogg_sync_reset(oy);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuogg_ogg_sync_wrote(PyObject *self, PyObject *args) {
	int c_out;
	int size;
	ogg_sync_state * oy;
	long bytes;
	PyArg_ParseTuple(args, "s#l", &oy, &size, &bytes);
	c_out = ogg_sync_wrote(oy, bytes);
	return Py_BuildValue("i", c_out);
	};



static PyObject * cuogg_page_header(PyObject *self, PyObject *args) {
        int size;
        ogg_page * og;
        PyArg_ParseTuple(args, "s#", &og, &size);
        return Py_BuildValue("s#", og->header, og->header_len);
        };


static PyObject * cuogg_page_body(PyObject *self, PyObject *args) {
        int size;
        ogg_page * og;
        PyArg_ParseTuple(args, "s#", &og, &size);
        return Py_BuildValue("s#", og->body, og->body_len);
        };



static PyMethodDef CuOggMethods[] = {
		{"make_ogg_page", cuogg_make_ogg_page, METH_VARARGS,
			"This structure encapsulates data into one ogg bitstream page."},
		{"make_ogg_stream_state", cuogg_make_ogg_stream_state, METH_VARARGS,
			"This structure contains current encode/decode data for a logical bitstream."},
		{"make_ogg_packet", cuogg_make_ogg_packet, METH_VARARGS,
			"This structure encapsulates the data and metadata for a single Ogg packet."},
		{"make_ogg_sync_state", cuogg_make_ogg_sync_state, METH_VARARGS,
			"Contains bitstream synchronization information."},
		{"oggpack_adv", cuogg_oggpack_adv, METH_VARARGS,
			"void oggpack_adv"},
		{"oggpack_adv1", cuogg_oggpack_adv1, METH_VARARGS,
			"void oggpack_adv1"},
		{"oggpack_bits", cuogg_oggpack_bits, METH_VARARGS,
			"long oggpack_bits"},
		{"oggpack_bytes", cuogg_oggpack_bytes, METH_VARARGS,
			"long oggpack_bytes"},
		{"ogg_packet_clear", cuogg_ogg_packet_clear, METH_VARARGS,
			"int ogg_packet_clear"},
		{"oggpack_get_buffer", cuogg_oggpack_get_buffer, METH_VARARGS,
			"unsigned char *oggpack_get_buffer"},
		{"oggpack_look1", cuogg_oggpack_look1, METH_VARARGS,
			"long oggpack_look1"},
		{"oggpack_look", cuogg_oggpack_look, METH_VARARGS,
			"long oggpack_look"},
		{"oggpack_read1", cuogg_oggpack_read1, METH_VARARGS,
			"long oggpack_read1"},
		{"oggpack_read", cuogg_oggpack_read, METH_VARARGS,
			"long oggpack_read"},
		{"oggpack_readinit", cuogg_oggpack_readinit, METH_VARARGS,
			"void oggpack_readinit"},
		{"oggpack_reset", cuogg_oggpack_reset, METH_VARARGS,
			"void oggpack_reset"},
		{"oggpack_writetrunc", cuogg_oggpack_writetrunc, METH_VARARGS,
			"void oggpack_writetrunc"},
		{"oggpack_writecheck", cuogg_oggpack_writecheck, METH_VARARGS,
			"int oggpack_writecheck"},
		{"oggpack_writeclear", cuogg_oggpack_writeclear, METH_VARARGS,
			"void oggpack_writeclear"},
		{"oggpack_writecopy", cuogg_oggpack_writecopy, METH_VARARGS,
			"void oggpack_writecopy"},
		{"oggpack_write", cuogg_oggpack_write, METH_VARARGS,
			"void oggpack_write"},
		{"oggpack_writeinit", cuogg_oggpack_writeinit, METH_VARARGS,
			"void oggpack_writeinit"},
		{"ogg_page_bos", cuogg_ogg_page_bos, METH_VARARGS,
			"int ogg_page_bos"},
		{"ogg_page_checksum_set", cuogg_ogg_page_checksum_set, METH_VARARGS,
			"void ogg_page_checksum_set"},
		{"ogg_page_continued", cuogg_ogg_page_continued, METH_VARARGS,
			"int ogg_page_continued"},
		{"ogg_page_eos", cuogg_ogg_page_eos, METH_VARARGS,
			"int ogg_page_eos"},
		{"ogg_page_granulepos", cuogg_ogg_page_granulepos, METH_VARARGS,
			"ogg_int64_t ogg_page_granulepos"},
		{"ogg_page_packets", cuogg_ogg_page_packets, METH_VARARGS,
			"int ogg_page_packets"},
		{"ogg_page_pageno", cuogg_ogg_page_pageno, METH_VARARGS,
			"long ogg_page_pageno"},
		{"ogg_page_serialno", cuogg_ogg_page_serialno, METH_VARARGS,
			"int ogg_page_serialno"},
		{"ogg_page_version", cuogg_ogg_page_version, METH_VARARGS,
			"int ogg_page_version"},
		{"ogg_stream_check", cuogg_ogg_stream_check, METH_VARARGS,
			"int ogg_stream_check"},
		{"ogg_stream_clear", cuogg_ogg_stream_clear, METH_VARARGS,
			"int ogg_stream_clear"},
		{"ogg_stream_destroy", cuogg_ogg_stream_destroy, METH_VARARGS,
			"int ogg_stream_destroy"},
		{"ogg_stream_flush", cuogg_ogg_stream_flush, METH_VARARGS,
			"int ogg_stream_flush"},
		{"ogg_stream_init", cuogg_ogg_stream_init, METH_VARARGS,
			"int ogg_stream_init"},
		{"ogg_stream_packetin", cuogg_ogg_stream_packetin, METH_VARARGS,
			"int ogg_stream_packetin"},
		{"ogg_stream_packetout", cuogg_ogg_stream_packetout, METH_VARARGS,
			"int ogg_stream_packetout"},
		{"ogg_stream_packetpeek", cuogg_ogg_stream_packetpeek, METH_VARARGS,
			"int ogg_stream_packetpeek"},
		{"ogg_stream_pagein", cuogg_ogg_stream_pagein, METH_VARARGS,
			"int ogg_stream_pagein"},
		{"ogg_stream_pageout", cuogg_ogg_stream_pageout, METH_VARARGS,
			"int ogg_stream_pageout"},
		{"ogg_stream_reset", cuogg_ogg_stream_reset, METH_VARARGS,
			"int ogg_stream_reset"},
		{"ogg_stream_reset_serialno", cuogg_ogg_stream_reset_serialno, METH_VARARGS,
			"int ogg_stream_reset_serialno"},
		{"ogg_sync_buffer", cuogg_ogg_sync_buffer, METH_VARARGS,
			"char *ogg_sync_buffer"},
		{"ogg_sync_check", cuogg_ogg_sync_check, METH_VARARGS,
			"int ogg_sync_check"},
		{"ogg_sync_clear", cuogg_ogg_sync_clear, METH_VARARGS,
			"int ogg_sync_clear"},
		{"ogg_sync_destroy", cuogg_ogg_sync_destroy, METH_VARARGS,
			"int ogg_sync_destroy"},
		{"ogg_sync_init", cuogg_ogg_sync_init, METH_VARARGS,
			"int ogg_sync_init"},
		{"ogg_sync_pageout", cuogg_ogg_sync_pageout, METH_VARARGS,
			"int ogg_sync_pageout"},
		{"ogg_sync_pageseek", cuogg_ogg_sync_pageseek, METH_VARARGS,
			"int ogg_sync_pageseek"},
		{"ogg_sync_reset", cuogg_ogg_sync_reset, METH_VARARGS,
			"int ogg_sync_reset"},
		{"ogg_sync_wrote", cuogg_ogg_sync_wrote, METH_VARARGS,
			"int ogg_sync_wrote"},
		{"open_file", cuogg_open_file, METH_VARARGS,
			"int open video/audio file"},
		{"read_page", cuogg_read_page, METH_VARARGS,
			"read page"},
		{"page_header", cuogg_page_header, METH_VARARGS,
			"return page header"},
		{"page_body", cuogg_page_body, METH_VARARGS,
			"return page body"},
		{NULL, NULL, 0, NULL}
	};

PyMODINIT_FUNC
initCuOgg(void) {
	(void) Py_InitModule("CuOgg", CuOggMethods);
	}
