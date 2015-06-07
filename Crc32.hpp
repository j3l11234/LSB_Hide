#pragma once

#include "stdafx.h"

class Crc32 {
protected:
	static int CRC32[256];
	static char init;

	//��ʼ����
	static void init_table() {
		int   i, j;
		int   crc;
		for (i = 0; i < 256; i++) {
			crc = i;
			for (j = 0; j < 8; j++) {
				if (crc & 1) {
					crc = (crc >> 1) ^ 0xEDB88320;
				} else {
					crc = crc >> 1;
				}
			}
			CRC32[i] = crc;
		}
	}

public:
	//crc32ʵ�ֺ���
	static int crc32(BYTE *buf, int len){
		int ret = 0xFFFFFFFF;
		int   i;
		if (!init)
		{
			init_table();
			init = 1;
		}
		for (i = 0; i < len; i++)
		{
			ret = CRC32[((ret & 0xFF) ^ buf[i])] ^ (ret >> 8);
		}
		ret = ~ret;
		return ret;
	}
};

int Crc32::CRC32[256];
char Crc32::init;





