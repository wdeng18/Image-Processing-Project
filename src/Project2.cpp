#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

class TGA {
	
public:

	struct Header
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;

		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;

		short xOrigin;
		short yOrigin;

		short width;
		short height;
		
		char bitsPerPixel;
		char imageDescriptor;

	};

	struct Pixel {

		Pixel() {
			R = 0;
			G = 0;
			B = 0;
		}

		unsigned char R;
		unsigned char B;
		unsigned char G;
	};

	Header thisHeader;
	vector<Pixel> pixels;
	
};

void ReadFromFile(string fileName, TGA &myTGA) {
	
	ifstream inputFile(fileName, ios_base::binary);

	inputFile.read((char*) &myTGA.thisHeader.idLength, sizeof(myTGA.thisHeader.idLength));
	inputFile.read((char*) &myTGA.thisHeader.colorMapType, sizeof(myTGA.thisHeader.colorMapType));
	inputFile.read((char*) &myTGA.thisHeader.dataTypeCode, sizeof(myTGA.thisHeader.dataTypeCode));
	
	inputFile.read((char*) &myTGA.thisHeader.colorMapOrigin, sizeof(myTGA.thisHeader.colorMapOrigin));
	inputFile.read((char*) &myTGA.thisHeader.colorMapLength, sizeof(myTGA.thisHeader.colorMapLength));
	inputFile.read((char*) &myTGA.thisHeader.colorMapDepth, sizeof(myTGA.thisHeader.colorMapDepth));
	
	inputFile.read((char*) &myTGA.thisHeader.xOrigin, sizeof(myTGA.thisHeader.xOrigin));
	inputFile.read((char*) &myTGA.thisHeader.yOrigin, sizeof(myTGA.thisHeader.yOrigin));

	inputFile.read((char*) &myTGA.thisHeader.width, sizeof(myTGA.thisHeader.width));
	inputFile.read((char*) &myTGA.thisHeader.height, sizeof(myTGA.thisHeader.height));

	inputFile.read((char*) &myTGA.thisHeader.bitsPerPixel, sizeof(myTGA.thisHeader.bitsPerPixel));
	inputFile.read((char*) &myTGA.thisHeader.imageDescriptor, sizeof(myTGA.thisHeader.imageDescriptor));

	int numPixels = myTGA.thisHeader.width * myTGA.thisHeader.height;

	for (int i = 0; i < numPixels; i++) {
		TGA::Pixel currentPixel;
		inputFile.read((char*) &currentPixel.B, sizeof(currentPixel.B));
		inputFile.read((char*) &currentPixel.G, sizeof(currentPixel.G));
		inputFile.read((char*) &currentPixel.R, sizeof(currentPixel.R));

		myTGA.pixels.push_back(currentPixel);
	}

	inputFile.close();

}

void WriteToFile(TGA myTGA, string fileName) {

	ofstream outputFile(fileName, ios_base::binary);

	outputFile.write((char*) &myTGA.thisHeader.idLength, sizeof(myTGA.thisHeader.idLength));
	outputFile.write((char*) &myTGA.thisHeader.colorMapType, sizeof(myTGA.thisHeader.colorMapType));
	outputFile.write((char*) &myTGA.thisHeader.dataTypeCode, sizeof(myTGA.thisHeader.dataTypeCode));

	outputFile.write((char*) &myTGA.thisHeader.colorMapOrigin, sizeof(myTGA.thisHeader.colorMapOrigin));
	outputFile.write((char*) &myTGA.thisHeader.colorMapLength, sizeof(myTGA.thisHeader.colorMapLength));
	outputFile.write((char*) &myTGA.thisHeader.colorMapDepth, sizeof(myTGA.thisHeader.colorMapDepth));

	outputFile.write((char*) &myTGA.thisHeader.xOrigin, sizeof(myTGA.thisHeader.xOrigin));
	outputFile.write((char*) &myTGA.thisHeader.yOrigin, sizeof(myTGA.thisHeader.yOrigin));

	outputFile.write((char*) &myTGA.thisHeader.width, sizeof(myTGA.thisHeader.width));
	outputFile.write((char*) &myTGA.thisHeader.height, sizeof(myTGA.thisHeader.height));

	outputFile.write((char*) &myTGA.thisHeader.bitsPerPixel, sizeof(myTGA.thisHeader.bitsPerPixel));
	outputFile.write((char*) &myTGA.thisHeader.imageDescriptor, sizeof(myTGA.thisHeader.imageDescriptor));

	for (int i = 0; i < myTGA.pixels.size(); i++) {
		TGA::Pixel tempPixel = myTGA.pixels[i];

		outputFile.write((char*) &tempPixel.B, sizeof(tempPixel.B));
		outputFile.write((char*) &tempPixel.G, sizeof(tempPixel.G));
		outputFile.write((char*) &tempPixel.R, sizeof(tempPixel.R));

	}

	outputFile.close();
}

//Tasks
//Task #1
void MultiplyBlend(TGA myTGA1, TGA myTGA2) {

	TGA tempTGA = myTGA2;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {
		tempTGA.pixels[i].B = ((float(tempTGA.pixels[i].B * myTGA1.pixels[i].B)/255) + 0.5f);
		tempTGA.pixels[i].G = ((float(tempTGA.pixels[i].G * myTGA1.pixels[i].G)/255) + 0.5f);
		tempTGA.pixels[i].R = ((float(tempTGA.pixels[i].R * myTGA1.pixels[i].R)/255) + 0.5f);
	}

	WriteToFile(tempTGA, "output\\part1.tga");
}

//Task #2
void SubtractBlend(TGA myTopTGA, TGA myBotTGA) {

	TGA tempTGA = myBotTGA;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {

		if (float(tempTGA.pixels[i].B - myTopTGA.pixels[i].B) < 0.0f) {
			tempTGA.pixels[i].B = (unsigned char) (0);
		}
		else {
			tempTGA.pixels[i].B = (unsigned char)((float)(tempTGA.pixels[i].B - myTopTGA.pixels[i].B));
		}
		

		if (float(tempTGA.pixels[i].G - myTopTGA.pixels[i].G) < 0.0f) {
			tempTGA.pixels[i].G = (unsigned char) (0);
		}
		else {
			tempTGA.pixels[i].G = (unsigned char)((float)(tempTGA.pixels[i].G - myTopTGA.pixels[i].G));
		}


		if (float(tempTGA.pixels[i].R - myTopTGA.pixels[i].R) < 0.0f) {
			tempTGA.pixels[i].R = (unsigned char) (0);
		}
		else {
			tempTGA.pixels[i].R = (unsigned char)((float)(tempTGA.pixels[i].R - myTopTGA.pixels[i].R));
		}
	}

	WriteToFile(tempTGA, "output\\part2.tga");
}

//Task #3
void MultiplyScreenBlend(TGA myTGA1, TGA myTGA2, TGA myTGA3) {

	TGA tempTGA = myTGA2;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {
		tempTGA.pixels[i].B = ((float(tempTGA.pixels[i].B * myTGA1.pixels[i].B) / 255) + 0.5f);
		tempTGA.pixels[i].G = ((float(tempTGA.pixels[i].G * myTGA1.pixels[i].G) / 255) + 0.5f);
		tempTGA.pixels[i].R = ((float(tempTGA.pixels[i].R * myTGA1.pixels[i].R) / 255) + 0.5f);
	}

	//Blend

	for (int i = 0; i < tempTGA.pixels.size(); i++) {

		//1-(1-A)*(1-B)
		float bluePixel = ((1.0f - ((1.0f - (float(tempTGA.pixels[i].B) / 255)) * (1.0f - (float(myTGA3.pixels[i].B) / 255)))) * 255.0);
		tempTGA.pixels[i].B = (int)(bluePixel + 0.5f);

		float greenPixel = ((1.0f - ((1.0f - (float(tempTGA.pixels[i].G) / 255)) * (1.0f - (float(myTGA3.pixels[i].G) / 255)))) * 255.0);
		tempTGA.pixels[i].G = (int)(greenPixel + 0.5f);
		
		float redPixel = ((1.0f - ((1.0f - (float(tempTGA.pixels[i].R) / 255)) * (1.0f - (float(myTGA3.pixels[i].R) / 255)))) * 255.0);
		tempTGA.pixels[i].R = (int)(redPixel + 0.5f);
	}

	WriteToFile(tempTGA, "output\\part3.tga");
}

//Task #4
void MultiplySubtractBlend(TGA myTGA1, TGA myTGA2, TGA myTopTGA) {
	
	TGA tempTGA = myTGA2;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {
		tempTGA.pixels[i].B = ((float(tempTGA.pixels[i].B * myTGA1.pixels[i].B) / 255) + 0.5f);
		tempTGA.pixels[i].G = ((float(tempTGA.pixels[i].G * myTGA1.pixels[i].G) / 255) + 0.5f);
		tempTGA.pixels[i].R = ((float(tempTGA.pixels[i].R * myTGA1.pixels[i].R) / 255) + 0.5f);
	}

	for (int i = 0; i < tempTGA.pixels.size(); i++) {

		if (float(tempTGA.pixels[i].B - myTopTGA.pixels[i].B) < 0.0f) {
			tempTGA.pixels[i].B = (unsigned char)(0);
		}
		else {
			tempTGA.pixels[i].B = (unsigned char)((float)(tempTGA.pixels[i].B - myTopTGA.pixels[i].B));
		}


		if (float(tempTGA.pixels[i].G - myTopTGA.pixels[i].G) < 0.0f) {
			tempTGA.pixels[i].G = (unsigned char)(0);
		}
		else {
			tempTGA.pixels[i].G = (unsigned char)((float)(tempTGA.pixels[i].G - myTopTGA.pixels[i].G));
		}


		if (float(tempTGA.pixels[i].R - myTopTGA.pixels[i].R) < 0.0f) {
			tempTGA.pixels[i].R = (unsigned char)(0);
		}
		else {
			tempTGA.pixels[i].R = (unsigned char)((float)(tempTGA.pixels[i].R - myTopTGA.pixels[i].R));
		}
	}

	WriteToFile(tempTGA, "output\\part4.tga");
}

//Task #5
void OverlayBlend(TGA myTopTGA, TGA myBotTGA) {

	TGA tempTGA = myBotTGA;

	int gray = 127;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {

		if (tempTGA.pixels[i].B <= gray && tempTGA.pixels[i].G <= gray && tempTGA.pixels[i].R <= gray) {

			tempTGA.pixels[i].B = ((float(tempTGA.pixels[i].B * myTopTGA.pixels[i].B * 2) / 255.0f) + 0.5f);
			tempTGA.pixels[i].G = ((float(tempTGA.pixels[i].G * myTopTGA.pixels[i].G * 2) / 255.0f) + 0.5f);
			tempTGA.pixels[i].R = ((float(tempTGA.pixels[i].R * myTopTGA.pixels[i].R * 2) / 255.0f) + 0.5f);

		}
		else {

			//(1 - (2 * (1 - A) * (1 - B)))
			float bluePixel = ((1.0f - ((1.0f - (float(tempTGA.pixels[i].B) / 255)) * (2.0f) * (1.0f - (float(myTopTGA.pixels[i].B) / 255)))) * 255.0);
			tempTGA.pixels[i].B = (int)(bluePixel + 0.5f);

			float greenPixel = ((1.0f - ((1.0f - (float(tempTGA.pixels[i].G) / 255)) * (2.0f) * (1.0f - (float(myTopTGA.pixels[i].G) / 255)))) * 255.0);
			tempTGA.pixels[i].G = (int)(greenPixel + 0.5f);

			float redPixel = ((1.0f - ((1.0f - (float(tempTGA.pixels[i].R) / 255)) * (2.0f) * (1.0f - (float(myTopTGA.pixels[i].R) / 255)))) * 255.0);
			tempTGA.pixels[i].R = (int)(redPixel + 0.5f);
		}
	}

	WriteToFile(tempTGA, "output\\part5.tga");

}

//Task #6
void AddGreen200(TGA myTGA1) {

	TGA tempTGA = myTGA1;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {

		if ((tempTGA.pixels[i].G + 200) > 255) {
			tempTGA.pixels[i].G = 255;
		}
		else {
			tempTGA.pixels[i].G = (float(tempTGA.pixels[i].G + 200.0f) + 0.5f);
		}
	
	}

	WriteToFile(tempTGA, "output\\part6.tga");
}

//Task #7
void MultiplyRedBlue(TGA myTGA1) {

	TGA tempTGA = myTGA1;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {

		tempTGA.pixels[i].B = (float(tempTGA.pixels[i].B * 0));

		if (((float)(tempTGA.pixels[i].R * 4) + 0.5f) > 255) {
			tempTGA.pixels[i].R = 255;
		}
		else {
			tempTGA.pixels[i].R = ((float)(tempTGA.pixels[i].R * 4) + 0.5f);
		}
	}
	WriteToFile(tempTGA, "output\\part7.tga");
}

//Task #8
void WriteSeperateFiles(TGA myTGA) {

	TGA tempRedTGA = myTGA;
	TGA tempGreenTGA = myTGA;
	TGA tempBlueTGA = myTGA;

	for (int i = 0; i < tempRedTGA.pixels.size(); i++) {
		tempRedTGA.pixels[i].G = tempRedTGA.pixels[i].R;
		tempRedTGA.pixels[i].B = tempRedTGA.pixels[i].R;
	}

	for (int i = 0; i < tempGreenTGA.pixels.size(); i++) {
		tempGreenTGA.pixels[i].R = tempGreenTGA.pixels[i].G;
		tempGreenTGA.pixels[i].B = tempGreenTGA.pixels[i].G;
	}

	for (int i = 0; i < tempBlueTGA.pixels.size(); i++) {
		tempBlueTGA.pixels[i].R = tempBlueTGA.pixels[i].B;
		tempBlueTGA.pixels[i].G = tempBlueTGA.pixels[i].B;
	}

	WriteToFile(tempRedTGA, "output\\part8_r.tga");
	WriteToFile(tempGreenTGA, "output\\part8_g.tga");
	WriteToFile(tempBlueTGA, "output\\part8_b.tga");
}

//Task #9
void CombineSeperateFiles(TGA myTGA1, TGA myTGA2, TGA myTGA3) {

	TGA tempTGA = myTGA1;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {
		tempTGA.pixels[i].R = myTGA1.pixels[i].R;
		tempTGA.pixels[i].G = myTGA2.pixels[i].G;
		tempTGA.pixels[i].B = myTGA3.pixels[i].B;
	}

	WriteToFile(tempTGA, "output\\part9.tga");

}

//Task #10
void RotateImage180(TGA myTGA1) {

	TGA tempTGA = myTGA1;

	int j = tempTGA.pixels.size() - 1;

	for (int i = 0; i < tempTGA.pixels.size(); i++) {

		tempTGA.pixels[i].R = myTGA1.pixels[j].R;
		tempTGA.pixels[i].G = myTGA1.pixels[j].G;
		tempTGA.pixels[i].B = myTGA1.pixels[j].B;

		j--;
	}

	WriteToFile(tempTGA, "output\\part10.tga");
}

//Testing Tasks
//Task #1, 2, 3, 4, 5, 6, 7, 8, 9, 10
bool TestPixelColors(TGA myOutput, TGA myExample, string testNumber, int &passCount) {

	cout << "Test #" << testNumber << ": ........";

	for (int i = 0; i < myOutput.pixels.size(); i++) {
		//PixelChecker
		if (myOutput.pixels[i].R != myExample.pixels[i].R) {
			cout << " Failed!" << endl;
			cout << "Red has a wrong pixel on this index: " << i << endl;
			cout << "My output is: " << (int)myOutput.pixels[i].R << endl << "Expected out is: " << (int)myExample.pixels[i].R << endl << endl;
			return false;
		}
		if (myOutput.pixels[i].G != myExample.pixels[i].G) {
			cout << " Failed!" << endl;
			cout << "Green has a wrong pixel on this index: " << i << endl;
			cout << "My output is: " << (int)myOutput.pixels[i].G << endl << "Expected out is: " << (int)myExample.pixels[i].G << endl << endl;
			return false;
		}
		if (myOutput.pixels[i].B != myExample.pixels[i].B) {
			cout << " Failed!" << endl;
			cout << "Blue has a wrong pixel on this index: " << i << endl;
			cout << "My output is: " << (int)myOutput.pixels[i].B << endl << "Expected out is: " << (int)myExample.pixels[i].B << endl << endl;
			return false;
		}

		//Header Checker
		if (myOutput.thisHeader.idLength != myExample.thisHeader.idLength) {
			cout << " Failed!" << endl;
			cout << "idLength is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.colorMapType != myExample.thisHeader.colorMapType) {
			cout << " Failed!" << endl;
			cout << "colorMapType is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.dataTypeCode != myExample.thisHeader.dataTypeCode) {
			cout << " Failed!" << endl;
			cout << "dataTypeCode is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.colorMapOrigin != myExample.thisHeader.colorMapOrigin) {
			cout << " Failed!" << endl;
			cout << "colorMapOrigin is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.colorMapLength != myExample.thisHeader.colorMapLength) {
			cout << " Failed!" << endl;
			cout << "colorMapLength is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.colorMapDepth != myExample.thisHeader.colorMapDepth) {
			cout << " Failed!" << endl;
			cout << "colorMapDepth is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.xOrigin != myExample.thisHeader.xOrigin) {
			cout << " Failed!" << endl;
			cout << "xOrigin is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.yOrigin != myExample.thisHeader.yOrigin) {
			cout << " Failed!" << endl;
			cout << "yOrigin is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.width != myExample.thisHeader.width) {
			cout << " Failed!" << endl;
			cout << "width is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.height != myExample.thisHeader.height) {
			cout << " Failed!" << endl;
			cout << "height is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.bitsPerPixel != myExample.thisHeader.bitsPerPixel) {
			cout << " Failed!" << endl;
			cout << "bitsPerPixel is incorrect" << endl << endl;
			return false;
		}
		if (myOutput.thisHeader.imageDescriptor != myExample.thisHeader.imageDescriptor) {
			cout << " Failed!" << endl;
			cout << "imageDescriptor is incorrect" << endl << endl;
			return false;
		}
	}

	cout << " Passed!" << endl;
	passCount++;
	return true;
}

int main() {

	int count = 0;

	//Read in all the input TGA files
	TGA car;
	ReadFromFile("input\\car.tga", car);

	TGA circles;
	ReadFromFile("input\\circles.tga", circles);

	TGA blueLayer;
	ReadFromFile("input\\layer_blue.tga", blueLayer);

	TGA greenLayer;
	ReadFromFile("input\\layer_green.tga", greenLayer);

	TGA redLayer;
	ReadFromFile("input\\layer_red.tga", redLayer);

	TGA layer1;
	ReadFromFile("input\\layer1.tga", layer1);

	TGA layer2;
	ReadFromFile("input\\layer2.tga", layer2);

	TGA pattern1;
	ReadFromFile("input\\pattern1.tga", pattern1);

	TGA pattern2;
	ReadFromFile("input\\pattern2.tga", pattern2);

	TGA text;
	ReadFromFile("input\\text.tga", text);

	TGA text2;
	ReadFromFile("input\\text2.tga", text2);

	//Read in example TGA files
	TGA example1;
	ReadFromFile("examples\\EXAMPLE_part1.tga", example1);

	TGA example2;
	ReadFromFile("examples\\EXAMPLE_part2.tga", example2);

	TGA example3;
	ReadFromFile("examples\\EXAMPLE_part3.tga", example3);
	
	TGA example4;
	ReadFromFile("examples\\EXAMPLE_part4.tga", example4);
	
	TGA example5;
	ReadFromFile("examples\\EXAMPLE_part5.tga", example5);
	
	TGA example6;
	ReadFromFile("examples\\EXAMPLE_part6.tga", example6);
	
	TGA example7;
	ReadFromFile("examples\\EXAMPLE_part7.tga", example7);

	TGA example8R;
	ReadFromFile("examples\\EXAMPLE_part8_r.tga", example8R);

	TGA example8G;
	ReadFromFile("examples\\EXAMPLE_part8_g.tga", example8G);

	TGA example8B;
	ReadFromFile("examples\\EXAMPLE_part8_b.tga", example8B);
	
	TGA example9;
	ReadFromFile("examples\\EXAMPLE_part9.tga", example9);
	
	TGA example10;
	ReadFromFile("examples\\EXAMPLE_part10.tga", example10);

	//Task #1
	MultiplyBlend(layer1, pattern1);
	TGA part1;
	ReadFromFile("output\\part1.tga", part1);
	TestPixelColors(part1, example1, "1", count);

	//Task #2
	SubtractBlend(layer2, car);
	TGA part2;
	ReadFromFile("output\\part2.tga", part2);
	TestPixelColors(part2, example2, "2", count);

	//Task #3
	MultiplyScreenBlend(layer1, pattern2, text);
	TGA part3;
	ReadFromFile("output\\part3.tga", part3);
	TestPixelColors(part3, example3, "3", count);

	//Task #4
	MultiplySubtractBlend(layer2, circles, pattern2);
	TGA part4;
	ReadFromFile("output\\part4.tga", part4);
	TestPixelColors(part4, example4, "4", count);

	//Task #5
	OverlayBlend(layer1, pattern1);
	TGA part5;
	ReadFromFile("output\\part5.tga", part5);
	TestPixelColors(part5, example5, "5", count);

	//Task #6
	AddGreen200(car);
	TGA part6;
	ReadFromFile("output\\part6.tga", part6);
	TestPixelColors(part6, example6, "6", count);

	//Task #7
	MultiplyRedBlue(car);
	TGA part7;
	ReadFromFile("output\\part7.tga", part7);
	TestPixelColors(part7, example7, "7", count);

	//Task #8
	WriteSeperateFiles(car);
	TGA part8R;
	ReadFromFile("output\\part8_r.tga", part8R);
	TestPixelColors(part8R, example8R, "8R", count);
	TGA part8G;
	ReadFromFile("output\\part8_g.tga", part8G);
	TestPixelColors(part8G, example8G, "8G", count);
	TGA part8B;
	ReadFromFile("output\\part8_b.tga", part8B);
	TestPixelColors(part8B, example8B, "8B", count);

	//Task #9
	CombineSeperateFiles(redLayer, greenLayer, blueLayer);
	TGA part9;
	ReadFromFile("output\\part9.tga", part9);
	TestPixelColors(part9, example9, "9", count);
	
	//Task #10
	RotateImage180(text2);
	TGA part10;
	ReadFromFile("output\\part10.tga", part10);
	TestPixelColors(part10, example10, "10", count);

	cout << endl << "Test Results: " << count << " / " << "12";
}