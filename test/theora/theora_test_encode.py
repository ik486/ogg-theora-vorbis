import sys
import Image as IKI
#sys.path.append("/home/ik/ogg/ogg/build/lib.linux-i686-2.6")
################################################################
from CuOgg import *
from CuTheora import *


class OggEncode:
	def __init__(self, width, height, videofile):
		self.width = width;
		self.height = height;
		self.packet = make_ogg_packet()
		self.page   = make_ogg_page()
		self.stream = make_ogg_stream_state()
		self.state  = make_ogg_sync_state()
		self.ret1 = ogg_sync_init(self.state)
		self.th_setupInfo_addr = 0
		self.theoraInfo = make_th_info()
		th_info_init(self.theoraInfo)
		set_th_info(self.theoraInfo, self.width, self.height)
                self.enc=th_encode_alloc (self.theoraInfo)
		self.mComment = make_th_comment()
		th_comment_init(self.mComment)
		self.ogg_packet = make_ogg_packet()
		ogg_stream_init(self.stream, 77771)
		self.fd = open(videofile,"wb")
		self.packetNo = 0
		return

	def printTheoraInfo(self):
		print get_th_info(self.theoraInfo)

	def getSize(self):
		w, h = width_height(self.theoraInfo)
		return w, h

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

	def isHeader(self):
		val = th_packet_isheader(self.packet)  
		return val

	def isKeyFrame(self):
		val = th_packet_iskeyframe(self.packet)
		return val

	#######################################################################

	def flushHeader(self):
		n = 1
		while n > 0:
			n = th_encode_flushheader(self.enc, self.mComment, self.ogg_packet)
			if n > 0:
				nnn = ogg_stream_packetin(self.stream, self.ogg_packet)
		self.savePage()
		return

	def flushStream(self):
		n = ogg_stream_flush(self.stream, self.page)
		self.savePage()
		return

	def savePage(self):
		n = ogg_stream_pageout(self.stream, self.page)
		if n:
			header = page_header(self.page)
			body = page_body(self.page)
			self.fd.write(header)
			self.fd.write(body)
		return

	def addImageFrame(self, img):
		img2 = img.resize([self.width, self.height])
		img3 = img2.convert('RGB')
		img4 = img3.tostring()
		n = th_encode_ycbcr_in(self.enc, img4, self.width, self.height)
		n = th_encode_packetout(self.enc, 0, self.ogg_packet)
		n = ogg_stream_packetin(self.stream, self.ogg_packet)
		self.savePage()
		self.packetNo += 1
		print self.packetNo,"\r",
		sys.stdout.flush()
		return n

	def readImage(self, filename = "aaa.jpg"):
		img = IKI.open(filename)
		return img

	def addImages(self, filename, no = 1):
		img = self.readImage(filename)
		for i in range(no):
			self.addImageFrame(img)
	def close(self):
		self.fd.close()
		return

if __name__ == '__main__':

	def test2():
		ogg = OggEncode(320, 240, 'ik.ogv')
		##############################################
		ogg.flushHeader()
		ogg.addImages("aaa.jpg",5)
		ogg.addImages("bbb.jpg",5)
		ogg.addImages("ccc.jpg",5)
		ogg.flushStream()
		##############################################
		ogg.close()
	
	def test1():
		ogg = OggEncode(320, 240, 'ik.ogv')
		##############################################
		ogg.flushHeader()
		ogg.addImages("aaa.jpg",500)
		ogg.addImages("bbb.jpg",500)
		ogg.addImages("ccc.jpg",500)
		ogg.flushStream()
		##############################################
		ogg.close()
		
	#test1()
	test2()


