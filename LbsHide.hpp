#pragma once

#include "stdafx.h"
#include <windows.h>
#include "Crc32.hpp"
#include "MyBMP.h"


class LbsData {
public:
	BYTE *data = NULL;
	unsigned int length;
	unsigned int crc32;

	~LbsData() {
		if (data != NULL) {
			delete[] data;
		}
	}
};

class LbsHide {
protected:

public:
	int setLbsData(MyBMP* bmp, BYTE *lbsData, int length) {
		BYTE *imagedata = bmp->getImagedata();
		int maxLength = bmp->getMaxLbsLength();

		if (length > maxLength) {
			return -1;
		}

		for (int i = 0; i < length; i++) {
			byteTobits(lbsData[i], imagedata, i * 8);
		}
		bmp->setImagedata(imagedata);

		delete[] imagedata;
		return length;
	}

	BYTE *getLbsData(MyBMP* bmp) {
		BYTE *imagedata = bmp->getImagedata();
		int length = bmp->getMaxLbsLength();

		BYTE *lbsData = new BYTE[length];
		for (int i = 0; i < length; i++) {
			lbsData[i] = bitsToByte(imagedata, i * 8);
		}
		delete[] imagedata;

		return lbsData;
	}

	int setLbsHideData(MyBMP* bmp, LbsData* lbsHideData) {
		BYTE *lbsData = new BYTE[lbsHideData->length + 8];

		lbsHideData->crc32 = Crc32::crc32(lbsHideData->data, lbsHideData->length);
		intTobytes(lbsHideData->length, lbsData, 0);
		intTobytes(lbsHideData->crc32, lbsData, 4);
		memcpy(lbsData + 8, lbsHideData->data, lbsHideData->length);
		
		int result = setLbsData(bmp, lbsData, lbsHideData->length + 8);
		delete[] lbsData;

		return result;
	}

	LbsData *getLbsHideData(MyBMP* bmp) {
		BYTE *lbsData = getLbsData(bmp);
		LbsData *lbsHideData = new LbsData;
		lbsHideData->length = bytestoInt(lbsData, 0);
		lbsHideData->crc32 = bytestoInt(lbsData, 4);
		
		unsigned int maxLength = bmp->getMaxLbsLength() - 8;
		if (lbsHideData->length > maxLength) {
			delete []lbsData;
			delete lbsHideData;
			return NULL;
		}

		lbsHideData->data = new BYTE[lbsHideData->length];
		memcpy(lbsHideData->data, lbsData + 8, lbsHideData->length);
		int crc32 = Crc32::crc32(lbsHideData->data, lbsHideData->length);
		if (lbsHideData->crc32 != crc32) {
			delete[]lbsData;
			delete lbsHideData;
			return NULL;
		}

		delete[]lbsData;
		return lbsHideData;
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

};
