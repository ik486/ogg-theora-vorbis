#include <Python.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <ogg/ogg.h>

static PyObject * cuvorbis_make_vorbis_info(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(vorbis_info);
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


static PyObject * cuvorbis_make_vorbis_block(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(vorbis_block);
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





static PyObject * cuvorbis_make_vorbis_dsp_state(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(vorbis_dsp_state);

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

static PyObject * cuvorbis_make_vorbis_comment(PyObject *self, PyObject *args) {
	PyObject *res;
	int size;
	unsigned char * c_out;
	size = sizeof(vorbis_comment);
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

static PyObject * cuvorbis_vorbis_encode_ctl(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	vorbis_info * vi;
	int request;
	void * arg;
	PyArg_ParseTuple(args, "s#is#", &vi, &size1, &request, &arg, &size2);
	c_out = vorbis_encode_ctl(vi, request, arg);
	return Py_BuildValue("i", c_out);
	};


static PyObject * cuvorbis_vorbis_info_init(PyObject *self, PyObject *args) {
        int c_out;
        int size1;
        vorbis_info * vi;
        PyArg_ParseTuple(args, "s#", &vi, &size1);
        vorbis_info_init(vi);
	c_out = 0;
        return Py_BuildValue("i", c_out);
        };


static PyObject * cuvorbis_vorbis_comment_init(PyObject *self, PyObject *args) {
        int c_out;
        int size1;
	vorbis_comment * vc;
        PyArg_ParseTuple(args, "s#", &vc, &size1);
        vorbis_comment_init(vc);
	c_out = 0;
        return Py_BuildValue("i", c_out);
        };



static PyObject * cuvorbis_vorbis_encode_init(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	vorbis_info * vi;
	long channels;
	long rate;
	long max_bitrate;
	long nominal_bitrate;
	long min_bitrate;
	PyArg_ParseTuple(args, "s#lllll", &vi, &size1, &channels, &rate, &max_bitrate, &nominal_bitrate, &min_bitrate);
	c_out = vorbis_encode_init(vi, channels, rate, max_bitrate, nominal_bitrate, min_bitrate);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_encode_init_vbr(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	vorbis_info * vi;
	long channels;
	long rate;
	float base_quality;
	PyArg_ParseTuple(args, "s#llf", &vi, &size1, &channels, &rate, &base_quality);
	c_out = vorbis_encode_init_vbr(vi, channels, rate, base_quality);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_encode_setup_init(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	vorbis_info * vi;
	PyArg_ParseTuple(args, "s#", &vi, &size1);
	c_out = vorbis_encode_setup_init(vi);
	return Py_BuildValue("i", c_out);
	};


static PyObject * cuvorbis_vorbis_analysis_init(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	vorbis_dsp_state * v;
	vorbis_info * vi;
	PyArg_ParseTuple(args, "s#s#", &v, &size1, &vi, &size2);
	c_out = vorbis_analysis_init(v, vi);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_block_init(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	vorbis_dsp_state * v;
	vorbis_block * vb;
	PyArg_ParseTuple(args, "s#s#", &v, &size1, &vb, &size2);
	c_out = vorbis_block_init(v, vb);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_analysis_headerout(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	int size3;
	int size4;
	int size5;
	vorbis_dsp_state * v;
	vorbis_comment * vc;
	ogg_packet * op;
	ogg_packet * op_comm;
	ogg_packet * op_code;
	PyArg_ParseTuple(args, "s#s#s#s#s#", &v, &size1, &vc, &size2, &op, &size3, &op_comm, &size4, &op_code, &size5);
	c_out = vorbis_analysis_headerout(v, vc, op, op_comm, op_code);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_analysis_buffer(PyObject *self, PyObject *args) {
	float ** c_out;
	int size1;
	vorbis_dsp_state * v;
	int vals;
	PyArg_ParseTuple(args, "s#i", &v, &size1, &vals);
	c_out = vorbis_analysis_buffer(v, vals);
	return Py_BuildValue("s#", c_out);
	};

static PyObject * cuvorbis_vorbis_analysis_wrote(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	vorbis_dsp_state * v;
	int vals;
	PyArg_ParseTuple(args, "s#i", &v, &size1, &vals);
	c_out = vorbis_analysis_wrote(v, vals);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_analysis_blockout(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	vorbis_dsp_state * v;
	vorbis_block * vb;
	PyArg_ParseTuple(args, "s#s#", &v, &size1, &vb, &size2);
	c_out = vorbis_analysis_blockout(v, vb);

	//if (c_out == OV_EINVAL) printf("Invalid parameters.\n");
	//else if (c_out == OV_EFAULT) printf("Internal fault; indicates a bug or memory corruption.\n");
	//else if (c_out == OV_EIMPL)  printf("Unimplemented; not supported by this version of the library.\n");
	//else if (c_out == 1) printf("success, more blocks are available.\n");
	//else if (c_out == 0) printf("success when this is the last block available from the current input.\n");
	//else
	//	printf("i do not know\n");
	
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_analysis(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	vorbis_block * vb;
	ogg_packet * op;
	PyArg_ParseTuple(args, "s#s#", &vb, &size1, &op, &size2);
	c_out = vorbis_analysis(vb, op);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_bitrate_addblock(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	vorbis_block * vb;
	PyArg_ParseTuple(args, "s#", &vb, &size1);
	c_out = vorbis_bitrate_addblock(vb);
	return Py_BuildValue("i", c_out);
	};

static PyObject * cuvorbis_vorbis_bitrate_flushpacket(PyObject *self, PyObject *args) {
	int c_out;
	int size1;
	int size2;
	vorbis_dsp_state * vd;
	ogg_packet * op;
	PyArg_ParseTuple(args, "s#s#", &vd, &size1, &op, &size2);
	c_out = vorbis_bitrate_flushpacket(vd, op);
	return Py_BuildValue("i", c_out);
	};




static PyObject * cuvorbis_vorbis_encode_nosound(PyObject *self, PyObject *args) {
	int i, j, c_out;
	int size1;
	int size2;
	vorbis_dsp_state * vd;
        vorbis_block *vb;
	int sampread;
	float **vorbis_buffer;
	int count=0;
	int audio_ch;
	PyArg_ParseTuple(args, "s#s#ii", &vd, &size1, 
					&vb, &size2, 
					&sampread, &audio_ch);
	/////////////////////////////////////////////////////////////////
        vorbis_buffer=vorbis_analysis_buffer(vd,sampread);
        /* uninterleave samples */
        for(i=0;i<sampread;i++){
            for(j=0;j<audio_ch;j++){
              vorbis_buffer[j][i]= 0.0;
              count+=2;
            }
        }
        c_out = vorbis_analysis_wrote(vd,sampread);
	return Py_BuildValue("i", c_out);
	};




static PyObject * cuvorbis_vorbis_encode_wave_frames(PyObject *self, PyObject *args) {
	int i, j, c_out;
	int size1;
	int size2;
	int size3;
	vorbis_dsp_state * vd;
        vorbis_block *vb;
	signed char *readptr;
	int sampread;
	float **vorbis_buffer;
	int count=0;
	int audio_ch;
	PyArg_ParseTuple(args, "s#s#s#ii", &vd, &size1, 
					&vb, &size2, 
					&readptr, &size3, 
					&sampread, &audio_ch);
	/////////////////////////////////////////////////////////////////
        vorbis_buffer=vorbis_analysis_buffer(vd,sampread);
        /* uninterleave samples */
        for(i=0;i<sampread;i++){
            for(j=0;j<audio_ch;j++){
              vorbis_buffer[j][i]=((readptr[count+1]<<8)|
                                   (0x00ff&(int)readptr[count]))/32768.f;
              count+=2;
            }
        }
        c_out = vorbis_analysis_wrote(vd,sampread);
	return Py_BuildValue("i", c_out);
	};





static PyObject * cuvorbis_wave_frames_to_float(PyObject *self, PyObject *args) {
	int i, j;
	int size;
	signed char *readptr;
	int sampread;
	int count=0;
	int audio_ch;
	float val;
	PyObject *list;
	PyObject *items;
	PyArg_ParseTuple(args, "s#ii",  &readptr, &size, 
					&sampread, &audio_ch);
	/////////////////////////////////////////////////////////////////
        list = PyList_New(sampread);
        for(i=0;i<sampread;i++){
            items = PyList_New(audio_ch);
            for(j=0;j<audio_ch;j++){
              val =((readptr[count+1]<<8)| (0x00ff&(int)readptr[count]))/32768.f;
	      PyList_SetItem(items, j, PyFloat_FromDouble(val));
              count+=2;
            }
	    PyList_SetItem(list, i, items);
        }
	return list;
	};





static PyObject * cuvorbis_wave_frames_to_int(PyObject *self, PyObject *args) {
	int i, j;
	int size;
	signed char *readptr;
	int sampread;
	int count=0;
	int audio_ch;
	int val;
	PyObject *list;
	PyObject *items;
	PyArg_ParseTuple(args, "s#ii",  &readptr, &size, 
					&sampread, &audio_ch);
	/////////////////////////////////////////////////////////////////
        list = PyList_New(sampread);
        for(i=0;i<sampread;i++){
            items = PyList_New(audio_ch);
            for(j=0;j<audio_ch;j++){
              val =(readptr[count+1]<<8)| (0x00ff&(int)readptr[count]);
	      PyList_SetItem(items, j, PyLong_FromLong(val));
              count+=2;
            }
	    PyList_SetItem(list, i, items);
        }
	return list;
	};












static PyObject * cuvorbis_vorbis_encode_int_values(PyObject *self, PyObject *args) {
	int i, j, c_out;
	int size1;
	int size2;
	vorbis_dsp_state * vd;
        vorbis_block *vb;
	PyObject *list;
	PyObject *item1;
	PyObject *item2;
	int sampread;
	float **vorbis_buffer;
	int count=0;
	int audio_ch;
	PyArg_ParseTuple(args, "s#s#Oii", &vd, &size1, 
					&vb, &size2, 
					&list, 
					&sampread, &audio_ch);
	/////////////////////////////////////////////////////////////////
        vorbis_buffer=vorbis_analysis_buffer(vd,sampread);
        /* uninterleave samples */
        for(i=0;i<sampread;i++){
            item1 = PyList_GetItem(list, i);
            Py_INCREF(item1);
            for(j=0;j<audio_ch;j++){
              item2 = PyList_GetItem(item1, j);
              Py_INCREF(item2);
              vorbis_buffer[j][i] = ((float) PyLong_AsLong(item2))/32768.f;
              Py_DECREF(item2);
              count+=2;
            }
            Py_DECREF(item1);
        }
        c_out = vorbis_analysis_wrote(vd,sampread);
	return Py_BuildValue("i", c_out);
	};



static PyObject * cuvorbis_vorbis_encode_float_values(PyObject *self, PyObject *args) {
	int i, j, c_out;
	int size1;
	int size2;
	vorbis_dsp_state * vd;
        vorbis_block *vb;
	PyObject *list;
	PyObject *item1;
	PyObject *item2;
	int sampread;
	float **vorbis_buffer;
	int count=0;
	int audio_ch;
	PyArg_ParseTuple(args, "s#s#Oii", &vd, &size1, 
					&vb, &size2, 
					&list, 
					&sampread, &audio_ch);
	/////////////////////////////////////////////////////////////////
        vorbis_buffer=vorbis_analysis_buffer(vd,sampread);
        /* uninterleave samples */
        for(i=0;i<sampread;i++){
            item1 = PyList_GetItem(list, i);
            Py_INCREF(item1);
            for(j=0;j<audio_ch;j++){
              item2 = PyList_GetItem(item1, j);
              Py_INCREF(item2);
              vorbis_buffer[j][i] = PyFloat_AsDouble(item2);
              Py_DECREF(item2);
              count+=2;
            }
            Py_DECREF(item1);
        }
        c_out = vorbis_analysis_wrote(vd,sampread);
	return Py_BuildValue("i", c_out);
	};



static PyObject * cuvorbis_list_to_wave(PyObject *self, PyObject *args) {
	int i, j;
	int size;
	PyObject *list;
	PyObject *item1;
	PyObject *item2;
	PyObject *res;
	int sampread;
	int count=0;
	int audio_ch;
	signed char *readptr;
	PyArg_ParseTuple(args, "Oii",   &list, 
					&sampread, &audio_ch);
	size = sampread*audio_ch*2;
	readptr = PyMem_New(signed char, size);
	/////////////////////////////////////////////////////////////////
        /* uninterleave samples */
        for(i=0;i<sampread;i++){
            item1 = PyList_GetItem(list, i);
            Py_INCREF(item1);
            for(j=0;j<audio_ch;j++){
              item2 = PyList_GetItem(item1, j);
              Py_INCREF(item2);
	      readptr[count+1] = ((short) PyLong_AsLong(item2)) >> 8;
	      readptr[count] = ((short) PyLong_AsLong(item2)) & 0x00ff;
              Py_DECREF(item2);
              count+=2;
            }
            Py_DECREF(item1);
        }
        //      vorbis_buffer[j][i]=((readptr[count+1]<<8)|
        //                           (0x00ff&(int)readptr[count]))/32768.f;
        res = Py_BuildValue("s#", readptr, size);
        PyMem_Free(readptr);
	return res;
	};



static PyMethodDef CuVorbisMethods[] = {
		{"make_vorbis_info", cuvorbis_make_vorbis_info, METH_VARARGS,
			"Information about a vorbis bitstream."},
		{"make_vorbis_comment", cuvorbis_make_vorbis_comment, METH_VARARGS,
			"vorbis comment"},
		{"make_vorbis_dsp_state", cuvorbis_make_vorbis_dsp_state, METH_VARARGS,
			"dsp state"},
		{"make_vorbis_block", cuvorbis_make_vorbis_block, METH_VARARGS,
			"vorbis_block"},
		{"vorbis_encode_ctl", cuvorbis_vorbis_encode_ctl, METH_VARARGS,
			"This function implements a generic interface to miscellaneous settings similar to the clasasic UNIX ioctl() system call. may use vorbis_encode_ctl() to query or set bitrate management or mode details by using one of several request arguments detailed Vorbis_encode_ctl() must be called after one of or vorbis_encode_setup_vbr(). When used to modify settings,"},
		{"vorbis_info_init", cuvorbis_vorbis_info_init, METH_VARARGS,
			"Info init"},
		{"vorbis_comment_init", cuvorbis_vorbis_comment_init, METH_VARARGS,
			"Vorbis comment init"},
		{"vorbis_encode_init", cuvorbis_vorbis_encode_init, METH_VARARGS,
			"This is the primary function within libvorbisenc for setting up"},
		{"vorbis_encode_init_vbr", cuvorbis_vorbis_encode_init_vbr, METH_VARARGS,
			"This is the primary function within libvorbisenc for setting up"},
		{"vorbis_encode_setup_init", cuvorbis_vorbis_encode_setup_init, METH_VARARGS,
			"This function performs the last stage of three-step encoding setup,"},
		{"vorbis_encode_init", cuvorbis_vorbis_encode_init, METH_VARARGS,
			"This function performs step-one of a three-step bitrate-managed setup. It functions similarly to the one-step setup performed by but allows an application to make further encode setup tweaks using before finally calling vorbis_encode_setup_init() to complete the"},
		{"vorbis_encode_init_vbr", cuvorbis_vorbis_encode_init_vbr, METH_VARARGS,
			"This function performs step-one of a three-step variable bitrate encode setup. It functions similarly to the one-step setup performed vorbis_encode_init_vbr() but allows an application to make further setup tweaks using vorbis_encode_ctl() before finally calling"},
		{"vorbis_analysis_init", cuvorbis_vorbis_analysis_init, METH_VARARGS,
			"This function allocates and initializes the encoder's analysis inside a is vorbis_dsp_state, based on the configuration in a"},
		{"vorbis_block_init", cuvorbis_vorbis_block_init, METH_VARARGS,
			"This function initializes a vorbis_block structure and allocates internal storage. A vorbis_block is used to represent a particular"},
		{"vorbis_analysis_headerout", cuvorbis_vorbis_analysis_headerout, METH_VARARGS,
			"This function creates and returns the three header packets needed to a decoder to accept compressed data. I should be called after all initialization and configuration is complete. The output packets be placed in order at the start of the compressed vorbis stream, prior"},
		{"vorbis_analysis_buffer", cuvorbis_vorbis_analysis_buffer, METH_VARARGS,
			"This fuction requests a buffer array for delivering audio to the"},
		{"vorbis_analysis_wrote", cuvorbis_vorbis_analysis_wrote, METH_VARARGS,
			"This function tells the encoder new data is available for Call this after writing new audio into the buffer array returned by"},
		{"vorbis_analysis_blockout", cuvorbis_vorbis_analysis_blockout, METH_VARARGS,
			"This fuction examines the available uncompressed data and tries to it into appropriate sized blocks. It should be called in a loop after new data with vorbis_analysis_buffer()/vorbis_analysis_wrote()"},
		{"vorbis_analysis", cuvorbis_vorbis_analysis, METH_VARARGS,
			"Once the uncompressed audio data has been divided into blocks, this is called on each block. It looks up the encoding mode and dispatches"},
		{"vorbis_bitrate_addblock", cuvorbis_vorbis_bitrate_addblock, METH_VARARGS,
			"This fuction submits a transformed block to the bitrate management for final encoding. Packets are buffered and the packet boundaries"},
		{"vorbis_bitrate_flushpacket", cuvorbis_vorbis_bitrate_flushpacket, METH_VARARGS,
			"This function returns the next available completed packet from the management engine. It should be called in a loop after any call to until it returns either 0 (more data needed) or a negative value"},
		{"vorbis_encode_nosound", cuvorbis_vorbis_encode_nosound, METH_VARARGS,
			"No Sound"},
		{"vorbis_encode_wave_frames", cuvorbis_vorbis_encode_wave_frames, METH_VARARGS,
			"Encode wave frames"},
		{"wave_frames_to_float", cuvorbis_wave_frames_to_float, METH_VARARGS,
			"Wave frames to float List of List"},
		{"wave_frames_to_int", cuvorbis_wave_frames_to_int, METH_VARARGS,
			"Wave frames to int List of List"},
		{"vorbis_encode_float_values", cuvorbis_vorbis_encode_float_values, METH_VARARGS,
			"Encode float List of List"},
		{"vorbis_encode_int_values", cuvorbis_vorbis_encode_int_values, METH_VARARGS,
			"Encode int List of List"},
		{"list_to_wave", cuvorbis_list_to_wave, METH_VARARGS,
			"Encode List of List to wave data"},
		{NULL, NULL, 0, NULL}
	};

PyMODINIT_FUNC
initCuVorbis(void) {
	(void) Py_InitModule("CuVorbis", CuVorbisMethods);
	}
