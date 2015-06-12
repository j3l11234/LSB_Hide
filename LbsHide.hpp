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
	BYTE *keyData = NULL;
	unsigned int keyLength;
	~LbsData() {
		if (data != NULL) {
			delete[] data;
		}
		if (keyData != NULL) {
			delete[] keyData;
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
		
		unsigned int keyCrc32 = 0;
		if (lbsHideData->keyData != NULL) {
			keyCrc32 = Crc32::crc32(lbsHideData->keyData, lbsHideData->keyLength);
		}

		unsigned int maxLength = bmp->getMaxLbsLength();
		unsigned int lbsDataLength = lbsHideData->length + 8;
		BYTE *newlbsData = getLbsData(bmp);
		BYTE *newlbsDataMap = new BYTE[maxLength];
		memset(newlbsDataMap, 0, maxLength * sizeof(BYTE));
		unsigned int next = keyCrc32;

		for (unsigned int i = 0; i < lbsDataLength; i++) {
			while (true) {
				next = imrand(next);
				if (newlbsDataMap[next % maxLength] == 0) {
					break;
				}
			}
			newlbsData[next % maxLength] = lbsData[i];
			newlbsDataMap[next % maxLength] = 1;
		}
		int result = setLbsData(bmp, newlbsData, maxLength);
		delete[]newlbsDataMap;
		delete[] newlbsData;
		delete[] lbsData;

		return result;
	}

	int getLbsHideData(MyBMP* bmp, LbsData* lbsHideData) {
		BYTE *lbsData = getLbsData(bmp);
		unsigned int keyCrc32 = 0;
		if (lbsHideData->keyData != NULL) {
			keyCrc32 = Crc32::crc32(lbsHideData->keyData, lbsHideData->keyLength);
		}

		unsigned int maxLength = bmp->getMaxLbsLength();
		unsigned int offset = keyCrc32 % maxLength;

		BYTE *lbsHeaderData = new BYTE[8];
		BYTE *newlbsDataMap = new BYTE[maxLength];
		memset(newlbsDataMap, 0, maxLength * sizeof(BYTE));
		unsigned int next = keyCrc32;

		for (unsigned int i = 0; i < 8; i++) {
			while (true) {
				next = imrand(next);
				if (newlbsDataMap[next % maxLength] == 0) {
					break;
				}
			}
			lbsHeaderData[i] = lbsData[next % maxLength];
			newlbsDataMap[next % maxLength] = 1;
		}
		lbsHideData->length = bytestoInt(lbsHeaderData, 0);
		lbsHideData->crc32 = bytestoInt(lbsHeaderData, 4);
		delete[] lbsHeaderData;

		if (lbsHideData->length > maxLength) {
			delete[]lbsData;
			return -1;
		}

		lbsHideData->data = new BYTE[lbsHideData->length];
		for (unsigned int i = 0; i < lbsHideData->length; i++) {
			while (true) {
				next = imrand(next);
				if (newlbsDataMap[next % maxLength] == 0) {
					break;
				}
			}
			lbsHideData->data[i] = lbsData[next % maxLength];
			newlbsDataMap[next % maxLength] = 1;
		}

		int crc32 = Crc32::crc32(lbsHideData->data, lbsHideData->length);
		if (lbsHideData->crc32 != crc32) {
			delete []lbsData;
			delete[]lbsHideData->data;
			return -1;
		}

		delete []lbsData;
		return 1;
	}

	int* statBinary(MyBMP* bmp) {
		BYTE *imagedata = bmp->getImagedata();
		int length = bmp->getMaxLbsLength();
		int count0 = 0, count1 = 0;
		for (int i = 0; i < length; i++) {
			if ((imagedata[i] & 0x01) == 1) {
				count1++;
			}
			else {
				count0++;
			}
		}
		int *result = new int[3];
		result[0] = length;
		result[1] = count0;
		result[2] = count1;

		return result;
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

	static unsigned int imrand(unsigned int next) {
		next = next * 1103515245 + 12345;
		return (int)(next) % 0x7fffffff;
	}
};
