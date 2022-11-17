// compileFormatter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <iostream>
#include <filesystem>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <cmath>
#include <fstream>
#include <windows.h>     

namespace fs = std::filesystem;
namespace po = boost::program_options;

int main(int argc, const char* const argv[])
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        std::cout << "Parameters example: compileFormatter.exe --directoryOfImages -nameOfProject --nameOfValidationProject --outputDirectory" << std::endl;
        std::cout << "Parameters example: compileFormatter.exe --pname --vpname --idirect --ext --outdir" << std::endl;
        std::cout << R"(--pname : Name for Model
--vpname : Name for Model Validation
--idirect : Image Directory Absolute Path
--ext : File Extension of Images (CASE SENSITIVE)
--outdir : Folder to Output (doesn't need specific directory))" << std::endl;
        return 0;
    }



    po::options_description desc("Parameters compileFormatter.exe -directoryOfImages \"dir\" -ext -nameOfProject \"nameOfProject\" -nameOfValidationProject \"nameOfValidation\" -outputDirectory \"dir\"");
    desc.add_options()
        ("nameOfProject,pname", po::value<std::string>())
        ("nameOfValidationProject,vpname", po::value<std::string>())
        ("directoryOfImages,idirect", po::value<std::string>())
        ("fileExtension,ext", po::value<std::string>())
        ("outputDirectory,outdir", po::value<std::string>());
        

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    std::cout << R"(

$$\      $$\ $$$$$$$\  $$\   $$\    $$\  $$$$$$\         $$$$$$\                                
$$$\    $$$ |$$  __$$\ $$ |  $$ |   $$ |$$  __$$\       $$  __$$\                               
$$$$\  $$$$ |$$ |  $$ |$$ |  $$ |   $$ |\__/  $$ |      $$ /  \__| $$$$$$\  $$$$$$$\ $$\    $$\ 
$$\$$\$$ $$ |$$$$$$$\ |$$ |  \$$\  $$  | $$$$$$  |      $$ |      $$  __$$\ $$  __$$\\$$\  $$  |
$$ \$$$  $$ |$$  __$$\ $$ |   \$$\$$  / $$  ____/       $$ |      $$ /  $$ |$$ |  $$ |\$$\$$  / 
$$ |\$  /$$ |$$ |  $$ |$$ |    \$$$  /  $$ |            $$ |  $$\ $$ |  $$ |$$ |  $$ | \$$$  /  
$$ | \_/ $$ |$$$$$$$  |$$$$$$$$\\$  /   $$$$$$$$\       \$$$$$$  |\$$$$$$  |$$ |  $$ |  \$  /   
\__|     \__|\_______/ \________|\_/    \________|       \______/  \______/ \__|  \__|   \_/    
                                                                                                
                                                                )" << std::endl;

     //START actual program (before was just command options..)

    std::string dirName = vm["directoryOfImages"].as<std::string>(); // where images are stored
    std::string projName = vm["nameOfProject"].as<std::string>(); // name of project
    std::string validName = vm["nameOfValidationProject"].as<std::string>(); //  test project name
    std::string outputDirectory = vm["outputDirectory"].as<std::string>();  // where to put the validationProject & regular project
    std::string ext = vm["fileExtension"].as<std::string>(); // ext = .jpg or .png, CASE SENSITIVE. Make sure all filetypes are the same!
    
    std::vector<fs::path> fileList, trainingList, validationList, testList, validationAndTrainingList;
    if (fs::exists(dirName) && fs::is_directory(dirName))
    {
        for (auto const& entry : fs::recursive_directory_iterator(dirName))
        {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext) {
                fileList.emplace_back(entry.path().filename());
            }
        }
    }

    fs::create_directories(outputDirectory); // CREATE OUTPUT directory (just in case does not exist)
    int size = fileList.size();
    // 70-20-10 split, change if 80-10-10
    int trainingSize = ceil(fileList.size() * 70 / 100);
    int validationSize = floor(fileList.size() * 20 / 100); // this will actually include training in the final file..
    int testSize = floor(fileList.size() * 10 / 100);

    std::cout << "[MBVL2] Total number of images found: " << size << std::endl;
    std::cout << "[MBVL2] For training: " << trainingSize << std::endl;
    std::cout << "[MBVL2] For validation: " << validationSize << std::endl;
    std::cout << "[MBVL2] For testing: " << testSize << std::endl;

    for (int i = 0; i < trainingSize; ++i) {
        trainingList.emplace_back(fileList.at(i));
    }
    for (int i = 0; i < validationSize; i++) {
        validationList.emplace_back(fileList.at(i));
    }
    for (int i = 0; i < validationSize + trainingSize;i++) {
        validationAndTrainingList.emplace_back(fileList.at(i));
    }
    int lastIndex = validationAndTrainingList.size();
    for (int i = lastIndex; i < size; i++) {
        testList.emplace_back(fileList.at(i));
    }


    std::cout << "[MBVL2] " << size - trainingSize - validationSize - testSize << " additional image(s) added to testing!" << std::endl;

    //fs::current_path(outputDirectory);

    std::vector<std::string> standardFormat = { "JPEGImages", "Annotations", "ImageSets" };

    //std::cout << projName << std::endl;
    //std::cout << outputDirectory << std::endl;
    //std::cout << validName<< std::endl;

    //std::cout << outputDirectory + "\\" + projName + "\\" + standardFormat[0] << std::endl;
    //std::cout << outputDirectory + "\\" + projName + "\\" + standardFormat[1] << std::endl;
    //std::cout << outputDirectory + "\\" + projName + "\\" + standardFormat[2] << std::endl;

    boost::filesystem::create_directories(outputDirectory + "\\" + projName);
    boost::filesystem::create_directories(outputDirectory + "\\" + validName);

    for (int i = 0; i < 3; i++) {
        boost::filesystem::create_directories(outputDirectory + "\\" + projName + "\\" + standardFormat[i]);
        boost::filesystem::create_directories(outputDirectory + "\\" + validName + "\\" + standardFormat[i]);
    }



    std::fstream file;
    //std::cout << outputDirectory + "\\" + projName + "\\" + standardFormat[2] + "\\train.txt" << std::endl;
    file.open(outputDirectory + "\\" + projName + "\\" + standardFormat[2] + "\\train.txt", std::ios_base::out);
    for (int i = 0;i < trainingList.size();i++)
    {
        file << trainingList[i].string() << std::endl;
    }
    file.close();
    file.open(outputDirectory + "\\" + projName + "\\" + standardFormat[2] + "\\trainval.txt", std::ios_base::out);
    for (int i = 0;i < validationAndTrainingList.size();i++)
    {
        file << validationAndTrainingList[i].string() << std::endl;
    }
    file.close();
    file.open(outputDirectory + "\\" + validName + "\\" + standardFormat[2] + "\\test.txt", std::ios_base::out);
    for (int i = 0;i < testList.size();i++)
    {
        file << testList[i].string() << std::endl;
    }
    file.close();
    std::cout << "[MBVL2] Successfully moved text files" << std::endl;



    //std::cout << dirName + "\\" + fileList.at(0).string() << std::endl;

    for (int i = 0; i < validationAndTrainingList.size(); i++) {
        boost::filesystem::rename(dirName + "\\" + fileList.at(i).string(), outputDirectory + "\\" + projName + "\\JPEGImages\\" + validationAndTrainingList.at(i).string());
    }
    for (int i = validationAndTrainingList.size(); i < size; i++) {
        boost::filesystem::rename(dirName + "\\" + fileList.at(i).string(), outputDirectory + "\\" + validName + "\\JPEGImages\\" + fileList.at(i).string());
    }

    std::cout << "[MBVL2] MOVE Labels.txt into both directories!!!! <<<< You as the user must do this!!" << std::endl;



    //std::cout << "There will be" << fileList.size() - training - validation - test << "images unused. Use for additional testing!";

}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
