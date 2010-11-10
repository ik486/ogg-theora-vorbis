import sys
import Image as IKI
#sys.path.append("/home/ik/ogg/ogg/build/lib.linux-i686-2.6")
################################################################
from CuOgg import *
from CuTheora import *


class IKOgg:
	def __init__(self, file_name):
		self.file_name = file_name
		self.packet = make_ogg_packet()
		self.page   = make_ogg_page()
		self.stream = make_ogg_stream_state()
		self.state  = make_ogg_sync_state()
		self.th_setupInfo_addr = 0

		self.file = open_file(self.file_name)
		self.ret1 = ogg_sync_init(self.state)

		self.readPage()
		self.slno = ogg_page_serialno(self.page)
		self.ret3 = ogg_stream_init(self.stream, self.slno)
		self.ret4 = ogg_stream_pagein(self.stream, self.page)

		self.theoraInfo    = make_th_info()
		self.mComment = make_th_comment()
		th_info_init(self.theoraInfo)
		th_comment_init(self.mComment)
		self.setupInfo_addr = 0

	def getSize(self):
		w, h = width_height(self.theoraInfo)
		return w, h

	def readPage(self):
		self.ret2 = read_page(self.file, self.state, self.page)
		#print "PAGE :-: ", self.pageNo()
		return self.ret2

	def isPageBOS(self):
		out = ogg_page_bos(self.page)
		if out > 0: out = 1
		elif out < 0:
			print "ERROR PAGE BOS"
		return out

	def isPageEOS(self):
		out = ogg_page_eos(self.page)
		if out > 0: out = 1
		return out

	def pageNo(self):
		no = ogg_page_pageno(self.page)
		return no

	def readPacket(self):
		self.ret5 = ogg_stream_packetout(self.stream, self.packet)
		while self.ret5 == 0:
			if not self.readPage(): 
				print "PAGE END"
				return None
			self.ret4 = ogg_stream_pagein(self.stream, self.page)
			self.ret5 = ogg_stream_packetout(self.stream, self.packet)
		return self.packet

	def isHeader(self):
		val = th_packet_isheader(self.packet)  
		return val

	def isKeyFrame(self):
		val = th_packet_iskeyframe(self.packet)
		return val

	def decodeHeader(self):
		ret = None
		while self.isHeader():
			ret, self.setupInfo_addr = th_decode_headerin(self.theoraInfo, 
					self.mComment, self.setupInfo_addr, self.packet)
			val = self.readPacket()
			if not val: return None
		while not ret == 'VIDEO':
			ret, self.setupInfo_addr = th_decode_headerin(self.theoraInfo, 
					self.mComment, self.setupInfo_addr, self.packet)
			if not ret == 'VIDEO':
				val = self.readPacket()
		return

	def beginVideo(self):
		self.dec = th_decode_alloc(self.theoraInfo, self.setupInfo_addr)
		th_setup_free(self.setupInfo_addr)
		self.gpos = 0
		w, h = self.getSize()
		self.buff = make_yuv_buffer(w*h*2)
		ret, self.gpos = th_decode_packetin(self.dec, self.packet, self.gpos)
		val = th_decode_ycbcr_out(self.dec, self.buff)

	def gotoKeyFrame(self):
		while not self.isKeyFrame():
			self.readPacket()
		return

	def rgbBuffer(self):
		self.rgb = get_rgb_buffer(self.buff)
		return self.rgb

	def readVideo(self):
		val = self.readPacket()
		if val == None: return None
		ret, self.gpos = th_decode_packetin(self.dec, self.packet, self.gpos)
		val = th_decode_ycbcr_out(self.dec, self.buff)
		return val

	def endVideo(self):
		th_decode_free(self.dec)
		return

	def saveImage(self, name = "frame.png"):
		w,h = self.getSize()
		img = IKI.fromstring('RGB', [w, h],self.rgb)
		img.save(name)

if __name__ == '__main__':

	def test2():
		ogg = IKOgg("ik.ogv")
		ogg.decodeHeader()
		print ogg.getSize()
		ogg.beginVideo()
		for i in range(1,2):
			val = ogg.readVideo()
			if val == 'ok':
				buff = ogg.rgbBuffer()
				ogg.saveImage("frame%03d.png" % (i))
		print get_th_info(ogg.theoraInfo)
		print_th_comment(ogg.mComment)
		ogg.endVideo()

	test2()


