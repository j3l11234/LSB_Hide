#pragma once

#include "stdafx.h"
#include <windows.h>
#include "Crc32.hpp"
#include "MyBMP.h"


class LbsData {
public:
	BYTE *data;
	int length;
	int crc32;
};

class LbsHide {

public:
	int setLbsData(MyBMP* bmp, LbsData lbsData) {
		BYTE *imagedata = bmp->getImagedata();
		int maxLength = bmp->getMaxLbsLength() - 8;
		if (lbsData.length > maxLength) {
			lbsData.length = maxLength;
		}
		lbsData.crc32 = Crc32::crc32(lbsData.data, lbsData.length);
		printf("crc32=%x\n", lbsData.crc32);

		BYTE *headerData = new BYTE[8];
		intTobytes(lbsData.length, headerData, 0);
		intTobytes(lbsData.crc32, headerData, 4);
		for (int i = 0; i < 8; i++) {
			byteTobits(headerData[i], imagedata, i * 8);
		}
		delete[] headerData;

		for (int i = 0; i < lbsData.length; i++) {
			byteTobits(lbsData.data[i], imagedata, (i + 8) * 8);
		}
		bmp->setImagedata(imagedata);

		delete[] imagedata;
		return lbsData.length;
	}


	LbsData getLbsData(MyBMP* bmp) {
		LbsData lbsData;
		BYTE *imagedata = bmp->getImagedata();
		int maxLength = bmp->getMaxLbsLength() - 8;

		BYTE *headerData = new BYTE[8];

		for (int i = 0; i < 8; i++) {
			headerData[i] = bitsToByte(imagedata, i * 8);
		}
		lbsData.length = bytestoInt(headerData, 0);
		lbsData.crc32 = bytestoInt(headerData, 4);
		printf("crc32=%x\n", lbsData.crc32);
		delete[] headerData;

		if (lbsData.length > maxLength || lbsData.length < 0) {
			lbsData.length = maxLength;
		}
		lbsData.data = new BYTE[lbsData.length];
		for (int i = 0; i < lbsData.length; i++) {
			lbsData.data[i] = bitsToByte(imagedata, (i + 8) * 8);
		}
		delete[] imagedata;

		return lbsData;
	}

	static void intTobytes(int num, BYTE *data, int offset) {
		*(data + offset + 0) = (num >> 0) & 0xff;
		*(data + offset + 1) = (num >> 8) & 0xff;
		*(data + offset + 2) = (num >> 16) & 0xff;
		*(data + offset + 3) = (num >> 24) & 0xff;
	}

	static int bytestoInt(BYTE *data, int offset) {
		int num =
			*(data + offset + 0) << 0 |
			*(data + offset + 1) << 8 |
			*(data + offset + 2) << 16 |
			*(data + offset + 3) << 24;
		return num;
	}

	static void byteTobits(BYTE byte, BYTE *data, int offset) {
		data[offset + 0] = (data[offset + 0] & 0xfe) | (byte >> 0 & 0x01);
		data[offset + 1] = (data[offset + 1] & 0xfe) | (byte >> 1 & 0x01);
		data[offset + 2] = (data[offset + 2] & 0xfe) | (byte >> 2 & 0x01);
		data[offset + 3] = (data[offset + 3] & 0xfe) | (byte >> 3 & 0x01);
		data[offset + 4] = (data[offset + 4] & 0xfe) | (byte >> 4 & 0x01);
		data[offset + 5] = (data[offset + 5] & 0xfe) | (byte >> 5 & 0x01);
		data[offset + 6] = (data[offset + 6] & 0xfe) | (byte >> 6 & 0x01);
		data[offset + 7] = (data[offset + 7] & 0xfe) | (byte >> 7 & 0x01);

	}

	static BYTE bitsToByte(BYTE *data, int offset) {
		BYTE byte =
			(data[offset + 0] & 0x01) << 0 |
			(data[offset + 1] & 0x01) << 1 |
			(data[offset + 2] & 0x01) << 2 |
			(data[offset + 3] & 0x01) << 3 |
			(data[offset + 4] & 0x01) << 4 |
			(data[offset + 5] & 0x01) << 5 |
			(data[offset + 6] & 0x01) << 6 |
			(data[offset + 7] & 0x01) << 7;

		return byte;
	}

protected:
};

