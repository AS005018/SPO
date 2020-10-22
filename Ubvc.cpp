// Ubvc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include<sstream>

using namespace std;


#pragma pack(2)

//Заголовок файла BMP 
typedef struct tBITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
}sFileHead;

//Заголовок BitMap's
typedef struct tBITMAPINFOHEADER
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}sInfoHead;

sFileHead FileHead;
sInfoHead InfoHead;

//Пиксель
struct Color
{
	BYTE red;
	BYTE green;
	BYTE blue;
};

int a, b, c;
//Размер 1-го пикселя
int pixel_size = sizeof(Color);


//1 - BMP, 2 - CMP
int img_type = 0;

//Исходное изображение
Color* src_image = 0;
//Результативное изображение
Color* dst_image = 0;

//Размер изображения
int width = 0;
int height = 0;

//Вывести заголовок BMP файла
void ShowBMPHeaders(tBITMAPFILEHEADER fh, tBITMAPINFOHEADER ih)
{
	cout << "Type: " << (CHAR)fh.bfType << endl;
	cout << "Size: " << fh.bfSize << endl;
	cout << "Shift of bits: " << fh.bfOffBits << endl;
	cout << "Width: " << ih.biWidth << endl;
	cout << "Height: " << ih.biHeight << endl;
	cout << "Planes: " << ih.biPlanes << endl;
	cout << "BitCount: " << ih.biBitCount << endl;
	cout << "Compression: " << ih.biCompression << endl;
}

//Функция для загрузки изображения
bool OpenImage(string path)
{
	ifstream img_file;
	Color temp;
	char buf[3];

	//Открыть файл на чтение
	img_file.open(path.c_str(), ios::in | ios::binary);
	if (!img_file)
	{
		cout << "File isn`t open!" << endl;
		return false;
	}

	//Считать заголовки BMP
	img_file.read((char*)&FileHead, sizeof(FileHead));
	img_file.read((char*)&InfoHead, sizeof(InfoHead));

	img_type = 1;
	ShowBMPHeaders(FileHead, InfoHead);
	//Присвоить длину и ширину изображения
	width = InfoHead.biWidth;
	height = InfoHead.biHeight;


	//Выделить место под изображение
	src_image = new Color[width * height];

	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img_file.read((char*)&temp, pixel_size);
			src_image[i * width + j] = temp;
		}
		//Дочитать биты используемые для выравнивания до двойного слова
		img_file.read((char*)buf, j % 4);
	}
	img_file.close();

	return true;
}

//Функция для сохранения изображение
bool SaveImage(string path)
{
	ofstream img_file;
	char buf[3];

	//Открыть файл на запись
	img_file.open(path.c_str(), ios::out | ios::binary);
	if (!img_file)
	{
		return false;
	}

	img_file.write((char*)&FileHead, sizeof(FileHead));
	img_file.write((char*)&InfoHead, sizeof(InfoHead));

	//Скопировать из исходного в результирующее изображение
	if (dst_image == 0)
	{
		dst_image = new Color[width * height];
		memcpy(dst_image, src_image, width * height * sizeof(Color));
	}

	//Записать файл
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img_file.write((char*)&dst_image[i * width + j], pixel_size);
		}
		img_file.write((char*)buf, j % 4);
	}
	img_file.close();

	return true;
}

//Скопировать содержимое результируещего изображения в начальное
void CopyDstToSrc()
{
	if (dst_image != 0)
	{
		memcpy(src_image, dst_image, width * height * sizeof(Color));
	}
}
//Отобразить текущее изображение с помощью вызова стандартного просмотрщика
void ShowImage(string path)
{
	ShowBMPHeaders(FileHead, InfoHead);
	system(path.c_str());
}



//Считать путь к изображению
void ReadPath(string& str)
{
	str.clear();
	cout << "Enter path to image" << endl;
	cin >> str;
}

int ftr(long pos) {
	int d, e, g;
	stringstream sw;
	d = src_image[pos].blue;
	e = src_image[pos].green;
	g = src_image[pos].red;
	sw << d << e << g;
	int s;
	sw >> s;

	return s;

}


void lab3() {
	for (int i = 1; i < height - 1; i = i + 4)
	{
		for (int j = 1; j < width - 1; j = j + 2)
		{
			/*if (src_image[(i - 1) * width + j].green == src_image[i * width + j].green
				== src_image[(i - 1) * width + j - 1].green == src_image[i * width + j - 1].green == 255 &&
				src_image[(i + 1) * width + j].green == src_image[(i + 2) * width + j].green
				== src_image[(i + 1) * width + j - 1].green == src_image[(i + 2) * width + j - 1].green == 255)
			{
					src_image[(i - 1) * width + j].green = src_image[i * width + j].green
						= src_image[(i - 1) * width + j - 1].green = src_image[i * width + j - 1].green = 100;
					src_image[(i + 1) * width + j].green = src_image[(i + 2) * width + j].green
						= src_image[(i + 1) * width + j - 1].green = src_image[(i + 2) * width + j - 1].green = 100;
			}*/
			int mm[40];
			mm[1] = ftr((i - 1) * width + j);
			mm[2] = ftr(i * width + j);
			mm[3] = ftr((i - 1) * width + j - 1);
			mm[4] = ftr(i * width + j - 1);
			mm[5] = ftr((i + 1) * width + j);
			mm[6] = ftr((i + 2) * width + j);
			mm[7] = ftr((i + 1) * width + j - 1);
			mm[8] = ftr((i + 2) * width + j - 1);
			int k = 20;
			/*if (ftr((i - 1) * width + j) == ftr(i * width + j)
				== ftr((i - 1) * width + j - 1) == ftr(i * width + j - 1) ==3417776 &&
				ftr((i + 1) * width + j) == ftr((i + 2) * width + j)
				== ftr((i + 1) * width + j - 1) == ftr((i + 2) * width + j - 1)== 3417776)*/
			if (mm[1] == 3417776 && mm[2] == 3417776 && mm[3] == 3417776 && mm[4] == 3417776)
				if (mm[5] == 3417776 && mm[6] == 3417776 && mm[7] == 3417776 && mm[8] == 3417776)
				{
					src_image[(i - 1) * width + j].green = k;
					src_image[i * width + j].green = k;
					src_image[(i - 1) * width + j - 1].green = k;
					src_image[i * width + j - 1].green = k;

					src_image[(i + 1) * width + j].green = k;
					src_image[(i + 2) * width + j].green = k;
					src_image[(i + 1) * width + j - 1].green = k;
					src_image[(i + 2) * width + j - 1].green = k;
				}
			//cout << ftr((i - 1) * width + j);
			//src_image[i * width + j] = pixels[1];
			//break;
		}//break;
	}
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	int a = 0;
	//Путь к текущему изображению
	string path_to_image, temp, temp1, filter;

	while (1) {
		cout << "Lab 1\n" << "Lab 2\n" << "Lab 3\n";
		cin >> a;
		switch (a)
		{
		
		case 3: {
			ReadPath(path_to_image);
			OpenImage(path_to_image);
			ShowImage(path_to_image);
			lab3();
			ReadPath(temp);
			SaveImage(temp);
			ShowImage(temp);
			return 1;
			break; }
		default:
			return 0; break;

		}
	};
//Освободить память исходного изображения
	if (src_image != 0)
	{
		delete[] src_image;
	}
	//Освободить память результрующего изображения
	if (dst_image != 0)
	{
		delete[] dst_image;
	}

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
