#include <iostream>

#include "ZipFile.h"
#include "ZipArchive.h"
#include "ZipArchiveEntry.h"

int main() {
    static const char* zipFilePath = "C:/Users/prapo/Documents/MerdasUni/2023-2ndSemester/PESTI/pdfPulse/data/teste_1/word/document.xml";

    try {
        ZipArchive::Ptr zipArchive = ZipFile::Open(zipFilePath);
        
        if (zipArchive == nullptr) {
            std::cerr << "Failed to open the zip file." << std::endl;
            return 1;
        }

        std::cout << "Zip file opened successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
