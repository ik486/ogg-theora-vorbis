#sys.path.append("/home/ik/ogg/ogg/build/lib.linux-i686-2.6")
################################################################

import sys
import random
import wave
import Image as IKI

from CuOgg import *
from CuVorbis import *
from CuTheora import *

class WaveData:
	def __init__(self, wave_file):
		self.fd         = wave.open(wave_file)
		self.noChannels = self.fd.getnchannels() # 2 for sterio
		self.width      = self.fd.getsampwidth() # 2 bytes
		self.frameRate  = self.fd.getframerate() # 44100
		self.noFrames   = self.fd.getnframes()   # total number of frames
		self.paramList  = self.fd.getparams() 
				# (2, 2, 44100, 2752, 'NONE', 'not compressed')
		self.video_fps  = 25
		self.frame_size = self.frameRate/self.video_fps

	def eof(self):
		if self.noFrames == self.fd.tell(): return 1
		return 0

	def getFrame(self):
		no = self.frame_size
		pos = self.fd.tell()
		if pos + no > self.noFrames:
			no = self.noFrames - pos
		frames = self.fd.readframes(no)
		vals = wave_frames_to_int(frames, no, self.noChannels)
		#print "\t\t===", self.fd.tell(), len(vals),self.fd.tell()+882
		if self.frame_size == 1764:
			return vals
		elif self.frame_size == 882:
			pos = self.fd.tell()
			if no == self.frame_size:
				framen = self.fd.readframes(1)
				valn = wave_frames_to_int(framen, 1, self.noChannels)
				self.fd.setpos(pos)
				valn = valn[0]
			else:
				valn = [0L]*self.noChannels
			return self.insertOne(vals, valn)
		else:
			print "ERROR getFrame"
			return None
			
	def appendNoSound(self):
		vals = self.getFrame()
		#print "AN sound", self.fd.tell(), len(vals), self.frame_size
		if len(vals) == 1764:
			return vals
		elif len(vals) < 1764:
			no = 1764 - len(vals)
			return vals + [[0L]*self.noChannels]*no
			self.eof = 1
		else:
			print "ERROR appendsound"
			return None


	def insertOne(self, vals, valn):
		out = []
		n = len(vals) -1
		for i in range(n):
			out.append(vals[i])
			data = []
			for j in range(self.noChannels):
				m = (vals[i][j] + vals[i+1][j])/2
				data.append(m)
			out.append(data)
		out.append(vals[-1])
		data = []
		for j in range(self.noChannels):
			m = (vals[-1][j] + valn[j])/2
			data.append(m)
		out.append(data)
		return out
		
	def getAudioFrameData(self):
		if self.eof(): return None
		vals = self.appendNoSound()
		return vals





class AudioEncode:
	def __init__(self, fd):
		self.noChannels = 2
		self.width      = 2
		self.frameRate  = 44100
				# (2, 2, 44100, 2752, 'NONE', 'not compressed')

		self.vi = make_vorbis_info()      # struct that stores all the static vorbis bitstream
		self.vc = make_vorbis_comment()   # struct that stores all the user comments */
		self.vd = make_vorbis_dsp_state() # central working state for the packet->PCM decoder */
		self.vb = make_vorbis_block()     # local working space for packet->PCM decode */

		self.header      = make_ogg_packet()
		self.header_comm = make_ogg_packet()
		self.header_code = make_ogg_packet()
		self.audio_pkt   = make_ogg_packet()

		self.to = make_ogg_stream_state()
		self.page        = make_ogg_page()
		self.fout = fd


	def flushFrames(self):
		vorbis_analysis_wrote(self.vd,0)
		while (vorbis_analysis_blockout(self.vd, self.vb) == 1):
			vorbis_analysis(self.vb,self.audio_pkt)
          		ogg_stream_packetin(self.to,self.audio_pkt)
		self.savePage()


	def addAudioFrame(self, vals):
		vorbis_encode_int_values(self.vd, self.vb, vals, len(vals), self.noChannels)
		while (vorbis_analysis_blockout(self.vd, self.vb) == 1):
			vorbis_analysis(self.vb,self.audio_pkt)
          		ogg_stream_packetin(self.to,self.audio_pkt)
		self.savePage()
		return 1


	def headerFrames(self):
		quality = 1.0 # values between -0.1 to 1.0
		r1 = vorbis_info_init(self.vi)
		r2 = vorbis_encode_init_vbr(self.vi, self.noChannels, self.frameRate, quality)
		r3 = vorbis_encode_setup_init(self.vi)

		r4 = vorbis_comment_init(self.vc)
		r5 = vorbis_analysis_init(self.vd,self.vi)
		r6 = vorbis_block_init(self.vd,self.vb)

		r7 = vorbis_analysis_headerout(self.vd, 
				self.vc, 
				self.header, 
				self.header_comm, 
				self.header_code)

		#print r1, r2, r3, '--', r4, r5, r6, '--', r7

		rnd = int(random.random()*10000)
		ogg_stream_init(self.to,rnd)

		r1 = ogg_stream_packetin(self.to, self.header)
		r2 = ogg_stream_packetin(self.to, self.header_comm)
		r3 = ogg_stream_packetin(self.to, self.header_code)

		self.savePage()

	def clear(self):
		vorbis_block_clear(self.vb)
		vorbis_dsp_clear(self.vd)
		vorbis_comment_clear(self.vc)
		vorbis_info_clear(self.vi)
		return

        def savePage(self):
                n = ogg_stream_pageout(self.to, self.page)
                if n:
			#print "Audio PAGE SAVED"
                        header = page_header(self.page)
                        body = page_body(self.page)
                        self.fout.write(header)
                        self.fout.write(body)
                return





class VideoEncode:
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


class AudioVideo:
	def __init__(self, width, height, output_file):
		self.video = VideoEncode(width, height, output_file)
		self.video.flushHeader()
		self.audio = AudioEncode(self.video.fd)
		self.audio.headerFrames()
		return
	
	def addAudioImages(self, img_file, wav_file):
		img = self.video.readImage(img_file)
		wav = WaveData(wav_file)
		no = 0
		while 1:
			val = wav.getAudioFrameData()
			if val == None: break
			self.video.addImageFrame(img)
			self.audio.addAudioFrame(val)
			no += 1
		print "%-5d frames added with audio" % (no)
		return

	def addNoAudioImages(self, img_file, no):
		img = self.video.readImage(img_file)
		for i in range(no):
			val = [[0L,0L]]*(44100/25)
			self.video.addImageFrame(img)
			self.audio.addAudioFrame(val)
		print "%-5d frames added" % (no)
		return no

	def close(self):
		self.video.close()
	


if __name__ == '__main__':

	def test():
		ogv = VideoEncode(320, 240, 'ik.ogv')
		ogv.flushHeader()
		#--------------------------------------------
		oga = AudioEncode(ogv.fd)
		oga.headerFrames()
		##############################################
		img = ogv.readImage("aaa.jpg")
		wav = WaveData('a.wav')
		while 1:
			val = wav.getAudioFrameData()
			if val == None: break
			ogv.addImageFrame(img)
			oga.addAudioFrame(val)
		##############################################
		#ogv.addImages("ccc.jpg",500)
		ogv.flushStream()
		oga.flushFrames()
		##############################################
		ogv.close()
		
	def test1():
		av = AudioVideo(320, 240, 'ik.ogv')
		av.addNoAudioImages("aaa.jpg",100)
		av.addAudioImages("bbb.jpg","a.wav")
		av.addAudioImages("ccc.jpg","wind.wav")
		av.close()
	test1()





