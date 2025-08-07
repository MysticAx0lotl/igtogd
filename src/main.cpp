#include <iostream>
#include <cmath>
#include <boost/iostreams/filter/gzip.hpp>
#include "gdstructs.hpp"
#include "compat_defs.hpp"
#include "libImpossibleLevel.hpp"

std::string buildObjectString(Level inLevel)
{
    gdObj tempGD;
    BlockObject* tempIG = new BlockObject;
    bool isPit = false;
    std::string result = level_string_base;

    for(int i = 0; i < inLevel.getBlockCount(); i++)
    {
        tempIG = inLevel.getBlockAtIndex(i);
        
        switch(tempIG->objType)
        {
            case 0:
                tempGD.p1_id = "1";
                break;
            case 1:
                tempGD.p1_id = "8";
                break;
            case 2:
                tempGD.p1_id = "9";
                isPit = true;
                break;
        }

        if(!isPit)
        {
            tempGD.p2_x = std::to_string(tempIG->xPos - 135);
            tempGD.p3_y = std::to_string(tempIG->yPos + 15);
            tempGD.p21_colorID = "0";
            tempGD.p24_zLayer = "0";
            result += "1,";
            result += tempGD.p1_id;
            result += ",2,";
            result += tempGD.p2_x;
            result += ",3,";
            result += tempGD.p3_y;
            result += ",21,";
            result += tempGD.p21_colorID;
            result += ",24,";
            result += tempGD.p24_zLayer;
            result += ";";
        }
        else
        {
            int iterations = round((tempIG->yPos - tempIG->xPos)/30) + 1;
            int currentX = (tempIG->xPos - 135);
            for(int j = 0; j < iterations; j++)
            {
                result += "1,";
                result += "9";
                result += ",2,";
                result += std::to_string(currentX);
                result += ",3,";
                result += "0";
                result += ",21,";
                result += tempGD.p21_colorID;
                result += ",24,";
                result += tempGD.p24_zLayer;
                result += ";";

                currentX += 30;
            }
        }
        isPit = false;
    }

    //delete tempIG;

    BackgroundChange* tempBC = new BackgroundChange;
    gdColorTrigger tempCT;

    for(int i = 0; i < inLevel.getBackgroundCount(); i++)
    {
        tempBC = inLevel.getBackgroundAtIndex(i);

        switch(tempBC->colorID)
        {
            case 0:
                //blue
                tempCT.p7_red = "63";
                tempCT.p8_green = "184";
                tempCT.p9_blue = "199";
                break;
            case 1:
                //yellow
                tempCT.p7_red = "236";
                tempCT.p8_green = "216";
                tempCT.p9_blue = "50";
                break;
            case 3:
                //violet
                tempCT.p7_red = "178";
                tempCT.p8_green = "38";
                tempCT.p9_blue = "227";
                break;
            case 4:
                //pink
                tempCT.p7_red = "241";
                tempCT.p8_green = "19";
                tempCT.p9_blue = "242";
                break;
            case 2:
                //green
                tempCT.p7_red = "83";
                tempCT.p8_green = "255";
                tempCT.p9_blue = "83";
                break;
            case 5:
                //black
                tempCT.p7_red = "0";
                tempCT.p8_green = "0";
                tempCT.p9_blue = "0";
                break;
        }
        //this is a fucking awful way to do it but the weirdness of GD has forced my hand
        tempCT.p2_x = std::to_string(tempBC->xPos - 135);
        tempCT.p3_y = std::to_string(3000);
        tempCT.p23_channel = std::to_string(1000);
        result += "1,";
        result += tempCT.p1_id;
        result += ",2,";
        result += tempCT.p2_x;
        result += ",3,";
        result += tempCT.p3_y;
        result += ",7,";
        result += tempCT.p7_red;
        result += ",8,";
        result += tempCT.p8_green;
        result += ",9,";
        result += tempCT.p9_blue;
        result += ",10,";
        result += tempCT.p10_duration;  
        result += ",23,";
        result += tempCT.p23_channel;
        result += tempCT.remainder;
        result += ";";

        tempCT.p2_x = std::to_string(tempBC->xPos - 135);
        tempCT.p3_y = std::to_string(3030);
        tempCT.p23_channel = std::to_string(1001);
        result += "1,";
        result += tempCT.p1_id;
        result += ",2,";
        result += tempCT.p2_x;
        result += ",3,";
        result += tempCT.p3_y;
        result += ",7,";
        result += tempCT.p7_red;
        result += ",8,";
        result += tempCT.p8_green;
        result += ",9,";
        result += tempCT.p9_blue;
        result += ",10,";
        result += tempCT.p10_duration;  
        result += ",23,";
        result += tempCT.p23_channel;
        result += tempCT.remainder;
        result += ";";

        tempCT.p2_x = std::to_string(tempBC->xPos - 135);
        tempCT.p3_y = std::to_string(3060);
        tempCT.p23_channel = std::to_string(1009); //wtf
        result += "1,";
        result += tempCT.p1_id;
        result += ",2,";
        result += tempCT.p2_x;
        result += ",3,";
        result += tempCT.p3_y;
        result += ",7,";
        result += tempCT.p7_red;
        result += ",8,";
        result += tempCT.p8_green;
        result += ",9,";
        result += tempCT.p9_blue;
        result += ",10,";
        result += tempCT.p10_duration;  
        result += ",23,";
        result += tempCT.p23_channel;
        result += tempCT.remainder;
        result += ";";
    }

    return result;
}

//Adapted from https://wyliemaster.github.io/gddocs/#/topics/levelstring_encoding_decoding
/*
std::string packInnerLevelString(std::string raw_string, bool mainLevel)
{
    const char* pointer = raw_string.data();
    std::string gzipped = gzip::compress(pointer, raw_string.size());
    std::string base64_encoded = base64::to_base64(gzipped);
    if(mainLevel)
    {
        base64_encoded.erase(base64_encoded.begin(), base64_encoded.begin() + 13);
    }
    return base64_encoded;
}
*/

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::cout << argv[0] << ": missing file operand" << std::endl;
        return -1;
    }
    /*
    else
    {
        //attempt to read GD level string and find level data index
        std::string levelFile = readFile(argv[1]);
        if(levelFile.empty())
        {
            std::cout << "ERROR: Failed to open file (empty or does not exist)" << std::endl;
            return -1;
        }
    }
    */

    Level igLevel(argv[1], false);
    std::cout << buildObjectString(igLevel);
    return 1;
}