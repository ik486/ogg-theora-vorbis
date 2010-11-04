//#include <string.h>
//#undef _POSIX_C_SOURCE 
//#undef _XOPEN_SOURCE
#include <Python.h>
#include <theora/codec.h>
#include <theora/theora.h>
#include <theora/theoradec.h>
#include <theora/theoraenc.h>
#include <ogg/ogg.h>

static PyObject * cutheora_make_th_comment(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	th_comment * comments;
	static char mess[3][20] = { "title=GNUSofts","artist=Kunjumon","album=Koilparampil"};
	static int imess[3] = {14,15,18};
	static char vendor[40] = "Xiph.Org libTheora I 20060526 3 2 0";
	size = sizeof(th_comment);
	c_out = PyMem_New(unsigned char, size);
	comments = (th_comment *) c_out;
	comments->user_comments = (char **) mess;
	comments->comment_lengths = imess;
	comments->comments = 3;
	comments->vendor = vendor;
	if (c_out == NULL) {
		printf("ERROR Not Enough Memory\n");
		Py_INCREF(Py_None);
		return Py_None;
	}
	res = Py_BuildValue("s#", c_out, size);
	PyMem_Free(c_out);
	return res;
	};

static PyObject * cutheora_print_th_comment(PyObject *self, PyObject *args) {
        int i, size;
        th_comment * comments;
	PyArg_ParseTuple(args, "s#", &comments, &size);
	printf("Vendor : [%s]\n", comments->vendor);
	for(i=0; i < comments->comments; ++i) {
		printf("Comments[%d] : [%s]\n", i, comments->user_comments[i]);
	}
        Py_INCREF(Py_None);
        return Py_None;
        };


static PyObject * cutheora_make_th_huff_code(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(th_huff_code);
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

static PyObject * cutheora_make_th_img_plane(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(th_img_plane);
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

static PyObject * cutheora_make_th_info(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(th_info);
	printf("TH INFO :%d\n",size);
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

static PyObject * cutheora_set_th_info(PyObject *self, PyObject *args) {
        int size;
	int width, height;
        th_info * info;
        PyArg_ParseTuple(args, "s#ii", &info, &size, &width, &height);
        th_info_init(info);
	info->frame_width = width;	//The encoded frame width.
	info->frame_height = height;	//The encoded frame height.
	info->pic_width = width;	//The displayed picture width.
	info->pic_height = height;	//The displayed picture height.
	info->pic_x = 0;		//The X offset of the displayed picture.
	info->pic_y = 0;		//The Y offset of the displayed picture.
	info->colorspace = TH_CS_ITU_REC_470M;//The color space.
	info->pixel_fmt = TH_PF_420;	//The pixel format.
	info->target_bitrate = 0;	//The target bit-rate in bits per second.
	info->quality = 32;		//The target quality level 0-63.
	info->keyframe_granule_shift = 6; //The amount to shift to extract the last 
	info->aspect_denominator = 1;
	info->aspect_numerator = 1;
	info->fps_numerator = 25000;
	info->fps_denominator = 1000;
        Py_INCREF(Py_None);
        return Py_None;
        };


static PyObject * cutheora_get_th_info(PyObject *self, PyObject *args) {
	PyObject *res;
        int size;
        th_info * info;
        PyArg_ParseTuple(args, "s#", &info, &size);
	res = Py_BuildValue("{s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i,s:i}", 
					"frame_width",info->frame_width,
        				"frame_height", info->frame_height,
        				"width", info->pic_width,
        				"height", info->pic_height,
        				"x_offset", info->pic_x,
        				"y_offset", info->pic_y,
        				"colorspace", info->colorspace,
        				"pixel_format", info->pixel_fmt,
        				"bitrate", info->target_bitrate,
        				"quality", info->quality,
					"version_major",info->version_major,
					"version_minor",info->version_minor,
					"version_subminor",info->version_subminor,
					"fps_numerator",info->fps_numerator,
					"fps_denominator",info->fps_denominator,
					"aspect_numerator",info->aspect_numerator,
					"aspect_denominator",info->aspect_denominator,
        				"keyframe_shift", info->keyframe_granule_shift);
	return res;
        };



static PyObject * cutheora_make_th_quant_info(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(th_quant_info);
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

static PyObject * cutheora_make_th_quant_ranges(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(th_quant_ranges);
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

static PyObject * cutheora_make_th_stripe_callback(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(th_stripe_callback);
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

static PyObject * cutheora_make_theora_comment(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(theora_comment);
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

static PyObject * cutheora_make_theora_info(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(theora_info);
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

static PyObject * cutheora_make_theora_state(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(theora_state);
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

static PyObject * cutheora_make_yuv_buffer(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	//size = sizeof(yuv_buffer);
	size = sizeof(th_ycbcr_buffer);
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

static PyObject * cutheora_th_version_string(PyObject *self, PyObject *args) {
	const char * c_out;
	c_out = th_version_string();
	return Py_BuildValue("s", c_out);
	};

static PyObject * cutheora_th_version_number(PyObject *self, PyObject *args) {
	ogg_uint32_t c_out;
	c_out = th_version_number();
	return Py_BuildValue("l", c_out);
	};

static PyObject * cutheora_th_granule_frame(PyObject *self, PyObject *args) {
	ogg_int64_t c_out;
	int size1;
	void * _encdec;
	ogg_int64_t _granpos;
	PyArg_ParseTuple(args, "s#l", &_encdec, &size1, &_granpos);
	c_out = th_granule_frame(_encdec, _granpos);
	return Py_BuildValue("l", c_out);
	};

static PyObject * cutheora_th_granule_time(PyObject *self, PyObject *args) {
	double c_out;
	int size1;
	void * _encdec;
	ogg_int64_t _granpos;
	PyArg_ParseTuple(args, "s#l", &_encdec, &size1, &_granpos);
	c_out = th_granule_time(_encdec, _granpos);
	return Py_BuildValue("f", c_out);
	};

static PyObject * cutheora_th_packet_isheader(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	ogg_packet * _op;
	PyArg_ParseTuple(args, "s#", &_op, &size1);
	c_out = th_packet_isheader(_op);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cutheora_th_packet_iskeyframe(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	ogg_packet * _op;
	PyArg_ParseTuple(args, "s#", &_op, &size1);
	c_out = th_packet_iskeyframe(_op);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cutheora_th_info_init(PyObject *self, PyObject *args) {
	int size1;
	th_info * _info;
	PyArg_ParseTuple(args, "s#", &_info, &size1);
	th_info_init(_info);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_th_info_clear(PyObject *self, PyObject *args) {
	int size1;
	th_info * _info;
	PyArg_ParseTuple(args, "s#", &_info, &size1);
	th_info_clear(_info);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_th_comment_init(PyObject *self, PyObject *args) {
	int size1;
	th_comment * _tc;
	PyArg_ParseTuple(args, "s#", &_tc, &size1);
	th_comment_init(_tc);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_th_comment_add(PyObject *self, PyObject *args) {
	int size1;
	th_comment * _tc;
	char * _comment;
	PyArg_ParseTuple(args, "s#s", &_tc, &size1, &_comment);
	th_comment_add(_tc, _comment);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_th_comment_add_tag(PyObject *self, PyObject *args) {
	int size1;
	th_comment * _tc;
	char * _tag;
	char * _val;
	PyArg_ParseTuple(args, "s#ss", &_tc, &size1, &_tag, &_val);
	th_comment_add_tag(_tc, _tag, _val);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_th_comment_query(PyObject *self, PyObject *args) {
	char * c_out;
	int size1;
	th_comment * _tc;
	char * _tag;
	int _count;
	PyArg_ParseTuple(args, "s#si", &_tc, &size1, &_tag, &_count);
	c_out = th_comment_query(_tc, _tag, _count);
	return Py_BuildValue("s", c_out);
	};

static PyObject * cutheora_th_comment_query_count(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	th_comment * _tc;
	char * _tag;
	PyArg_ParseTuple(args, "s#s", &_tc, &size1, &_tag);
	c_out = th_comment_query_count(_tc, _tag);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cutheora_th_comment_clear(PyObject *self, PyObject *args) {
	int size1;
	th_comment * _tc;
	PyArg_ParseTuple(args, "s#", &_tc, &size1);
	th_comment_clear(_tc);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_th_encode_alloc(PyObject *self, PyObject *args) {
	th_enc_ctx * c_out;
	int size1;
	const th_info * _info;
	PyArg_ParseTuple(args, "s#", &_info, &size1);
	c_out = th_encode_alloc(_info);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cutheora_th_encode_ctl(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	int size3;
	th_enc_ctx * _enc;
	int _req;
	void * _buf;
	size_t _buf_sz;
	PyArg_ParseTuple(args, "s#is#s#", &_enc, &size1, &_req, &_buf, &size2, &_buf_sz, &size3);
	c_out = th_encode_ctl(_enc, _req, _buf, _buf_sz);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cutheora_th_encode_flushheader(PyObject *self, PyObject *args) {
	int c_out;
	int size2;
	int size3;
	unsigned int address;
	th_enc_ctx * _enc;
	th_comment * comments;
	ogg_packet * _op;
	PyArg_ParseTuple(args, "is#s#", &address, &comments, &size2, &_op, &size3);
	_enc = (th_enc_ctx *) address;
	c_out = th_encode_flushheader(_enc, comments, _op);
	return Py_BuildValue("i", c_out);
	};

/*
static PyObject * cutheora_th_encode_ycbcr_in(PyObject *self, PyObject *args) {
	int c_out;
	int size2;
	th_enc_ctx * _enc;
	unsigned int address;
	th_ycbcr_buffer *_ycbcr;
	PyArg_ParseTuple(args, "is#", &address, &_ycbcr, &size2);
	_enc = (th_enc_ctx *) address;
	printf("[%d]\n", size2);
	c_out = th_encode_ycbcr_in(_enc, *_ycbcr);
	return Py_BuildValue("i", c_out);
	};
*/

static PyObject * cutheora_th_encode_packetout(PyObject *self, PyObject *args) {
	int c_out;
	int size2;
	th_enc_ctx * _enc;
	int _last;
	unsigned int address;
	ogg_packet * _op;
	PyArg_ParseTuple(args, "iis#", &address, &_last, &_op, &size2);
	_enc = (th_enc_ctx *) address;
	c_out = th_encode_packetout(_enc, _last, _op);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cutheora_th_encode_free(PyObject *self, PyObject *args) {
	int size1;
	th_enc_ctx * _enc;
	PyArg_ParseTuple(args, "s#", &_enc, &size1);
	th_encode_free(_enc);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_th_decode_headerin(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	//int size3;
	int size4;
	unsigned int address;
	th_info * _info;
	th_comment * _tc;
	th_setup_info *_setup;
	ogg_packet * _op;
	PyArg_ParseTuple(args, "s#s#is#", &_info, &size1, &_tc, &size2, &address, &_op, &size4);
	_setup = (th_setup_info *) address;
	c_out = th_decode_headerin(_info, _tc, &_setup, _op);
	if (c_out == TH_EFAULT)
		return Py_BuildValue("[s,l]", "FAULT", (unsigned int) _setup);
	else if (c_out == TH_EBADHEADER)
		return Py_BuildValue("[s,l]", "BADHEADER", (unsigned int) _setup);
	else if (c_out == TH_EVERSION)
		return Py_BuildValue("[s,l]", "VERSION", (unsigned int) _setup);
	else if (c_out == TH_ENOTFORMAT)
		return Py_BuildValue("[s,l]", "NOTFORMAT", (unsigned int) _setup);
	else if (c_out > 0)
		return Py_BuildValue("[s,l]", "ok",(unsigned int) _setup);
	else if (c_out == 0)
		return Py_BuildValue("[s,l]", "VIDEO",(unsigned int) _setup);
	else
		return Py_BuildValue("[s,l]", "UNKNOWN",(unsigned int) _setup);
	};

static PyObject * cutheora_th_decode_alloc(PyObject *self, PyObject *args) {
	th_dec_ctx * c_out;
	int size1;
	const th_info * _info;
	const th_setup_info * _setup;
	unsigned int address;
	PyArg_ParseTuple(args, "s#i", &_info, &size1, &address);
	_setup = (th_setup_info *) address;
	c_out = th_decode_alloc(_info, _setup);
	return Py_BuildValue("l", (unsigned int) c_out);
	};

static PyObject * cutheora_th_setup_free(PyObject *self, PyObject *args) {
	th_setup_info * _setup;
	unsigned int address;
	PyArg_ParseTuple(args, "i", &address);
	_setup = (th_setup_info *) address;
	th_setup_free(_setup);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_th_decode_ctl(PyObject *self, PyObject *args) {
	int c_out;
	th_dec_ctx * _dec;
	int _req;
	void * _buf;
	size_t _buf_sz;
	unsigned int address;
	PyArg_ParseTuple(args, "iis#i", &address, &_req, &_buf, &_buf_sz);
	_dec = (th_dec_ctx *) address;
	c_out = th_decode_ctl(_dec, _req, _buf, _buf_sz);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cutheora_th_decode_packetin(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	th_dec_ctx * _dec;
	const ogg_packet * _op;
	unsigned int address;
	ogg_int64_t  _granpos;
	PyArg_ParseTuple(args, "is#i", &address, &_op, &size1, &_granpos);
	_dec = (th_dec_ctx *) address;
	c_out = th_decode_packetin(_dec, _op, &_granpos);
	if (c_out == 0)
		return Py_BuildValue("[s,i]", "ok", _granpos);
	else if (c_out == TH_DUPFRAME)
		return Py_BuildValue("[s,i]", "DUPFRAME", _granpos);
	else if (c_out == TH_EFAULT)
		return Py_BuildValue("[s,i]", "FAULT", _granpos);
	else if (c_out == TH_EBADPACKET)
		return Py_BuildValue("[s,i]", "BADPACKET", _granpos);
	else if (c_out == TH_EIMPL)
		return Py_BuildValue("[s,i]", "EIMPL", _granpos);
	return Py_BuildValue("[s,i]", "UNKNOWN", 0);
	};

static PyObject * cutheora_th_decode_ycbcr_out(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	unsigned int address;
	th_dec_ctx * _dec;
	th_ycbcr_buffer *_ycbcr;
	th_ycbcr_buffer buffer;
	PyArg_ParseTuple(args, "is#", &address, &_ycbcr, &size1);
	_dec = (th_dec_ctx *) address;
	c_out = th_decode_ycbcr_out(_dec, buffer);
	memcpy(_ycbcr,buffer,sizeof(buffer));
        if (c_out == TH_EFAULT)
                return Py_BuildValue("s", "FAULT");
        else if (c_out == 0)
                return Py_BuildValue("s", "ok");
        else
                return Py_BuildValue("s", "UNKNOWN");
	};

static PyObject * cutheora_th_decode_free(PyObject *self, PyObject *args) {
	th_dec_ctx * _dec;
	unsigned int address;
	PyArg_ParseTuple(args, "i", &address);
	_dec = (th_dec_ctx *) address;
	th_decode_free(_dec);
	Py_INCREF(Py_None);
	return Py_None;
	};

static PyObject * cutheora_width_height(PyObject *self, PyObject *args) {
	int size1;
	const th_info * info;
	PyArg_ParseTuple(args, "s#", &info, &size1);
	return Py_BuildValue("[i,i]", info->pic_width, info->pic_height);
	}

static PyObject * IKFuns_rgb(PyObject *self, PyObject *args) {
        PyObject *res;
        unsigned char *rgb;
        long size, size1, size2, size3;
	int pos, pos1, pos2;
	int Y, U, V;
	int R, G, B;
	int i, j, i2, j2;
	th_ycbcr_buffer buffer;
	th_ycbcr_buffer *_ycbcr;
	PyArg_ParseTuple(args, "s#", &_ycbcr, &size);
	memcpy(buffer,_ycbcr, sizeof(buffer));
        size1 = buffer[0].width * buffer[0].height;
        size2 = buffer[1].width * buffer[1].height;
        size3 = buffer[2].width * buffer[2].height;
        size = size1*3;
	/*
	printf("W : %d\n",buffer[0].width);
	printf("H : %d\n",buffer[0].height);
	printf("S : %d\n",buffer[0].stride);
	printf("W : %d\n",buffer[1].width);
	printf("H : %d\n",buffer[1].height);
	printf("S : %d\n",buffer[1].stride);
	printf("W : %d\n",buffer[2].width);
	printf("H : %d\n",buffer[2].height);
	printf("S : %d\n",buffer[2].stride);
	*/
        rgb = PyMem_New(unsigned char, size);
        for(i=0;i<buffer[0].height;i++) {
        	for(j=0;j<buffer[0].width;j++) {
			i2 = (int) i/2;
			j2 = (int) j/2;
			pos = i*buffer[0].stride +j;
			pos1 = i2*buffer[1].stride + j2;
			pos2 = i2*buffer[2].stride + j2;
			Y = (int) buffer[0].data[pos];
			U = (int) buffer[1].data[pos1];
			V = (int) buffer[2].data[pos2];
			Y = Y - 128 - 16;
			U = U - 128;
			V = V - 128;

			R = Y + 1.140*V;
			G = Y - 0.395*U - 0.581*V;
			B = Y + 2.032*U;
			R += 128;
			G += 128;
			B += 128;
			if (R > 255) R = 255;
			if (R < 0) R = 0;
			if (G > 255) G = 255;
			if (G < 0) G = 0;
			if (B > 255) B = 255;
			if (B < 0) B = 0;
			pos2 = (i*buffer[0].width+j)*3;
			rgb[pos2] = R; 
			rgb[pos2+1] = G; 
			rgb[pos2+2] = B; 
		}
	}
        res = Py_BuildValue("s#", rgb, size);
        PyMem_Free(rgb);
        return res;
        }



static PyObject * cutheora_th_encode_ycbcr_in(PyObject *self, PyObject *args) {
	int c_out;
	int size2;
	th_enc_ctx * _enc;
	unsigned int address;
	int w, h;
	char *data;
	int i, j, n,nn;
	int i1, i2, i3, i4;
	int p1, p2, p3, p4;

	float r1, g1, b1, r2, g2, b2;
	float r3, g3, b3, r4, g4, b4;

	float y1, u1, v1, y2, u2, v2;
	float y3, u3, v3, y4, u4, v4;
	float u, v;
	unsigned char iy1, iy2, iy3, iy4, iu, iv;
	th_ycbcr_buffer ycbcr;

	PyArg_ParseTuple(args, "is#ii", &address, &data, &size2, &w, &h);
	_enc = (th_enc_ctx *) address;
	ycbcr[0].data = (unsigned char *) malloc(w*h);
	ycbcr[1].data = (unsigned char *) malloc(w*h/4);
	ycbcr[2].data = (unsigned char *) malloc(w*h/4);
	ycbcr[0].width = w;
	ycbcr[0].height = h;
	ycbcr[0].stride = w;

	ycbcr[1].width = w/2;
	ycbcr[1].height = h/2;
	ycbcr[1].stride = w/2;

	ycbcr[2].width = w/2;
	ycbcr[2].height = h/2;
	ycbcr[2].stride = w/2;
	n = w*h/2;
	nn = 0;
	for (i =0; i < h; i+=2) {
		for (j =0; j < w; j+=2) {
                	i1 = i*w+j;
	                i2 = i*w+(j+1);
        	        i3 = (i+1)*w+j;
                	i4 = (i+1)*w+(j+1);
	                p1 = i1*3;
        	        p2 = i2*3;
	                p3 = i3*3;
        	        p4 = i4*3;

                        r1 = (float) (((unsigned char) data[p1])   - 128);
                        g1 = (float) (((unsigned char) data[p1+1]) - 128);
                        b1 = (float) (((unsigned char) data[p1+2]) - 128);
                        r2 = (float) (((unsigned char) data[p2])   - 128);
                        g2 = (float) (((unsigned char) data[p2+1]) - 128);
                        b2 = (float) (((unsigned char) data[p2+2]) - 128);

                        r3 = (float) (((unsigned char) data[p3])   - 128);
                        g3 = (float) (((unsigned char) data[p3+1]) - 128);
                        b3 = (float) (((unsigned char) data[p3+2]) - 128);
                        r4 = (float) (((unsigned char) data[p4])   - 128);
                        g4 = (float) (((unsigned char) data[p4+1]) - 128);
                        b4 = (float) (((unsigned char) data[p4+2]) - 128);

			r1 *= 0.80;
			r2 *= 0.80;
			r3 *= 0.80;
			r4 *= 0.80;

                        y1 = 0.299*r1 + 0.587*g1 + 0.114*b1 + 128;
                        u1 = -0.14713*r1 -0.28886*g1 + 0.436*b1 + 128;
                        v1 = 0.615*r1 + -0.51499*g1 + -0.10001*b1 + 128;

                        y2 = 0.299*r2 + 0.587*g2 + 0.114*b2 + 128;
                        u2 = -0.14713*r2 -0.28886*g2 + 0.436*b2 + 128;
                        v2 = 0.615*r2 + -0.51499*g2 + -0.10001*b2 + 128;

                        y3 = 0.299*r3 + 0.587*g3 + 0.114*b3 + 128;
                        u3 = -0.14713*r3 -0.28886*g3 + 0.436*b3 + 128;
                        v3 = 0.615*r3 + -0.51499*g3 + -0.10001*b3 + 128;

                        y4 = 0.299*r4 + 0.587*g4 + 0.114*b4 + 128;
                        u4 = -0.14713*r4 -0.28886*g4 + 0.436*b4 + 128;
                        v4 = 0.615*r4 + -0.51499*g4 + -0.10001*b4 + 128;

                        u = (u1 + u2 + u3 + u4)/4;
                        v = (v1 + v2 + v3 + v4)/4;

                        iy1 = (unsigned char) (y1);
                        iy2 = (unsigned char) (y2);
                        iy3 = (unsigned char) (y2);
                        iy4 = (unsigned char) (y2);

                        iu  = (unsigned char) (u);
                        iv  = (unsigned char) (v);

			ycbcr[0].data[i1]   = iy1;
			ycbcr[0].data[i2]   = iy2;
			ycbcr[0].data[i3]   = iy3;
			ycbcr[0].data[i4]   = iy4;
			ycbcr[1].data[nn] = iu;
			ycbcr[2].data[nn] = iv;
			++nn;
		}		
	}
	c_out = th_encode_ycbcr_in(_enc, ycbcr);
	//free(ycbcr[0].data);
	//free(ycbcr[1].data);
	//free(ycbcr[2].data);
	//printf("TH_EFAULT : %d\n",TH_EFAULT);
	//printf("TH_EINVAL : %d\n",TH_EINVAL);
	return Py_BuildValue("i", c_out);
	};



static PyMethodDef CuTheoraMethods[] = {
		{"make_th_comment", cutheora_make_th_comment, METH_VARARGS,
			"The comment information"},
		{"print_th_comment", cutheora_print_th_comment, METH_VARARGS,
			"Print the comment information"},
		{"make_th_huff_code", cutheora_make_th_huff_code, METH_VARARGS,
			"A Huffman code for a Theora DCT token"},
		{"make_th_img_plane", cutheora_make_th_img_plane, METH_VARARGS,
			"A buffer for a single color plane in an uncompressed image"},
		{"make_th_info", cutheora_make_th_info, METH_VARARGS,
			"Theora bitstream information"},
		{"make_th_quant_info", cutheora_make_th_quant_info, METH_VARARGS,
			"A complete set of quantization parameters"},
		{"make_th_quant_ranges", cutheora_make_th_quant_ranges, METH_VARARGS,
			"A set of qi ranges"},
		{"make_th_stripe_callback", cutheora_make_th_stripe_callback, METH_VARARGS,
			"The striped decode callback data to pass to TH_DECCTL_SET_STRIPE_CB"},
		{"make_theora_comment", cutheora_make_theora_comment, METH_VARARGS,
			"Comment header metadata"},
		{"make_theora_info", cutheora_make_theora_info, METH_VARARGS,
			"Theora bitstream info"},
		{"make_theora_state", cutheora_make_theora_state, METH_VARARGS,
			"Codec internal state and context"},
		{"make_yuv_buffer", cutheora_make_yuv_buffer, METH_VARARGS,
			"A YUV buffer for passing uncompressed frames to and from the codec "},
		{"th_version_string", cutheora_th_version_string, METH_VARARGS,
			"Retrieves a human-readable string to identify the library vendor and version."},
		{"th_version_number", cutheora_th_version_number, METH_VARARGS,
			"Retrieves the library version number."},
		{"th_granule_frame", cutheora_th_granule_frame, METH_VARARGS,
			"Converts a granule position to an absolute frame index, starting at 0."},
		{"th_granule_time", cutheora_th_granule_time, METH_VARARGS,
			"Converts a granule position to an absolute time in seconds."},
		{"th_packet_isheader", cutheora_th_packet_isheader, METH_VARARGS,
			"Determines whether a Theora packet is a header or not."},
		{"th_packet_iskeyframe", cutheora_th_packet_iskeyframe, METH_VARARGS,
			"Determines whether a theora packet is a key frame or not."},
		{"th_info_init", cutheora_th_info_init, METH_VARARGS,
			"Initializes a th_info structure."},
		{"th_info_clear", cutheora_th_info_clear, METH_VARARGS,
			"Clears a th_info structure."},
		{"th_comment_init", cutheora_th_comment_init, METH_VARARGS,
			"Initialize a th_comment structure."},
		{"th_comment_add", cutheora_th_comment_add, METH_VARARGS,
			"Add a comment to an initialized th_comment structure."},
		{"th_comment_add_tag", cutheora_th_comment_add_tag, METH_VARARGS,
			"Add a comment to an initialized th_comment structure."},
		{"th_comment_query", cutheora_th_comment_query, METH_VARARGS,
			"Look up a comment value by its tag."},
		{"th_comment_query_count", cutheora_th_comment_query_count, METH_VARARGS,
			"Look up the number of instances of a tag."},
		{"th_comment_clear", cutheora_th_comment_clear, METH_VARARGS,
			"Clears a th_comment structure."},
		{"th_encode_alloc", cutheora_th_encode_alloc, METH_VARARGS,
			"Allocates an encoder instance."},
		{"th_encode_ctl", cutheora_th_encode_ctl, METH_VARARGS,
			"Encoder control function."},
		{"th_encode_flushheader", cutheora_th_encode_flushheader, METH_VARARGS,
			"Outputs the next header packet."},
		{"th_encode_ycbcr_in", cutheora_th_encode_ycbcr_in, METH_VARARGS,
			"Submits an uncompressed frame to the encoder."},
		{"th_encode_packetout", cutheora_th_encode_packetout, METH_VARARGS,
			"Retrieves encoded video data packets."},
		{"th_encode_free", cutheora_th_encode_free, METH_VARARGS,
			"Frees an allocated encoder instance."},
		{"th_decode_headerin", cutheora_th_decode_headerin, METH_VARARGS,
			"Decodes the header packets of a Theora stream."},
		{"th_decode_alloc", cutheora_th_decode_alloc, METH_VARARGS,
			"Allocates a decoder instance."},
		{"th_setup_free", cutheora_th_setup_free, METH_VARARGS,
			"Releases all storage used for the decoder setup information."},
		{"th_decode_ctl", cutheora_th_decode_ctl, METH_VARARGS,
			"Decoder control function."},
		{"th_decode_packetin", cutheora_th_decode_packetin, METH_VARARGS,
			"Submits a packet containing encoded video data to the decoder."},
		{"th_decode_ycbcr_out", cutheora_th_decode_ycbcr_out, METH_VARARGS,
			"Outputs the next available frame of decoded YCbCr data."},
		{"th_decode_free", cutheora_th_decode_free, METH_VARARGS,
			"Frees an allocated decoder instance."},
		{"width_height", cutheora_width_height, METH_VARARGS,
			"width and height"},
		{"get_rgb_buffer", IKFuns_rgb, METH_VARARGS, 
			"return rgb data"},
		//{"rgb2ycbcr", IKGSTFuns_rgb2ycbcr, METH_VARARGS, 
		//	"return yCbCr data"},
		{"set_th_info", cutheora_set_th_info, METH_VARARGS,
			"Set Theora bitstream information Width and Height"},
		{"get_th_info", cutheora_get_th_info, METH_VARARGS,
			"Get Theora bitstream information"},
		{NULL, NULL, 0, NULL}
	};

PyMODINIT_FUNC
initCuTheora(void) {
	(void) Py_InitModule("CuTheora", CuTheoraMethods);
	}
