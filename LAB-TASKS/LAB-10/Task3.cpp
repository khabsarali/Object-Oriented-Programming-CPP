#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    const string srcFilename = "source.txt";
    const string destFilename = "destination.txt";

    // Step 1: Create and populate the source document
    ofstream srcWriter(srcFilename);
    if (!srcWriter.is_open()) {
        cerr << "Error: Failed to create " << srcFilename << endl;
        return 1;
    }
    srcWriter << "Hello World\n";
    srcWriter << "This is the source file\n";
    srcWriter << "We are copying this content\n";
    srcWriter.close();

    // Step 2: Open source file for reading
    ifstream srcReader(srcFilename);
    if (!srcReader.is_open()) {
        cerr << "Error: Could not open source file for reading." << endl;
        return 1;
    }

    // Step 3: Open destination file for writing
    ofstream destWriter(destFilename);
    if (!destWriter.is_open()) {
        cerr << "Error: Could not open destination file for writing." << endl;
        srcReader.close();
        return 1;
    }

    // Step 4: Transfer content stream line by line
    string bufferLine;
    int copiedLines = 0;
    while (getline(srcReader, bufferLine)) {
        destWriter << bufferLine << "\n";
        copiedLines++;
    }

    srcReader.close();
    destWriter.close();

    cout << "Success: " << copiedLines << " lines copied from '" 
         << srcFilename << "' to '" << destFilename << "'." << endl;

    return 0;
}
